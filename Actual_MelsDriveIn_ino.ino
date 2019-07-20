 const int RELAY13 = 13; //the pin for the RELAY13 - DPDT double pole, double throw
const int RELAY12 = 12; //the pin for the RELAY12 - DPDT
const int RELAY11 = 11; //the pin for the RELAY11 - DPDT
const int RELAY10 = 10; //the pin for the RELAY10 - DPDT
const int RELAY9 = 9; //the pin for the RELAY 9- SPST single pole, single throw
const int RELAY8 = 8; //the pin for the RELAY 8- SPST
const int RELAY7 = 7; //the pin for the RELAY 7- SPST
const int RELAY6 = 6; //the pin for the RELAY 6- SPST

const int BUTTON1 = 2; // input pin
const int CAR_LIMIT_FWD = 5;  // trips when car is all the way forward, at the waitress
const int CAR_LIMIT_BACK  = A2;  // trips when car is all the way back, behind the restaurant

int Butn1ReturnValue = 0;  // store button return value
int val =0; // val will be used to store the state of the input pin
int old_val =0; // this variable stores the previous value of val
int state = 0; // 0= RELAY13 off and 1= RELAY13 on
int SENSORval = 0;  // reads car fwd/back sensors

// time limit for moving car 3 seconds
const int CAR_MSECONDS = 3000; // seconds in milliseconds
int CAR_COUNT_MSECONDS = 0;

void setup() {
  pinMode(RELAY13, OUTPUT);  // tell arduino RELAY13 is an output
  pinMode(RELAY12, OUTPUT);  // tell arduino RELAY13 is an output
  pinMode(RELAY11, OUTPUT);  // tell arduino RELAY13 is an output
  pinMode(RELAY10, OUTPUT);  // tell arduino RELAY13 is an output
  pinMode(RELAY9, OUTPUT);  // tell arduino RELAY 13 is an output
  pinMode(RELAY8, OUTPUT);  // tell arduino RELAY 13 is an output
  pinMode(RELAY7, OUTPUT);  // tell arduino RELAY 13 is an output
  pinMode(RELAY6, OUTPUT);  // tell arduino RELAY 6 is an output

  pinMode(BUTTON1, INPUT);  // AND button  IS AN INPUT
  pinMode(CAR_LIMIT_FWD, INPUT);  // AND button  IS AN INPUT
//  pinMode(CAR_LIMIT_BACK, INPUT);  // AND button  IS AN INPUT removed due to now being used as an ANALOG input
}
void loop(){

    val = digitalRead(BUTTON1); // read input value and store it
    Butn1ReturnValue = val;
 // check if there was a transition
  if ((val == HIGH) ){
    state = 1;
    delay(10);
  }
  
  old_val = val; // val is now old, lets store it
//   delay(100);
  
  if (state == 1) {
    //car
    digitalWrite(RELAY13, HIGH); // turn RELAY1 ON- sets car direction FORWARD
    digitalWrite(RELAY9, HIGH); // turn RELAY ON- turns power on/off- car in motion
    
    SENSORval=0;
    while((SENSORval != HIGH) && (CAR_COUNT_MSECONDS < CAR_MSECONDS)){
          SENSORval = digitalRead(CAR_LIMIT_FWD); // read input value and store it
          delay(10);
          CAR_COUNT_MSECONDS += 10; 

       // wait until fwd switch/sensor is tripped
     }
    
    CAR_COUNT_MSECONDS = 0; 

    digitalWrite(RELAY9, LOW); // turn RELAY OFF- turns power on/off- car stops
    
    //girl
    digitalWrite(RELAY12, HIGH); // turn RELAY ON ' girl out (tortoise turns itself off)
    delay(3000);
     digitalWrite(RELAY12, LOW); // turn RELAY OFF ' girl in (tortoise turns itself off)
    delay(3000);
    digitalWrite(RELAY12, HIGH); // turn RELAY ON ' girl out (tortoise turns itself off)
    delay(2000) ;
    
    //car
    digitalWrite(RELAY13, LOW); // turn RELAY13 ON- sets car direction- REVERSE
    digitalWrite(RELAY9, HIGH); // turn RELAY ON- turns power on/off
    
    SENSORval=0;
    while((SENSORval <900) && (CAR_COUNT_MSECONDS < CAR_MSECONDS)){
          SENSORval = analogRead(CAR_LIMIT_BACK); // read input value and store it
          delay(10);
          CAR_COUNT_MSECONDS += 10; 

       // wait until back switch/sensor is tripped
     }
     CAR_COUNT_MSECONDS = 0; 
    
     digitalWrite(RELAY9, LOW); // turn RELAY ON- turns power on/off
    
    //girl
   /// digitalWrite(RELAY12, LOW); // turn RELAY OFF ' girl in (tortoise turns itself off)
    delay(1000);
    
    
  } else {
  }
  state = 0;  // event over
}
