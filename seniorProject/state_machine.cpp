//Need to add an opening state and closing state
//Need to properly Select the sequence of buttons presses simulated for the bread maker, and the four recipes
//Need to properly assign buttons presses, ouput variables, and press function



#include "state_machine.h"
const float recipe1[6] = {9.375, 0.375, 2.25, 0.3, 20000, 20000}; //Sugar, Salt, Yeast, Flour, Water    9.375, .375, 2.25, .3, 20000
const float recipe2[6] = {9.375, 0.375, 2.25, 0.3, 20000, 20000}; // 12.5, 0.5, 3, 3, 0.4, 20000
const float recipe3[6] = {12.5, 0.5, 3, 0.4, 20000, 20000}; //NOW: Flour, Salt, Sugar, Yeast
const float recipe4[6] = {12.5, 0.5, 3, 0.4, 20000, 20000};
float recipe_selected[6] = {0, 0, 0, 0, 0, 0};


enum states_sm1{Start, idle, prime_buttons, selection, open, dispense_salt, dispense_flour, dispense_yeast, dispense_sugar, dispense_water, dispense_oil, close, done} state_sm1;

const int b0 = 13; //event trigger from MCU#2
const int b1 = 12;
const int b2 = 11;
const int b3 = 10;

const int b4 = 7; //physical buttons
const int b5 = 6;
const int b6 = 5;
const int b7 = 4;

const int outputPins[] = {40, 38, 36, 34, 32, 30};

void press(int num1){
  digitalWrite(num1, HIGH);     //Button Press Simulated
  delay(200);                   //Button held down for 200ms, needed to be properly detected
  digitalWrite(num1, LOW);      //Button Realease Simulated
  delay(200);
  return;
}


void recipe_selection_fct(int num){
  switch(num){
    case 0: //small lite
    Serial.println("POWER");
    press(outputPins[0]);
    delay(2000);
    Serial.println("SET");
    press(outputPins[4]);
    delay(2000);
    Serial.println("SET");
    press(outputPins[4]);
    delay(2000);
    //press(outputPins[5]);
    break;

    case 1: //small dark
    press(outputPins[0]);
    delay(2000);
    press(outputPins[4]);
    delay(2000);
    press(outputPins[4]);
    delay(2000);
    press(outputPins[3]);
    delay(2000);
    press(outputPins[3]);
    delay(2000);
    press(outputPins[4]);
    delay(2000);
    //press(outputPins[5]);
    break;

    case 2: //large lite
    press(outputPins[0]);
    delay(2000);
    press(outputPins[4]);
    delay(2000);
    press(outputPins[4]);
    delay(2000);
    press(outputPins[4]);
    delay(2000);
    press(outputPins[3]);
    delay(2000);
    //press(outputPins[5]);
    break;

    case 3://large dark
    press(outputPins[0]);
    delay(2000);
    press(outputPins[4]);
    delay(2000);
    press(outputPins[4]);
    delay(2000);
    press(outputPins[3]);
    delay(2000);
    press(outputPins[3]);
    delay(2000);
    press(outputPins[4]);
    delay(2000);
    press(outputPins[3]);
    delay(2000);
    //press(outputPins[5]);
    break;

    default:
    break;
  }
}


void sm1_setup() {
  pinMode(b0, INPUT);
  pinMode(b1, INPUT);
  pinMode(b2, INPUT);
  pinMode(b3, INPUT);

  pinMode(b4, INPUT);
  pinMode(b5, INPUT);
  pinMode(b6, INPUT);
  pinMode(b7, INPUT);

  for(int i=0; i<6; i++){
    pinMode(outputPins[i], OUTPUT);
  }
  return;
  state_sm1 = Start;
}


