#include "resourses.h"
#include <iostream>
#include "event_system.h"

Resourses::Resourses(float x, float y, int amount): x(x), y(y), weight(amount) {
    EventSystem::addEvent({x, y, this});
}

int Resourses::bring_with_ant(int size_of_ant_heap) {
    if (size_of_ant_heap - this->weight >= 0) {
        this->weight = 0;
    }
    if (size_of_ant_heap - this->weight < 0) {
        //EMERGENCY SYSTEM - delim na myraviev kotorie prishli
    }
    return this->weight;
}

int Resourses::getX() const {
    return x;
}

int Resourses::getY() const {
    return y;
}

int Resourses::getWeight() const {
    return weight;
}

void Resourses::setPosition(int new_x, int new_y) {
    x = new_x;
    y = new_y;
}

