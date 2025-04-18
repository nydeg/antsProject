cmake_minimum_required(VERSION 3.28)
project(projectAnts LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})


include(FetchContent)
FetchContent_Declare(SFML
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG 3.0.0
        GIT_SHALLOW ON
        EXCLUDE_FROM_ALL
        SYSTEM)
FetchContent_MakeAvailable(SFML)

add_executable(projectAnts main.cpp
ant.cpp
babysitter.cpp
builder.cpp
cleaner.cpp
collector.cpp
dead.cpp
soldier.cpp
stepherd.cpp
        anthill.cpp
        food.cpp
        resourses.cpp
        hay.cpp
        draw.cpp
        event_system.cpp
        storage.cpp
        storage.h
        baby.cpp
        baby.h)

target_compile_features(projectAnts PRIVATE cxx_std_17)
target_link_libraries(projectAnts PRIVATE SFML::Graphics SFML::Audio SFML::Window)
