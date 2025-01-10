#ifndef CYTRON_MD10A_H
#define CYTRON_MD10A_H

#include <Arduino.h>

#define DIR1  16  // D0
#define PWM1  5  // D1
#define DIR2  4  // D2
#define PWM2  0  // D3

enum Motor 
{
    MOTOR_LEFT,
    MOTOR_RIGHT
};

class CytronMD10A 
{
    private:
        uint8_t dirPins[2];
        uint8_t pwmPins[2];
        int lastSpeeds[2];
        
    public:
        CytronMD10A(void);
        ~CytronMD10A() = default;

        void setSpeed(Motor motor, int8_t speed);
        void setSpeeds(int8_t speedLeft, int8_t speedRight);
};

#endif // CYTRON_MD10A_H
