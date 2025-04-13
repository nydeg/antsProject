#ifndef EVENT_SYSTEM_H
#define EVENT_SYSTEM_H
#include <vector>
#include "resourses.h"

struct resourse_spawn {
    int x;
    int y;
    resourses* resourse;
};

class event_system {
private:
    static std::vector<resourse_spawn> spawns;
public:
    static void addEvent(const resourse_spawn& spawn);
    static std::vector<resourse_spawn> getSpawns();
    static void clearSpawns();
};
#endif //EVENT_SYSTEM_H
