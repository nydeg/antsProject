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

	const std::vector<Ant>& getAnts() const;

	std::vector<Ant>& getAnts() { return ants; }

	static int getCount() { return count; }

	void birth();

	void growAll();
};