#include <Arduino.h>

#include <config.h>

#include "screen.h"
#include "encoders.h"
#include "mpu6050.h"
#include "l298n.h"

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

  Wire.begin();
  Wire.setClock(400000L); // run I2C at high speed (optional)

  // display.begin(&SH1106_128x64, 0x3C);
  display.begin(&Adafruit128x32, SCREEN_ADDRESS); // confirm I2C address is correct for your display

  display.setFont(Adafruit5x7); // standard font
  display.clear();

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

  mpu6050.begin();

  infoMessln("Starting calibration ...");

  clearLine(2);
  display.setCursor(0, 2);
  display.print("Calibrating ...");

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
  infoMessln("Setting up L298 ...");

  clearLine(2);
  display.setCursor(0, 2);
  display.print("Motor driver ...");

  motor.setSpeed(initialMotorSpeed); // Set initial speed

  clearLine(2);
  display.setCursor(0, 2);
  display.write("Motor driver!");

  delay(500);
  infoMessLF();

  /*******************************
    PID Regulator
  *******************************/
  // 1. Konfigurera PID-regulatorn
  myPID.SetOutputLimits(-255, 255); // Tillåt negativa värden för backläge
  myPID.SetSampleTimeUs(10000);     // Beräkna PID var 10:e millisekund (10000 µs)

  // 2. Starta PID-regulatorn i automatiskt läge
  //myPID.SetMode(myPID.Control::automatic);
  myPID.SetMode(QuickPID::Control::automatic);
  //myPID.SetMode(1); // 1 motsvarar 'automatic', 0 motsvarar 'manual'

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

void loop()
{
  /*******************************
    Read MPU6050
  *******************************/
  readMPU(); // gives the variable 'angle', the actual position of the motor/wheel

  /*******************************
    Read Encoders
  *******************************/
  PidValues myGain = readEncoders(); // besides Kp, Ki and Kd, it also gives gives the variable 'setpoint'

  input = angle; // the actual angle

  myPID.SetTunings(myGain.p, myGain.i, myGain.d); // send updated PID-values to the regulator

  myPID.Compute(); // the regulator calculates the output signal

  infoMessVar(input);
  infoMess("\t");
  infoMessVar(output);
  infoMess("\t");
  infoMessVarln(setpoint);

  controlMotor(output); // control the motor

  // motorTest();
}
