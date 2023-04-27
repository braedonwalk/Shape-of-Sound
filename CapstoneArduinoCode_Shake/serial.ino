void serialMonitor(float aX, float aY, float aZ, float gX, float gY, float gZ){
  /* Print out the values */
//  Serial.print("Acceleration X: ");
//  Serial.print(aX);
//  Serial.print(", Y: ");
//  Serial.print(aY);
//  Serial.print(", Z: ");
//  Serial.print(aZ);
//  Serial.println(" m/s^2");

  Serial.print("Rotation X: ");
  Serial.print(gX);
  Serial.print(", Y: ");
  Serial.print(gY);
  Serial.print(", Z: ");
  Serial.print(gZ);
  Serial.println(" rad/s");

  Serial.println("");
//  delay(100);
}

void serialPlotter(int aX, int aY, int aZ){
  /* Print out the values */
  Serial.print(aX);
  Serial.print(",");
  Serial.print(aY);
  Serial.print(",");
  Serial.print(aZ);

//  Serial.print(", ");
//  Serial.print(g.gyro.x);
//  Serial.print(",");
//  Serial.print(g.gyro.y);
//  Serial.print(",");
//  Serial.print(g.gyro.z);
//  Serial.println("");

  delay(10);
}
