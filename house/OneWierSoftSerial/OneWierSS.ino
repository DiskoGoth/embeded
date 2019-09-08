#include <SoftwareSerial.h>

#define PORT 10
#define ISMASTER true

void setup() {
    //Start the PC serial connection
    Serial.begin(4800);
    Serial.println(ISMASTER ? "Master" : "Slave");
    pinMode(13, OUTPUT);
}

void loop() {
    if (ISMASTER) {
        // Master Test Code
        // This code starts by sending data out on the bus
        // It is assumed that the slave will respond immediatly, so the
        // master listens for one second for this data before sending more data
        send("abra"); 
        digitalWrite(13, HIGH);
        recieverRunMaster();
        digitalWrite(13, LOW);
    } else {
        // Slave Test Code
        // This code starts by listening for a transmission
        // And it will only respond after it recieves a message
        // If the message is larger than one char, change the recieve
        // condition to match the new message characteristic
        digitalWrite(13, HIGH);
        recieverRunSlave();
        digitalWrite(13, LOW);
        send("cadabra");
    }
}

void send(String message) {
    // Setup the sending system with TX as pin 11, and RX as a throwaway pin 30
    SoftwareSerial mySerial(30,PORT);
    mySerial.begin(4800);
    // A quick delay to make sure the reciever is ready
    delay(1);
    // Send the data and indicate that on the PC serial bus
    mySerial.print(message);
    // The serial terminal will end here as it goes out of scope and the destructor is called
}

void recieverRunMaster() {
    //Setup the recieving serial connection with RX as pin 11 and TX as a throwaway pin 30
    SoftwareSerial mySerial(PORT,30);
    mySerial.begin(4800);
    //For one second print any recieved data to the PC terminal
    long time = millis();
    Serial.print("Master: rec - ");
    while (millis() - time < 1000) {
        if (mySerial.available()) {
            Serial.write((char)mySerial.read());
        }
    }
    Serial.println("");
    //The recieving connection will close as it goes out of scope and the destructor is called
}

void recieverRunSlave() {
    // Set up the recieving system with RX as pin 11 and TX as a throwaway pin 30
    SoftwareSerial mySerial(PORT,30);
    mySerial.begin(4800);
    boolean recieved = false;
    // Wait for data to be recieved and if it is print it and move on

    while (!recieved) {
        while (mySerial.available()) {
            Serial.print("Slave: rec - ");
            Serial.write((char)mySerial.read());
            recieved = true;
        }
    }
    Serial.println("");
    // The serial terminal will end here as it goes out of scope and the destructor is called
}

