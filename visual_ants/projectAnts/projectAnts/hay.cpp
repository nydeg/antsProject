#include "hay.h"
#include <algorithm>
#include <iostream>

void hay::update() {
    curr_grow += regrow;
    if (curr_grow >= 1.0f) {
        weight = std::min(weight + static_cast<int>(curr_grow), max_size_of_hay);
        curr_grow -= static_cast<int>(curr_grow);
    }
}

void hay::print() {
    std::cout << "Ya seno moi weight " << this->weight << " " << "ya na " << this->x << " " << this->y << std::endl;
}
