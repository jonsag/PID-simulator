#include <Arduino.h>

#include <config.h>

// #include <runMotor.h>
#include <screen.h>
#include <encoders.h>

void setup()
{
    /*******************************
      Serial Setup, Start information
    *******************************/
    Serial.begin(serialSpeed);
    while (!Serial)
    {
        // do nothing
    }

    infoMessLF();
    infoMessln(programName); // print information
    infoMessln(date);
    infoMess("by ");
    infoMessln(author);
    infoMessln(email);
    infoMessLF();

    /*******************************
      Display Setup
    *******************************/
    delay(500);

    infoMessln("Starting screen ...");
    infoMessLF();

    /*if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS))
    {
        infoMessln("SSD1306 allocation failed");
        for (;;)
            ; // Don't proceed, loop forever
    }

    display.display(); // Show initial display buffer contents on the screen -- the library initializes this with an Adafruit splash screen.
    delay(500);

    display.clearDisplay(); // Clear the buffer
    // display.drawPixel(10, 10, SSD1306_WHITE); // Draw a single pixel in white

    display.setTextSize(1);              // Normal 1:1 pixel scale
    display.setTextColor(SSD1306_WHITE); // Draw white text
    display.cp437(true);                 // Use full 256 char 'Code Page 437' font

    display.setCursor(0 * columnWidth, 0 * lineHeight);
    display.write(programName);
    display.setCursor(0 * columnWidth, 1 * lineHeight);
    display.write(web);

    display.display(); // Show the display buffer on the screen. You MUST call display() after drawing commands to make them visible on screen!*/

    Wire.begin();
    Wire.setClock(400000L); // run I2C at high speed (optional)

    // display.begin(&SH1106_128x64, 0x3C);
    display.begin(&Adafruit128x32, SCREEN_ADDRESS); // check I2C address

    display.setFont(Adafruit5x7); // standard font
    display.clear();

    // Skriv ut text (Du behöver inte anropa display.display() längre!)
    display.println(programName);
    display.println(web);

    display.setCursor(0, 0);
    display.print(programName);
    display.setCursor(0, 1);
    display.print(web);

    /*******************************
      MPU6050 Setup
    *******************************/
    infoMessln("Starting MPU6050 ...");

    display.setCursor(0, 2);
    display.print("Accelerometer...");

    /*if (!mpu.begin()) // Try to initialize!
    {
        infoMessln("Failed to find MPU6050 chip");
        while (1)
        {
            delay(10);
        }
    }

    infoMessln("MPU6050 Found!");
    infoMessln("Setting up MPU6050 ...");

    mpu.setAccelerometerRange(MPU6050_RANGE_8_G);

#ifdef DEBUG
    debugMess("Accelerometer range set to: ");
    switch (mpu.getAccelerometerRange())
    {
    case MPU6050_RANGE_2_G:
        debugMessln("+-2G");
        break;
    case MPU6050_RANGE_4_G:
        debugMessln("+-4G");
        break;
    case MPU6050_RANGE_8_G:
        debugMessln("+-8G");
        break;
    case MPU6050_RANGE_16_G:
        debugMessln("+-16G");
        break;
    }
#endif
    mpu.setGyroRange(MPU6050_RANGE_500_DEG);

#ifdef DEBUG
    debugMess("Gyro range set to: ");
    switch (mpu.getGyroRange())
    {
    case MPU6050_RANGE_250_DEG:
        debugMessln("+- 250 deg/s");
        break;
    case MPU6050_RANGE_500_DEG:
        debugMessln("+- 500 deg/s");
        break;
    case MPU6050_RANGE_1000_DEG:
        debugMessln("+- 1000 deg/s");
        break;
    case MPU6050_RANGE_2000_DEG:
        debugMessln("+- 2000 deg/s");
        break;
    }
#endif
    mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);

#ifdef DEBUG
    debugMess("Filter bandwidth set to: ");
    switch (mpu.getFilterBandwidth())
    {
    case MPU6050_BAND_260_HZ:
        debugMessln("260 Hz");
        break;
    case MPU6050_BAND_184_HZ:
        debugMessln("184 Hz");
        break;
    case MPU6050_BAND_94_HZ:
        debugMessln("94 Hz");
        break;
    case MPU6050_BAND_44_HZ:
        debugMessln("44 Hz");
        break;
    case MPU6050_BAND_21_HZ:
        debugMessln("21 Hz");
        break;
    case MPU6050_BAND_10_HZ:
        debugMessln("10 Hz");
        break;
    case MPU6050_BAND_5_HZ:
        debugMessln("5 Hz");
        break;
    }
#endif*/

    mpu6050.begin();
    infoMessln("Starting calibration ...");
    mpu6050.calcGyroOffsets(true);

    infoMessLF();

    clearLine(2);
    display.setCursor(0, 2);
    display.print("Accelerometer!");

    infoMessLF();
    delay(500);

    /*******************************
      L298N Setup
    *******************************/
    /*infoMessln("Setting up L298 ...");

    clearLine(2);
    display.setCursor(Column_1, Line_3);
    display.write("Motor driver ...");
    display.display();

    motor.setSpeed(initialMotorSpeed); // Set initial speed

    clearLine(2);
    display.setCursor(Column_1, Line_3);
    display.write("Motor driver!");
    display.display();
    delay(500);
    infoMessLF();*/

    /*******************************
      Finished
    *******************************/
    infoMessln("Finished booting up!");
    infoMessln("Entering main ...");
    infoMessLF();

    clearLine(2);
    display.setCursor(0, 2);
    display.write("Starting ...");
    delay(1000);

    display.clear();

    startMillis = millis();
}

