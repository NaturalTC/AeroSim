//
// Created by Jose Jimenez on 8/17/26.
//

#include "Fighter.h"
#include <iostream>

Fighter::Fighter(std::string m, int s, int missiles) : Aircraft(m, s) {
    missileCount = missiles;
}

void Fighter::describe() {
    std::cout << "Model: " << getModel() << " Speed: " << getSpeed() << " missileCount: " << missileCount << std::endl;
}