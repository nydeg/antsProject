#pragma once
#include "role.h"
#include <iostream>
#include <string>

class Collector : public Role {
public:
	virtual void work() override {
		std::cout << "i am collecting" << std::endl;
	}

	virtual std::string getName() const override {
		return "Collector";
	}

};