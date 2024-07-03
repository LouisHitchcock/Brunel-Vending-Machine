int data; //Initialized variable to store recieved data
int buzzer = 13;

void setup() {
Serial.begin(9600); //Serial Begin at 9600 Baud
pinMode(13, OUTPUT);  // Sets the Buzzer as an Output Device
}

void loop() {
data = Serial.read(); //Read the serial data and store it
delay(1000); // Controls the "Polling rate" of the sensor. Should not be below 250


if (data == 123) { // If motion is detected, Run this code:
  Serial.println("Motion Detected");  // Debug for Console

  //############################ BUZZER Code ################
  digitalWrite(buzzer, HIGH);   // turn the Buzzer on (HIGH is the voltage level)
  delay(200);
  digitalWrite(buzzer, LOW);    // turn the Buzzer off by making the voltage LOW
  delay(100);  
  digitalWrite(buzzer, HIGH);   // turn the Buzzer on (HIGH is the voltage level)
  delay(200);  
  digitalWrite(buzzer, LOW);    // turn the Buzzer off by making the voltage LOW
  delay(100);
  digitalWrite(buzzer, HIGH);   // turn the Buzzer on (HIGH is the voltage level)
  delay(400);  
  digitalWrite(buzzer, LOW);    // turn the Buzzer off by making the voltage LOW
  delay(100);
  //######################################################
}
else if (data != 123) { // Else If motion is NOT detected, Run this code:
  Serial.println("No Motion Detected");  // Debug for Console
  
}
}
