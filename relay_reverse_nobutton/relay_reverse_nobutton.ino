#include <NewPing.h>

// Arduino being used because I'm sick of the Bachmann system, maybe Dallee too. And it's cheaper than both
// ---------------------------------------------------------------------------

#include <NewPing.h>

#define TRIGGER_PIN  7  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN     8  // Arduino pin tied to echo pin on the ultrasonic sensor.
#define MAX_DISTANCE 75 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // NewPing setup of pins and maximum distance.
int previous_direction;
int present_direction;
boolean change_direction;
int count_of_max_range_tries;
char text_direction ;

// variables will change:

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pins 11-13 as an output.
  pinMode(5, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(3, OUTPUT);
  digitalWrite(3, LOW);   // turn the TRACK POWER off (LOW is the voltage level)
  digitalWrite(4, LOW);   // turn the relay OFF (LOW is the voltage level)
  digitalWrite(5, LOW);   // turn the relay OFF (LOW is the voltage level)

  Serial.begin(115200); // Open serial monitor at 115200 baud to see ping results.
}

// the loop function runs over and over again forever
void loop() {
  int reading;
    
    // turn TRAIN on:
  
      delay(150);                     // Wait *ms between pings (about 20 pings/sec). 29ms should be the shortest delay between pings.

      reading = sonar.ping_cm(); //get the reading
      Serial.print("Ping: ");
      Serial.print(reading); // Send ping, get distance in cm and print result (0 == outside set distance range)
      Serial.print("cm");

      // change direction by boolean value and a second boolean value indicating a change has been made!
      
      if (reading > 45 || reading ==0){
        count_of_max_range_tries = count_of_max_range_tries + 1;
        if (count_of_max_range_tries == 10) {
           present_direction = 1; 
           text_direction = 'FORWARD';
           count_of_max_range_tries = 1;
          }
        }
       
       if (reading < 19) {
        present_direction = 2; 
        text_direction = 'REVERSE';
       }

       change_direction = false;
       if (present_direction != previous_direction) {
        change_direction = true;
       }

       if (change_direction == true){
        Serial.print("CHANGE OF DIRECTION: ");
        Serial.println(text_direction); // print result (0 == outside set distance range)

        if (present_direction == 1){
          digitalWrite(3, HIGH);   // turn the TRACK POWER off (LOW is the voltage level)
          digitalWrite(5, LOW);   // turn the relay on (LOW is the voltage level)
          digitalWrite(4, LOW);   // turn the relay on (LOW is the voltage level)
          delay(2000);
          digitalWrite(3, LOW);   // turn the TRACK POWER on (LOW is the voltage level)
        }  else {
          digitalWrite(3, HIGH);   // turn the TRACK POWER off (LOW is the voltage level)
          digitalWrite(4, HIGH);   // turn the relay off 
          digitalWrite(5, HIGH);    // turn the relay off by making the voltage HIGH
          delay(2000);
          digitalWrite(3, LOW);   // turn the TRACK POWER on (LOW is the voltage level)
        }
       }

           change_direction = false;   // no change
           previous_direction = present_direction;  // save for comparision

}
