//
// Created by Jose Jimenez on 8/17/26.
//

#pragma once
#include "Aircraft.h"

class Fighter : public Aircraft {
private:
    int missileCount;
public:
    Fighter(std::string m, int s, double a, int missiles);
    void describe() override;
};