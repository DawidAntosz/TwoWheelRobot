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

MotionController::~MotionController() {
    navigationTimer.detach();
}

void MotionController::init(void)
{
    leftEncoder.init();
    rightEncoder.init();
    
    encodersTimer.attach_ms(TIMER_INTERVAL_ENCODER_MS, [this]() { this->encodersTimerCallback(); });
    navigationTimer.attach_ms(TIMER_INTERVAL_NAVIGATE_MS, [this]() { this->navigateTimerCallback(); });
}

void MotionController::encodersTimerCallback(void)
{
    unsigned long currentTime = millis();
    unsigned long deltaTime = currentTime - lastUpdateTime;
    lastUpdateTime = currentTime;

    // update linear Velocity
    float currentVelocities[2];
    currentVelocities[LEFT] = leftEncoder.getAngularVelocity() * WHEEL_RADIUS;
    currentVelocities[RIGHT] = rightEncoder.getAngularVelocity() * WHEEL_RADIUS;

    velocities[LEFT] = (currentVelocities[LEFT] + lastVelocities[LEFT]) / 2.0f;
    velocities[RIGHT] = (currentVelocities[RIGHT] + lastVelocities[RIGHT]) / 2.0f;
    
    lastVelocities[LEFT] = currentVelocities[LEFT];
    lastVelocities[RIGHT] = currentVelocities[RIGHT];
    Serial.print("left: ");
    Serial.println(velocities[LEFT]);
    Serial.print("right: ");
    Serial.println(velocities[RIGHT]);
    

    // update Distance
    float deltaDistance[2];
    deltaDistance[LEFT] = velocities[LEFT] * deltaTime;
    deltaDistance[RIGHT] = velocities[RIGHT] * deltaTime;

    distance[LEFT] += deltaDistance[LEFT];
    distance[RIGHT] += deltaDistance[RIGHT];

    float centerDistance = (deltaDistance[LEFT] + deltaDistance[RIGHT]) / 2.0f;
    totalDistance += centerDistance;

    // update current position
    currentPose.theta += (deltaDistance[LEFT] - deltaDistance[RIGHT]) / WHEEL_BASE;
    // Normalize theta
    currentPose.theta = fmod(currentPose.theta, 2 * M_PI);
    if (currentPose.theta < 0) {
        currentPose.theta += 2 * M_PI;
    }
    currentPose.x += centerDistance * cos(currentPose.theta);
    currentPose.y += centerDistance * sin(currentPose.theta);
}

void MotionController::navigateTimerCallback(void)
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

Pose MotionController::readCurrentPose() const 
{
    Serial.print("Adress to private variable currentPose: ");
    Serial.println((uintptr_t)&currentPose, HEX);
    return currentPose;
}