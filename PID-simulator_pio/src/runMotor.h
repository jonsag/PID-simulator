/*
Print some informations in Serial Monitor
*/
void printSomeInfo()
{
    Serial.print("Motor is moving = ");
    Serial.print(motor.isMoving());
    Serial.print(" at speed = ");
    Serial.println(motor.getSpeed());
}

void motorTest()
{
    motor.forward(); // Tell the motor to go forward (may depend by your wiring)
    // Alternative method:
    // motor.run(L298N::FORWARD);

    printSomeInfo(); // print the motor status in the serial monitor

    delay(3000);

    motor.stop(); // Stop
    // Alternative method:
    // motor.run(L298N::STOP);

    printSomeInfo();

    motor.setSpeed(255); // Change speed

    delay(3000);

    motor.backward(); // Tell the motor to go back (may depend by your wiring)
    // Alternative method:
    // motor.run(L298N::BACKWARD);

    printSomeInfo();

    motor.setSpeed(120);

    delay(3000);

    motor.stop(); // Stop

    printSomeInfo();

    delay(3000);
}


