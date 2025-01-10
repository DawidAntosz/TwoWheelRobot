#include "Pose.hpp"

Pose::Pose() : x(0.0f), y(0.0f), theta(0.0f) {}

Pose::Pose(float x, float y, float theta) : x(x), y(y), theta(theta) {}

float Pose::distanceTo(const Pose& other) const
{
    return sqrt((other.x - x) * (other.x - x) + (other.y - y) * (other.y - y)); 
}

float Pose::AngleDifferenceTo(const Pose& other) const
{
    float diff = other.theta - theta;
    while (diff > M_PI) diff -= 2 * M_PI;
    while (diff < -M_PI) diff += 2 * M_PI;
    return diff;
}

void Pose::updatePose(float newX, float newY, float newTheta)
{
    x = newX;
    y = newY;
    theta = newTheta;
}