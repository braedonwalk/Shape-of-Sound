void initMPU() {
  // Try to initialize!
  if (!mpu.begin()) {
    Serial.println("Failed to find MPU6050 chip");
    while (1) {
      delay(10);
    }
  }
  Serial.println("MPU6050 Found!");

  // set accelerometer range to +-8G
  mpu.setAccelerometerRange(MPU6050_RANGE_8_G);

  // set gyro range to +- 500 deg/s
  mpu.setGyroRange(MPU6050_RANGE_500_DEG);

  // set filter bandwidth
  //  mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);
  mpu.setFilterBandwidth(MPU6050_BAND_5_HZ);

  delay(100);
}

void getMPUData() {
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);

//  checkMovement();

  accelValues[0] = a.acceleration.x;
  accelValues[1] = a.acceleration.y;
  accelValues[2] = a.acceleration.z;

  velValues[0] = g.gyro.x;
  velValues[1] = g.gyro.y;
  velValues[2] = g.gyro.z;
}

void getPrevVal(){
  for (int i = 0; i < 3; i++) {
    prevAccel[i] = accelValues[i];
//    Serial.print("PrevAccel: ");
//    Serial.println(prevAccel[i]);
//    Serial.print("CurAccel: ");
//    Serial.println(accelValues[i]);
  }
}
