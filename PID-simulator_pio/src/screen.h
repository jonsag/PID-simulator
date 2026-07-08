void ClearLine(int LineNo)
{
    debugMess("Clearing line ");
    debugMessln(LineNo);
    debugMess(" ...");
    debugMessln();

    int y;

    switch (LineNo)
    {
    case 2:
        y = Line_2;
        break;
    case 3:
        y = Line_3;
        break;
    default:
        y = Line_1;
        break;
    }
    // Syntax: display.fillRect(X-start, Y-start, bredd, höjd, färg);
    display.fillRect(Column_1, y, SCREEN_WIDTH, 8, SSD1306_BLACK);
    display.display();
}

void ClearColumn(int ColumnNo, int LineNo)
{
    debugMess("Clearing column ");
    debugMess(ColumnNo);
    debugMess(", line ");
    debugMess(LineNo);
    debugMess(" ...");
    debugMessln();

    int x;
    int y;

    switch (ColumnNo)
    {
    case 2:
        x = Column_2;
        break;
    default:
        x = Column_1;
        break;
    }

    switch (LineNo)
    {
    case 2:
        y = Line_2;
        break;
    case 3:
        y = Line_3;
        break;
    default:
        y = Line_1;
        break;
    }

    // Syntax: display.fillRect(X-start, Y-start, bredd, höjd, färg);
    display.fillRect(x, y, SCREEN_WIDTH / 2, 8, SSD1306_BLACK);
    display.display();
}

void displayPID(String factor, long value)
{
    // debugMessln("Writing value on screen ...");

    if (factor == "P")
    {
        debugMess("Writing P-value, ");
        debugMess(value);
        debugMessln(", on line 1");
        ClearColumn(1, 1);
        display.setCursor(Column_1, Line_1);
        display.write("P");
        display.setCursor(Column_1 + 1 * textWidth + 2, Line_1);
        display.print(value);
        display.display();
    }
    else if (factor == "I")
    {
        debugMess("Writing I-value, ");
        debugMess(value);
        debugMessln(", on line 2");
        ClearColumn(1, 2);
        display.setCursor(Column_1, Line_2);
        display.write("I");
        display.setCursor(Column_1 + 1 * textWidth + 2, Line_2);
        display.print(value);
        display.display();
    }
    else if (factor == "D")
    {
        debugMess("Writing D-value, ");
        debugMess(value);
        debugMessln(", on line 3");
        ClearColumn(1, 3);
        display.setCursor(Column_1, Line_3);
        display.write("D");
        display.setCursor(Column_1 + 1 * textWidth + 2, Line_3);
        display.print(value);
        display.display();
    }
    else
    {
        debugMess("Writing Set-value, ");
        debugMess(value);
        debugMessln(", on line 4");
        ClearColumn(1, 4);
        display.setCursor(Column_1, Line_4);
        display.write("Set ");
        display.setCursor(Column_1 + 3 * textWidth + 2, Line_4);
        display.print(value);
        display.display();
    }
}