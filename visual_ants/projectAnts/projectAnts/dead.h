#pragma once
#include "role.h"
#include <iostream>
#include <string>

class Dead : public Role {
public:
	virtual void work() override {
		std::cout << "i am dead" << std::endl;
	}

	virtual std::string getName() const override {
		return "the ant is dead";
	}
};