#include <SoftwareSerial.h>

#define mySerial_tx 0
#define mySerial_rx 2

//#define mySensor_tx 9
//#define mySensor_rx 8

SoftwareSerial mySerial(mySerial_rx, mySerial_tx);

//SoftwareSerial mySensor(mySensor_rx, mySensor_tx);

void setup() {
  Serial.begin(9600);

  pinMode(mySerial_tx, OUTPUT);
  pinMode(mySerial_rx, INPUT);
  digitalWrite(mySerial_rx, HIGH);
  mySerial.begin(9600);

  //  pinMode(mySensor_tx, OUTPUT);
  //  pinMode(mySensor_rx, INPUT);
  //  digitalWrite(mySensor_rx, HIGH);
  //  mySensor.begin(9600);
}

void loop() {
  byte slaveID = '1';
  byte receivedframe[8];
  byte transmitframe[8];

  byte frame[8] = {'1', '3', '0', '2', '0', '1', '1', '1'};

  // Print the sent frame
  Serial.print("Sent frame: ");
  for (int i = 0; i < 8; i++) {
    Serial.print(frame[i] - '0');
    if (i < 7) {
      Serial.print(" ");
    }
  }
  Serial.println();

  // Send frame to slave
  for (int i = 0; i < 8; i++) {
    mySerial.write(frame[i]);
  }

  // Read response from slave
  if (mySerial.available() >= 8) {
    Serial.print("Received Arduino Slave Frame: ");
    for (int i = 0; i < 8; i++) {
      receivedframe[i] = mySerial.read();
      Serial.print(receivedframe[i] - '0');
      if (i < 7) {
        Serial.print(" ");
      }
    }
    Serial.println();
    delay(1000);
  }
  //   Check if response is from the correct slave
  if ( receivedframe[0] == slaveID) {

    Serial.println("After Matching Response from Arduino slave:");
    for (int i = 0; i < 8; i++) {
      Serial.print(receivedframe[i] - '0');
      if (i < 7) {
        Serial.print(" ");
      }
    }
    Serial.println();
    delay(1000);
  }
  else {
    Serial.println("Invalid response or wrong slave ID");
  }

  delay(1000);
}
