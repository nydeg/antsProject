#include "ant.h"

#include <cmath>
#include <queue>
#define SIZE_OF_TILE 40.f

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


bool Ant::isWalkable(int gridX, int gridY) const {
	return (gridX >= 0 && gridX < MAIN_FIELD &&
				gridY >= 0 && gridY < MAIN_FIELD &&
				maze[gridY][gridX] == 0);
}

bool Ant::checkAntCollision(const Vector2f &pos) const {
	const float halfWidth = antShape.getSize().x / 2;
	const float halfHeight = antShape.getSize().y / 2;

	Vector2f points[5] = {
		{pos.x - halfWidth, pos.y - halfHeight},
		{pos.x + halfWidth, pos.y - halfHeight},
		{pos.x + halfWidth, pos.y + halfHeight},
		{pos.x - halfWidth, pos.y + halfHeight},
		{pos.x, pos.y}
	};

	for (const auto& point : points) {
		int gridX = static_cast<int>((point.x + 30) / SIZE_OF_TILE);
		int gridY = static_cast<int>((point.y + 15) / SIZE_OF_TILE);

		if (!isWalkable(gridX, gridY)) {
			return true;
		}
	}
	return false;
}

vector<Vector2f> Ant::findPathAStar(const Vector2i &start, const Vector2i &end) {
	vector<Vector2f> result;
        if (!isWalkable(start.x, start.y) || !isWalkable(end.x, end.y)) {
            return result;
        }

        auto cmp = [](Node* left, Node* right) { return left->f > right->f; };
        priority_queue<Node*, vector<Node*>, decltype(cmp)> openList(cmp);
        unordered_map<Node, Node*> allNodes;

        Node* startNode = new Node(start.x, start.y);
        openList.push(startNode);
        allNodes[*startNode] = startNode;

        while (!openList.empty()) {
            Node* current = openList.top();
            openList.pop();

            if (current->x == end.x && current->y == end.y) {
                while (current != nullptr) {
                    result.push_back(Vector2f(
                        current->x * SIZE_OF_TILE - 30 + SIZE_OF_TILE/2,
                        current->y * SIZE_OF_TILE - 15 + SIZE_OF_TILE/2
                    ));
                    current = current->parent;
                }
                reverse(result.begin(), result.end());
                break;
            }

            // Проверяем 8 направлений (для диагонального движения)
            const int dx[] = {-1, 1, 0, 0, -1, -1, 1, 1};
            const int dy[] = {0, 0, -1, 1, -1, 1, -1, 1};

            for (int i = 0; i < 8; ++i) {
                int nx = current->x + dx[i];
                int ny = current->y + dy[i];

                if (!isWalkable(nx, ny)) continue;

                // Для диагоналей проверяем, чтобы соседние клетки тоже были проходимы
                if (i >= 4) { // диагональные направления
                    if (!isWalkable(current->x + dx[i], current->y) ||
                        !isWalkable(current->x, current->y + dy[i])) {
                        continue;
                    }
                }

                Node neighbor(nx, ny);
                float newG = current->g + (i < 4 ? 1.0f : 1.414f); // Стоимость диагонали больше

                if (allNodes.find(neighbor) == allNodes.end() || newG < allNodes[neighbor]->g) {
                    Node* newNode = new Node(nx, ny);
                    newNode->g = newG;
                    newNode->h = sqrt(pow(nx - end.x, 2) + pow(ny - end.y, 2)); // Евклидово расстояние
                    newNode->f = newNode->g + newNode->h;
                    newNode->parent = current;

                    openList.push(newNode);
                    allNodes[neighbor] = newNode;
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
		if (age < 5) {
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
	Vector2i startGrid(
				static_cast<int>((position.x + 30 - SIZE_OF_TILE/2) / SIZE_OF_TILE),
				static_cast<int>((position.y + 15 - SIZE_OF_TILE/2) / SIZE_OF_TILE)
			);

	Vector2i endGrid(
		static_cast<int>((target.x + 30 - SIZE_OF_TILE/2) / SIZE_OF_TILE),
		static_cast<int>((target.y + 15 - SIZE_OF_TILE/2) / SIZE_OF_TILE)
	);

	path = findPathAStar(startGrid, endGrid);
	stuckTimer.restart();
}

void Ant::update(float deltaTime) {
	if (path.empty()) return;

	// Проверяем, не застрял ли муравей
	if (distance(position, lastPosition) < 0.1f) {
		stuckTime += deltaTime;
		if (stuckTime > 1.0f) { // Если застрял более 1 секунды
			tryFindAlternativePath(path.back());
			stuckTime = 0;
		}
	} else {
		stuckTime = 0;
	}
	lastPosition = position;

	Vector2f target = path.back();
	Vector2f direction = target - position;
	float distance = sqrt(direction.x*direction.x + direction.y*direction.y);

	if (distance < 5.f) {
		path.pop_back();
	} else {
		direction /= distance;
		Vector2f newPosition = position + direction * speed * deltaTime;

		if (!checkAntCollision(newPosition)) {
			position = newPosition;
		} else {
			// Пробуем двигаться по касательной к стене
			Vector2f tangent(-direction.y, direction.x);
			Vector2f tryPosition1 = position + tangent * speed * deltaTime;
			Vector2f tryPosition2 = position - tangent * speed * deltaTime;

			if (!checkAntCollision(tryPosition1)) {
				position = tryPosition1;
			} else if (!checkAntCollision(tryPosition2)) {
				position = tryPosition2;
			} else {
				// Если не получается - ищем новый путь
				tryFindAlternativePath(target);
			}
		}
	}
	antShape.setPosition(position);
}

void Ant::draw(RenderWindow &window) {
	window.draw(antShape);
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
