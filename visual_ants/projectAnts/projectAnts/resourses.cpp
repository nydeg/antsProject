#include "resourses.h"
#include <iostream>
#include "event_system.h"

resourses::resourses(int x, int y, int amount): x(x), y(y), weight(amount) {
    event_system::addEvent({x, y, this});
}

int resourses::bring_with_ant(int size_of_ant_heap) {
    if (size_of_ant_heap - this->weight >= 0) {
        this->weight = 0;
    }
    if (size_of_ant_heap - this->weight < 0) {
        //EMERGENCY SYSTEM - delim na myraviev kotorie prishli
    }
    return this->weight;
}

int resourses::getX() const {
    return x;
}

int resourses::getY() const {
    return y;
}

int resourses::getWeight() const {
    return weight;
}

void resourses::setPosition(int new_x, int new_y) {
    x = new_x;
    y = new_y;
}

