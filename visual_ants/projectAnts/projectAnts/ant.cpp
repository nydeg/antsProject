#include "ant.h"

#include <cmath>
#include <queue>
#define SIZE_OF_TILE 40.f
#include "baby.h"
#include "food.h"
#include "storage.h"

struct Node {
	int x, y;
	float f, g, h;
	Node* parent;

	Node(int x, int y): x(x), y(y), f(0), g(0), h(0), parent(nullptr) {}

	bool operator==(const Node& other) const {
		return x == other.x && y == other.y;
	}
};

namespace std {
	template<>
	struct hash<Node> {
		size_t operator()(const Node& node) const {
			return hash<int>()(node.x) ^ hash<int>()(node.y);
		}
	};
}

Vector2i worldToGrid(const Vector2f& worldPosition) {
	int gridX = static_cast<int>((worldPosition.x + 30) / SIZE_OF_TILE);
	int gridY = static_cast<int>((worldPosition.y + 15) / SIZE_OF_TILE);
	return {gridX, gridY};
}

Vector2f gridToWorld(int gridX, int gridY) {
	float worldX = gridX * SIZE_OF_TILE - 30 + SIZE_OF_TILE / 2;
	float worldY = gridY * SIZE_OF_TILE - 15 + SIZE_OF_TILE / 2;
	return {worldX, worldY};
}


bool Ant::isWalkable(int gridX, int gridY) const {
	return (gridX >= 0 && gridX < MAIN_FIELD &&
			gridY >= 0 && gridY < MAIN_FIELD &&
			maze[gridY][gridX] == 0);
}

bool Ant::checkAntCollision(const Vector2f &pos) const {
	int gridX = static_cast<int>((pos.x + 30) / SIZE_OF_TILE);
	int gridY = static_cast<int>((pos.y + 15) / SIZE_OF_TILE);

	return !isWalkable(gridX, gridY);
}

vector<Vector2f> Ant::findPathAStar(const Vector2i& start, const Vector2i& end) {
    vector<Vector2f> result;

    if (!isWalkable(start.x, start.y) || !isWalkable(end.x, end.y)) {
        cerr << "Start or end position is not walkable.\n";
        return result;
    }

    auto cmp = [](Node* left, Node* right) { return left->f > right->f; };
    priority_queue<Node*, vector<Node*>, decltype(cmp)> openList(cmp);
    unordered_map<int, Node*> allNodes;

    auto key = [](int x, int y) { return y * MAIN_FIELD + x; };

    Node* startNode = new Node(start.x, start.y);
    startNode->g = 0;
    startNode->h = abs(end.x - start.x) + abs(end.y - start.y);
    startNode->f = startNode->g + startNode->h;
    openList.push(startNode);
    allNodes[key(start.x, start.y)] = startNode;

    while (!openList.empty()) {
        Node* current = openList.top();
        openList.pop();

        if (current->x == end.x && current->y == end.y) {
            while (current != nullptr) {
                result.push_back(gridToWorld(current->x, current->y));
                current = current->parent;
            }
            reverse(result.begin(), result.end());
            break;
        }

        const int dx[] = {-1, 1, 0, 0};
        const int dy[] = {0, 0, -1, 1};

        for (int i = 0; i < 4; ++i) {
            int nx = current->x + dx[i];
            int ny = current->y + dy[i];

            if (!isWalkable(nx, ny)) continue;

            int neighborKey = key(nx, ny);
            float newG = current->g + 1;

            if (allNodes.find(neighborKey) == allNodes.end() || newG < allNodes[neighborKey]->g) {
                Node* neighborNode = new Node(nx, ny);
                neighborNode->g = newG;
                neighborNode->h = abs(nx - end.x) + abs(ny - end.y);
                neighborNode->f = neighborNode->g + neighborNode->h;
                neighborNode->parent = current;

                openList.push(neighborNode);
                allNodes[neighborKey] = neighborNode;
            }
        }
    }

    for (auto& pair : allNodes) {
        delete pair.second;
    }

    return result;
}

void Ant::tryFindAlternativePath(const Vector2f &target) {
	// Если муравей застрял, ищем обходной путь
	Vector2i currentGrid(
		static_cast<int>((position.x + 30 - SIZE_OF_TILE/2) / SIZE_OF_TILE),
		static_cast<int>((position.y + 15 - SIZE_OF_TILE/2) / SIZE_OF_TILE)
	);

	Vector2i targetGrid(
		static_cast<int>((target.x + 30 - SIZE_OF_TILE/2) / SIZE_OF_TILE),
		static_cast<int>((target.y + 15 - SIZE_OF_TILE/2) / SIZE_OF_TILE)
	);

	path = findPathAStar(currentGrid, targetGrid);
}

