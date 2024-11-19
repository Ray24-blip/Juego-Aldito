#include <SFML/Graphics.hpp>

int main()
{

    sf::RenderWindow ventana(sf::VideoMode(1280, 720), "Redball!");
   

    while (ventana.isOpen())
    {
    
        sf::Event event;
        while (ventana.pollEvent(event))
        {
            if (event.type == event.Closed)
                ventana.close();
        }
    
    }
}
