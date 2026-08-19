#include "Fighter.h"
#include "PIDController.h"
#include <iostream>
#include <vector>
#include <map>

int main() {
    // Weights and Parameters
    double targetAltitude = 30000;
    std::unique_ptr<PIDController> controller = std::make_unique<PIDController>(0.05 , .05 , 0.01, -10, 10);

    // Fighter Object
    std::unique_ptr<Fighter> falcon = std::make_unique<Fighter>("F-35",700,0,5);

    // Time Loop for Altitude Climb
    for (int i = 0; i<150; i++) {
        double output = controller->calculate(targetAltitude, falcon->getAltitude(), 0.1);
        falcon->setAltitude(output + falcon->getAltitude());
        std::cout << "Current Altitude: " << falcon->getAltitude() << "\nCurrent Clock Cycle: " << i << std::endl;
        if (std::abs(targetAltitude - falcon->getAltitude()) < 10.0) {
            std::cout << "Finished at iteration: " << i << std::endl;
            break;
        }
    }

    return 0;
}