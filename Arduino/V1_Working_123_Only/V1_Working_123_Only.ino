int data; //Initialized variable to store recieved data
void setup() {
Serial.begin(9600); //Serial Begin at 9600 Baud
}
void loop() {
data = Serial.read(); //Read the serial data and store it
delay(1000);
Serial.println(data); //prints the stored value in ‘data’ to the serial monitor
}
