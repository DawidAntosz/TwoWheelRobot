#ifndef POSE_H
#define POSE_H

#include <Arduino.h>
#include <cmath>

struct Pose
{
    float x, y, theta;
    Pose();
    Pose(float x, float y, float theta);

    float distanceTo(const Pose& other) const;
    float AngleDifferenceTo(const Pose& other) const;
    void updatePose(float newX, float newY, float newTheta);
};

#endif // POSE_H
