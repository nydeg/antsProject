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
    Ant first(150, 0, nullptr);
    Ant second(UNHEALTHY_ANT, 9, nullptr);
    Ant* pf = &first;
    pf->getHealth();
    pf->getAge();
    first.setRole(std::make_unique<Soldier>());
    cout << first << endl;
    first.setRole(std::make_unique<Babysitter>());
    cout << first << endl;
    cout << second << endl;
    second.growAge();
    cout << second << endl;
    second.getAge();
    second.doTask();


    Anthill hill(10);
    const auto& ants = hill.getAnts();
    for (auto& ant : ants) {
        cout << ant << endl;
    }
}

