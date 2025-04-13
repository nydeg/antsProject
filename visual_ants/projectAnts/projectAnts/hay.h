#ifndef HAY_H
#define HAY_H
#include "resourses.h"

class Hay : public Resourses{
private:
    const int max_size_of_hay = 1000;
    float regrow = 0.5f;
    float curr_grow = 0.0f;
public:
    Hay(int x, int y, int weight = 100) : Resourses(x, y, weight){}
    void update() override;
    void print() override;
};
#endif //HAY_H
