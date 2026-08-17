#include "Aircraft.h"
#include "Fighter.h"
#include <iostream>
#include <vector>
#include <map>

int main() {
    std::vector<Fighter> fighterPlanes;
    fighterPlanes.emplace_back("f-16", 2000, 8);
    fighterPlanes.emplace_back("f-35", 2500, 4);
    fighterPlanes.emplace_back("f-135", 1000, 7);

    for (Fighter& f : fighterPlanes) {
        f.describe();
    }

    std::map<std::string, int> flightHours;
    flightHours["DinoThor"] = 1000;
    flightHours["Jose"] = 10;
    flightHours["Felicity"] = 25;

    std::string topPilot;
    int maxHours = 0;
    for (const auto& p : flightHours) {
        if (p.second > maxHours) {
            maxHours = p.second;
            topPilot = p.first;
        }
    }

    std::cout << topPilot << ": " << maxHours << " hours" << std::endl;

    return 0;
}