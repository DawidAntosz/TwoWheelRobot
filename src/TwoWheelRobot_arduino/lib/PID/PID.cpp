#include "PID.hpp"

PID::PID(float kp, float ki, float kd, float outputMin, float outputMax)
    : kp(kp), ki(ki), kd(kd), 
    integral(0), previousError(0), 
    outputMin(outputMin), outputMax(outputMax) 
{
}

float PID::compute(float setpoint, float measurement)
{
    float error = setpoint - measurement;
    integral += error;
    float derivative = error - previousError;

    float output = (kp * error) + (ki * integral) + (kd * derivative);

    output = constrain(output, outputMin, outputMax);

    previousError = error;
    return output;
}


void PID::reset()
{
    integral = 0;
    previousError = 0;
}