#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "ant.h"
#include "anthill.h"

class Enemy {
public:
    Enemy(sf::Vector2f position);

    void setAggression(float level) {
        aggression = std::clamp(level, 0.0f, 1.0f);
        strength = 10 + static_cast<int>(aggression * 20); // Сила зависит от агрессии
    }

    // Основные методы
    void update(float dt, std::vector<Ant>& ants, Anthill& anthill);
    void draw(sf::RenderWindow& window) const;

    // Взаимодействие с муравьями
    void attackAnt(Ant& ant);
    bool tryStealFood(Ant& ant);
    void takeDamage(int damage);

    // Состояние
    bool isAlive() const;
    sf::Vector2f getPosition() const;
    sf::FloatRect getGlobalBounds() const;
    int getStrength() const { return strength; }

private:
    enum BehaviorState {
        PATROLLING,
        CHASING,
        FIGHTING,
        FLEEING
    };

    sf::CircleShape shape;
    int health;
    int strength;
    BehaviorState state;
    sf::Vector2f targetPosition;
    sf::Clock attackCooldown;
    sf::Clock directionChangeClock;
    float speed;
    float aggression; // Уровень агрессии (0.0 - 1.0)

    void changeState(BehaviorState newState);
    void findNewTarget(const std::vector<Ant>& ants);
};
