#include "food.h"
#include <algorithm>
#include <iostream>
#include <ostream>
#include <cstdlib>
#include <ctime>
#include "consts.h"
#include "SFML/Graphics/RenderWindow.hpp"

#define SIZE_OF_TILE 40.f

Food::Food() : Resourses(this->getPosition().x, this->getPosition().y, 1) {
    shape.setRadius(10.f);
    shape.setFillColor(sf::Color::Green);
    shape.setOrigin({10.f, 10.f});
    std::srand(static_cast<unsigned>(std::time(nullptr))); // Инициализация генератора случайных чисел
}

void Food::consume() {
    exists = false;       // Убираем еду с поля
    weight = 0;           // Сбрасываем вес еды
    shape.setFillColor(sf::Color::Transparent); // Скрываем графически
}

void Food::spawn(const int maze[MAIN_FIELD][MAIN_FIELD]) {
    int gridX, gridY;
    bool validPosition = false;

    while (!validPosition) {
        gridX = std::rand() % MAIN_FIELD; // Случайное значение по X
        gridY = std::rand() % MAIN_FIELD; // Случайное значение по Y

        if (maze[gridY][gridX] == 0) { // Проверка, что клетка не занята стеной
            validPosition = true;
        }
    }

    position = sf::Vector2f(
        gridX * SIZE_OF_TILE - 30 + SIZE_OF_TILE / 2,
        gridY * SIZE_OF_TILE - 15 + SIZE_OF_TILE / 2
    );

    exists = true;
    weight = std::rand() % max_size_of_food + 1; // Случайный вес от 1 до max_size_of_food
    shape.setFillColor(sf::Color::Green);
    shape.setPosition(position);
}

void Food::draw(sf::RenderWindow& window) {
    if (exists) {
        window.draw(shape); // Рисуем только если еда существует
    }
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