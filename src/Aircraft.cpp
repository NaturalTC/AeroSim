//
// Created by Jose Jimenez on 8/17/26.
//

#include "Aircraft.h"
#include <iostream>

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
