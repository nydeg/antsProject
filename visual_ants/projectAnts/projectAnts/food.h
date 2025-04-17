#ifndef FOOD_H
#define FOOD_H
#include "consts.h"
#include "draw.h"
#include "resourses.h"
#include "SFML/Graphics/CircleShape.hpp"
#include "SFML/System/Vector2.hpp"

namespace sf {
    class RenderWindow;
}

class Food : public Resourses{
private:
    //usual
    const int max_size_of_food = 25;
    float regrow = 0.1f;
    float curr_grow = 0.0f;

    //sfml
    sf::CircleShape shape;
    sf::Vector2f position;
    bool exists = false;

public:
    //sfml
    Food();
    void spawn(const int maze[MAIN_FIELD][MAIN_FIELD]);
    void draw(sf::RenderWindow& window);
    sf::Vector2f getPosition() const;
    void consume();
    bool isExists() const;
    int getWeight() const { return weight; }

    //usual
    Food(int x, int y, int weight = 25) : Resourses(x, y, weight){}
    void update() override;
    void print() override;

};
#endif FOOD_H
