#pragma once

#include <string>


class Role {
public:
	virtual void work() = 0;
	virtual ~Role() = default;
	
	virtual std::string getName() const = 0;
};