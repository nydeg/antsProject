#ifndef DRAW_H
#define DRAW_H
class draw {
public:
    template<typename T> static T* create_resourses(int x, int y, int weight) {
        return new T(x, y, weight);
    }
};
#endif //DRAW_H
