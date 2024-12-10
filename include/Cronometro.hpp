#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <sstream>
#include <iostream> // Para imprimir en la consola

class Cronometro {
private:
    sf::Clock reloj;               // Reloj interno de SFML
    sf::Font fuente;               // Fuente para el texto
    sf::Text texto;                // Texto para mostrar el tiempo
    bool pausado;                  // Estado del cronómetro
    sf::Time tiempoAcumulado;      // Tiempo acumulado antes de pausar

public:
    Cronometro(unsigned int tamanoTexto, const std::string& rutaFuente) : pausado(false), tiempoAcumulado(sf::Time::Zero) {
        if (!fuente.loadFromFile(rutaFuente)) {
            throw std::runtime_error("No se pudo cargar la fuente");
        }

        texto.setFont(fuente);
        texto.setCharacterSize(tamanoTexto);
        texto.setFillColor(sf::Color::Green);
    }

    void reiniciar() {
        reloj.restart();
        tiempoAcumulado = sf::Time::Zero;
        pausado = false;
    }

    void pausar() {
        if (!pausado) {
            tiempoAcumulado += reloj.getElapsedTime();
            pausado = true;
        }
    }

    void reanudar() {
        if (pausado) {
            reloj.restart();
            pausado = false;
        }
    }

    void actualizar() {
        sf::Time tiempoActual = pausado ? tiempoAcumulado : tiempoAcumulado + reloj.getElapsedTime();
        std::ostringstream ss;
        ss << "Tiempo: " << tiempoActual.asSeconds() << " s";
        texto.setString(ss.str());
    }

    void ajustarPosicion(const sf::View& vista) {
        sf::Vector2f esquinaSuperiorDerecha = vista.getCenter() + sf::Vector2f(vista.getSize().x / 2.0f, -vista.getSize().y / 2.0f);
        texto.setPosition(esquinaSuperiorDerecha.x - texto.getLocalBounds().width - 10.0f, esquinaSuperiorDerecha.y + 10.0f);
    }

    void dibujar(sf::RenderWindow& ventana) {
        ventana.draw(texto);
    }

    float obtenerTiempoFinal() const {
        return (pausado ? tiempoAcumulado : tiempoAcumulado + reloj.getElapsedTime()).asSeconds();
    }
};
