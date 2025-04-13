#ifndef FOOD_H
#define FOOD_H
#include "draw.h"
#include "resourses.h"

class Food : public Resourses{
private:
    const int max_size_of_food = 25;
    float regrow = 0.1f;
    float curr_grow = 0.0f;
public:
    Food(int x, int y, int weight = 25) : Resourses(x, y, weight){}
    void update() override;
    void print() override;

};
#endif //FOOD_H
