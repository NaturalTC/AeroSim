//
// Created by Jose Jimenez on 8/17/26.
//

#pragma once
#include <string>
#include <SFML/Graphics.hpp>

class Aircraft {
private:
    std::string model;
    int speed;
    double altitude;
public:
    virtual ~Aircraft() = default;
    Aircraft(std::string m, int s, double a);
    virtual void describe();
    virtual void draw(sf::RenderWindow& window, float screenY, float tiltAngle = 0.f);

    [[nodiscard]] std::string getModel() const;
    [[nodiscard]] int getSpeed() const;
    [[nodiscard]] double getAltitude() const;
    void setModel(const std::string& model);
    void setSpeed(int speed);
    void setAltitude(double altitude);
};