// Master Test Code
// This code starts by sending data out on the bus
// It is assumed that the slave will respond immediatly, so the
// master listens for one second for this data before sending more data
#include <SoftwareSerial.h>

void setup()  
{
  //Start the PC serial connection
  Serial.begin(4800);
  Serial.println("Master System");
  pinMode(13, OUTPUT);
}

void loop() 
{
  senderRunMaster(); 
  digitalWrite(13, HIGH);
  recieverRunMaster();
  digitalWrite(13, LOW);
}

void senderRunMaster(){
  //Setup the sending serial connection with TX as pin 11 and RX as a throwaway pin 30
  SoftwareSerial mySerial(30,11);
  mySerial.begin(4800);
  //Send the character and alert the user it was sent
  mySerial.print("a");
  Serial.println("a Sent");
  
  //The sending connection will close as it goes out of scope and the destructor is called
}

void recieverRunMaster(){
  //Setup the recieving serial connection with RX as pin 11 and TX as a throwaway pin 30
  SoftwareSerial mySerial(11,10);
  mySerial.begin(4800);
  //For one second print any recieved data to the PC terminal
  long time = millis();
  Serial.print("rec - ");
  while ( millis() - time < 1000){
    if(mySerial.available()){
      Serial.write(mySerial.read());
    }
  }
  Serial.println("");
  //The recieving connection will close as it goes out of scope and the destructor is called
}

