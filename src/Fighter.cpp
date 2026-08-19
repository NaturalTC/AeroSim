//
// Created by Jose Jimenez on 8/17/26.
//

#include "Fighter.h"
#include <iostream>

Fighter::Fighter(std::string m, int s, double a, int missiles) : Aircraft(m, s, a) {
    missileCount = missiles;
}

void Fighter::describe() {
    std::cout << "Model: " << getModel() << " Speed: " << getSpeed() << " missileCount: " << missileCount << std::endl;
}