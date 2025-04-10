#include "collector.h"
#include "ant.h"

void Collector::work(Ant& ant)
{
	std::cout << "i am collecting" << std::endl;
	ant.getAge();
}
