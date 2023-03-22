//#include "dispense_functions.h"
//#include "lcd_display_functions.h"
//Stepper Motor Index Order:
//0 Flour
//1 Sugar
//2 Salt
//3 Yeast
//4 Lid

#include <AccelStepper.h>
#include "state_machine.h"
#include "dispense_functions.h"
//#include "lcd_display_functions.h"

float amount1 = 4;

void setup() {
  Serial.begin(9600);
  sm1_setup();
  stepperSetup();
}


void loop() {
  tick_fct_sm1();
  //yeast_test();
  //delay(20000);
}
