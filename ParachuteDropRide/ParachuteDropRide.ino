/*
  Parachute Drop Ride - Are the chutes all the way DOWN? If so, allow it to turn OFF if so desired

  Turns on and off a RELAY connected to digital pin 13,
  when checking a REED SWITCH attached to pin 2.

  The circuit:
  - RELAY attached from pin 13 to ground
  - REED SWITCH attached to pin 2 from +5V
  - 10K resistor attached to pin 2 from ground

  - Note: on most Arduinos there is already an LED on the board
    attached to pin 13.
*/

const int reedSwitchPin = 2;     // the number of the pushbutton pin
const int relayPin =  13;      // the number of the LED pin
const int buttonPin =  10;      // the number of the LED pin

// variables will change:
int sensorState = 0;         // variable for reading the REED SWITCH status
int buttonState = 0;
bool bMotorInMotion = false;

void setup() {
  // initialize the RELAY pin as an output:
  pinMode(relayPin, OUTPUT);
  // initialize the REED SWITCH pin as an input:
  pinMode(reedSwitchPin, INPUT);
  // initialize the pushbutton pin as an input:
  pinMode(buttonPin, INPUT);
}

void loop() {
  // read the state of the pushbutton value:
  buttonState = digitalRead(buttonPin);

    // check if the button is pressed. If it is, the sensorState is HIGH:
    if (buttonState == HIGH and bMotorInMotion == false) {
      digitalWrite(relayPin, LOW);   //start motor
      bMotorInMotion = true;
      delay(2000);  // wait to clear magnet range
      }
    
  sensorState = digitalRead(reedSwitchPin);

    if (sensorState == HIGH) {
      digitalWrite(relayPin, HIGH);   //stop motor
      bMotorInMotion = false;
      }
    
}




