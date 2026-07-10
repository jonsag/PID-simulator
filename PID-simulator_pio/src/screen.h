#pragma once
#include <Arduino.h>

void clearLine(byte LineNo);

void clearColumn(byte ColumnNo, byte LineNo);

void clearChars(byte col, byte row, byte numChars);

void displayPID(String factor, float value);

void printAngle(double angleX);
