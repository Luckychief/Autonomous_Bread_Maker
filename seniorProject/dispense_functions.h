#ifndef DISPENSE_FUNCTIONS_H
#define DESPENSE_FUNCTIONS_H

#include <Arduino.h>
#include <AccelStepper.h>

//Stepper Motor Index Order:
//0 Flour
//1 Sugar
//2 Salt
//3 Yeast

//Note stepper opearting the led position of the bread maker has its own function call
//Also Note: the stepper driver for the lid stepper motor must not be put to sleep, for it will hold the position of the stepper.

//extern  is needed when you are using a function or global variable that is defined in a different file

extern int stepperSleep[]; //Pin Number for sleeping pins of Stepper Driver Note: Low means driver is put to sleep
extern int stepperStep[]; //Pin Number for stepping signal pin

extern float stepperRotations[]; //Number of rotations assigned to stepper motors
extern int primeButtons[]; //Buttuns used to prime ingridients to the auger

extern const int dir_pin;

extern const int max_speed;
extern const int init_speed;
extern const int increment;


void stepperSetup(); //Initializes GPIOs

void stepper_priming(); //Mnaually primes the auger systems with buttons
void stepper_dispense(int num, float amount); //num is the selected steppermotor
void openLid();
void closeLid();

void yeast_test();

void dispense_liquid1(float amount);
void dispense_liquid2(float amount);

#endif 