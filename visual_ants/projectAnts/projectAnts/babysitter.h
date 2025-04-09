#pragma once
#include "role.h"
#include <iostream>
#include <string>

class Babysitter : public Role {
public:
	virtual void work() override {
		std::cout << "I am sitting with baby" << std::endl;
	}

	virtual std::string getName() const override {
		return "Babysitter";
	}

};