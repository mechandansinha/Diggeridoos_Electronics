// Using ICM20948 9-DoF IMU 
// Yellow is SCL, Blue is SDA

#include <Adafruit_ICM20X.h>
#include <Adafruit_ICM20948.h>
#include <Adafruit_Sensor.h>3
#include <Wire.h>

Adafruit_ICM20948 icm;
const int numSamples = 10;

// Variables for storing the sensor data
float accelX, accelY, accelZ;
float gyroX, gyroY, gyroZ;
float magX, magY, magZ;

// Arrays for storing the last numSamples values
float accelXSamples[numSamples], accelYSamples[numSamples], accelZSamples[numSamples];
float gyroXSamples[numSamples], gyroYSamples[numSamples], gyroZSamples[numSamples];
float magXSamples[numSamples], magYSamples[numSamples], magZSamples[numSamples];

void setup(void) {
  Serial.begin(115200);
  while (!Serial){
    delay(10);
  }
  
  if (!icm.begin_I2C()) {
    Serial.println("Failed to find ICM20948 chip");
    while (1) {
      delay(10);
    }
  }
  Serial.println("ICM20948 Found!");
  
  icm.setAccelRange(ICM20948_ACCEL_RANGE_16_G);
  icm.setGyroRange(ICM20948_GYRO_RANGE_2000_DPS);
  icm.setMagDataRate(AK09916_MAG_DATARATE_50_HZ);

  // icm.setAccelRateDivisor(4095);
  uint16_t accel_divisor = icm.getAccelRateDivisor();
  float accel_rate = 1125 / (1.0 + accel_divisor);

  //  icm.setGyroRateDivisor(255);
  uint8_t gyro_divisor = icm.getGyroRateDivisor();
  float gyro_rate = 1100 / (1.0 + gyro_divisor);

  // Wait for the ICM20948 to stabilize
  delay(500);
}

void loop() {
  accelX = 0;
  accelY = 0;
  accelZ = 0;
  gyroX = 0;
  gyroY = 0;
  gyroZ = 0;
  magX = 0;
  magY = 0;
  magZ = 0;

  for(int i=0; i<numSamples; i++){
    // Get a new normalized sensor event
    sensors_event_t accel;
    sensors_event_t gyro;
    sensors_event_t temp;
    sensors_event_t mag;
    icm.getEvent(&accel, &gyro, &temp, &mag);

    accelXSamples[i] = accel.acceleration.x;
    accelYSamples[i] = accel.acceleration.y;
    accelZSamples[i] = accel.acceleration.z;
    gyroXSamples[i] = gyro.gyro.x;
    gyroYSamples[i] = gyro.gyro.y;
    gyroZSamples[i] = gyro.gyro.z;
    magXSamples[i] = mag.magnetic.x;
    magYSamples[i] = mag.magnetic.y;
    magZSamples[i] = mag.magnetic.z;

    accelX += accelXSamples[i];
    accelY += accelYSamples[i];
    accelZ += accelZSamples[i];
    gyroX += gyroXSamples[i];
    gyroY += gyroYSamples[i];
    gyroZ += gyroZSamples[i];
    magX += magXSamples[i];
    magY += magYSamples[i];
    magZ += magZSamples[i];

    Serial.print("Taking sample: ");
    Serial.println(i+1);
    delay(50);
  }

  accelX /= numSamples;
  accelY /= numSamples;
  accelZ /= numSamples;
  gyroX /= numSamples;
  gyroY /= numSamples;
  gyroZ /= numSamples;
  magX /= numSamples;
  magY /= numSamples;
  magZ /= numSamples;

  // Print the stabilized sensor readings to the serial monitor
  Serial.print("Accelerometer: ");
  Serial.print(accelX);
  Serial.print(", ");
  Serial.print(accelY);
  Serial.print(", ");
  Serial.println(accelZ);
  Serial.print("Gyroscope: ");
  Serial.print(gyroX);
  Serial.print(", ");
  Serial.print(gyroY);
  Serial.print(", ");
  Serial.println(gyroZ);
  Serial.print("Magnetometer: ");
  Serial.print(magX);
  Serial.print(", ");
  Serial.print(magY);
  Serial.print(", ");
  Serial.println(magZ);
  Serial.println("---------------------------");

  delay(500);
}
