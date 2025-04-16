#ifndef RESOURSES_H
#define RESOURSES_H


class Resourses{
public:
    Resourses(float x, float y, int amount);

    int bring_with_ant(int size_of_ant_heap);
    virtual void update() = 0; //?
    int getX() const;
    int getY() const;
    int getWeight() const;
    void setPosition(int new_x, int new_y);
    virtual void print() = 0;
protected:
    int x, y; //coordinates of resourse
    int weight; //weight of resourse
};
#endif //RESOURSES_H
