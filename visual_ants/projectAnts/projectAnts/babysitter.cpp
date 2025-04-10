#include "babysitter.h"
#include "ant.h"

void Babysitter::work(Ant& ant)
{
	std::cout << "I am sitting with baby" << std::endl;
	ant.getAge();
}
