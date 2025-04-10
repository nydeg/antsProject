#pragma once
#include "role.h"
#include <iostream>
#include <string>

class Ant;

class Builder : public Role {
public:
	virtual void work(Ant& ant) override;

	virtual std::string getName() const override {
		return "Builder";
	}
};