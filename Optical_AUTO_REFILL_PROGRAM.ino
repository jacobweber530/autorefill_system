/*
  Analog input, analog output, serial output

 Reads an analog input pin, maps the result to a range from 0 to 255
 and uses the result to set the pulsewidth modulation (PWM) of an output pin.
 Also prints the results to the serial monitor.

 The circuit:
 * potentiometer connected to analog pin 0.
   Center pin of the potentiometer goes to the analog pin.
   side pins of the potentiometer go to +5V and ground
 * LED connected from digital pin 9 to ground

 created 29 Dec. 2008
 modified 9 Apr 2012
 by Tom Igoe

 This example code is in the public domain.

 */

// These constants won't change.  They're used to give names
// to the pins used:

// const int analogOutPin = 9;  Analog output pin that the LED is attached to

//constants//////////////////

const int Shigh = A0;  // Analog input pin for water sensor
const int Slow = A1;  // Analog input pin for water sensor

int relayPin1 = 13;         // IN1 connected to digital pin 12
int switchPin = 11;         // number of manual switch pin
////////////////////////////


//variables//////////////////
int LowSensor = LOW;        // value read from the pot
int HighSensor = LOW;        // value read from the pot
int Mswitch = 0;            // switch status
boolean laston = false;             // recent autofill 
int timer = 0;           
/////////////////////////////

void setup() {
  // initialize serial communications at 9600 bps:
  Serial.begin(9600);
  pinMode(relayPin1, OUTPUT);      // sets the digital pin as output
  pinMode(switchPin, INPUT);       // sets digital pin to take switch input
  digitalWrite(relayPin1, HIGH);        // Prevents relays from starting up engaged
  
}

void loop() {
  // Old Code------------------------------------------
  // read the analog in value:
  // sensorValue = analogRead(analogInPin);
  // map it to the range of the analog out:
  // outputValue = map(sensorValue, 0, 1023, 0, 255);
  // height = map(sensorValue, 575, 720, 12, 42);
  // change the analog out value:
  //  analogWrite(analogOutPin, outputValue);
  //---------------------------------------------------

  

// Check Manual switch input
Mswitch = digitalRead(switchPin);



// If Manual switch is on run manually***********************************************
  if (Mswitch == HIGH){
              Serial.println ("Manual mode on");
              digitalWrite(relayPin1, LOW); // Send power to the solenoid
               
  }
//***********************************************************************************


// If Manual switch is off then run automatically///////////////////////////////////
  else {
//      laston = false;
      // Check water level///////////////
      LowSensor = analogRead(Slow); // Read the water sensor value
              // print the results to the serial monitor:
              Serial.print("Low Sensor = " );
              Serial.print(LowSensor);
              Serial.print("\t High Sensor = ");
              Serial.println(HighSensor);
      ///////////////////////////////////

  // If the water level is too low
  if (LowSensor == LOW){
    //Start autofill
    do {
      //Check if manual switch is on**********************
      Mswitch = digitalRead(switchPin);
          // If Manual switch is on, override the autofill
          if (Mswitch == HIGH){
              Serial.println ("Manual mode on");
              break;
          }
      //***************************************************
          
          //Otherwise continue autofilling
          else{
              Serial.println ("autofilling");
                     // Check water level///////////////
                    HighSensor = analogRead(Shigh); // Read the water sensor value
                    ////////////////////////////////////
              digitalWrite(relayPin1, LOW); // Send power to the solenoid
             
          }
          Serial.print("\t High Sensor = ");
              Serial.println(HighSensor);
      } while (HighSensor == LOW); // Auto fill until water level reach maximum height
      
      delay(300);
      
  digitalWrite(relayPin1, HIGH); // Turn solenoid off
  }
   // Otherwise turn Solenoid off 
  else
  {
    digitalWrite(relayPin1, HIGH);
    
  }
/////////////////////////////////////////////////////////////////
 
   
  delay(500); // normal system delay
  }
}

