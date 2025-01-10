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
#define L 200 // rozstaw kol (od srodka kola)
#define D 67 // srednica kola
// position algorithm
#define POSITION_TOLERANCE 5.0 // [mm]
#define ANGLE_TOLERANCE 0.1 // [rad]

#define TIMER_INTERVAL_ENCODER_MS 100 // [ms] <= 10ms is good
#define TIMER_INTERVAL_NAVIGATE_MS 100 // [ms]

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
        static void encoderTimerCallback(MotionController *controller);
        float lastVelocities[2];
        float velocities[2];
        unsigned long lastUpdateTime;

        Ticker navigationTimer;
        static void navigateTimerCallback(MotionController *controller);

    public:
        MotionController();
        ~MotionController() = default;

        void init(void);
        void stop(void);
        void setTarget(float x, float y, float theta);
        void navigate(void);
};

#endif // MOTION_CONTROLLER_H
