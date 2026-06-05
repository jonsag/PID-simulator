#include <Arduino.h>

#include <config.h>

#include <runMotor.h>

void setup()
{
  /*******************************
    Serial Setup , Start information
  *******************************/
  Serial.begin(serialSpeed);
  while (!Serial)
  {
    // do nothing
  }

  infoMessln(programName); // print information
  infoMessln(date);
  infoMess("by ");
  infoMessln(author);
  infoMessln(email);
  infoMessln();

  /*******************************
    Display Setup
  *******************************/
  delay(500);

  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS))
  {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;)
      ; // Don't proceed, loop forever
  }

  display.display(); // Show initial display buffer contents on the screen -- the library initializes this with an Adafruit splash screen.
  delay(2000);       // Pause for 2 seconds

  display.clearDisplay(); // Clear the buffer

  display.drawPixel(10, 10, SSD1306_WHITE); // Draw a single pixel in white

  display.display(); // Show the display buffer on the screen. You MUST call display() after drawing commands to make them visible on screen!
  delay(2000);

  /*******************************
    MPU6050 Setup
  *******************************/
  infoMessln("Adafruit MPU6050 test!");

  if (!mpu.begin()) // Try to initialize!
  {
    infoMessln("Failed to find MPU6050 chip");
    while (1)
    {
      delay(10);
    }
  }

  infoMessln("MPU6050 Found!");

  mpu.setAccelerometerRange(MPU6050_RANGE_8_G);

#ifdef debug
  Serial.print("Accelerometer range set to: ");
  switch (mpu.getAccelerometerRange())
  {
  case MPU6050_RANGE_2_G:
    Serial.println("+-2G");
    break;
  case MPU6050_RANGE_4_G:
    Serial.println("+-4G");
    break;
  case MPU6050_RANGE_8_G:
    Serial.println("+-8G");
    break;
  case MPU6050_RANGE_16_G:
    Serial.println("+-16G");
    break;
  }
#endif

  mpu.setGyroRange(MPU6050_RANGE_500_DEG);

#ifdef debug
  Serial.print("Gyro range set to: ");
  switch (mpu.getGyroRange())
  {
  case MPU6050_RANGE_250_DEG:
    Serial.println("+- 250 deg/s");
    break;
  case MPU6050_RANGE_500_DEG:
    Serial.println("+- 500 deg/s");
    break;
  case MPU6050_RANGE_1000_DEG:
    Serial.println("+- 1000 deg/s");
    break;
  case MPU6050_RANGE_2000_DEG:
    Serial.println("+- 2000 deg/s");
    break;
  }
#endif
  mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);

#ifdef debug
  Serial.print("Filter bandwidth set to: ");
  switch (mpu.getFilterBandwidth())
  {
  case MPU6050_BAND_260_HZ:
    Serial.println("260 Hz");
    break;
  case MPU6050_BAND_184_HZ:
    Serial.println("184 Hz");
    break;
  case MPU6050_BAND_94_HZ:
    Serial.println("94 Hz");
    break;
  case MPU6050_BAND_44_HZ:
    Serial.println("44 Hz");
    break;
  case MPU6050_BAND_21_HZ:
    Serial.println("21 Hz");
    break;
  case MPU6050_BAND_10_HZ:
    Serial.println("10 Hz");
    break;
  case MPU6050_BAND_5_HZ:
    Serial.println("5 Hz");
    break;
  }
#endif

  infoMessln("");
  delay(100);

  /*******************************
    L298N Setup
  *******************************/
  motor.setSpeed(initialMotorSpeed); // Set initial speed
}

void loop()
{
  /*******************************
    Read Encoders
  *******************************/
  setNewPosition = setEnc.read();
  if (setNewPosition != setOldPosition)
  {
    setOldPosition = setNewPosition;
    infoMessln(setNewPosition);
  }

  PNewPosition = PEnc.read();
  if (PNewPosition != POldPosition)
  {
    POldPosition = PNewPosition;
    infoMessln(PNewPosition);
  }

  INewPosition = IEnc.read();
  if (INewPosition != IOldPosition)
  {
    IOldPosition = INewPosition;
    infoMessln(INewPosition);
  }

  DNewPosition = DEnc.read();
  if (DNewPosition != DOldPosition)
  {
    DOldPosition = DNewPosition;
    infoMessln(DNewPosition);
  }

  /*******************************
    Read MPU6050
  *******************************/
  sensors_event_t a, g, temp; // Get new sensor events with the readings
  mpu.getEvent(&a, &g, &temp);

#ifdef debug
  Serial.print("Acceleration X: "); // Print out the values
  Serial.print(a.acceleration.x);
  Serial.print(", Y: ");
  Serial.print(a.acceleration.y);
  Serial.print(", Z: ");
  Serial.print(a.acceleration.z);
  Serial.println(" m/s^2");

  Serial.print("Rotation X: ");
  Serial.print(g.gyro.x);
  Serial.print(", Y: ");
  Serial.print(g.gyro.y);
  Serial.print(", Z: ");
  Serial.print(g.gyro.z);
  Serial.println(" rad/s");

  Serial.print("Temperature: ");
  Serial.print(temp.temperature);
  Serial.println(" degC");

  Serial.println("");
#endif

  delay(500);

  motorTest();
}
