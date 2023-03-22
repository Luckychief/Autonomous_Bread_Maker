#ifndef LCD_DISPLAY_FUNCTIONS_H
#define LCD_DISPLAY_FUNCTIONS_H

#include <Arduino.h>

extern const int rs; //declaring all the 7 GPIO pins needed for lcd
extern const int en;
extern const int d4;
extern const int d5;
extern const int d6;
extern const int d7;

extern int start_time; //recording the time at which the bread maker started making the food

//Note there are no string data types within arduino
//If you want to declare what would be considered as a string follow example bellow
// char my_string[] = "Write Message Here"
// data_type - variable_name = "string content"


void displaySetup(); //Initializes GPIOs

void displayState(char code); // used to update the user about the device

void startTimer();

void displayProgress(int time); //time variable is the time in seconds for the bread maker to finish baking
                                //progress will be displayed by a value of 0-100
                   

#endif