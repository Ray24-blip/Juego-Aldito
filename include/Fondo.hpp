#include <SFML/Graphics.hpp>

class Fondo {
private:
    sf::Texture texturaFondo;
    sf::Sprite fondoSprite;
    int anchoMundo;
    int altoMundo;

public:
    // Constructor
    Fondo(const std::string& rutaTextura, int ancho, int alto) 
        : anchoMundo(ancho), altoMundo(alto) {
        if (!texturaFondo.loadFromFile(rutaTextura)) {
            throw std::runtime_error("Error: No se pudo cargar la textura del fondo.");
        }
        texturaFondo.setRepeated(true); // Habilitar repetición
        fondoSprite.setTexture(texturaFondo);
        fondoSprite.setTextureRect(sf::IntRect(0, 0, anchoMundo, altoMundo));
    }

    // Actualiza la posición del fondo con respecto a la vista
    void actualizar(const sf::View& vista, const sf::RenderWindow& ventana) {
        fondoSprite.setPosition(vista.getCenter().x - ventana.getSize().x / 2, 
                                vista.getCenter().y - ventana.getSize().y / 2);
    }

    // Renderiza el fondo en la ventana
    void dibujar(sf::RenderWindow& ventana) const {
        ventana.draw(fondoSprite);
    }
};