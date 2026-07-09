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
        infoMess("Set value: ");
        infoMessVarln(setNewPosition);
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
        infoMess("P change\t");
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
        infoMess("I change\t");
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
        infoMess("D change\t");
        debugMess("D value:   ");
        debugMessVarln(DNewPosition);
        values.d = float(DNewPosition) / 10;
        displayPID("D", values.d);
        showValues = true;
    }

#if INFO || DEBUG
    if (showValues)
    {
        infoMess("Kp: ");
        infoMessVar(values.p);
        infoMess("\tKi: ");
        infoMessVar(values.i);
        infoMess("\tKp: ");
        infoMessVarln(values.d);
    }
#endif

    return values; // return the whole container at once
}