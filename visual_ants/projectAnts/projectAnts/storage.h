#ifndef STORAGE_H
#define STORAGE_H
#include <SFML/Graphics.hpp>
#include <iostream>

#include "ant.h"
#include "food.h"
#include "hay.h"

class Storage {
private:
    sf::Sprite storageSprite; // Спрайт склада
    sf::Texture storageEmptyTexture, storageHalfTexture, storageFullTexture; // Текстуры склада
    int currentStorage = 0; // Текущее количество ресурсов на складе
    const int maxStorage = 100; // Максимальная емкость склада
    sf::Font font; // Шрифт для текста
    sf::Text storageText; // Текст для отображения состояния склада

    sf::RectangleShape storageShape;   // Прямоугольник склада
    sf::Texture storageTexture;        // Текстура склада
    int maxCapacity;                   // Максимальная вместимость
    int currentCapacity;               // Текущее количество еды
    sf::Vector2f position;
    std::string type;
    float width;
    float height;

public:
    Storage(sf::Vector2f position, sf::Vector2f size, int maxCapacity, std::string type); // Конструктор

    void addFood(Food& food, int weight);

    // void addHay(Hay &hay, int weight);

    int getCurrentCapacity() const;
    int getMaxCapacity() const;
    sf::Vector2f getPosition() const;
    float getPositionX() const;
    float getPositionY() const;
    float getWidth() const;
    float getHeight() const;
    void updateAppearance(std::string type);
    bool isAntNearStorage(const Ant& ant, const Storage& storage);
    void draw(sf::RenderWindow &window, std::string type);
};
#endif //STORAGE_H