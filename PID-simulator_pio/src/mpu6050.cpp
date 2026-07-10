#include "config.h"
#include "mpu6050.h"
#include "maths.h"
#include "screen.h"

void readMPU()
{
    mpu6050.update(); // read values
    angle = mpu6050.getAngleX();

    if (millis() - startMillis < measureTime)
    {
        /*******************************
            Measure angles
        *******************************/
        values++;

        // mpu6050.update(); // read values

        angleXAcc += mpu6050.getAngleX();
    }
    else
    {
        /*******************************
          Calculate angles
        *******************************/
        angleX = round1dec(angleXAcc / values); // calculate averages and round
        if (angleX != oldAngleX)
        {
            printAngle(angleX);
            oldAngleX = angleX;
        }

        angleXAcc = 0; // reset all accumulated values

        values = 0;

        startMillis = millis();
    }

    debugMess("\tAngles, X: ");
    debugMessVar(angleX);
    /*debugMess("\tY: ");
    debugMessVar(angleY);
    debugMess("\tZ: ");
    debugMessVar(angleZ);*/

    debugMess("\t");
    debugMessVar(values);
    debugMess(" values");
    debugMessLF();
}