#ifndef EVENT_SYSTEM_H
#define EVENT_SYSTEM_H
#include <vector>

class Resourses;

struct resourse_spawn {
    float x;
    float y;
    Resourses* resourse;
};

class EventSystem {
private:
    static std::vector<resourse_spawn> spawns;
public:
    static void addEvent(const resourse_spawn& spawn);
    static std::vector<resourse_spawn> getSpawns();
    static void clearSpawns();
};
#endif //EVENT_SYSTEM_H
