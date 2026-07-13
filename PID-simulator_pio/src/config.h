#pragma once
#include <Arduino.h> // needed for serial

#define programName "PID-Simulator"
#define date "20260709"
#define author "Jon Sagebrand"
#define email "jonsagebrand@gmail.com"
#define web "github.com/jonsag"

/*******************************
  Serial & Debugging
*******************************/
#define serialSpeed 9600
#define DEBUG 0
#define INFO 1

#if DEBUG
#define debugMess(x) Serial.print(F(x))
#define debugMessln(x) Serial.println(F(x))
#define debugMessLF() Serial.println() // for line feeds

#define debugMessVar(x) Serial.print(x) // use this for variables (int, long, float etc.)
#define debugMessVarln(x) Serial.println(x)

#else
#define debugMess(x)
#define debugMessln(x)
#define debugMessLF()
#define debugMessVar(x)
#define debugMessVarln(x)
#endif

#if INFO || DEBUG
#define infoMess(x)        \
  {                        \
    Serial.print(F("\t")); \
    Serial.print(F(x));    \
  } // this macro is only for text strings
#define infoMessln(x)      \
  {                        \
    Serial.print(F("\t")); \
    Serial.println(F(x));  \
  }
#define infoMessLF() Serial.println() // for line feeds

#define infoMessVar(x)     \
  {                        \
    Serial.print(F("\t")); \
    Serial.print(x);       \
  } // use this for variables (int, long, float etc.)
#define infoMessVarln(x)   \
  {                        \
    Serial.print(F("\t")); \
    Serial.println(x);     \
  }

#else
#define infoMess(x)
#define infoMessln(x)
#define infoMessLF()
#define infoMessVar(x)
#define infoMessVarln(x)
#endif

/*******************************
  Screen (and Common Libraries)
*******************************/
#include <Wire.h>
#include <SPI.h>

#include <SSD1306Ascii.h>
#include <SSD1306AsciiWire.h> // for I2C

extern SSD1306AsciiWire display; // announce the screen, declared in config.h

// #define SCREEN_WIDTH 128
// #define SCREEN_HEIGHT 32
#define SCREEN_ADDRESS 0x3C

#define charWidth 6
// #define charHeight 8
#define columnWidth 11

/*******************************
  Encoders
*******************************/
#include <RotaryEncoder.h>

extern RotaryEncoder setEnc; // announce the encoders
extern RotaryEncoder PEnc;
extern RotaryEncoder IEnc;
extern RotaryEncoder DEnc;

extern long setOldPosition; // announce position variables
extern long setNewPosition;
extern long POldPosition;
extern long PNewPosition;
extern long IOldPosition;
extern long INewPosition;
extern long DOldPosition;
extern long DNewPosition;

#define setMinValue -180.0
#define setMaxValue 180.0
#define PMinValue 0.0
#define PMaxValue 500.0 // note: these values are 10 times larger than the actual gains
#define IMinValue 0.0
#define IMaxValue 500.0
#define DMinValue 0.0
#define DMaxValue 500.0

/*******************************
  PID
*******************************/
struct PidValues
{
  float p;
  float i;
  float d;
};

//PidValues readEncoders(); // function declaration that returns our struct

#include <QuickPID.h>

extern float setpoint; // Ditt börvärde från rotationsenkodern (-180 till +180)
extern float input;    // Ditt ärvärde (angle från MPU6050)
extern float output;   // Utsignalen som PID räknar ut (-255 till +255)

extern QuickPID myPID;

/*******************************
  MPU6050, accelerometer
*******************************/
#include <MPU6050_tockn.h>

extern MPU6050 mpu6050; // announce gyro definition

extern double angle; // the value used by the regulator

extern double angleXAcc; // holds the accumulated readings
extern double angleX;    // holds the averaged angles
extern double oldAngleX; // holds the old values

extern boolean anglesLocked;

extern double measureTime; // for how long should values be read before averaged, ms
extern int values;

/*******************************
  L298N, motor driver
*******************************/
#include <L298N.h>

#define IN1 2 // const are safe to keep in .h files, they will not cause "multiple definition"
#define IN2 3
#define EN 1
#define initialMotorSpeed 70

extern L298N motor; // announce motor definition

/*******************************
  Misc
*******************************/
extern double startMillis;

// String mess = ""; // holds the message
// String oldMess = "";

// extern double messMillis;
// #define messTime 2000 // how long to show a message, ms