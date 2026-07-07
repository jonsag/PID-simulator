void ClearLine(int LineNo)
{
    debugMess("Clearing line ");
    debugMessln(LineNo);
    debugMessln();
    
    // Syntax: display.fillRect(X-start, Y-start, bredd, höjd, färg);
    display.fillRect(Column_1, LineNo, SCREEN_WIDTH, 8, SSD1306_BLACK); 
    display.display();


    /*display.setCursor(Column_1, LineNo); // Start at top-left corner
    display.write("                      ");
    display.display();*/
}