#ifndef PID_H
#define PID_H

#include <Arduino.h>

class PID
{
    private:
        float kp, ki, kd;
        float integral;
        float previousError;
        float outputMin, outputMax;

    public:
        PID(float kp, float ki, float kd, float outputMin = -100.0, float outputMax = 100.0);

        float compute(float setpoint, float measurement);
        void reset();
};

#endif // PID_H
