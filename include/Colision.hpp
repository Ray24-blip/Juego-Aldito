#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include <iostream>

class MyContactListener : public b2ContactListener {
public:
    bool isGrounded = false; // Indica si la bola está en contacto con el suelo

    void BeginContact(b2Contact* contact) override {
        b2Fixture* fixtureA = contact->GetFixtureA();
        b2Fixture* fixtureB = contact->GetFixtureB();

        // Verificar si uno de los fixtures es el sensor
        if (fixtureA->IsSensor() || fixtureB->IsSensor()) {
            isGrounded = true;
            std::cout << "Sensor detecto contacto con el suelo." << std::endl;
        }
    }

    void EndContact(b2Contact* contact) override {
        b2Fixture* fixtureA = contact->GetFixtureA();
        b2Fixture* fixtureB = contact->GetFixtureB();

        // Verificar si uno de los fixtures es el sensor
        if (fixtureA->IsSensor() || fixtureB->IsSensor()) {
            isGrounded = false;
            std::cout << "Sensor dejo de detectar el suelo." << std::endl;
        }
    }
};