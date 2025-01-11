#include <Arduino.h>
#include "constants.hpp"
#include "MotionController.hpp"

MotionController motionController;

void setup(void)
{ 
  Serial.begin(115200);
  motionController.init();
  motionController.setTarget(100, 100, 0);
}

void loop(void) 
{
  Pose currentPoseCopy = motionController.readCurrentPose();

  Serial.print("Adress COPY of variable currentPose: ");
  Serial.println((uintptr_t)&currentPoseCopy, HEX);

  Serial.println("Main whlie current position:");
  
  Serial.print("x:");
  Serial.println(currentPoseCopy.x);
  
  Serial.print("y:");
  Serial.println(currentPoseCopy.y);

  Serial.print("theta:");
  Serial.println(currentPoseCopy.theta);

  delay(1000);
}