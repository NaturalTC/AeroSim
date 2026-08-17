#include <iostream>
#include <map>
#include <string>
#include <memory>
#include <vector>
#include <algorithm>

class Aircraft {
private:
    std::string model;
    int speed;
public:
    virtual ~Aircraft() = default;

    Aircraft(std::string m, int s) {
        model = m;
        speed = s;
    }
    virtual void describe() {
        std::cout << "Model: " << model << " Speed: " << speed << std::endl;
    }
    // Getters
    [[nodiscard]] std::string getModel() const {
        // no discard just means that whoever returns the value must use it (used in mission crititcal systems)
        return model;
    }

    [[nodiscard]] int getSpeed() const {
        return speed;
    }

    // Setters
    void setModel(const std::string &model) {
        this->model = model;
    }

    void setSpeed(int speed) {
        if (speed > 0) this->speed = speed;
    }
};
class Fighter : public Aircraft{
private:
    int missileCount;
public:
    Fighter(std::string m, int s, int missiles) : Aircraft(m,s) {
        missileCount = missiles;
    }

    void describe() override {
        std::cout << "Model: " << getModel() << " Speed: " << getSpeed() << " missileCount: " << missileCount << std::endl;
    };
};

int main() {

    std::map<std::string, int> flightHours;
    std::string mostPilotHours;
    int tmp = 0;

    flightHours["DinoThor"] = 1000;
    flightHours["Jose"] = 10;
    flightHours["Felicity"] = 25;

    for (const auto& p : flightHours) {
        if (p.second > tmp) {
            tmp = p.second;
            mostPilotHours = p.first;
        }
    }

    std::cout << mostPilotHours << std::endl;

    return 0;
}
