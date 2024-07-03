int data; //Initialized variable to store recieved data
int buzzer = 12;
int red =  11;
int yellow =  10;
int green = 9;
int grey = 8;
int pause = 5; // 5 ms is the shortest delay that can be used  effectively​
int button = 13;
uint8_t segmentPins[6] = {2, 3, 4, 5, 6, 7};
uint8_t segment[4][6] = {{LOW, LOW, LOW, LOW, LOW, LOW}, // Turns Display off - Calling number 0
                        {HIGH, LOW, LOW, LOW, LOW, HIGH }, // Print 1 Calling number 1
                        {HIGH, HIGH, HIGH, HIGH, HIGH, LOW }, // Prints 2 Calling number 2
                        {HIGH, HIGH, HIGH, HIGH, LOW, HIGH }}; // Prints 3 Calling number 3


uint8_t wireColours[4] = {red, yellow, green, grey};
uint8_t movement[4][4] = {{LOW, HIGH, HIGH, LOW},
                        {LOW, HIGH, LOW, HIGH},
                        {HIGH, LOW, LOW, HIGH},
                        {HIGH, LOW, HIGH, HIGH}};







template<size_t size>
void digitalWrite(const uint8_t (&pin)[size], const uint8_t (&val)[size]) {
    for (size_t i = 0; i < size; ++i) {
        digitalWrite(pin[i], val[i]); } }


void setup() {
Serial.begin(9600); //Serial Begin at 9600 Baud  -- THIS IS ESSENTIAL FOR THE I2C INTERFACE
pinMode(13, OUTPUT);  // Sets the Buzzer as an Output Device
pinMode(button, INPUT);  // Set the button as an Inptu Device

for(int i = 2; i<12; i++) {    // Starts a loop where it defines all pins between 2 & 12 as an output.
  pinMode(i, OUTPUT); }
}

void loop() { 
data = Serial.read(); //Read the serial data and store it
delay(250); // Controls the "Polling rate" of the sensor. Should not be below 250

  //############################ 7 Seg Code ################
      if (digitalRead(button) == HIGH){ 
         digitalWrite(segmentPins, segment[3]); // print 3
         delay(1000);
         digitalWrite(segmentPins, segment[2]); // print 2
         delay(1000);
         digitalWrite(segmentPins, segment[1]); // print 1
         delay(1000);
         digitalWrite(segmentPins, segment[0]); // Turns off Display
          }
  //#####################################################

  
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
  //#####################################################

  //############################ MOTOR Code ################
  for(int i = 0; i<30; i++) {
         digitalWrite(wireColours, movement[0]);
         delay(pause);
         digitalWrite(wireColours, movement[1]);
         delay(pause);
         digitalWrite(wireColours, movement[2]);
         delay(pause);
         digitalWrite(wireColours, movement[3]);
         delay(pause);
       }
    //#####################################################
   }

else if (data != 123) { // Else If motion is NOT detected, Run this code:
  Serial.println("No Motion Detected");  // Debug for Console
}
}
