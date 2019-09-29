#include <SoftwareSerial.h>

#define PORT 10
#define ISMASTER_PIN 12
#define STATUS_PIN 13

#define MASTER_RECIEVE_TIME 1000
#define SS_SPEED 4800
#define SS_DELAY 1

bool isMaster = false;

void setup() {
    //Start the PC serial connection
    Serial.begin(9600);
    pinMode(ISMASTER_PIN, INPUT);
    isMaster = digitalRead(ISMASTER_PIN);
    Serial.println(isMaster ? "Master" : "Slave");
}

void loop() {
    if (isMaster) {
        // Master Test Code
        // This code starts by sending data out on the bus
        // It is assumed that the slave will respond immediatly, so the
        // master listens for one second for this data before sending more data
        send("abra"); 
        digitalWrite(STATUS_PIN, HIGH);
        masterRecieve();
        digitalWrite(STATUS_PIN, LOW);
    } else {
        // Slave Test Code
        // This code starts by listening for a transmission
        // And it will only respond after it recieves a message
        // If the message is larger than one char, change the recieve
        // condition to match the new message characteristic
        digitalWrite(STATUS_PIN, HIGH);
        slaveRecieve();
        digitalWrite(STATUS_PIN, LOW);
        send("cadabra");
    }
}

SoftwareSerial initConnection(bool isReciever) {
    SoftwareSerial mySerial(isReciever ? PORT : 30, isReciever? 30 : PORT);
    mySerial.begin(SS_SPEED);
    // A quick delay to make sure the reciever is ready
    delay(SS_DELAY);

    return mySerial;
}

SoftwareSerial initConnection() {
    return initConnection(false);
}

void send(String message) {
    initConnection().print(message);
    // The serial terminal will end here as it goes out of scope and the destructor is called
    Serial.println(String(isMaster ? "Master" : "Slave") + ": send - " + message);
}

void masterRecieve() {
    SoftwareSerial mySerial = initConnection(true);
    long time = millis();

    Serial.print("Master: rec - ");
    while (millis() - time < MASTER_RECIEVE_TIME) {
        while (mySerial.available()) {
            Serial.write((char)mySerial.read());
        }
    }
    Serial.println("");
    //The recieving connection will close as it goes out of scope and the destructor is called
}

void slaveRecieve() {
    SoftwareSerial mySerial = initConnection(true);
    boolean recieved = false;

    // Wait for data to be recieved and if it is print it and move on
    Serial.print("Slave: rec - ");
    while (!recieved) {
        while (mySerial.available()) {
            Serial.write((char)mySerial.read());
            delay(SS_DELAY);
            recieved = !mySerial.available();
        }
    }
    Serial.println("");
    // The serial terminal will end here as it goes out of scope and the destructor is called
}

