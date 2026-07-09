#include "screen.h"
#include "config.h"

void ClearLine(int LineNo)
{
    debugMess("Clearing line ");
    debugMessVar(LineNo);
    debugMessln(" ...");
    debugMessLF();

    // Syntax: display.fillRect(X-start, Y-start, bredd, höjd, färg);
    display.fillRect(0, LineNo * lineHeight, SCREEN_WIDTH, 8, SSD1306_BLACK);
    display.display();
}

void ClearColumn(int ColumnNo, int LineNo)
{
    debugMess("Clearing column ");
    debugMessVar(ColumnNo);
    debugMess(", line ");
    debugMessVar(LineNo);
    debugMessln(" ...");
    debugMessLF();

    // Syntax: display.fillRect(X-start, Y-start, bredd, höjd, färg);
    display.fillRect(ColumnNo * columnWidth, LineNo * lineHeight, SCREEN_WIDTH / 2, 8, SSD1306_BLACK);
    display.display();
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
    ClearColumn(0, LineNo);
    display.setCursor(0 * columnWidth, LineNo * lineHeight);
    display.print(factor);
    display.setCursor(0 * columnWidth + 3 * textWidth + 2, LineNo * lineHeight);
    if (factor == "Set")
    {
        display.print(int(value));
    }
    else
    {
        display.print(value);
    }
    display.display();
}