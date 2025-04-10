#include "ant.h"

void Ant::UpdateRole()
{
	if (age > 0) {
		if (age < 5) {
			setRole(std::make_unique<Babysitter>());
		}
		else if (age >= 5 && age < 10 && health > UNHEALTHY_ANT) {
			setRole(std::make_unique<Soldier>());
		}
		else if (age >= 5 && age < 10 && health <= UNHEALTHY_ANT) {
			setRole(std::make_unique<Stepherd>());
		}
		else if (age >= 10 && age < 15 && health > UNHEALTHY_ANT) {
			setRole(std::make_unique<Builder>());
		}
		else if (age >= 10 && age < 15 && health <= UNHEALTHY_ANT) {
			setRole(std::make_unique<Collector>());
		}
		else if (age >= 15 && age < DEATH_AGE) {
			setRole(std::make_unique<Cleaner>());
		} 
		else {
			setRole(std::make_unique<Dead>());
			health = 0;
		}
	}
}

void Ant::doTask()
{
	if (role) {
		role->work(*this);
	}
}

std::ostream& operator<<(std::ostream& out, Ant& ant)
{
	out << "Role: " << ant.getRole();
	return out;
}

std::ostream& operator<<(std::ostream& out, const Ant& ant) {
	out << "Role: " << ant.getRole();
	return out;
}
