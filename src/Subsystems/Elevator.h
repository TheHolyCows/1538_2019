/*
 * Elevator.h
 *
 *  Created on: Feb 18, 2018
 *      Author: theholycows
 */

#ifndef SRC_SUBSYSTEMS_ELEVATOR_H_
#define SRC_SUBSYSTEMS_ELEVATOR_H_
#include "../CowLib/CowMotorController.h"
#include "../CowConstants.h"
#include <frc/WPILib.h>
#include "../CowLib/CowPid.h"

class Elevator {
private:
	CowLib::CowMotorController *m_MotorRight;
	CowLib::CowMotorController *m_MotorLeft;
	float m_Speed;
	frc::Encoder *m_Encoder;
	CowLib::CowPID *m_PID;
	float m_Position;
public:
	Elevator(int motorRight, int motorLeft, int encoderA, int encoderB);
	virtual ~Elevator();
	void handle();
	void SetSpeed(float speed);
	void SetPosition(float position);
	float GetSetPoint()
	{
		return m_Position;
	}
	float GetDistance();
	void ResetConstants();
	bool AtTarget();

};

#endif /* SRC_SUBSYSTEMS_ELEVATOR_H_ */
