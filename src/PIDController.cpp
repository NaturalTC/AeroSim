//
// Created by Jose Jimenez on 8/18/26.
//

#include "PIDController.h"
#include <algorithm>

PIDController::PIDController(double p, double i, double d, double minI, double maxI) {
    kp = p;
    ki = i;
    kd = d;
    minIntegral = minI;
    maxIntegral = maxI;
    integral = 0.0;
    previousError = 0.0;
    firstCall = true;
}

double PIDController::getLastError() {
    return previousError;
}

double PIDController::calculate(double setpoint, double measured, double dt) {
    double error = setpoint - measured;
    integral += error * dt;
    integral = std::clamp(integral, minIntegral, maxIntegral);
    double derivative;
    if (firstCall) {
        firstCall = false;
        derivative = 0.0;
    } else {
        derivative = (error - previousError) / dt;
    }
    double output = (kp * error) + (ki * integral) + (kd * derivative);
    previousError = error;
    return output;
}
