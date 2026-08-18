#include "Fighter.h"
#include "PIDController.h"
#include <iostream>
#include <vector>
#include <map>

int main() {
    double targetAltitude = 30000;
    double currentAltitude = 28000;
    std::unique_ptr<PIDController> controller = std::make_unique<PIDController>(0.25 , 0.01 , 0.01);

    for (int i = 0; i<50; i++) {
        double output = controller->calculate(targetAltitude, currentAltitude, 0.1);
        currentAltitude = output + currentAltitude;
        std::cout << "Current Altitude: " << currentAltitude << "\nCurrent Iteration: " << i << std::endl;
        if (std::abs(targetAltitude - currentAltitude) < 10.0) {
            std::cout << "Finished at iteration: " << i << std::endl;
            break;
        }
    }

    return 0;
}