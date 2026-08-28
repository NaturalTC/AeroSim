//
// Created by Jose Jimenez on 8/17/26.
//

#include "Fighter.h"
#include <iostream>
#include <SFML/Graphics.hpp>

Fighter::Fighter(std::string m, int s, double a, int missiles) : Aircraft(m, s, a) {
    missileCount = missiles;
}

void Fighter::describe() {
    std::cout << "Model: " << getModel() << " Speed: " << getSpeed() << " missileCount: " << missileCount << std::endl;
}

void Fighter::draw(sf::RenderWindow& window, float screenY, float tiltAngle) {
    sf::Transform t;
    t.translate({200.f, screenY});
    t.rotate(sf::degrees(tiltAngle));

    sf::RectangleShape fuselage(sf::Vector2f(70.f, 10.f));
    fuselage.setFillColor(sf::Color(70, 70, 80));
    fuselage.setPosition({-35.f, -5.f});

    sf::ConvexShape nose(3);
    nose.setFillColor(sf::Color(70, 70, 80));
    nose.setPoint(0, {35.f, -5.f});
    nose.setPoint(1, {35.f,  5.f});
    nose.setPoint(2, {55.f,  0.f});

    sf::ConvexShape wing(3);
    wing.setFillColor(sf::Color(55, 55, 65));
    wing.setPoint(0, { 5.f,  5.f});
    wing.setPoint(1, {-20.f, 5.f});
    wing.setPoint(2, {-10.f, 18.f});

    sf::ConvexShape tailFin(3);
    tailFin.setFillColor(sf::Color(55, 55, 65));
    tailFin.setPoint(0, {-25.f, -5.f});
    tailFin.setPoint(1, {-35.f, -5.f});
    tailFin.setPoint(2, {-30.f, -15.f});

    sf::ConvexShape hTail(3);
    hTail.setFillColor(sf::Color(55, 55, 65));
    hTail.setPoint(0, {-28.f,  5.f});
    hTail.setPoint(1, {-35.f,  5.f});
    hTail.setPoint(2, {-35.f, 12.f});

    window.draw(wing,     t);
    window.draw(hTail,    t);
    window.draw(tailFin,  t);
    window.draw(fuselage, t);
    window.draw(nose,     t);
}