#pragma once

#include <vector>
#include "ant.h"


class Anthill {
	int size;
	std::vector<Ant> ants;

public:
	Anthill(int size=100) : size(size), ants(size) {}

	int getSize() { return size; }

	// Для чтения (константная версия)
	const std::vector<Ant>& getAnts() const { return ants; }

	// Для модификации (неконстантная версия)
	std::vector<Ant>& getAnts() { return ants; }
};