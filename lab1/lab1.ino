#include <Arduino.h>
#include <MD_TCS230.h>

/*
#define  S0_OUT  2
#define  S1_OUT  3
#define  S2_OUT  4
#define  S3_OUT  5
*/
#define R_OUT 6
#define G_OUT 7
#define B_OUT 8

#include "pitches.h"
#include "button.h"
#include "buzzer.h"

#define PIN_1_BUTTON 5
#define PIN_2_BUTTON 4
#define PIN_3_BUTTON 3

Button button1(PIN_1_BUTTON);
Button button2(PIN_2_BUTTON);
Button button3(PIN_3_BUTTON);

bool is_out_r = false;
int old_r = 255;
bool is_out_g = false;
int old_g = 255;
bool is_out_b = false;
int old_b = 255;
 
void setup()
{
    Serial.begin(9600);
    pinMode(R_OUT, OUTPUT);
    pinMode(G_OUT, OUTPUT);
    pinMode(B_OUT, OUTPUT);
}

void loop() 
{ 

    if (button1.wasPressed())
    {
       if (!is_out_r)
       {
         analogWrite(R_OUT, 255);
         is_out_r = true; 
         Serial.println("was pressed"); 
       }
       else
       {
         analogWrite(R_OUT, 255 - old_r);
         is_out_r = false; 
         Serial.println("was pressed kek");
         Serial.println(old_r);
       }
    }

    if (button2.wasPressed())
    {
       if (!is_out_g)
       {
         analogWrite(G_OUT, 255);
         is_out_g = true; 
         Serial.println("was pressed"); 
       }
       else
       {
         analogWrite(G_OUT, 255 - old_g);
         is_out_g = false; 
         Serial.println("was pressed kek");
       }
    }

    if (button3.wasPressed())
    {
       if (!is_out_b)
       {
         analogWrite(B_OUT, 255);
         is_out_b = true; 
         Serial.println("was pressed"); 
       }
       else
       {
         analogWrite(B_OUT, 255 - old_b);
         is_out_b = false; 
         Serial.println("was pressed kek");
       }
    }
    
    while (Serial.available() > 0)
  {
    String data = Serial.readString();
    char charBufVar[20];
    data.toCharArray(charBufVar, 20);
    char * pch;
    pch = strtok (charBufVar," ");
    Serial.println(data.substring(0, data.indexOf(" ")));
    old_r = data.substring(0, data.indexOf(" ")).toInt();
    Serial.println(data.substring(data.indexOf(" ") + 1, data.lastIndexOf(" ")));
    old_g = data.substring(data.indexOf(" ") + 1, data.lastIndexOf(" ")).toInt();
    Serial.println(data.substring(data.lastIndexOf(" ") + 1));
    old_b = data.substring(data.lastIndexOf(" ") + 1).toInt();
    // устанавливаем яркость светодиода
    
    analogWrite(R_OUT, 255 - old_r);
    analogWrite(G_OUT, 255 - old_g);
    analogWrite(B_OUT, 255 - old_b);
    
  }
}
