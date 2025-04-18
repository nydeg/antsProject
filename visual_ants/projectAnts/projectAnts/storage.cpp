#include "storage.h"

#include "ant.h"
#include "hay.h"

Storage::Storage(sf::Vector2f position, sf::Vector2f size, int maxCapacity, std::string type)
    : storageSprite(storageEmptyTexture), position(position), font("rubik-extrabold.ttf"), storageText(font),
      maxCapacity(maxCapacity), currentCapacity(0), storageShape(size), width(size.x), height(size.y) {

    // Загрузка текстур склада
    if (type == "food") {
        if (!storageEmptyTexture.loadFromFile("storage_empty.png")) {
            std::cerr << "Failed to load storage_empty.png" << std::endl;
        }
        if (!storageHalfTexture.loadFromFile("storage_half.png")) {
            std::cerr << "Failed to load storage_half.png" << std::endl;
        }
        if (!storageFullTexture.loadFromFile("storage_full.png")) {
            std::cerr << "Failed to load storage_full.png" << std::endl;
        }
    }
    // else if (type == "hay") {
    //     if (!storageEmptyTexture.loadFromFile("hay_storage_empty.png")) {
    //         std::cerr << "Failed to load hay_storage_empty.png" << std::endl;
    //     }
    //     if (!storageHalfTexture.loadFromFile("hay_storage_half.png")) {
    //         std::cerr << "Failed to load hay_storage_half.png" << std::endl;
    //     }
    //     if (!storageFullTexture.loadFromFile("hay_storage_full.png")) {
    //         std::cerr << "Failed to load hay_storage_full.png" << std::endl;
    //     }
    // }

    // Отключение сглаживания для текстур
    storageEmptyTexture.setSmooth(false);
    storageHalfTexture.setSmooth(false);
    storageFullTexture.setSmooth(false);

    // Установка начальной текстуры и масштабирование спрайта
    storageSprite.setTexture(storageEmptyTexture);
    sf::Vector2u textureSize = storageEmptyTexture.getSize();
    storageSprite.setScale({
        size.x / static_cast<float>(textureSize.x),
        size.y / static_cast<float>(textureSize.y)
    });
    storageSprite.setPosition(position);

    // Установка текстуры и размеров для прямоугольника
    storageShape.setSize(size);
    storageShape.setPosition(position);
    storageShape.setTexture(&storageEmptyTexture);
    storageText.setFont(font);
    storageText.setString("Storage: " + std::to_string(currentCapacity) + "/" + std::to_string(maxCapacity));
    storageText.setCharacterSize(25);
    storageText.setFillColor(sf::Color::White);
    storageText.setPosition({position.x, position.y + size.y + 10.f});
}

void Storage::addFood(Food& food, int weight) {
    currentCapacity = std::min(currentCapacity + weight, maxCapacity);
    if (currentCapacity > maxCapacity) {
        storageText.setString("Storage is full!");
    }
    updateAppearance("food");
}

int Storage::getCurrentCapacity() const {
    return currentCapacity;
}

int Storage::getMaxCapacity() const {
    return maxCapacity;
}

sf::Vector2f Storage::getPosition() const {
    return position;
}

float Storage::getPositionX() const {
    return position.x;
}

// Геттер для координаты Y склада
float Storage::getPositionY() const {
    return position.y;
}

// Геттер для ширины склада
float Storage::getWidth() const {
    return width;
}

// Геттер для высоты склада
float Storage::getHeight() const {
    return height;
}

void Storage::updateAppearance(std::string type) {
    float fillPercent = static_cast<float>(currentCapacity) / maxCapacity;

    // Обновление текстуры склада
    if (type == "food") {
        if (fillPercent <= 0.0f) {
            storageSprite.setTexture(storageEmptyTexture);
            storageShape.setTexture(&storageEmptyTexture);
        } else if (fillPercent <= 0.5f) {
            storageSprite.setTexture(storageHalfTexture);
            storageShape.setTexture(&storageHalfTexture);
        } else {
            storageSprite.setTexture(storageFullTexture);
            storageShape.setTexture(&storageFullTexture);
        }
    }
    // else if (type == "hay") {
    //     if (fillPercent <= 0.0f) {
    //         storageSprite.setTexture(storageEmptyTexture);
    //         storageShape.setTexture(&storageEmptyTexture);
    //     }
    //     else if (fillPercent <= 0.5f) {
    //         storageSprite.setTexture(storageHalfTexture);
    //         storageShape.setTexture(&storageHalfTexture);
    //     }
    //     else {
    //         storageSprite.setTexture(storageFullTexture);
    //         storageShape.setTexture(&storageFullTexture);
    //     }
    // }

    // Обновление текста
    storageText.setString("Storage: " + std::to_string(currentCapacity) + "/" + std::to_string(maxCapacity));
}

bool Storage::isAntNearStorage(const Ant& ant, const Storage& storage) { // добавлен параметр storage
    return ant.getPosition().x >= storage.getPosition().x &&
           ant.getPosition().x <= storage.getPosition().x + storage.getWidth() &&
           ant.getPosition().y >= storage.getPosition().y &&
           ant.getPosition().y <= storage.getPosition().y + storage.getHeight();
}

void Storage::draw(sf::RenderWindow& window, std::string type) {
    if (type == "hay"){updateAppearance("hay");}
    else if (type == "food"){updateAppearance("food");}
    window.draw(storageSprite);
    window.draw(storageText);
}