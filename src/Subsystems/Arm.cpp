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
	
	
	//SetCurrentLimit();

	m_UpLimit = upLimit;
	m_DownLimit = downLimit;

	m_Name = name;
    m_PeakOutput = peakOutput;

	ResetConstants(upLimit, downLimit, peakOutput);
	m_Motor->SetInverted(changeDirection);
}

bool Arm::AtTarget()
{
	std::string toleranceName = m_Name + "_TOLERANCE";
	return (fabs(m_Position - m_Motor->GetPosition() * m_DegreesPerTick) < CONSTANT(toleranceName.c_str()));
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
    
    //if (position < m_Position)
    //{
    //    position *= 0.68;
    //}

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
    m_PeakOutput = 0;
	std::string pConstant = m_Name + "_P";
	std::string iConstant = m_Name + "_I";
	std::string dConstant = m_Name + "_D";

	m_Motor->SetPIDGains(CONSTANT(pConstant.c_str())*CONSTANT("DEBUG_PID"), CONSTANT(iConstant.c_str())*CONSTANT("DEBUG_PID"), CONSTANT(dConstant.c_str())*CONSTANT("DEBUG_PID"), 0, m_PeakOutput);
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
	std::string slowConstantStr = m_Name + "_SC";
	std::string pConstant = m_Name + "_P";
	std::string iConstant = m_Name + "_I";
	std::string dConstant = m_Name + "_D";
    float slowConstant = 1;
    if ((GetPosition() > 0))
    {
        if (GetSetpoint()*GetDegreesPerTick() < GetPosition())
        {
            slowConstant = CONSTANT(slowConstantStr.c_str());
        }
	    m_Motor->SetPIDGains(CONSTANT(pConstant.c_str())*CONSTANT("DEBUG_PID")*slowConstant, CONSTANT(iConstant.c_str())*CONSTANT("DEBUG_PID")*slowConstant, CONSTANT(dConstant.c_str())*CONSTANT("DEBUG_PID")*slowConstant, 0, m_PeakOutput);
    }
    else
    {
        if (GetSetpoint()*GetDegreesPerTick() > GetPosition())
        {
            slowConstant = CONSTANT(slowConstantStr.c_str());
        }
	    m_Motor->SetPIDGains(CONSTANT(pConstant.c_str())*CONSTANT("DEBUG_PID")*slowConstant, CONSTANT(iConstant.c_str())*CONSTANT("DEBUG_PID")*slowConstant, CONSTANT(dConstant.c_str())*CONSTANT("DEBUG_PID")*slowConstant, 0, m_PeakOutput);
    }
	if(m_Motor)
	{
		m_Motor->Set(m_Position);
	}

    //SmartDashboard::PutNumber("Arm", (m_Motor->GetPosition()-m_PlanetaryHardstop));
	//std::cout << m_Name << " position: " << m_Motor->GetPosition() << std::endl;
}
void Arm::SetCurrentLimit(float peakAmps, float continuousAmps, int peakDuration, int ms)
{
	m_Motor->GetInternalMotor()->ConfigPeakCurrentLimit(peakAmps, ms);
	m_Motor->GetInternalMotor()->ConfigPeakCurrentDuration(peakDuration, ms);
	m_Motor->GetInternalMotor()->ConfigContinuousCurrentLimit(continuousAmps, ms);
	m_Motor->GetInternalMotor()->EnableCurrentLimit(true);
}

Arm::~Arm()
{
	delete m_Motor;
}

