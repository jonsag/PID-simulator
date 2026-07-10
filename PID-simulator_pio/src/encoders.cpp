#include "config.h"
#include "screen.h"
#include "encoders.h"

PidValues readEncoders()
{
    PidValues values; // create the container

    boolean showValues = false;

    setEnc.tick();
    setNewPosition = setEnc.getPosition();
    if (setNewPosition < setMinValue)
    {
        setEnc.setPosition(setMinValue);
        setNewPosition = setMinValue;
    }
    else if (setNewPosition > setMaxValue)
    {
        setEnc.setPosition(setMaxValue);
        setNewPosition = setMaxValue;
    }
    if (setNewPosition != setOldPosition)
    {
        setOldPosition = setNewPosition;
        debugMess("Set value: ");
        debugMessVarln(setNewPosition);
        displayPID("Set", setNewPosition);
        // showValues = true;
    }

    PEnc.tick();
    PNewPosition = PEnc.getPosition();
    if (PNewPosition < PMinValue)
    {
        PEnc.setPosition(PMinValue);
        PNewPosition = PMinValue;
    }
    else if (PNewPosition > PMaxValue)
    {
        PEnc.setPosition(PMaxValue);
        PNewPosition = PMaxValue;
    }
    if (PNewPosition != POldPosition)
    {
        POldPosition = PNewPosition;
        debugMess("P change\t");
        debugMess("P value:   ");
        debugMessVarln(PNewPosition);
        values.p = float(PNewPosition) / 10;
        displayPID("P", values.p);
        showValues = true;
    }

    IEnc.tick();
    INewPosition = IEnc.getPosition();
    if (INewPosition < IMinValue)
    {
        IEnc.setPosition(IMinValue);
        INewPosition = IMinValue;
    }
    else if (INewPosition > IMaxValue)
    {
        IEnc.setPosition(IMaxValue);
        INewPosition = IMaxValue;
    }
    if (INewPosition != IOldPosition)
    {
        IOldPosition = INewPosition;
        debugMess("I change\t");
        debugMess("I value:   ");
        debugMessVarln(INewPosition);
        values.i = float(INewPosition) / 10;
        displayPID("I", values.i);
        showValues = true;
    }

    DEnc.tick();
    DNewPosition = DEnc.getPosition();
    if (DNewPosition < DMinValue)
    {
        DEnc.setPosition(DMinValue);
        DNewPosition = DMinValue;
    }
    else if (DNewPosition > DMaxValue)
    {
        DEnc.setPosition(DMaxValue);
        DNewPosition = DMaxValue;
    }
    if (DNewPosition != DOldPosition)
    {
        DOldPosition = DNewPosition;
        debugMess("D change\t");
        debugMess("D value:   ");
        debugMessVarln(DNewPosition);
        values.d = float(DNewPosition) / 10;
        displayPID("D", values.d);
        showValues = true;
    }

#if INFO || DEBUG
    if (showValues)
    {
        debugMess("Kp: ");
        debugMessVar(values.p);
        debugMess("\tKi: ");
        debugMessVar(values.i);
        debugMess("\tKp: ");
        debugMessVarln(values.d);
    }
#endif

    return values; // return the whole container at once
}