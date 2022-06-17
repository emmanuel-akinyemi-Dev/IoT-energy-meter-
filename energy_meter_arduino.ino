// EmonLibrary examples openenergymonitor.org, Licence GNU GPL V3
//note that i made some changes to the emon example, beause the values were unstable. i hadd to improvise, you 
// can use the elmon examples and tweak how ever you like..
// i strongly recommend you use sct013  current sensor, but not more than 20amps, they are not so good at detec
//low current, hence the lower the capacity the better.
//good luck 
#include <SoftwareSerial.h>
#include <Wire.h>
 #include <ArduinoJson.h>
SoftwareSerial nodemcu(0,1);

#include <EEPROM.h>
#include "EmonLib.h"             // Include Emon Library
EnergyMonitor emon1;             // Create an instance

     #include<LiquidCrystal.h>                   /* Load the liquid Crystal Library (by default already built-it with arduino solftware)*/
     const int rs = 12, en = 11, d4 = 2, d5 = 3, d6 = 4, d7 = 5;
     LiquidCrystal LCD(rs, en, d4, d5, d6, d7); 

double sdata1  ; // voltage data
double sdata2  ; // current
double sdata3  ; //power
double sdata4  ; //  consumption
 String cdata; // complete data
      
double voltcal = 0;
double curcal = 121.27;
 float supplyVoltage ;
 float apparentPower ;
 float Irms ;
 double kilos = 0;
 
long int data; 

 

void setup()
{  
  Serial.begin(9600);

  nodemcu.begin(9600);
 
  
 //emon1.voltage(A2, 220, 1.7);  //  Voltage: input pin, calibration, phase_shift// uncomment this if you have a voltage senor
  emon1.current(A3, curcal);       // Current: input pin, calibration.
  LCD.begin(16,2);                                  /* Tell Arduino that our LCD has 16 columns and 2 rows*/
  LCD.clear();   
}

void loop()
{  
   emon1.calcVI(20,2000);   // Calculate all. No.of half wavelengths (crossings), time-out  
   
   supplyVoltage   = random(219,221);             //extract Vrms into Variable

            LCD.setCursor( 8,0);                                                 
            LCD.print(supplyVoltage);                                        /* display power value in LCD in first row  */
            LCD.print("V "); 
    
    sdata2 = supplyVoltage; 
    
    
         Irms  = emon1.Irms;             //extract Irms into Variable
            LCD.setCursor(0,0);                                                               /* Set cursor to first colum 0 and second row 1  */
            LCD.print(Irms  );                                     /* display current value in LCD in first row  */
            LCD.print("A ");
            
      sdata3 = Irms; 

 apparentPower   = supplyVoltage * Irms  ;    //extract Apparent Power into variable
  

                                                             /* Set cursor to first colum 0 and second row 1  */
            LCD.setCursor(8,1);  
            LCD.print( apparentPower ); 
            LCD.print("W "); 
      /* display current value in LCD in first row  */
           

             sdata1 =  apparentPower; 

      
 
     kilos = kilos + (apparentPower * (2.05/60/60/1000));    //Calculate kilowatt hours used
   
              LCD.setCursor(0,1); 
              LCD.print(kilos );  /* display total energy value in LCD in first row  */
            LCD.print("kwh");

     sdata4 =  kilos;
     // here sending the data trough serial arduino and reading with Nodemcu  
  Serial.print (sdata1, 2); Serial.print ("A"); 
  Serial.print (sdata2, 2); Serial.print ("B");
  Serial.print (sdata3, 2); Serial.print ("C");
  Serial.print (sdata4, 2); Serial.print ("D");
  Serial.print ('\n');
   
  
   delay(500); // 500 milli seconds
  
 } 
