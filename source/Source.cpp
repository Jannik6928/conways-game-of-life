#include <vector>
#include <iostream>

#include "Grid.h"
#include "Tile.h"
#include "Camera.h"

int main() {

    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;

    sf::RenderWindow window(sf::VideoMode(1000, 600), "Conway's Game of Life", sf::Style::Default, settings);
    sf::Mouse mouse;

    Camera camera(Vector2<double>(0, 0), Vector2<double>(1000, 600), -2, 2, 2);
    Grid grid(20);

    window.setFramerateLimit(60);

    int frame = 0;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            switch (event.type)
            {
            case sf::Event::Closed: {
                window.close();
                break;
            }
            case sf::Event::MouseButtonPressed: {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    grid.insert_tile(camera.click(mouse.getPosition(window)), camera);
                }
                if (event.mouseButton.button == sf::Mouse::Right) {
                    grid.remove_tile(camera.click(mouse.getPosition(window)), camera);
                }
                break;
            }
            case sf::Event::KeyPressed: {
                switch (event.key.code)
                {
                case sf::Keyboard::M: {
                    grid.clear();
                    break;
                }
                }
                break;
            }
            case sf::Event::MouseWheelMoved: {
                //std::cout << event.mouseWheel.delta << std::endl;
                //camera.change_zoom_level(event.mouseWheel.delta);
                camera.zoom_in(event.mouseWheel.delta, mouse.getPosition(window));
                break;
            }
            }
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        {
            camera.change_position(Vector2<double>(0, -4 / camera.zoom()));
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        {
            camera.change_position(Vector2<double>(-4 / camera.zoom(), 0));
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        {
            camera.change_position(Vector2<double>(0, 4 / camera.zoom()));
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        {
            camera.change_position(Vector2<double>(4 / camera.zoom(), 0));
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::N) && frame == 5)
        {
            grid.make_step();
        }

        window.clear();
        grid.draw(window, camera);
        window.display();

        frame = (frame + 1) % 6;
    }

    return 0;

}