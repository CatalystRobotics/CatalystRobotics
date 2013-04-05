// Created by Christopher Su
// Catalyst Robotics 2012-2013 Season

#pragma config(Hubs,  S1, HTMotor,  none,     none,     none)
#pragma config(Hubs,  S2, HTMotor,  none,     none,     none)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Sensor, S2,     ,               sensorI2CMuxController)
#pragma config(Motor,  motorA,          mtrA,          tmotorNXT, PIDControl, encoder)
#pragma config(Motor,  motorB,          mtrB,          tmotorNXT, PIDControl, encoder)
#pragma config(Motor,  motorC,          mtrC,          tmotorNXT, PIDControl, encoder)
#pragma config(Motor,  mtr_S1_C1_1,     motorD,        tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C1_2,     motorE,        tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S2_C1_1,     motorF,        tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S2_C1_2,     motorG,        tmotorTetrix, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#include "JoystickDriver.c"  //joystick things

void TeleOp() //teleop method
{
	getJoystickSettings(joystick);  //get updates from joystick

	if ( abs(joystick.joy1_y2) > 15 )
	{
    motor[motorD] = -joystick.joy1_y2*0.5;
    motor[motorG] = joystick.joy1_y2*0.5;
  }
  else
  {
    motor[motorD] = 0;
    motor[motorG] = 0;
  }

  if ( abs(joystick.joy1_y1) > 15 )
  {
    motor[motorE] = -joystick.joy1_y1*0.5;
    motor[motorF] = joystick.joy1_y1*0.5;
  }
  else
  {
    motor[motorE] = 0;
    motor[motorF] = 0;
  }
}

task main()
{
  while (true)
  {
    TeleOp();
  }


}
