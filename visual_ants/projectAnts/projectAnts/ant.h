#pragma once

#include <memory>
#include <iostream>
#include "role.h"
#include "soldier.h"
#include "babysitter.h"
#include "cleaner.h"
#include "collector.h"
#include "stepherd.h"
#include "builder.h"
#include "dead.h"
#include "consts.h"
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
#include <vector>

#include "food.h"
class Food;
using namespace std;
#define SIZE_OF_TILE 40.f
class Storage;

class Ant {
private:
	//sfml
	Texture antTexture;
	RectangleShape antShape;
	Vector2f position;
	vector<Vector2f> path;
	float speed = 200.0f;
	Clock stuckTimer;
	float stuckTime = 0;
	Vector2f lastPosition;
	const float detectionRadius = 20.f;
	bool isWalkable(int gridX, int gridY) const;
	bool checkAntCollision(const Vector2f& pos) const;
	vector<Vector2f> findPathAStar(const Vector2i& start, const Vector2i& end);
	void tryFindAlternativePath(const Vector2f& target);
	float distance(const Vector2f& a, const Vector2f& b) const;

	//usual
	int carryingCapacity = 10;
	bool carryingFood = false;
	bool carryingHay = false;
	std::unique_ptr<Role> role;
	int health, age;
	void UpdateRole();


public:
	//sfml
	int carriedFoodWeight;
	int carriedHayWeight;
	void setTarget(const Vector2f& target);
	void update(float deltaTime, Food& food);

	void setPosition(float x, float y) {
		position = {x, y};
	}

	float getPositionX() const;

	float getPositionY() const;

	sf::Vector2f getPosition() const;



	// void update(float deltaTime, Hay &hay);
	void draw(RenderWindow& window);
	bool isCarryingFood() const {return carryingFood;}
	void dropFood() {carryingFood = false;}
	bool isNear(const Vector2f& target) const {
		float dx = position.x - target.x;
		float dy = position.y - target.y;
		return (dx * dx + dy * dy) <= (detectionRadius * detectionRadius);
	}
	void collectFood(Food& food){
		if (isNear(food.getPosition())) {
			carryingFood = true;
			carriedFoodWeight = food.getWeight();
			food.consume(); // Убираем еду с карты
		}
	};
	void deliverToStorage(Storage& storage, Food& food);

	void doTask(const sf::FloatRect &bounds);

	//usual
	Ant(int health = HEALTHY_ANT, int age = 0, std::unique_ptr<Role> role = nullptr) : health(health), age(age), role(std::move(role)), position({80.f, 80.f}) {
		if (!antTexture.loadFromFile("ant.png")) {
			cerr << "Failed to load ant texture" << endl;
		}
		antShape.setSize(Vector2f(40, 25));
		antShape.setTexture(&antTexture);
		antShape.setOrigin({20.f, 12.5f});
		antShape.setPosition(position);
		lastPosition = position;
		UpdateRole();
	}

	// thanks for this we can push ant objects into Anthil::ants
	Ant(Ant&& other) noexcept = default; 
	Ant& operator=(Ant&& other) noexcept = default;

	// maybe should to be a private in future
	void setRole(std::unique_ptr<Role> newRole) { role = std::move(newRole); }

	void growAge() { age++; UpdateRole(); }

	void doTask();

	std::string getRole() { return role ? role->getName() : "empty"; }
	std::string getRole() const { return role ? role->getName() : "empty"; }

	void getHealth() const { std::cout << health << std::endl; }

	void getAge() const { std::cout << age << std::endl; }

	void setHealth(int health_) { health = health_; UpdateRole(); }

	void setAge(int age_) { age = age_; UpdateRole(); }

	~Ant() = default;
};

std::ostream& operator<<(std::ostream& out, Ant& ant);
std::ostream& operator<<(std::ostream& out, const Ant& ant);