#pragma once
#include "role.h"
#include <iostream>
#include <string>

class Ant;

class Dead : public Role {
public:
	virtual void work(Ant& ant) override;

	virtual std::string getName() const override {
		return "the ant is dead";
	}
};