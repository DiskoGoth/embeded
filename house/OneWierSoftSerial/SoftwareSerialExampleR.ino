// Slave Test Code
// This code starts by listening for a transmission
// And it will only respond after it recieves a message
// If the message is larger than one char, change the recieve 
// condition to match the new message characteristic
#include <SoftwareSerial.h>

void setup()  
{
  //Setup the normal serial link to the PC
  Serial.begin(4800);
  Serial.println("Slave System");
  //LED to indicate when recieving
  pinMode(13, OUTPUT);
}

void loop() 
{
  digitalWrite(13, HIGH);
  recieverRunSlave();
  digitalWrite(13, LOW);
  senderRunSlave();
}

void senderRunSlave(){
  // Setup the sending system with TX as pin 11, and RX as a throwaway pin 30
  SoftwareSerial mySerial(30,11);
  mySerial.begin(4800);
  // A quick delay to make sure the reciever is ready
  delay(1);
  // Send the data and indicate that on the PC serial bus
  mySerial.print("abcde");
  Serial.println("abcde sent");
  
  // The serial terminal will end here as it goes out of scope and the destructor is called
}

void recieverRunSlave(){
  // Set up the recieving system with RX as pin 11 and TX as a throwaway pin 30
  SoftwareSerial mySerial(11,30);
  mySerial.begin(4800);
  boolean recieved = false;
  // Wait for data to be recieved and if it is print it and move on
  while (!recieved){
    if(mySerial.available()){
      Serial.print("rec - ");
      Serial.write(mySerial.read());
      recieved = true;
      Serial.println("");
    }
  }
  
  // The serial terminal will end here as it goes out of scope and the destructor is called
}


