#pragma config(Sensor, S4,     analogSensor,      sensorAnalogActive)
#pragma config(Sensor, S4,     irsensor2,      sensorHiTechnicIRSeeker1200)
#pragma config(Motor,  motorA,          nxtMotorA,     tmotorNXT, openLoop)
#pragma config(Motor,  motorB,          nxtMotorB,     tmotorNXT, openLoop)
#pragma config(Motor,  motorC,          nxtMotorB,     tmotorNXT, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

//short ThatWasGramaticallyCorrectIThink = 0;
short shortshortshort = 0;

task main()
{
	while(true) {
		//ThatWasGramaticallyCorrectIThink = SensorValue[S3];
		shortshortshort = SensorValue[S4];
		//nxtDisplayCenteredTextLine(3, "%d", ThatWasGramaticallyCorrectIThink);
		nxtDisplayCenteredTextLine(4, "%d", shortshortshort);
		wait10Msec(10);
		eraseDisplay();
	}
}
