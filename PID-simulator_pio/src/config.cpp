#include "config.h"

/*******************************
  in this file definitions are created "for real"
*******************************/

/*******************************
  Screen
*******************************/
// Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
SSD1306AsciiWire display;

/*******************************
  Encoders
*******************************/
RotaryEncoder setEnc(7, 6, RotaryEncoder::LatchMode::TWO03);
RotaryEncoder PEnc(9, 8, RotaryEncoder::LatchMode::TWO03);
RotaryEncoder IEnc(11, 10, RotaryEncoder::LatchMode::TWO03);
RotaryEncoder DEnc(13, 12, RotaryEncoder::LatchMode::TWO03);

long setOldPosition = -999;
long setNewPosition;
long POldPosition = -999;
long PNewPosition;
long IOldPosition = -999;
long INewPosition;
long DOldPosition = -999;
long DNewPosition;

/*******************************
  PID
*******************************/

/*******************************
  MPU6050, accelerometer
*******************************/
// Adafruit_MPU6050 mpu;

MPU6050 mpu6050(Wire); // start mpu instance

double angle = 0; // the value used by the regulator

double angleXAcc = 0; // holds the accumulated readings
double angleX = 0;    // holds the averaged angles
double oldAngleX = 0; // holds the old values

/*double angleYAcc = 0;
double angleY = 0;
double oldAngleY = 0;

double angleZAcc = 0;
double angleZ = 0;
double oldAngleZ = 0;

double angleXLock = 0; // stores the locked angles
double angleYLock = 0;
double angleZLock = 0;

boolean angleXLocked = false;
boolean angleYLocked = false;
boolean angleZLocked = false;
boolean anglesLocked = false;*/

double measureTime = 282; // for how long should values be read before averaged, ms
int values = 0;           // counting values read

/*******************************
  L298N, motor driver
*******************************/
// L298N motor(EN, IN1, IN2);

/*******************************
  Misc
*******************************/
double startMillis;

// String mess = ""; // holds the message
// String oldMess = "";

double messMillis;
