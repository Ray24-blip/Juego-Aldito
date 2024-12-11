#include <SFML/Graphics.hpp>

class Fondo
{
private:
    sf::Texture texturaFondo;
    sf::Sprite fondoSprite;
    int anchoMundo;
    int altoMundo;

public:
    Fondo(const std::string &rutaTextura, int ancho, int alto)
        : anchoMundo(ancho), altoMundo(alto)
    {
        if (!texturaFondo.loadFromFile(rutaTextura))
        {
            throw std::runtime_error("Error: No se pudo cargar la textura del fondo.");
        }
        texturaFondo.setRepeated(true);
        fondoSprite.setTexture(texturaFondo);
        fondoSprite.setTextureRect(sf::IntRect(0, 0, anchoMundo, altoMundo));
    }

    void actualizar(const sf::View &vista, const sf::RenderWindow &ventana)
    {
        fondoSprite.setPosition(vista.getCenter().x - ventana.getSize().x / 2,
                                vista.getCenter().y - ventana.getSize().y / 2);
    }

    void dibujar(sf::RenderWindow &ventana) const
    {
        ventana.draw(fondoSprite);
    }
};