#include "screen.h"
#include "config.h"

void clearLine(byte line)
{
    display.setCursor(0, line);
    display.print("                     "); // write 21 spaces which fills an entire line on a 128px wide screen with 5x7 font
}

void clearColumn(byte col, byte line)
{
    debugMess("Clearing column ");
    debugMessVar(col);
    debugMess(", line ");
    debugMessVar(line);
    debugMessln(" ...");
    debugMessLF();

    display.setCursor(col * columnWidth * charWidth, line);
    for (byte i = 0; i < columnWidth; i++) // write as many spaces as it takes to delete the text
    {
        display.print(" ");
    }
}

void clearChars(byte col, byte row, byte numChars)
{
    display.setCursor(col, row); // move the cursor to the start position

    for (byte i = 0; i < numChars; i++) // write as many spaces as column width
    {
        display.print(" ");
    }
}

void displayPID(String factor, float value)
{
    // debugMessln("Writing value on screen ...");
    int LineNo;

    if (factor == "P")
    {
        LineNo = 0;
    }
    else if (factor == "I")
    {
        LineNo = 1;
    }
    else if (factor == "D")
    {
        LineNo = 2;
    }
    else
    {
        LineNo = 3;
    }

    debugMess("Writing ");
    debugMessVar(factor);
    debugMess("-value, ");
    debugMessVar(value);
    debugMess(", on line ");
    debugMessVarln(LineNo);

    clearColumn(0, LineNo);
    display.setCursor(0, LineNo);
    display.print(factor);
    display.setCursor(4 * charWidth, LineNo);
    if (factor == "Set")
    {
        display.print(int(value));
    }
    else
    {
        display.print(value);
    }
}

void printAngle(double angle)
{
    clearColumn(1, 3);
    display.setCursor(columnWidth * charWidth, 3);
    display.print("Act ");
    display.print(angle);
}