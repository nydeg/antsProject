cmake_minimum_required(VERSION 3.30)
project(projectAnts)

set(CMAKE_CXX_STANDARD 20)

add_executable(projectAnts main.cpp
ant.cpp
babysitter.cpp
builder.cpp
cleaner.cpp
collector.cpp
dead.cpp
soldier.cpp
stepherd.cpp
        Game.cpp
        Game.h
        anhill.cpp
        food.cpp
        food.h
        resourses.cpp
        resourses.h
        hay.cpp
        hay.h
        draw.cpp
        draw.h
        event_system.cpp
        event_system.h)
