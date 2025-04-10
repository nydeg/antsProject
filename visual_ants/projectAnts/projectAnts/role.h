#pragma once

#include <string>

class Ant;

class Role {
public:
	virtual void work(Ant& ant) = 0;
	virtual ~Role() = default;
	virtual std::string getName() const = 0;
};