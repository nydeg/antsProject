#pragma once
#include "role.h"
#include <iostream>
#include <string>

class Cleaner : public Role {
public:
	virtual void work() override {
		std::cout << "i am cleaning" << std::endl;
	}

	virtual std::string getName() const override {
		return "Cleaner";
	}

};