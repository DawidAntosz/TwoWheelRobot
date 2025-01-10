#ifndef ENCODER_H
#define ENCODER_H

#include <Arduino.h>

#define PINA_1 14 // D5
#define PINB_1 12 // D6
#define PINA_2 13 // D7
#define PINB_2 15 // D8

#define REDUCTIONRATIO 46 // 46:1 gears reduction
#define SIGNALCOUNT 44 // 11 full signals per revolution
#define PULSES_PER_REVOLUTION (SIGNALCOUNT * REDUCTIONRATIO)
#define CONSTANT_FACTOR (2.0 * PI / PULSES_PER_REVOLUTION)

class Encoder 
{
    private:
        uint8_t pinA;
        uint8_t pinB;
        bool lastStateA;
        volatile int32_t count;
        int32_t lastCount;
        int32_t deltaCount;

        uint32_t currentTime;
        uint32_t lastUpdateTime;
        uint32_t deltaTime;
        float angularVelocity;

        static void IRAM_ATTR handleInterrupt(Encoder* encoder);
        static void IRAM_ATTR interruptHandler(void* arg);

    public:
        Encoder(uint8_t pinA, uint8_t pinB);
        ~Encoder() = default;

        void init(void);
        float getAngularVelocity(void);
};

#endif // ENCODER_H
