#include "l298n.h"
#include "config.h"

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
  // motor.run(L298N::FORWARD); // Alternative method
  printSomeInfo(); // print the motor status in the serial monitor
  delay(3000);

  motor.stop(); // Stop
  // motor.run(L298N::STOP); // Alternative method
  printSomeInfo();

  motor.setSpeed(255); // Change speed
  delay(3000);

  motor.backward(); // Tell the motor to go back (may depend by your wiring)
  // motor.run(L298N::BACKWARD); // Alternative method
  printSomeInfo();
  motor.setSpeed(120);
  delay(3000);

  motor.stop(); // Stop
  printSomeInfo();
  delay(3000);
}

void controlMotor(float pidOutput)
{
  int speed = abs(pidOutput); // get the absolute value of the speed

  if (speed < 10) // allow some deadzone
  {
    motor.stop();
    return;
  }

  if (pidOutput > 0)
  {
    motor.setSpeed(speed); // positive value, turn forwards
    motor.forward();
  }
  else
  {
    motor.backward();      // negative value, backwards
    motor.setSpeed(speed); // some libraries wants the speed before/after the direction
  }
}
