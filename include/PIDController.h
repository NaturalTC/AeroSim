//
// Created by Jose Jimenez on 8/17/26.
//

#ifndef RADARTECH_PIDCONTROLLER_H
#define RADARTECH_PIDCONTROLLER_H

class PIDController {
private:
    double kp;
    double ki;
    double kd;

    double integral;
    double previousError;

    double minIntegral;
    double maxIntegral;

    bool firstCall;
public:
    PIDController(double p, double i, double d, double minI, double maxI);
    double calculate(double setpoint, double measured, double dt);
};


#endif //RADARTECH_PIDCONTROLLER_H