#ifndef BABY_H
#define BABY_H
#include <cfloat>
#include <iostream>
#include <ctime>

#include "ant.h"
#include "role.h"

class Baby : public Role {
public:
    Baby() {
        // Инициализация случайного генератора
        std::srand(static_cast<unsigned>(std::time(nullptr)));
    }
    std::string getName() const override {
        return "Baby";
    }

    void work(Ant& ant, const sf::FloatRect& bounds) override {
        sf::Vector2f position = ant.getPosition();
        float dx = static_cast<float>(std::rand() % 3 - 1);
        float dy = static_cast<float>(std::rand() % 3 - 1);

        float newX = position.x + dx;
        float newY = position.y + dy;

        if (newX < bounds.position.x) newX = bounds.position.x;
        if (newX > bounds.position.x + bounds.size.x) newX = bounds.position.x + bounds.size.x;
        if (newY < bounds.position.y) newY = bounds.position.y;
        if (newY > bounds.position.y + bounds.size.y) newY = bounds.position.y + bounds.size.y;

        ant.setPosition(newX, newY);

        //std::cout << "Baby moved to (" << newX << ", " << newY << ")." << std::endl;
    }

    void work(Ant& ant) override {
        // По умолчанию движение без границ
        work(ant, sf::FloatRect({-FLT_MAX, -FLT_MAX}, {FLT_MAX * 2, FLT_MAX * 2}));
    }
};


#endif //BABY_H
