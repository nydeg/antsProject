#pragma once
#include "role.h"
#include <iostream>
#include <string>

class Ant;
class resourses;

class Collector : public Role {
	int x, y;
	resourses* target = nullptr;
	int collector_heap_size = 50;
public:
	virtual void work(Ant& ant) override;
	void update();
	void find_closest_res();
	void move_to_res();
	virtual std::string getName() const override {
		return "Collector";
	}

};