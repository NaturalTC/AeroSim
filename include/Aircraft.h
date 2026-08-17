//
// Created by Jose Jimenez on 8/17/26.
//

#pragma once
#include <string>

class Aircraft {
private:
    std::string model;
    int speed;
public:
    virtual ~Aircraft() = default;
    Aircraft(std::string m, int s);
    virtual void describe();

    [[nodiscard]] std::string getModel() const;
    [[nodiscard]] int getSpeed() const;

    void setModel(const std::string& model);
    void setSpeed(int speed);
};