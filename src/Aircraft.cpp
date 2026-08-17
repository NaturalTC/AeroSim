//
// Created by Jose Jimenez on 8/17/26.
//

#include "Aircraft.h"
#include <iostream>

Aircraft::Aircraft(std::string m, int s) {
    model = m;
    speed = s;
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

void Aircraft::setModel(const std::string& model) {
    this->model = model;
}

void Aircraft::setSpeed(int speed) {
    if (speed > 0) this->speed = speed;
}