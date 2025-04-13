#include "food.h"
#include <algorithm>
#include <iostream>
#include <ostream>

void food::update() {
    curr_grow += regrow;
    if (curr_grow >= 1.0f) {
        weight = std::min(weight + static_cast<int>(curr_grow), max_size_of_food);
        curr_grow -= static_cast<int>(curr_grow);
    }
}

void food::print() {
    std::cout << "Ya eda moi weight " << this->weight << " " << "ya na " << this->x << " " << this->y << std::endl;
}
