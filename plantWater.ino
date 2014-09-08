#include <JeeLib.h>
#include <EEPROM.h>
                                                

int waterCount;
int moistureThreshold;
int moistureTesterOnTime;
int pumpOnTime;
int allTimeWaterEvents;

ISR(WDT_vect) { Sleepy::watchdogEvent(); }                               
 
int moisturePin = 0;
                                                                        
void setup() {

                                           
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);

  waterCount = 0;
  moistureThreshold = 700;
  moistureTesterOnTime = 50;
  pumpOnTime = 5000;
  allTimeWaterEvents = EEPROM.read(0);
  
  Serial.begin(19200);                                              
  Serial.println("\r\nStarting..\n");
  digitalWrite(5, HIGH);                                                 
  delay(500);
  digitalWrite(5, LOW);                                                 
  delay(500);
  digitalWrite(5, HIGH);                                                 
  delay(500);
  digitalWrite(5, LOW);                                                 
  delay(500);
  digitalWrite(5, HIGH);                                                 
  delay(500);
  digitalWrite(5, LOW);                                                  
      
}

                                                     
void loop() {
  int val;

  digitalWrite(6, HIGH);                           
  delay(moistureTesterOnTime);                                  
  val = analogRead(moisturePin);                         
  digitalWrite(6, LOW);  

  Serial.print(moistureThreshold);
  Serial.print(" is the threshold, actual value is ");
  Serial.print(val);                           
  Serial.print(" total watering events ");
  Serial.print(waterCount);
  Serial.print(" , all time events - ");
  Serial.print(allTimeWaterEvents);
  
  Serial.println(".");
                                       
  delay(10);
                 
  if(val > 200) {
    
    if(val < moistureThreshold) {
      digitalWrite(5, HIGH);                                                 
      waterCount++;
      allTimeWaterEvents++;
      EEPROM.write(0, allTimeWaterEvents);
      // Hold the pump on
      delay(pumpOnTime);
      digitalWrite(5, LOW);                                                 
    } else {
      digitalWrite(5, LOW);                                                 

    }
  }

  delay(50);                                 
  Sleepy::loseSomeTime(1000*3600);
                                       
}

