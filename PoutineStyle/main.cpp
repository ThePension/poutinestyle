/*
* Authors       : AUBERT Nicolas
*                 COMI Alessio
*                 VUILLIOMENET Théo
* Creation date : 28.09.2021
* Version       : 0.1
* Context       : HE-Arc, Projet P2 IL, 2021-2022
* Description   : Remake of Wolfenstein 3D with raycasting
*/

#include <SFML/Graphics.hpp>

int main()
{
    sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(shape);
        window.display();
    }

    return 0;
}