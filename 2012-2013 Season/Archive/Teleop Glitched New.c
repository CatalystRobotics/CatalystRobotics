// Created by Christopher Su
// Catalyst Robotics 2012-2013 Season

#pragma config(Hubs,  S1, HTMotor,  HTMotor,  none,     none)
#pragma config(Hubs,  S2, HTMotor,  HTMotor,  none,     none)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Sensor, S2,     ,               sensorI2CMuxController)
#pragma config(Sensor, S3,     touchMuxer,     sensorHiTechnicTouchMux)
#pragma config(Sensor, S4,     IRseeker,       sensorHiTechnicIRSeeker1200)
#pragma config(Motor,  mtr_S1_C1_1,     motor11,       tmotorTetrix, PIDControl, reversed, encoder)
#pragma config(Motor,  mtr_S1_C1_2,     motor12,       tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C2_1,     motor21,       tmotorTetrix, PIDControl, encoder)
#pragma config(Motor,  mtr_S1_C2_2,     motor22,       tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S2_C1_1,     motorArm,      tmotorTetrix, PIDControl, reversed, encoder)
#pragma config(Motor,  mtr_S2_C1_2,      ,             tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S2_C2_1,      ,             tmotorTetrix, PIDControl, reversed, encoder)
#pragma config(Motor,  mtr_S2_C2_2,      ,             tmotorTetrix, openLoop)
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

void processWheels() {
	 motor11Power = 0;
	 motor12Power = 0;
	 motor21Power = 0;
	 motor22Power = 0;

	if(Button(CONTROLLER_A, 5))
			spinRight();
	else if(Button(CONTROLLER_A, 6))
			spinLeft();

	if (((Happy(CONTROLLER_A, JOYSTICK_L, AXIS_X) > joystickUpperThreshold) || (Happy(CONTROLLER_A, JOYSTICK_L, AXIS_X) < joystickLowerThreshold))) {
		MotorF(motor11, Happy(CONTROLLER_A, JOYSTICK_L, AXIS_X));
		MotorF(motor21, Happy(CONTROLLER_A, JOYSTICK_L, AXIS_X));
	}
	else if ((Happy(CONTROLLER_A, JOYSTICK_R, AXIS_Y) > joystickUpperThreshold) || (Happy(CONTROLLER_A, JOYSTICK_R, AXIS_Y) < joystickLowerThreshold)) {
		MotorF(motor12, Happy(CONTROLLER_A, JOYSTICK_R, AXIS_Y));
		MotorF(motor22, Happy(CONTROLLER_A, JOYSTICK_R, AXIS_Y));
	}

	if (Hat(CONTROLLER_A) == HAT_NE) {
		MotorF(motor12, 90);
		MotorF(motor22, 90);
		MotorF(motor11, 90);
		MotorF(motor21, 90);
	}
	else if (Hat(CONTROLLER_A) == HAT_NW) {
		MotorF(motor12, 90);
		MotorF(motor22, 90);
		MotorF(motor11, -90);
		MotorF(motor21, -90);
	}
	else if (Hat(CONTROLLER_A) == HAT_SW) {
		MotorF(motor12, -90);
		MotorF(motor22, -90);
		MotorF(motor11, -90);
		MotorF(motor21, -90);
	}
	else if (Hat(CONTROLLER_A) == HAT_SE) {
		MotorF(motor12, -90);
		MotorF(motor22, -90);
		MotorF(motor11, 90);
		MotorF(motor21, 90);
	}

	MotorF(motor11, motor11Power);
	MotorF(motor12, motor12Power);
	MotorF(motor21, motor21Power);
	MotorF(motor22, motor22Power);
}

void processArm() {
	 motorArmPower = 0;

	if ((Happy(CONTROLLER_B, JOYSTICK_R, AXIS_Y) > 15) || (Happy(CONTROLLER_B, JOYSTICK_R, AXIS_Y) < -15)) {
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

	MotorF(motorArm, motorArmPower);
}

void processSensors() {
	touchMultiplexerUpdate();
}

task main() {
	initializeRobot();
	for (int i=0; ; i++) {
		CatsAndCorgis();
		processSensors();
		processWheels();
		processArm();
	}
}
