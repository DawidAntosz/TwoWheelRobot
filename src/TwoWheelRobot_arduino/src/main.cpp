#include <Arduino.h>
#include "constants.h"
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
  // motionController.navigate();
  delay(1000);
  Serial.println("main while");
}