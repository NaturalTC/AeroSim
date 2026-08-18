//
// Created by Jose Jimenez on 8/18/26.
//

#include "PIDController.h"
#include <iostream>

PIDController::PIDController(double p, double i, double d) {
    kp = p;
    ki = i;
    kd = d;
    integral = 0.0;
    previousError = 0.0;
}

double PIDController::calculate(double setpoint, double measured, double dt) {
    double error = setpoint - measured;
    integral += error * dt;
    double derivative = (error - previousError) / dt;
    double output = (kp * error) + (ki * integral) + (kd * derivative);
    previousError = error;
    return output;
}
