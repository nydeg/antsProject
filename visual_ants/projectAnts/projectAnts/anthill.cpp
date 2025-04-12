#include "anthill.h"
#include "ant.h"

int Anthill::count = 0;

void Anthill::birth()
{
	ants.emplace_back();
	count++;
}

void Anthill::growAll()
{
	for (Ant& ant : ants) {
		ant.growAge();
	}
}
