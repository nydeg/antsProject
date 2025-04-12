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

class Ant {
private:
	std::unique_ptr<Role> role;
	int health, age;

	void UpdateRole();

public:
	Ant(int health = HEALTHY_ANT, int age = 0, std::unique_ptr<Role> role = nullptr) : health(health), age(age), role(std::move(role)) { UpdateRole(); }

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