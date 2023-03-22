#include "lcd_display_functions.h"
#include <LiquidCrystal.h>

extern const int rs = 52; 
extern const int en = 50;
extern const int d4 = 48;
extern const int d5 = 46;
extern const int d6 = 44;
extern const int d7 = 42;

extern int start_time = 0;

LiquidCrystal lcd(rs, en, d4, d5, d6, d7);


void displaySetup() {
  lcd.begin(16,2);
  lcd.print("Hello, World!");
  return;
}

void displayState(char code){      //TEMP TEST ACTION
  lcd.setCursor(0,1);
  lcd.print(millis()/1000);
  return;
}

void startTimer(){
  start_time = millis();
  return;
}

void displayProgress(int time){
  int remaining_time = millis() - start_time;
  int percentage = remaining_time % (time * 1000);
  lcd.setCursor(0,1);
  lcd.print(percentage);
  lcd.print("%");
  return;
}
