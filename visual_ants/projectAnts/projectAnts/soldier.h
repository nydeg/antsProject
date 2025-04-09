#pragma once
#include "role.h"
#include <iostream>
#include <string>

class Soldier : public Role {
public:
	virtual void work() override {
		std::cout << "i am protecting" << std::endl;
	}

	virtual std::string getName() const override {
		return "Soldier";
	}

};