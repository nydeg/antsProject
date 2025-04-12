#include <iostream>
#include <memory>

#include "ant.h"

#include "soldier.h"
#include "babysitter.h"
#include "cleaner.h"
#include "dead.h"
#include "collector.h"
#include "stepherd.h"
#include "builder.h"
#include "consts.h"
#include "anthill.h"


using namespace std;


int main()
{
    Anthill hill(10);
    for (int i = 0; i < 10; i++) {
        hill.birth();
    }
    for (Ant& ant : hill.getAnts()) {
        cout << ant << endl;
    }
    hill.growAll();
    for (Ant& ant : hill.getAnts()) {
        ant.getAge();
    }
    hill.getAnts()[4].setAge(16);
    for (Ant& ant : hill.getAnts()) {
        cout << ant << endl;
    }
}

