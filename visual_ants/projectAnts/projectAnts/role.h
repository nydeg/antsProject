#pragma once

#include <string>

#include "SFML/Graphics/Rect.hpp"

class Ant;

class Role {
public:
	virtual void work(Ant& ant) = 0;
	virtual void work(Ant& ant, const sf::FloatRect& bounds) {
		// По умолчанию игнорируем bounds
		work(ant);
	}
	virtual ~Role() = default;
	virtual std::string getName() const = 0;
};