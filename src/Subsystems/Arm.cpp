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

Arm::Arm(int motorController, double maxSpeed, double upLimit, double downLimit, std::string name, bool changeDirection, double degreesPerTick, double peakOutput)
{
	m_Motor = new CowLib::CowMotorController(motorController);
	m_Motor->SetControlMode(CowLib::CowMotorController::POSITION);
	m_Position = 0;
	m_DegreesPerTick = degreesPerTick;
    //m_MaxSpeed = maxSpeed;
	
	
	SetCurrentLimit();

	m_UpLimit = upLimit;
	m_DownLimit = downLimit;

	m_Name = name;

	ResetConstants(upLimit, downLimit, peakOutput);
	m_Motor->SetInverted(changeDirection);
}

bool Arm::AtTarget()
{
	return (fabs(m_Position - m_Motor->GetPosition() * m_DegreesPerTick) < CONSTANT("ARM_TOLERANCE"));
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
	position = position / m_DegreesPerTick;

	m_Position = position;
}

float Arm::GetSetpoint()
{
	return m_Position;
}

float Arm::GetPosition()
{
	return m_Motor->GetPosition()*m_DegreesPerTick;
}

void Arm::ResetConstants(double upLimit, double downLimit, double peakOutput)
{
	m_UpLimit = upLimit;
	m_DownLimit = downLimit;
	m_Position = 0;
	std::string pConstant = m_Name + "_P";
	std::string iConstant = m_Name + "_I";
	std::string dConstant = m_Name + "_D";

	m_Motor->SetPIDGains(CONSTANT(pConstant.c_str())*CONSTANT("DEBUG_PID"), CONSTANT(iConstant.c_str())*CONSTANT("DEBUG_PID"), CONSTANT(dConstant.c_str())*CONSTANT("DEBUG_PID"), 0, peakOutput);
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
	//std::cout << m_Name << " position: " << m_Motor->GetPosition() << std::endl;
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

