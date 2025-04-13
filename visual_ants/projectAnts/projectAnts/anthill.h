#pragma once

#include <vector>
#include <memory>

class Ant;


class Anthill {
	int size;
	std::vector<Ant> ants;
	static int count;

public:
	Anthill(int size=100) : size(size) {}

	int getSize() { return size; }

	// Для чтения (константная версия)
	const std::vector<Ant>& getAnts() const { return ants; }

	// Для модификации (неконстантная версия)
	std::vector<Ant>& getAnts() { return ants; }

	static int getCount() { return count; }

	void birth();

	void growAll();
};