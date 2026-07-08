#define programName "PID-Simulator"
#define date "20260605"
#define author "Jon Sagebrand"
#define email "jonsagebrand@gmail.com"
#define web "github.com/jonsag"

/*******************************
  Serial
*******************************/
#define serialSpeed 9600

/*******************************
  Debugging
*******************************/
#define DEBUG 1 // debugMess is off when 0
#define INFO 1

#if DEBUG
#define debugMess(x) Serial.print(x)
#define debugMessln(x) Serial.println(x)
#else
#define debugMess(x)
#define debugMessln(x)
#endif

#if INFO || DEBUG
#define infoMess(x) Serial.print(x)
#define infoMessln(x) Serial.println(x)
#else
#define infoMess(x)
#define infoMessln(x)
#endif

/*******************************
  Common Libraries
*******************************/
#include <Wire.h>

/*******************************
  Encoders
*******************************/
#include <Encoder.h>
  
Encoder setEnc(7, 6);
Encoder PEnc(9, 8);
Encoder IEnc(11, 10);
Encoder DEnc(13, 12);

long setOldPosition = -999;
long setNewPosition;
long POldPosition = -999;
long PNewPosition;
long IOldPosition = -999;
long INewPosition;
long DOldPosition = -999;
long DNewPosition;

#define setMinValue -18.0
#define setMaxValue 18.0
#define PMinValue 0.0
#define PMaxValue 10.0
#define IMinValue 0.0
#define IMaxValue 10.0
#define DMinValue 0.0
#define DMaxValue 10.0

/*******************************
  Screen
*******************************/
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels

#define OLED_RESET -1       // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C // See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32

#define Line_1 0
#define Line_2 8
#define Line_3 16
#define Line_4 24
#define Column_1 0
#define Column_2 64

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

/*******************************
  MPU6050
*******************************/
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>

#define MPU_ADDRESS 0x68

Adafruit_MPU6050 mpu;

/*******************************
  L298N
*******************************/
#include <L298N.h>

const unsigned int IN1 = 2;
const unsigned int IN2 = 3;
const unsigned int EN = 1;

L298N motor(EN, IN1, IN2);

#define initialMotorSpeed 70
