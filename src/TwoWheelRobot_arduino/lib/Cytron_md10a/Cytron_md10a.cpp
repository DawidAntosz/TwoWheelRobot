#include "cytron_md10a.hpp"

CytronMD10A::CytronMD10A(void) 
{
    dirPins[MOTOR_LEFT] = DIR1;
    pwmPins[MOTOR_LEFT] = PWM1;
    dirPins[MOTOR_RIGHT] = DIR2;
    pwmPins[MOTOR_RIGHT] = PWM2;
    lastSpeeds[MOTOR_LEFT] = 0;
    lastSpeeds[MOTOR_RIGHT] = 0;

    pinMode(DIR1, OUTPUT);
    pinMode(DIR2, OUTPUT);
    pinMode(PWM1, OUTPUT);
    pinMode(PWM2, OUTPUT);
    analogWrite(PWM1, 0);
    analogWrite(PWM2, 0);
}

void CytronMD10A::setSpeeds(int8_t speedLeft, int8_t speedRight)
{
    setSpeed(MOTOR_LEFT, speedLeft);
    setSpeed(MOTOR_RIGHT, speedRight);
}

void CytronMD10A::setSpeed(Motor motor, int8_t speed)
{
    if (motor != MOTOR_LEFT && motor != MOTOR_RIGHT) return;

    speed = constrain(speed, -100, 100);
    if (abs(speed) < 10) speed = 0;

    if (lastSpeeds[motor] == speed) return;
    lastSpeeds[motor] = speed;

    digitalWrite(dirPins[motor], speed >= 0 ? HIGH : LOW);
    speed = abs(speed);

    int pwmValue = map(speed, 0, 100, 0, 255);
    analogWrite(pwmPins[motor], pwmValue);
}