double round1dec(double b)
{
    if ((int)((b * 10 - (int)(b * 10)) * 10) >= 5)
    {
        return (double)(int)(b * 10) / 10 + 0.1;
    }
    else
    {
        return (double)(int)(b * 10) / 10;
    }
}

void loop()
{
    /*******************************
      Read Encoders
    *******************************/
    PidValues myGain = readEncoders();

    /*******************************
      Read MPU6050
    *******************************/
    /*sensors_event_t a, g, temp; // Get new sensor events with the readings
    mpu.getEvent(&a, &g, &temp);

#ifdef DEBUG
    debugMess("Acceleration X: "); // Print out the values
    debugMessVar(a.acceleration.x);
    debugMess(", Y: ");
    debugMessVar(a.acceleration.y);
    debugMess(", Z: ");
    debugMessVar(a.acceleration.z);
    debugMessln(" m/s^2");

    debugMess("Rotation X: ");
    debugMessVar(g.gyro.x);
    debugMess(", Y: ");
    debugMessVar(g.gyro.y);
    debugMess(", Z: ");
    debugMessVar(g.gyro.z);
    debugMessln(" rad/s");

    debugMess("Temperature: ");
    debugMessVar(temp.temperature);
    debugMessln(" degC");

    debugMessln("");

    delay(500);
#endif*/

    mpu6050.update(); // read values
    angle += mpu6050.getAngleX();

    if (millis() - startMillis < measureTime)
    {
        /*******************************
            Measure angles
        *******************************/
        values++;

        // mpu6050.update(); // read values

        angleXAcc += mpu6050.getAngleX();
        // angleYAcc += mpu6050.getAngleY();
        // angleZAcc += mpu6050.getAngleZ();
    }
    else
    {
        /*******************************
          Calculate angles
        *******************************/
        angleX = round1dec(angleXAcc / values); // calculate averages and round
        // angleY = round1dec(angleYAcc / values);
        // angleZ = round1dec(angleZAcc / values);

        // lightLED(angleX, angleXLock); // light the LED

        if (angleX != oldAngleX)
        {
            // printActualAng(0, angleX, angleXLock); // prints the actual values on screen
            printAngle(angleX);
            oldAngleX = angleX;
        }
        /*if (angleY != oldAngleY)
        {
            // printActualAng(2, angleY, angleYLock);
            oldAngleY = angleY;
        }
        if (angleZ != oldAngleZ)
        {
            // printActualAng(4, angleZ, angleZLock);
            oldAngleZ = angleZ;
        }*/

        angleXAcc = 0; // reset all accumulated values
        // angleYAcc = 0;
        // angleZAcc = 0;

        values = 0;

        startMillis = millis();
    }

    debugMess("\tAngles, X: ");
    debugMessVar(angleX);
    /*debugMess("\tY: ");
    debugMessVar(angleY);
    debugMess("\tZ: ");
    debugMessVar(angleZ);*/

    debugMess("\t");
    debugMessVar(values);
    debugMess(" values");
    debugMessLF();

    // motorTest();
}
