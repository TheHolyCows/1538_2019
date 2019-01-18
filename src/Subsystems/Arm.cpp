/*
 * Arm.cpp
 *
 *  Created on: Feb 18, 2018
 *      Author: kchau
 */

#include <Subsystems/Arm.h>
#include <String>
#include <iostream>
#include <frc/Timer.h>

Arm::Arm(int motorController, double upLimit, double downLimit)
{
	m_Motor = new CowLib::CowMotorController(motorController);
	m_Motor->SetControlMode(CowLib::CowMotorController::POSITION);
	m_Position = 0;
	
	SetCurrentLimit();

	m_UpLimit = upLimit;
	m_DownLimit = downLimit;
}

void Arm::SetPosition(float position)
{
	if(position < m_DownLimit)
	{
		position = m_DownLimit;
	}
	else if(position > m_UpLimit)
	{
		position = m_UpLimit;
	}

	m_Position = position;
}

float Arm::GetSetpoint()
{
	return m_Position;
}

void Arm::ResetConstants(double upLimit, double downLimit)
{
	m_UpLimit = upLimit;
	m_DownLimit = downLimit;
	m_Position = CONSTANT("ARM_UP");
	m_Motor->SetPIDGains(CONSTANT("ARM_P"), CONSTANT("ARM_I"), CONSTANT("ARM_D"), 0);
	SetCurrentLimit();
	std::cout << "In the arm reset constants" << std::endl;
}

// void Arm::DisabledCalibration()
// {
// 	//std::cout << "Current hardstop value: " << m_PlanetaryHardstop << " ArmPos: " << m_Motor->GetPosition() << std::endl;
// 	if(m_Motor->GetPosition() > m_PlanetaryHardstop)
// 	{
// 		m_PlanetaryHardstop = m_Motor->GetPosition();
// 	}
// }

void Arm::handle()
{
	if(m_Motor)
	{
		m_Motor->Set(m_Position);
	}

    //SmartDashboard::PutNumber("Arm", (m_Motor->GetPosition()-m_PlanetaryHardstop));
	std::cout << "Current arm: " << m_Motor->GetPosition() << std::endl;
}
void Arm::SetCurrentLimit()
{
	// m_Motor->GetInternalMotor()->ConfigPeakCurrentLimit(60, 10);
	// m_Motor->GetInternalMotor()->ConfigPeakCurrentDuration(300, 10);
	// m_Motor->GetInternalMotor()->ConfigContinuousCurrentLimit(CONSTANT("ARM_CURRENT_LIMIT"), 10);
	// m_Motor->GetInternalMotor()->EnableCurrentLimit(true);
}

Arm::~Arm()
{
	delete m_Motor;
}

