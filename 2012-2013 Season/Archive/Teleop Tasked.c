// Created by Christopher Su
// Catalyst Robotics 2012-2013 Season

#pragma config(Hubs,  S1, HTMotor,  HTMotor,  none,     none)
#pragma config(Hubs,  S2, HTMotor,  HTMotor,  none,     none)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Sensor, S2,     ,               sensorI2CMuxController)
#pragma config(Sensor, S3,     touchMuxer,     sensorHiTechnicTouchMux)
#pragma config(Sensor, S4,     IRseeker,       sensorHiTechnicIRSeeker1200)
#pragma config(Motor,  mtr_S1_C1_1,     motor12,       tmotorTetrix, PIDControl, reversed, encoder)
#pragma config(Motor,  mtr_S1_C1_2,     motorE,        tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C2_1,     motor11,       tmotorTetrix, PIDControl, encoder)
#pragma config(Motor,  mtr_S1_C2_2,     motorG,        tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S2_C1_1,     motorArm,      tmotorTetrix, PIDControl, reversed, encoder)
#pragma config(Motor,  mtr_S2_C1_2,     motorI,        tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S2_C2_1,     motor21,       tmotorTetrix, PIDControl, reversed, encoder)
#pragma config(Motor,  mtr_S2_C2_2,     motor22,       tmotorTetrix, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

//#pragma DebuggerWindows("debugStream")
//#pragma DebuggerWindows("joystickSimple")

#include "JoystickDriver.c"
#include "../Headers/CSEnumerated.h"
#include "../Headers/CSMethods.h"

int motor11Power = 0;
int motor12Power = 0;
int motor21Power = 0;
int motor22Power = 0;
int motorArmPower = 0;

void initializeRobot() { return; }

task ProcessControllerA() {
	for (int i=0;; i++) {
		CatsAndCorgis();

		motor11Power = 0;
		motor12Power = 0;
		motor21Power = 0;
		motor22Power = 0;

		if(Button(CONTROLLER_A, 5))
			spinRight();
		else if(Button(CONTROLLER_A, 6))
			spinLeft();

		if (((Happy(CONTROLLER_A, JOYSTICK_L, AXIS_X) > JOYSTICK_UPPER_THRESHOLD) || (Happy(CONTROLLER_A, JOYSTICK_L, AXIS_X) < JOYSTICK_LOWER_THRESHOLD))) {
			motor12Power = Happy(CONTROLLER_A, JOYSTICK_L, AXIS_X);
			motor22Power = Happy(CONTROLLER_A, JOYSTICK_L, AXIS_X);
			motor11Power = Happy(CONTROLLER_A, JOYSTICK_L, AXIS_X);
			motor21Power = Happy(CONTROLLER_A, JOYSTICK_L, AXIS_X);
		}
		else if ((Happy(CONTROLLER_A, JOYSTICK_R, AXIS_Y) > JOYSTICK_UPPER_THRESHOLD) || (Happy(CONTROLLER_A, JOYSTICK_R, AXIS_Y) < JOYSTICK_LOWER_THRESHOLD)) {
			motor12Power = Happy(CONTROLLER_A, JOYSTICK_R, AXIS_Y);
			motor22Power = Happy(CONTROLLER_A, JOYSTICK_R, AXIS_Y);
			motor11Power = -Happy(CONTROLLER_A, JOYSTICK_R, AXIS_Y);
			motor21Power = -Happy(CONTROLLER_A, JOYSTICK_R, AXIS_Y);
		}

		if (Hat(CONTROLLER_A) == HAT_NE) {
			motor12Power = 90;
			motor22Power = 90;
		}
		else if (Hat(CONTROLLER_A) == HAT_NW) {
			motor11Power = 90;
			motor21Power = 90;
		}
		else if (Hat(CONTROLLER_A) == HAT_SW) {
			motor12Power = 90;
			motor22Power = 90;
		}
		else if (Hat(CONTROLLER_A) == HAT_SE) {
			motor11Power = 90;
			motor21Power = 90;
		}

		wait1Msec(CONTROLLER_A_UPDATE_DELAY);
	}
}

task ProcessControllerB() {
	for (int i=0;; i++) {
		CatsAndCorgis();
		motorArmPower = 0;

		if ((Happy(CONTROLLER_B, JOYSTICK_R, AXIS_Y) > JOYSTICK_UPPER_THRESHOLD) || (Happy(CONTROLLER_B, JOYSTICK_R, AXIS_Y) < JOYSTICK_LOWER_THRESHOLD)) {
			if(!touchMuxer1 && !touchMuxer2)
				motorArmPower = Happy(CONTROLLER_B, JOYSTICK_R, AXIS_Y)*2;
			else if (!touchMuxer1 && (Happy(CONTROLLER_B, JOYSTICK_R, AXIS_Y)*2 < 0))
				motorArmPower = Happy(CONTROLLER_B, JOYSTICK_R, AXIS_Y)*2;
			else if (!touchMuxer2 && (Happy(CONTROLLER_B, JOYSTICK_R, AXIS_Y)*2 > 0))
				motorArmPower = Happy(CONTROLLER_B, JOYSTICK_R, AXIS_Y)*2;
			else if (!touchMuxer1 || !touchMuxer2)
				motorArmPower = 0;
		}
		else
			motorArmPower = 0;

		if (Button(CONTROLLER_B, 4)) {
			ArmUpDistance(0.25);
			return;
		}
		else if (Button(CONTROLLER_B, 2)) {
			ArmDownDistance(0.25);
			return;
		}

		wait1Msec(CONTROLLER_B_UPDATE_DELAY);
	}
}

task UpdateMotors() {
	for (int i=0;; i++) {
		MotorF(motor11, motor11Power);
		MotorF(motor12, motor12Power);
		MotorF(motor21, motor21Power);
		MotorF(motor22, motor22Power);
		MotorF(motorArm, motorArmPower);

		wait1Msec(MOTOR_UPDATE_DELAY);
	}
}

task UpdateSensors() {
	for (int i=0;; i++) {
		touchMultiplexerUpdate();

		wait1Msec(SENSOR_UPDATE_DELAY);
	}
}

task main() {
	initializeRobot();
	//waitForStart();

	StartTask(ProcessControllerA);
	StartTask(ProcessControllerB);
	StartTask(UpdateMotors);
	StartTask(UpdateSensors);

	while(1) wait10Msec(1000);
}
