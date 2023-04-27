void initMIDI() {
  Serial.println("Initializing bluetooth");
  BLEMidiServer.begin("Octa");  //CHANGE THIS BEFORE UPLOAD
  Serial.println("Waiting for connections...");
}

void sendMidi(int control, int value) {
  BLEMidiServer.controlChange(0, control, value);
}

void sendMappedMidi(int x, float in_min, float in_max, float out_min, float out_max, int control) {
  float newValue = mapFloat(accelValues[x], in_min, in_max, out_min, out_max); newValue = constrain(newValue, out_min, out_max); //0-1(00)
  //  Serial.print("Control: "); Serial.println(control);
  //  Serial.print("Value: "); Serial.println(newValue);

  if (BLEMidiServer.isConnected()) {
    BLEMidiServer.controlChange(0, control, newValue); //channel, control, value
  }
}

void sendSphere() {
  if (!timerTriggered()) {
    for (int i = 0; i < 2; i++) {
      sendMappedMidi(i, -10.0, 10.0, 0.0, 100.0, i + 1); //int x, float in_min, float in_max, float out_min, float out_max, int control // -10.0, 10.0, 0.0, 100.0
    }
  }
  else {
    sendMappedMidi(0, -10.0, 10.0, 0.0, 100.0, 7);
    //    sendMidi(7, 0); //"turn off" command
  }
}

void sendCube() {
  float x = accelValues[0];
  float y = accelValues[1];
  float z = accelValues[2];
  int controlValue;

  //  serialMonitor(x, y, z);

  if      (x > 9 && z < 6 && y < 6) {
    //    Serial.println("High X");
    controlValue = 1;
  }
  else if (y > 9 && z < 6 && x < 6) {
    //    Serial.println("High Y");
    controlValue = 2;
  }
  else if (z > 8.5 && x < 6 && y < 6) {
    //    Serial.println("High Z");
    controlValue = 3;
  }
  else if (x < -9 && z > -6 && y > -6) {
    //    Serial.println("Low X");
    controlValue = 4;
  }
  else if (y < -9 && z > -6 && x > -6) {
    //    Serial.println("Low Y");
    controlValue = 5;
  }
  else if (z < -9 && y > -6 && x > -6) {
    //    Serial.println("Low Z");
    controlValue = 6;
  }

  if (BLEMidiServer.isConnected()) {
    if (!timerTriggered()) {
      sendMidi(controlValue, 0);
      Serial.print("Sending: "); Serial.println(controlValue);
    }
    else {
      sendMidi(7, 0); //send "turn off" command
    }
  }
}

void sendOcta() {
  //  interval = 8000;
  if (BLEMidiServer.isConnected()) {
    //  for (int i = 1; i < 3; i++) {
    if (!timerTriggered()) {
      //      sendMidi(1, 0);
      //    sendMappedMidi(shakeNum, 0.0, 100.0, 0.0, 100.0, 1); //int x, float in_min, float in_max, float out_min, float out_max, int control // -10.0, 10.0, 0.0, 100.0
      sendMidi(1, constrain(shakeNum, 0, 100));
    }
    //}
    else {
      sendMidi(7, 0);
      //    sendMappedMidi(7, -10.0, 10.0, 0.0, 100.0, 7); //int x, float in_min, float in_max, float out_min, float out_max, int control // -10.0, 10.0, 0.0, 100.0
    }
  }
  //  }
}

float mapFloat(float x, float in_min, float in_max, float out_min, float out_max) {
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

//void sendMidi() {
//  float newValue = mapFloat(accelValues[0], -10.0, 10.0, 0.0, 100.0); newValue = constrain(newValue, 0, 100); //0-1(00)
//  //    float newValue = mapFloat(accelValues[1], -10.0, 10.0, 0.0, 100.0); newValue = constrain(newValue, 0, 100); //0-1(00)
//  //    float newValue = mapFloat(accelValues[0], -10.0, 10.0, 0.0, 100.0); newValue = constrain(newValue, 0, 100); //0-1(00)
//  //    float newValue = mapFloat(accelValues[2], -10.0, 10.0, -100.0, 100.0); newValue = constrain(newValue, -100, 100);  //-1, 1
//  Serial.println(newValue);
//
//  if (BLEMidiServer.isConnected()) {
//    if (millis() - startTime > interval) {
//      BLEMidiServer.controlChange(0, 3, newValue); //channel, control, value
//      delay(delayTime);
//    }
//  }
//}
