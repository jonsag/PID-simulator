#include <Arduino.h>

#include <config.h>

#include <runMotor.h>
#include <screen.h>

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

    infoMessln();
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

    infoMessln("Starting screen ...");
    infoMessln();

    if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS))
    {
        Serial.println(F("SSD1306 allocation failed"));
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

    display.setCursor(Column_1, Line_1);
    display.write(programName);
    display.setCursor(Column_1, Line_2);
    display.write(web);

    display.display(); // Show the display buffer on the screen. You MUST call display() after drawing commands to make them visible on screen!

    /*******************************
      MPU6050 Setup
    *******************************/
    infoMessln("Starting MPU6050 ...");

    display.setCursor(Column_1, Line_3);
    display.write("Accelerometer...");

    if (!mpu.begin()) // Try to initialize!
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

    ClearLine(3);
    display.setCursor(Column_1, Line_3);
    display.write("Accelerometer!");
    display.display();
    
    infoMessln();
    delay(500);

    /*******************************
      L298N Setup
    *******************************/
    infoMessln("Setting up L298 ...");

    ClearLine(3);
    display.setCursor(Column_1, Line_3);
    display.write("Motor driver ...");
    display.display();

    motor.setSpeed(initialMotorSpeed); // Set initial speed
    
    ClearLine(3);
    display.setCursor(Column_1, Line_3);
    display.write("Motor driver!");
    display.display();
    delay(500);
    infoMessln();

    /*******************************
      Finished
    *******************************/
    infoMessln("Finished booting up!");
    infoMessln("Entering main ...");
    infoMessln();
    
    ClearLine(3);
    display.setCursor(Column_1, Line_3);
    display.write("Starting ...");
    display.display();
    delay(1000);

    display.clearDisplay();
    display.display();

}

void loop()
{
    /*******************************
      Read Encoders
    *******************************/
    setNewPosition = setEnc.read();
    if (setNewPosition != setOldPosition){
        if (setNewPosition < setMinValue)
        {
            setEnc.write(setMinValue);
            setNewPosition = setMinValue;
        }
        else if (setNewPosition > setMaxValue)
        {
            setEnc.write(setMaxValue);
            setNewPosition = setMaxValue;
        }
        setOldPosition = setNewPosition;
        infoMess("Set value: ");
        infoMessln(setNewPosition);
    }

    PNewPosition = PEnc.read();
    if (PNewPosition != POldPosition)
    {
        if (PNewPosition < PMinValue)
        {
            PEnc.write(PMinValue);
            PNewPosition = PMinValue;
        }
        else if (PNewPosition > PMaxValue)
        {
            PEnc.write(PMaxValue);
            PNewPosition = PMaxValue;
        }
        POldPosition = PNewPosition;
        infoMess("P value:   ");
        infoMessln(PNewPosition);
        displayPID("P", PNewPosition);
    }

    INewPosition = IEnc.read();
    if (INewPosition != IOldPosition)
    {
        if (INewPosition < IMinValue)
        {
            IEnc.write(IMinValue);
            INewPosition = IMinValue;
        }
        else if (INewPosition > IMaxValue)
        {
            IEnc.write(IMaxValue);
            INewPosition = IMaxValue;
        }
        IOldPosition = INewPosition;
        infoMess("I value:   ");
        infoMessln(INewPosition);
        displayPID("I", INewPosition);
    }

    DNewPosition = DEnc.read();
    if (DNewPosition != DOldPosition)
    {
        if (DNewPosition < DMinValue)
        {
            DEnc.write(DMinValue);
            DNewPosition = DMinValue;
        }
        else if (DNewPosition > DMaxValue)
        {
            DEnc.write(DMaxValue);
            DNewPosition = DMaxValue;
        }
        DOldPosition = DNewPosition;
        infoMess("D value:   ");
        infoMessln(DNewPosition);
        displayPID("D", DNewPosition);
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

    // delay(500);

    // motorTest();
}
