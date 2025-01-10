#include "MotionController.hpp"
#include <cmath>

MotionController::MotionController() :
    leftEncoder(PINA_1, PINB_1), 
    rightEncoder(PINA_2, PINB_2),
    leftPID(KP, KI, KD),
    rightPID(KP, KI, KD),
    currentPose{0, 0, M_PI/2},
    targetPose{0, 0, M_PI/2}
{
}

void MotionController::init(void)
{
    leftEncoder.init();
    rightEncoder.init();
    encodersTimer.attach_ms(TIMER_INTERVAL_ENCODER_MS, encoderTimerCallback, this);
    navigationTimer.attach_ms(TIMER_INTERVAL_NAVIGATE_MS, navigateTimerCallback, this);
}

void MotionController::encoderTimerCallback(MotionController *controller)
{
    float vl = controller->leftEncoder.getAngularVelocity();
    float vr = controller->rightEncoder.getAngularVelocity();

    controller->velocities [0] = vl;
    controller->velocities [1] = vr;
    
    unsigned long currentTime = millis();
    unsigned long deltaTime = currentTime - controller->lastUpdateTime;
    controller->lastUpdateTime = currentTime;
    
    float distance = (vl + vr) / 2.0f * (deltaTime / 1000.0f);

    Serial.print("Distance: ");
    Serial.println(distance);
}

void MotionController::navigateTimerCallback(MotionController *controller)
{
    controller->navigate();
    Serial.print("Navigate: ");
}

void MotionController::navigate(void)
{
    float distance = currentPose.distanceTo(targetPose);
    float angleDifference = currentPose.AngleDifferenceTo(targetPose);

    if(distance <= POSITION_TOLERANCE && angleDifference <= ANGLE_TOLERANCE) 
    {
        stop();
        return;
    }
}

void MotionController::stop(void)
{
    motorController.setSpeeds(0, 0);
}

void MotionController::setTarget(float x, float y, float theta)
{
    targetPose.updatePose(x, y, theta);
}
