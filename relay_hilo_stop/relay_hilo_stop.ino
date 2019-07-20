
// Arduino being used instead of Altronix 6062 due to need to have TWO times (one on, one off)
// ---------------------------------------------------------------------------

// the setup function runs once when you press reset or power the board
    int i;


void setup() {
  // initialize digital pin 3 as an output.
  pinMode(3, OUTPUT);

}

// the loop function runs over and over again forever
void loop() {
    
    // turn STATION SECTION on:
  
          digitalWrite(3, HIGH);   // turn the TRACK POWER off (LOW is the voltage level)
          delay(5000); // # of seconds to leave the section
          digitalWrite(3, LOW);   // turn the TRACK POWER on (LOW is the voltage level)

      // 3 minute hold
          for (i=0; i <= 120; i++){
          delay(1000); // # of seconds to HOLD
            }
          
          
}
