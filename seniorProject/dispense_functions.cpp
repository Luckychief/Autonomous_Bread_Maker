//Note stepper dierection pin is not needed, just use a negative value in the .move function
//Note to self: Might have to add liquidCrystal Library inside of the state_machin.h file


#include "dispense_functions.h"


extern int stepperSleep[] = {53, 47, 41, 35, 29}; //Pin Number for sleeping pins of Stepper Driver Note: Low means driver is put to sleep
extern int stepperStep[] = {51, 45, 39, 33, 27}; //Pin Number for stepping signal pin

extern float stepperRotations[] = {1, 1, 1, 1}; //Number of rotations assigned to stepper motors
extern int primeButtons[] = {9, 10, 11, 12}; //Pin corresponding to button

extern const int dir_pin = 0; //Throw away pin, becuase direction is not being picekd by mcu

extern const int max_speed = 2000;
extern const int init_speed = 150;
extern const int increment = 100;


#define motorInterfaceType 1

AccelStepper stepper0(motorInterfaceType, stepperStep[0], dir_pin);
AccelStepper stepper1(motorInterfaceType, stepperStep[1], dir_pin);
AccelStepper stepper2(motorInterfaceType, stepperStep[2], dir_pin);
AccelStepper stepper3(motorInterfaceType, stepperStep[3], dir_pin);
AccelStepper stepper4(motorInterfaceType, stepperStep[4], 22); //This is the stepper motor for the lid

void yeast_test(){
    digitalWrite(stepperSleep[3], HIGH);
    stepper3.move(stepperRotations[3]*16*200*0.4);
    while (stepper3.distanceToGo() != 0 ){
      stepper3.run();        
    }
    digitalWrite(stepperSleep[3], LOW);
  return;
}


void stepperSetup(){
  stepper0.setAcceleration(increment);
  stepper0.setMaxSpeed(max_speed);
  stepper0.setSpeed(init_speed);

  stepper1.setAcceleration(increment);
  stepper1.setMaxSpeed(max_speed);
  stepper1.setSpeed(init_speed);

  stepper2.setAcceleration(increment);
  stepper2.setMaxSpeed(max_speed);
  stepper2.setSpeed(init_speed);
  
  stepper3.setAcceleration(increment);
  stepper3.setMaxSpeed(max_speed);
  stepper3.setSpeed(init_speed);

  stepper4.setAcceleration(increment);
  stepper4.setMaxSpeed(max_speed);
  stepper4.setSpeed(init_speed);

  for(int i = 0; i < 4; i++){ 
    
    pinMode(primeButtons[i], INPUT);
    pinMode(stepperSleep[i], OUTPUT);
    digitalWrite(stepperSleep[i], LOW); //puts all steppers to sleep
  }

  digitalWrite(stepperSleep[4], LOW);

  pinMode(2, OUTPUT); //Relay Switch 1
  digitalWrite(2, HIGH);

  pinMode(3, OUTPUT); //Relay Switch 1
  digitalWrite(3, HIGH);

  pinMode(8, OUTPUT); //little dc motor that could
  digitalWrite(8, HIGH);

}

void stepper_priming(){
  if (digitalRead(primeButtons[0]) == HIGH) {
    stepper0.move(2500);
    while(stepper0.distanceToGo() != 0 ){
      stepper0.run();
    }
  }
  else if (digitalRead(primeButtons[1]) == HIGH){
    stepper1.move(2500);
   while(stepper1.distanceToGo() != 0 ){
    stepper1.run();
    }
  }
  else if (digitalRead(primeButtons[2]) == HIGH){
    stepper2.move(2500);
    while(stepper2.distanceToGo() != 0 ){
    stepper2.run();
    }
  }
  else if(digitalRead(primeButtons[3]) == HIGH) {
    stepper3.move(2500);
    while(stepper3.distanceToGo() != 0 ) {
      stepper3.run();
    }
  }

  return;
}

void stepper_dispense(int num, float amount){//Make sure to set sleep pin high, run the steper, then back low to enter sleep again
  switch(num){
    case 0:
    digitalWrite(8, LOW);                             //Used to control different module                   
    digitalWrite(stepperSleep[0], HIGH);              //Turns off stepper Driver Module
      stepper0.move(stepperRotations[0]*16*200*amount);   //Sets the number of steps needed to dispense ingridients
      //Serial.println(stepper0.distanceToGo());
      while (stepper0.distanceToGo() != 0 ){              //Moves stepper by specified number of steps
        stepper0.run();        
      }
      digitalWrite(stepperSleep[0], LOW);             //Puts Motor Driver to sleep
      digitalWrite(8, HIGH);                          //Used to control different module
      break;
    case 1:
      digitalWrite(stepperSleep[1], HIGH);            
      stepper1.move(stepperRotations[1]*16*200*amount);
      while (stepper1.distanceToGo() != 0 ){
        stepper1.run();        
      }
      digitalWrite(stepperSleep[1], LOW);
      break;
    case 2:
      digitalWrite(stepperSleep[2], HIGH);
      stepper2.move(stepperRotations[2]*16*200*amount);
      while (stepper2.distanceToGo() != 0 ){
        stepper2.run();        
      }
      digitalWrite(stepperSleep[2], LOW);
      break;
    case 3:
      digitalWrite(stepperSleep[3], HIGH);
      stepper3.move(stepperRotations[3]*16*200*amount);
      while (stepper3.distanceToGo() != 0 ){
        stepper3.run();        
      }
      digitalWrite(stepperSleep[3], LOW);
      break;
    default:
    break;
  }
  
  return;
}

void openLid(){
  digitalWrite(stepperSleep[4], HIGH);           //Turns stepper Driver
  stepper4.move(200*16*1.5);                     //Number of steps needed to open lid
  //Serial.print("Distance: ");
  //Serial.println(stepper4.distanceToGo());
  while(stepper4.distanceToGo() != 0){          //Stepper motor runs number of steps needed = 0
    stepper4.run();
  }
  return;                                       //steper Driver Remains On
}

void closeLid(){
  stepper4.move(-200*16*1.5);                   //Number of steps need to close lid
  //Serial.print("Distance: ");
  //Serial.println(stepper4.distanceToGo());
  while(stepper4.distanceToGo() != 0){         //Stepper motor runs number of steps needed = 0
    stepper4.run();
  }
  digitalWrite(stepperSleep[4], LOW);         //steper Driver is put to sleep
  return;
}

void dispense_liquid1(float amount) {
  digitalWrite(2, LOW);
  Serial.println("Water Dispenser ON");
  delay(amount);
  Serial.println(amount);
  Serial.println("Water Dispenser OFF");
  digitalWrite(2, HIGH);
  return;
}

void dispense_liquid2(float amount) {
  digitalWrite(3, LOW);
  Serial.println("Water Dispenser ON");
  delay(amount);
  Serial.println(amount);
  Serial.println("Water Dispenser OFF");
  digitalWrite(3, HIGH);
  return;
}