float Ant::distance(const Vector2f &a, const Vector2f &b) const {
	return sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2));
}


void Ant::UpdateRole()
{
	if (age > 0) {
		if (0 < age < 2) {
			setRole(std::make_unique<Baby>());
		}
		else if (2 < age < 5) {
			setRole(std::make_unique<Babysitter>());
		}
		else if (age >= 5 && age < 10 && health > UNHEALTHY_ANT) {
			setRole(std::make_unique<Soldier>());
		}
		else if (age >= 5 && age < 10 && health <= UNHEALTHY_ANT) {
			setRole(std::make_unique<Stepherd>());
		}
		else if (age >= 10 && age < 15 && health > UNHEALTHY_ANT) {
			setRole(std::make_unique<Builder>());
		}
		else if (age >= 10 && age < 15 && health <= UNHEALTHY_ANT) {
			setRole(std::make_unique<Collector>());
		}
		else if (age >= 15 && age < DEATH_AGE) {
			setRole(std::make_unique<Cleaner>());
		} 
		else {
			setRole(std::make_unique<Dead>());
			health = 0;
		}
	}
}

void Ant::setTarget(const Vector2f &target) {
	Vector2i startGrid = worldToGrid(position);
	Vector2i endGrid = worldToGrid(target);

	// Генерация пути с использованием A*
	path = findPathAStar(startGrid, endGrid);

	if (path.empty()) {
		std::cerr << "Unable to find a path to the target.\n";
	}
}

Vector2f storagePosition = {60.f, 60.f};

void Ant::update(float deltaTime, Food& food) {
    // Если путь пуст, необходимо задать новую цель
    if (path.empty()) {
        if (carryingFood) {
            // Если муравей несет еду, цель — склад
            setTarget(storagePosition);
        } else if (food.isExists()) {
            // Если еда существует и муравей не несет еду, цель — еда
            setTarget(food.getPosition());
        }
        return; // Прерываем выполнение, так как путь будет сгенерирован
    }

    // Целевая точка пути
    sf::Vector2f targetWorld = path.front();
    float distanceToTarget = distance(position, targetWorld);

    if (distanceToTarget < speed * deltaTime) {
        // Достигли текущей точки пути
        position = targetWorld;
        path.erase(path.begin());

        if (carryingFood) {
            // Проверяем, достиг ли склада
            if (distance(position, storagePosition) < SIZE_OF_TILE / 2) {
                std::cout << "Food delivered to storage!" << std::endl;

                // После доставки еды ищем новую цель — еду
                if (food.isExists()) {
                    setTarget(food.getPosition());
                }
            }
        } else {
            // Если не несет еду и достиг еды
            if (food.isExists() && distance(position, food.getPosition()) < SIZE_OF_TILE / 2) {
                if (food.getWeight() <= carryingCapacity) {
                	collectFood(food);
                    std::cout << "Food collected!" << std::endl;

                    // Устанавливаем цель доставки еды к складу
                    setTarget(storagePosition);
                } else {
                    std::cout << "The food is too heavy!" << std::endl;
                }
            }
        }
    } else {
        // Двигаемся к следующей точке пути
        sf::Vector2f direction = (targetWorld - position) / distanceToTarget;
        position += direction * speed * deltaTime;
    }

    // Обновляем положение муравья
    antShape.setPosition(position);
}

// Геттер для координаты X
float Ant::getPositionX() const {
	return position.x;
}

// Геттер для координаты Y
float Ant::getPositionY() const {
	return position.y;
}

// Метод для получения полной позиции (вектор)
sf::Vector2f Ant::getPosition() const {
	return position;
}



void Ant::draw(RenderWindow &window) {
	window.draw(antShape);
}

void Ant::deliverToStorage(Storage &storage, Food &food) {
		// Если муравей несет еду и он рядом со складом
	storage.addFood(food, carriedFoodWeight);
	carryingFood = false;
		carriedFoodWeight = 0;
		std::cout << "Food delivered! Current storage: "
				<< storage.getCurrentCapacity() << "/"
				<< storage.getMaxCapacity() << std::endl;
		storage.updateAppearance("food");
	}

void Ant::doTask(const sf::FloatRect& bounds = sf::FloatRect({-FLT_MAX, -FLT_MAX}, {FLT_MAX * 2, FLT_MAX * 2})) {
	if (role) {
		role->work(*this, bounds);
	}
	antShape.setPosition(position);
}


void Ant::doTask()
{
	if (role) {
		role->work(*this);
	}
}


std::ostream& operator<<(std::ostream& out, Ant& ant)
{
	out << "Role: " << ant.getRole();
	return out;
}

std::ostream& operator<<(std::ostream& out, const Ant& ant) {
	out << "Role: " << ant.getRole();
	return out;
}
