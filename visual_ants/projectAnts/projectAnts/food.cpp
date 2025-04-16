#include "food.h"
#include <algorithm>
#include <iostream>
#include <ostream>
#include "consts.h"
#include "SFML/Graphics/RenderWindow.hpp"
#define SIZE_OF_TILE 40.f

Food::Food(): Resourses(this->getPosition().x, this->getPosition().y, 1) {
    shape.setRadius(10.f);
    shape.setFillColor(sf::Color::Green);
    shape.setOrigin({10.f, 10.f});
}

void Food::spawn(const sf::Vector2f &mousePos) {
    int gridX = static_cast<int>((mousePos.x + 30) / SIZE_OF_TILE);
    int gridY = static_cast<int>((mousePos.y + 15) / SIZE_OF_TILE);

    if (gridX >= 0 && gridX < MAIN_FIELD &&
        gridY >= 0 && gridY < MAIN_FIELD &&
        maze[gridY][gridX] == 0) {

        position = Vector2f(
            gridX * SIZE_OF_TILE - 30 + SIZE_OF_TILE/2,
            gridY * SIZE_OF_TILE - 15 + SIZE_OF_TILE/2
        );
        exists = true;
        shape.setPosition(position);
        } else {
            exists = false;
        }
}

void Food::draw(sf::RenderWindow &window) {
    if (exists) window.draw(shape);
}

sf::Vector2f Food::getPosition() const { return position; }

bool Food::isExists() const { return exists; }


void Food::update() {
    curr_grow += regrow;
    if (curr_grow >= 1.0f) {
        weight = std::min(weight + static_cast<int>(curr_grow), max_size_of_food);
        curr_grow -= static_cast<int>(curr_grow);
    }
}

void Food::print() {
    std::cout << "Ya eda moi weight " << this->weight << " " << "ya na " << this->x << " " << this->y << std::endl;
}