void tick_fct_sm1() {
  switch(state_sm1){ //Transition Action
    case Start:
    state_sm1 = idle;
    break;

    case idle:
    Serial.println("Idle");
    if ((digitalRead(b4) == HIGH) || (digitalRead(b5) == HIGH) || (digitalRead(b6) == HIGH) || (digitalRead(b7) == HIGH)){
      state_sm1 = prime_buttons;
    }
    else if((digitalRead(b0) == HIGH) || (digitalRead(b1) == HIGH) || (digitalRead(b2) == HIGH) || (digitalRead(b3) == HIGH)){
      state_sm1 = selection; 
    }
    else{
      state_sm1 = idle;
    }
    break;

    case prime_buttons:
    Serial.println("Prime");
    if (!(digitalRead(b4) == HIGH) && !(digitalRead(b5) == HIGH) && !(digitalRead(b6) == HIGH) && !(digitalRead(b7)== HIGH)){
      state_sm1 = idle;
    }
    else{
      state_sm1 = prime_buttons;
    }
    break;

    case selection:
    Serial.println("selection");
    state_sm1 = open;
    break;

    case open:
    Serial.println("open");
    state_sm1 = dispense_salt;
    break;

    case dispense_salt:
    Serial.println("salt");
    state_sm1 = dispense_flour;
    break;

    case dispense_flour:
    Serial.println("flour");    
    state_sm1 = dispense_yeast;
    break;

    case dispense_yeast:
    Serial.println("yeast");
    state_sm1 = dispense_sugar;
    break;

    case dispense_sugar:
    Serial.println("sugar");
    state_sm1 = dispense_water;
    break;

    case dispense_water:
    Serial.print("water");
    state_sm1 = dispense_oil;
    break;

    case dispense_oil:
    state_sm1 = close;
    break;

    case close:
    Serial.println("close");
    state_sm1 = done;
    break;

    case done:
    Serial.println("done");
    state_sm1 = done;
    break;

    default:
    break;
  }

   switch(state_sm1){ // State Action
     case Start:
     break;

     case idle:
     break;

     case prime_buttons:
     stepper_priming();
     break;

     case selection:     
     if(digitalRead(b0) == HIGH){
      recipe_selection_fct(0);
      recipe_selected[0] = recipe1[0];
      recipe_selected[1] = recipe1[1];
      recipe_selected[2] = recipe1[2];
      recipe_selected[3] = recipe1[3];
      recipe_selected[4] = recipe1[4];
      recipe_selected[5] = recipe1[5];

      Serial.println("Recipe_Selected = ");
      Serial.print(recipe_selected[0]);
      Serial.print(", ");
      Serial.print(recipe_selected[1]);
      Serial.print(", ");
      Serial.print(recipe_selected[2]);
      Serial.print(", ");
      Serial.print(recipe_selected[3]);
      Serial.println();
     }
     else if(digitalRead(b1) == HIGH){
      recipe_selection_fct(1);
      recipe_selected[0] = recipe2[0];
      recipe_selected[1] = recipe2[1];
      recipe_selected[2] = recipe2[2];
      recipe_selected[3] = recipe2[3];
      recipe_selected[4] = recipe2[4];
      recipe_selected[5] = recipe2[5];
    }
    else if(digitalRead(b2) == HIGH){
      recipe_selection_fct(2);
      recipe_selected[0] = recipe3[0];
      recipe_selected[1] = recipe3[1];
      recipe_selected[2] = recipe3[2];
      recipe_selected[3] = recipe3[3];
      recipe_selected[4] = recipe3[4];
      recipe_selected[5] = recipe3[5];
    }
    else if(digitalRead(b3) == HIGH){
      recipe_selection_fct(3);
      recipe_selected[0] = recipe4[0];
      recipe_selected[1] = recipe4[1];
      recipe_selected[2] = recipe4[2];
      recipe_selected[3] = recipe4[3];
      recipe_selected[4] = recipe4[4];
      recipe_selected[5] = recipe4[5];
    }
    break;

    case open:
    openLid();
    break;

    case dispense_salt:
    stepper_dispense(1, recipe_selected[1]);
    break;

    case dispense_flour:
    stepper_dispense(0, recipe_selected[0]);
    break;

    case dispense_yeast:
    stepper_dispense(3, recipe_selected[3]);
    break;

    case dispense_sugar:
    stepper_dispense(2, recipe_selected[2]);
    break;

    case dispense_water:
    dispense_liquid1(recipe_selected[4]);
    break;

    case dispense_oil:
    dispense_liquid2(recipe_selected[5]);
    break;

    case close:
    closeLid();
    press(outputPins[5]);
    break;

    case done:
    break;

    default:
    break;
  }
}