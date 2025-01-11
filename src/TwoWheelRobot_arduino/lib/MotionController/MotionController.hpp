#ifndef MOTION_CONTROLLER_H
#define MOTION_CONTROLLER_H

#include <Arduino.h>
#include <Ticker.h>
#include "cytron_md10a.hpp"
#include "encoder.hpp"
#include "PID.hpp"
#include "Pose.hpp"

// PID parameters
#define KP 1.0
#define KI 0.1
#define KD 0.05
// physical dimensions
#define WHEEL_BASE 200 // rozstaw kol (od srodka kola)
#define WHEEL_RADIUS 33.5 // srednica kola 67/2 [mm]
// position algorithm
#define POSITION_TOLERANCE 5.0 // [mm]
#define ANGLE_TOLERANCE 0.1 // [rad]

#define TIMER_INTERVAL_ENCODER_MS 100 // [ms] <= 10ms is good
#define TIMER_INTERVAL_NAVIGATE_MS 100 // [ms]

enum Side {
    LEFT = 0,
    RIGHT = 1
};

class MotionController 
{
    private:
        Encoder leftEncoder;
        Encoder rightEncoder;
        CytronMD10A motorController;

        PID leftPID;
        PID rightPID;

        Pose currentPose;
        Pose targetPose;

        Ticker encodersTimer;
        void encodersTimerCallback(void);
        float velocities[2]; //V = [mm]/[ms]
        float lastVelocities[2];
        unsigned long lastUpdateTime;

        float distance[2];
        float totalDistance;

        Ticker navigationTimer;
        void navigateTimerCallback(void);

    public:
        MotionController();
        ~MotionController();

        void init(void);
        void stop(void);
        void setTarget(float x, float y, float theta);
        Pose readCurrentPose() const;
};

#endif // MOTION_CONTROLLER_H
