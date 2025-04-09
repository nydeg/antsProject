#pragma once
#include "role.h"
#include <iostream>
#include <string>

class Builder : public Role {
public:
	virtual void work() override {
		std::cout << "I am building" << std::endl;
	}

	virtual std::string getName() const override {
		return "Builder";
	}

};