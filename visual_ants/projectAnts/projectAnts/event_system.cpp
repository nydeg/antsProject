//
// Created by Admin on 12.04.2025.
//

#include "event_system.h"

std::vector<resourse_spawn> event_system::spawns;

void event_system::addEvent(const resourse_spawn &spawn) {
    spawns.push_back(spawn);
}

std::vector<resourse_spawn> event_system::getSpawns() {
    return spawns;
}

void event_system::clearSpawns() {
    spawns.clear();
}


