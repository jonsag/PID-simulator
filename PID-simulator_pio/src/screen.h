#pragma once
#include <Arduino.h>

void ClearLine(int LineNo);

void ClearColumn(int ColumnNo, int LineNo);

void displayPID(String factor, float value);
 