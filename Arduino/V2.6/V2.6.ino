int data;    // Variable to store "secretcode" (123) from ESP8622, lets the Arduino know when to trigger.
const int red =  11;    //  ################################################################################
const int yellow =  10; //  ################################################################################
const int green = 9;    //                    Could be replaced straight with pin numbers
const int grey = 8;     //  ##################        but becomes less readable.   #########################
const int buzzer = 12;  //  ################################################################################
const int button = 13;  //  ################################################################################
uint8_t segmentPins[6] = {2, 3, 4, 5, 6, 7};  // Defines the array of pins used in the segment. 
uint8_t segment[4][6] = {{LOW, LOW, LOW, LOW, LOW, LOW}, // Turns Display off - Calling number 0
                        {HIGH, LOW, LOW, LOW, LOW, HIGH }, // Print 1 Calling number 1
                        {HIGH, HIGH, HIGH, HIGH, HIGH, LOW }, // Prints 2 Calling number 2
                        {HIGH, HIGH, HIGH, HIGH, LOW, HIGH }}; // Prints 3 Calling number 3               
uint8_t wireColours[4] = {red, yellow, green, grey};  // Defines the varables used in for the motors, Could be replaced straight with pin numbers, but becomes less readable.
uint8_t movement[4][4] = {{LOW, HIGH, HIGH, LOW},     //state 1: (1.8 deg) - (red. yellow. green. grey - 0110 )​
                        {LOW, HIGH, LOW, HIGH},       //state 2: (3.6 deg) - (red. yellow. green. grey - 0101 )​
                        {HIGH, LOW, LOW, HIGH},       //state 3: (5.4 deg) - (red. yellow. green. grey - 1001 )​
                        {HIGH, LOW, HIGH, LOW}};     //state 4: (7.2 deg) - (red. yellow. green. grey - 1010 )​
                        
template<size_t size>       // Effectively turns a digitalWrite command into a for loop, allows for a single digitalWrite command to run multiple times.
void digitalWrite(const uint8_t (&pin)[size], const uint8_t (&val)[size]) { // Re-Writes how digitalWrite works.
    for (size_t i = 0; i < size; ++i) { // runs until size_t is equal to size, both are derived from the arrays, so if an array is [4] [4] the size_t value would go up to 4, allowing for digitalWrites to be ran multiple times. 
        digitalWrite(pin[i], val[i]); } } // Takes the pin & value (High/Low) from 'i', used for the arrays

void setup() {
Serial.begin(9600); //Serial Begin at 9600 Baud  -- THIS IS ESSENTIAL FOR THE I2C INTERFACE
pinMode(button, INPUT);  // Set the button as an Input Device
for(int i = 2; i<12; i++) {    // Starts a loop where it defines all pins between 2 & 12 as an output.
  pinMode(i, OUTPUT); }
pinMode(buzzer, OUTPUT); // Sets buzzer as an Output Device
}
void beeper() {  // Declares a "beeper" function, allows for the buzzer to be used in serveral applications, without being re-written.
  Serial.println("buzzer Activated"); // Mostly used for Debug
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
  }

void loop() { 
  data = Serial.read(); //Read the serial data and store it
  delay(250); // Controls the "Polling rate" of the sensor. Should not be below 250
if (digitalRead(button) == HIGH){  // Checks to see if Button (Pin 13) has been pressed.
    digitalWrite(segmentPins, segment[3]); // print 3
    delay(1000);
    digitalWrite(segmentPins, segment[2]); // print 2
    delay(1000);
    digitalWrite(segmentPins, segment[1]); // print 1
    delay(1000);
    digitalWrite(segmentPins, segment[0]); // Turns off Display
    beeper();  // calls the beeper function
  }
    
if (data == 123) { // If motion is detected, Run this code:
  Serial.println("Motion Detected");  // Debug for Console
  beeper(); // calls the beeper function
for(int i = 0; i<30; i++) {  // Starts a loop - will continue until 'i' has counted to 30. At which point it will end task.
   digitalWrite(wireColours, movement[0]);   // Writes the Array code, to the motor, first 1.8Degrees.
   delay(5);                                 // 5 ms is the shortest delay that can be used  effectively​
   digitalWrite(wireColours, movement[1]);   // Writes the Array code, to the motor, 3.8Degrees.
   delay(5);
   digitalWrite(wireColours, movement[2]);   // Writes the Array code, to the motor, 5.4Degrees.
   delay(5);
   digitalWrite(wireColours, movement[3]);   // Writes the Array code, to the motor, 7.2Degrees.
   delay(5); 
  }
}
else if (data != 123) { // Else If motion is NOT detected, Run this code:
    Serial.println("No Motion Detected");  // Debug for Console
  }
}
