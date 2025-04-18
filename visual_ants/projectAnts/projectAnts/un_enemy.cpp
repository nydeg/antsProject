#include "enemy.h"
#include <cmath>
#include <cstdlib>
#include <algorithm>
#include <iostream>
#include "ant.h"
#include "anthill.h"
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

Enemy::Enemy(sf::Vector2f position) :
    health(100),
    strength(15),
    state(PATROLLING),
    speed(40.f) {

    shape.setRadius(15.f);
    shape.setFillColor(sf::Color::Magenta);
    shape.setPosition(position);
}

void Enemy::update(float dt, std::vector<Ant>& ants, Anthill& anthill) {
    if (!isAlive()) return;

    // 1. Логика выбора цели
    if (state != FLEEING) {
        bool foundTarget = false;
        for (auto& ant : ants) {
        auto diff = shape.getPosition() - ant.getPosition();
            if (ant.getRole() == "Soldier" &&
                std::sqrt(diff.x * diff.x + diff.y * diff.y) < 100.f) {
                targetPosition = ant.getPosition();
                changeState(CHASING);
                foundTarget = true;
                break;
            }
        }
        if (!foundTarget && state == CHASING) {
            changeState(PATROLLING);
        }
    }

    // 2. Поведение в зависимости от состояния
    switch (state) {
        case PATROLLING: {
            if (directionChangeClock.getElapsedTime().asSeconds() > 2.f) {
                float angle = (rand() % 360) * 3.14f / 180.f;
                targetPosition = sf::Vector2f(cos(angle), sin(angle)) * 50.f;
                directionChangeClock.restart();
            }
            break;
        }

        case CHASING: {
            sf::Vector2f moveDir = targetPosition - shape.getPosition();
            float distance = sqrt(moveDir.x*moveDir.x + moveDir.y*moveDir.y);
            if (distance > 20.f && distance > 0) {
                moveDir /= distance;
                shape.move(moveDir * speed * 1.2f * dt);
            } else if (distance <= 20.f) {
                changeState(FIGHTING);
            }
            break;
        }

        case FIGHTING: {
            if (attackCooldown.getElapsedTime().asSeconds() > 1.f) {
                for (auto& ant : ants) {
                    if (getGlobalBounds().intersects(ant.getGlobalBounds())) {
                        attackAnt(ant);
                    }
                }
                attackCooldown.restart();
            }
            break;
        }

        case FLEEING: {
            sf::Vector2f fleeDir = shape.getPosition() - anthill.getPosition();
            float length = sqrt(fleeDir.x*fleeDir.x + fleeDir.y*fleeDir.y);
            if (length > 0) fleeDir /= length;
            shape.move(fleeDir * speed * 1.5f * dt);

            if (health > 50) changeState(PATROLLING);
            break;
        }
    }

    // 3. Ограничение границ
    sf::Vector2f pos = shape.getPosition();
    pos.x = std::clamp(pos.x, 0.f, 680.f);
    pos.y = std::clamp(pos.y, 0.f, 680.f);
    shape.setPosition(pos);
}

void Enemy::attackAnt(Ant& ant) {
    if (ant.getRole() == "Soldier") {
        int outcome = rand() % 100;
        if (outcome < 40) { // 40% победить
            takeDamage(25);
            std::cout << "Солдат победил врага!" << std::endl;
        }
        else if (outcome < 70) { // 30% проиграть
            ant.setHealth(0);
            std::cout << "Солдат погиб в бою!" << std::endl;
        }
        else { // 30% отпугнуть
            takeDamage(10);
            std::cout << "Солдат отпугнул врага!" << std::endl;
        }
    } else {
        ant.setHealth(ant.getHealth() - strength);
        std::cout << "Враг атаковал " << ant.getRole() << "!" << std::endl;
    }
}

bool Enemy::tryStealFood(Ant& ant) {
    auto diff = shape.getPosition() - ant.getPosition();
    if (ant.isCarryingFood() &&
        std::sqrt(diff.x * diff.x + diff.y * diff.y) < 100.f) {
        if (rand() % 100 < 40) {
            ant.dropFood();
            return true;
        }
    }
    return false;
}

void Enemy::takeDamage(int damage) {
    health -= damage;
    if (health < 30 && state != FLEEING) {
        changeState(FLEEING);
    }
}


void Enemy::draw(sf::RenderWindow& window) const {
    if (!isAlive()) return;

    window.draw(shape);

    // Полоска здоровья
    sf::RectangleShape healthBar(sf::Vector2f(30.f * (health / 100.f), 5.f));
    healthBar.setFillColor(health > 50 ? sf::Color::Green : sf::Color::Red);
    sf::Vector2f pos = shape.getPosition();
    float pos_x = pos.x;
    float pos_y = pos.x;
    healthBar.setPosition({pos_x - 15, pos_y - 25});
    // window.draw(healthBar);
}

bool Enemy::isAlive() const {
    return health > 0;
}

sf::Vector2f Enemy::getPosition() const {
    return shape.getPosition();
}

sf::FloatRect Enemy::getGlobalBounds() const {

    return sf::FloatRect(
        {shape.getPosition().x - shape.getRadius(),
        shape.getPosition().y - shape.getRadius()},
        {shape.getRadius() * 2,
        shape.getRadius() * 2}
    );
}

void Enemy::changeState(BehaviorState newState) {
    state = newState;
    // Можно добавить дополнительную логику при смене состояния
}
