#include <SoftwareSerial.h>

#define mySerial_tx 11
#define mySerial_rx 10

#define mySensor_rx 8
#define mySensor_tx 9

SoftwareSerial mySerial(mySerial_rx, mySerial_tx);
SoftwareSerial mySensor(mySensor_rx, mySensor_tx);

void setup() {
  Serial.begin(9600);
  pinMode(mySerial_tx, OUTPUT);
  pinMode(mySerial_rx, INPUT);
  digitalWrite(mySerial_rx, HIGH);
  mySerial.begin(9600);

  pinMode(mySensor_rx, INPUT);
  digitalWrite(mySensor_rx, HIGH);
  mySensor.begin(9600);
}

void loop() {
  byte slaveID = '1';
  byte receivedFrame[8];
  byte transmitFrame[8];
  byte sensorDataArray[7];

  if (mySerial.available() >= 8) {
    // Read frame from master
    Serial.print("Received Frame from ESP Master: ");
    for (int i = 0; i < 8; i++) {
      receivedFrame[i] = mySerial.read();
      transmitFrame[i] = receivedFrame[i] - '0';
      Serial.print(transmitFrame[i]);
      if (i < 7) {
        Serial.print(" ");
      }
    }
    Serial.println();
  }
  if (receivedFrame[0] == slaveID) {
    sensorDataArray[0] = receivedFrame[0];
    sensorDataArray[1] = '3';
    sensorDataArray[2] = '5';
    sensorDataArray[3] = '2';

    for (int i = 0; i < 3; i++) {
      if (mySensor.available()) {
        sensorDataArray[i + 4] = mySensor.read();
      }
    }

    // Send the data back to the master
    for (int i = 0; i < 7; i++) {
      mySerial.write(sensorDataArray[i]);
    }
  }

  delay(1000);
}
