#include "collector.h"

#include <cmath>
#include <limits>
#include "ant.h"
#include "event_system.h"
#include "resourses.h"

void Collector::work(Ant& ant)
{
	std::cout << "i am collecting" << std::endl;
	ant.getAge();
}

void Collector::update() {
	if (!target) {
		find_closest_res();
	}
	else {
		move_to_res();
	}
}

void Collector::find_closest_res() {
	auto new_res = EventSystem::getSpawns();
	if (new_res.empty()) return;
	float min_dist = std::numeric_limits<float>::max();
	Resourses* closest = nullptr;
	for (const auto& res : new_res) {
		float dist = std::hypot(res.x - x, res.y - y);
		if (dist < min_dist) {
			min_dist = dist;
			closest = res.resourse;
		}
	}
	target = closest;
}

void Collector::move_to_res() {
	if (!target) return;
	int dx = target->getX() - x;
	int dy = target->getY() - y;
	if (dx != 0) {
		x += dx > 0 ? 1 : -1;
		y += dy > 0 ? 1 : -1;
	}

	if (x == target->getX() && y == target->getY()) {
		while (target->getWeight() != 0) {
			if (target->getWeight() < collector_heap_size) {
				int bring = target->bring_with_ant(collector_heap_size);
				collector_heap_size -= target->getWeight();
				target = nullptr;
			}
			else {
				//ZOVEM DRYGIX COLLECTOROV
			}
		}
	}
}


