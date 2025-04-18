#include <iostream>
#include <memory>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
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
#include "baby.h"
#include "draw.h"
#include "food.h"
#include "hay.h"
#include "storage.h"
using namespace std;
using namespace sf;
#define SIZE_OF_TILE 40.f

int main() {
    VideoMode desktopMode = VideoMode::getDesktopMode();
    const unsigned int width = 980;
    const unsigned int height = 760;

    RenderWindow window(sf::VideoMode({width, height}), L"Муравьи", sf::Style::Close | sf::Style::Titlebar );
    window.setFramerateLimit(60);

    Ant ant_collector(HEALTHY_ANT, 0,  nullptr);
    Ant ant_collector_2(HEALTHY_ANT, 0,  nullptr);
    Ant ant_collector_3(HEALTHY_ANT, 0,  nullptr);
    Ant ant1(HEALTHY_ANT, 0, std::make_unique<Baby>());
    ant1.setPosition(30.f, 520.f);
    std::vector<std::unique_ptr<Ant>> baby_ants;
    for (int i = 0; i < 7; ++i) {
        auto ann = std::make_unique<Ant>(HEALTHY_ANT, 0, std::make_unique<Baby>());
        ann->setPosition(30.f, 520.f);
        baby_ants.push_back(std::move(ann));
    }

    const sf::FloatRect bounds({30.f, 520.f},{270.f, 180.f});

    Food food;
    Storage storage({60.f, 60.f}, {100.f, 100.f}, 50, "food");
    Clock clock;
    Clock spawnClock;           // Таймер для спавна еды

    Font font("rubik-extrabold.ttf");

    //иконка
    Image icon;
    if (!icon.loadFromFile("icon.png")) { return 1; }
    window.setIcon({icon.getSize().x, icon.getSize().y}, icon.getPixelsPtr());

    //муравей
    Image ant_1;
    if (!ant_1.loadFromFile("ant.png")) {
        std::cerr << "Failed to load ant.png" << std::endl;
        return -1;
    }
    Texture anttexture;
    if (!anttexture.loadFromImage(ant_1)) {
        std::cerr << "Failed to create texture from image" << std::endl;
        return -1;
    }
    anttexture.setSmooth(true);
    RectangleShape antrec(Vector2f(40, 25));
    antrec.setTexture(&anttexture);
    antrec.setPosition(Vector2f(2 * SIZE_OF_TILE - 30, 2 * SIZE_OF_TILE - 15));

    //главное поле
    Texture field;
    if (!field.loadFromFile("field.png")) { return 1; }
    field.setSmooth(true);
    RectangleShape field_main(Vector2f(680, 680));
    field_main.setTexture(&field);
    field_main.setPosition(Vector2f(10, 25));

    //еда
    Texture food1;
    if (!food1.loadFromFile("storage_full.png")) {return 1;}
    food1.setSmooth(true);
    RectangleShape food1_main(Vector2f(120, 120));
    food1_main.setTexture(&food1);
    food1_main.setPosition(Vector2f(35, 50));

    //сено
    Texture hay1;
    if (!hay1.loadFromFile("hay_storage_full.png")) {return 1;}
    hay1.setSmooth(true);
    RectangleShape hay1_main(Vector2f(180, 120));
    hay1_main.setTexture(&hay1);
    hay1_main.setPosition(Vector2f(150, 50));

    //выход с поля
    RectangleShape rectangle({120.f, 50.f});
    rectangle.setFillColor(TEXT_COLOR);
    rectangle.setPosition({430.f, 0.f});

    //ANTS
    Text text(font);
    text.setString("ANTS");
    text.setCharacterSize(80);
    text.setFillColor(TEXT_COLOR);
    text.setPosition({710, 20});

    while (window.isOpen()) {
        float deltaTime = clock.restart().asSeconds();
        while (const std::optional<Event> event = window.pollEvent()) {
            if (event->is<Event::Closed>())
                window.close();
        }

        for (auto& ann : baby_ants) {
            ann->doTask(bounds);
        }

        ant1.doTask(bounds);

        if (spawnClock.getElapsedTime().asSeconds() >= 5.f) {
            food.spawn(maze);  // Спавн еды в случайном месте
            cout << food.getWeight() << endl;
            if (!ant_collector.isCarryingFood()) {
                ant_collector.setTarget(food.getPosition()); // Устанавливаем цель на еду
            } else {
                ant_collector.setTarget(storage.getPosition()); // Устанавливаем цель на склад
            }
            spawnClock.restart();   // Сброс таймера
        }
        ant_collector.update(deltaTime, food);
        if (ant_collector.isCarryingFood()) {
            ant_collector.setTarget(storage.getPosition());  // Отправляем муравья к складу
            ant_collector.deliverToStorage(storage, food);   // Доставляем еду на склад
        }

        window.clear(Color(86, 48, 33));
        window.draw(field_main);

        for (int x = 0; x < MAIN_FIELD; ++x) {
            for (int y = 0; y < MAIN_FIELD; ++y) {
                sf::RectangleShape cell(sf::Vector2f(SIZE_OF_TILE, SIZE_OF_TILE));
                cell.setPosition({x * SIZE_OF_TILE - 30, y * SIZE_OF_TILE - 15});
                //cell.setOutlineColor(Color::Red);
                //cell.setOutlineThickness(1);
                cell.setFillColor(Color(0, 0, 0, 256));
                if (maze[y][x] == 1) {
                    cell.setFillColor(Color(86, 48, 33));
                }
                window.draw(cell);
            }
        }

        storage.draw(window, "food");
        window.draw(food1_main);
        window.draw(hay1_main);
        window.draw(rectangle);
        window.draw(text);
        food.draw(window);
        for (auto& ann : baby_ants) {
            ann->draw(window);
        }
        ant_collector.draw(window);
        window.display();
    }

    return 0;
}