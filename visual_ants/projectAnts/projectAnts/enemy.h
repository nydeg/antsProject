#pragma once

#include "ant.h"
#include "anthill.h"

class Enemy {
private:
    int health;
    int attackPower;
    bool isActive;

public:
    Enemy(int health = 100, int attackPower = 10);

    // Атакует муравья (уменьшает его здоровье через setHealth)
    void attack(Ant& ant);

    // Атакует муравейник (может убить одного муравья)
    void attackAnthill(Anthill& anthill);

    // Враг получает урон, возвращает true если побежден
    bool takeDamage(int damage);

    bool isDefeated() const { return health <= 0; }
    bool isActiveEnemy() const { return isActive; }

    // Бой с солдатом (без зависимости от методов Ant)
    bool fightAgainstSoldier();
};