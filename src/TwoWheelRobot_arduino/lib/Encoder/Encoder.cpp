#include "encoder.hpp"

Encoder::Encoder(uint8_t pinA, uint8_t pinB)
    : pinA(pinA), pinB(pinB), lastStateA(LOW),
    count(0), 
    lastCount(0), 
    lastUpdateTime(0), 
    angularVelocity(0.0f)
{
    init();
}

void Encoder::init(void)
{
    pinMode(pinA, INPUT_PULLUP);
    pinMode(pinB, INPUT_PULLUP);
    lastStateA = digitalRead(pinA);
    lastUpdateTime = millis();
    attachInterruptArg(digitalPinToInterrupt(pinA), Encoder::interruptHandler, this, CHANGE);
}

void IRAM_ATTR Encoder::interruptHandler(void* arg)
{
    Encoder* encoder = static_cast<Encoder*>(arg);
    Encoder::handleInterrupt(encoder);
}

void IRAM_ATTR Encoder::handleInterrupt(Encoder* encoder) 
{
    bool stateA = digitalRead(encoder->pinA);
    bool stateB = digitalRead(encoder->pinB);

    if (stateA != encoder->lastStateA) 
    {
        encoder->count += (stateA != stateB) ? 1 : -1;
        encoder->lastStateA = stateA;
    }
}

float Encoder::getAngularVelocity(void)
{
    currentTime = millis();
    deltaTime = currentTime - lastUpdateTime;

    noInterrupts();
    deltaCount = count - lastCount;
    lastCount = count;
    interrupts();

    lastUpdateTime = currentTime;

    return (deltaCount * CONSTANT_FACTOR) / (deltaTime / 1000.0f); // (rad/s)
}
