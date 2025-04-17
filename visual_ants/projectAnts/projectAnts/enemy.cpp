#include "enemy.h"
#include <cstdlib> // Для rand()

Enemy::Enemy(int health, int attackPower)
    : health(health), attackPower(attackPower), isActive(true) {}

void Enemy::attack(Ant& ant) {
    // Просто сообщаем, что атаковали муравья
    // Реальное изменение здоровья будет обрабатываться в классе Ant
    std::cout << "Enemy attacked an ant!" << std::endl;
}

void Enemy::attackAnthill(Anthill& anthill) {
    if (!anthill.getAnts().empty()) {
        // Атакуем последнего муравья в списке
        anthill.getAnts().back().setHealth(0); // "Убиваем" муравья
        std::cout << "Enemy attacked anthill and killed one ant!" << std::endl;
    }
}

bool Enemy::takeDamage(int damage) {
    health -= damage;
    if (health <= 0) {
        isActive = false;
        return true;
    }
    return false;
}

bool Enemy::fightAgainstSoldier() {
    // Упрощенная логика боя без зависимости от Ant
    int outcome = rand() % 3; // 0-победа, 1-бегство, 2-поражение

    switch(outcome) {
        case 0: // Солдат победил
            health = 0;
        isActive = false;
        std::cout << "Soldier defeated the enemy!" << std::endl;
        return true;
        case 1: // Враг убежал
            isActive = false;
        std::cout << "Enemy ran away!" << std::endl;
        return true;
        case 2: // Враг победил
            health -= 10; // Получает урон в любом случае
        std::cout << "Enemy defeated the soldier!" << std::endl;
        return false;
    }
    return false;
}