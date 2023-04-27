#include <BLEMidi.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>

Adafruit_MPU6050 mpu;
float accelValues[3];
float prevAccel[3];
float velValues[3];

//timer
long startTime;
int minutes = 60000;
int interval = minutes * 0.1; //* 5

//shaking
int shakeNum;
long shakeTime;
int shakeInterval = 2000;

int delayTime = 100;

void setup(void) {
  Serial.begin(115200);
  initMIDI();
  initMPU();
}

void loop() {
  getPrevVal();

  //  sendSphere();
  //    sendCube();
  sendOcta();
  //  serialMonitor(accelValues[0], accelValues[1], accelValues[2], velValues[0], velValues[1], velValues[2]);

  delay(delayTime);
  getMPUData();

  checkMovement();
  checkShake();
}

void checkMovement() {
  float threshold = 0.75;

  for (int i = 0; i < 3; i++) {
    float check = abs(accelValues[i] - prevAccel[i]);
    //    float check = (accelValues[i] - prevAccel[i]);
    //    Serial.println(check);
    //        Serial.println(threshold);
    if (check > threshold) {
      startTime = millis();
      //      Serial.println("Check!");
    }
  }
}

boolean timerTriggered() {
  if (millis() - startTime > interval) {
    Serial.println("Timer Triggered");
    return true;
  }
  else {
    return false;
  }
}

void checkShake() {
  float threshold = 3.0;

  for (int i = 0; i < 3; i++) {
    float check = abs(velValues[i]);
    if (check > threshold) {
      Serial.println("Check!");
      if (shakeNum < 100) {
        shakeNum += 3;
      }
      shakeTime = millis();
    }
  }

  if (shakeTimerTriggered() && shakeNum > 0) {
    shakeNum -= 5;
    if(shakeNum < 0){
      shakeNum = 0;
    }
  }

  Serial.println(constrain(shakeNum, 0, 100));
}

boolean shakeTimerTriggered() {
  if (millis() - shakeTime > shakeInterval) {
    Serial.println("Stopped shaking!");
    return true;
  }
  else {
    return false;
  }
}

void testMidi() {
  if (BLEMidiServer.isConnected()) {
    BLEMidiServer.controlChange(0, 1, 60);
    delay(1000);
    BLEMidiServer.controlChange(0, 2, 60);
    delay(1000);
    BLEMidiServer.controlChange(0, 3, 60);
    delay(1000);

  }
}
