/*
 * Arm.h
 *
 *  Created on: Feb 18, 2018
 *      Author: kchau
 */

#ifndef SRC_SUBSYSTEMS_ARM_H_
#define SRC_SUBSYSTEMS_ARM_H_

#include "../CowLib/CowMotorController.h"
#include "../CowConstants.h"
#include <frc/WPILib.h>
#include <frc/Timer.h>



class Arm 
{
public:
	Arm(int motorController, double upLimit, double downLimit);
	void SetPosition(float position);
	float GetSetpoint();
	//void DisabledCalibration();
	void ResetConstants(double upLimit, double downLimit);
	void handle();

	void SetCurrentLimit();
	virtual ~Arm();

private:
	CowLib::CowMotorController *m_Motor;
	float m_Position;
	float m_UpLimit;
	float m_DownLimit;
};

#endif /* SRC_SUBSYSTEMS_ARM_H_ */
