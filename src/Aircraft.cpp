//
// Created by Jose Jimenez on 8/17/26.
//

#include "Aircraft.h"
#include <iostream>
#include <SFML/Graphics.hpp>

Aircraft::Aircraft(std::string m, int s, double a) {
    model = m;
    speed = s;
    altitude = a;
}

void Aircraft::describe() {
    std::cout << "Model: " << model << " Speed: " << speed << std::endl;
}

std::string Aircraft::getModel() const {
    return model;
}

int Aircraft::getSpeed() const {
    return speed;
}

double Aircraft::getAltitude() const {
    return altitude;
}

void Aircraft::setModel(const std::string& model) {
    this->model = model;
}

void Aircraft::setSpeed(int speed) {
    if (speed > 0) this->speed = speed;
}

void Aircraft::setAltitude(double altitude) {
    if (altitude > 0) this->altitude = altitude;
}

void Aircraft::draw(sf::RenderWindow& window, float screenY, float tiltAngle) {
    sf::RectangleShape body(sf::Vector2f(60.f, 10.f));
    body.setFillColor(sf::Color(70, 70, 80));
    body.setOrigin({30.f, 5.f});
    body.setPosition({200.f, screenY});
    body.setRotation(sf::degrees(tiltAngle));
    window.draw(body);
}
