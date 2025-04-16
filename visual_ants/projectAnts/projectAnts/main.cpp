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
#include "draw.h"
#include "food.h"
#include "hay.h"
using namespace std;
using namespace sf;
#define SIZE_OF_TILE 40.f

int main()
{
    VideoMode desktopMode = VideoMode::getDesktopMode();
    const unsigned int width = 980;
    const unsigned int height = 760;

    RenderWindow window(sf::VideoMode({width, height}), L"Муравьи", sf::Style::Close | sf::Style::Titlebar );
    window.setFramerateLimit(60);

    Ant ant(HEALTHY_ANT, 0,  nullptr);
    Food food;
    Clock clock;

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
            if (event->is<Event::MouseButtonPressed>() && Mouse::isButtonPressed(Mouse::Button::Left)) {
                sf::Vector2i mousePos;
                mousePos = Mouse::getPosition(window);
                food.spawn(Vector2f(mousePos.x, mousePos.y));
                if (food.isExists()) ant.setTarget(food.getPosition());
                ant.setTarget(food.getPosition());
            }
        }
        ant.update(deltaTime);

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
        window.draw(rectangle);
        window.draw(text);
        food.draw(window);
        ant.draw(window);
        window.display();
    }

    return 0;
}

