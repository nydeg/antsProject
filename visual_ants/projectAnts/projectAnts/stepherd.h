#pragma once
#include "role.h"
#include <iostream>
#include <string>

class Stepherd : public Role {
public:
	virtual void work() override {
		std::cout << "i am pastuh hz" << std::endl;
	}

	virtual std::string getName() const override {
		return "Stepherd";
	}

};