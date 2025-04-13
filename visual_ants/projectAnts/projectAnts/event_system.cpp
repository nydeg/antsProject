//
// Created by Admin on 12.04.2025.
//

#include "event_system.h"
#include "resourses.h"

std::vector<resourse_spawn> EventSystem::spawns;

void EventSystem::addEvent(const resourse_spawn &spawn) {
    spawns.push_back(spawn);
}

std::vector<resourse_spawn> EventSystem::getSpawns() {
    return spawns;
}

void EventSystem::clearSpawns() {
    spawns.clear();
}


