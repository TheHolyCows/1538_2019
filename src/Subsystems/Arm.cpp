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
	m_Motor->SetControlMode(CowLib::CowMotorController::MOTIONMAGIC);
	m_Position = 0;
	m_DegreesPerTick = degreesPerTick;
    //m_MaxSpeed = maxSpeed;
	
	
	//SetCurrentLimit();

	m_UpLimit = upLimit;
	m_DownLimit = downLimit;

	m_Name = name;
    m_PeakOutput = peakOutput;

	ResetConstants(upLimit, downLimit, peakOutput);
	m_Motor->SetInverted(false);
}

bool Arm::AtTarget()
{
	std::string toleranceName = m_Name + "_TOLERANCE";
	return (fabs(m_Position - m_Motor->GetPosition() * m_DegreesPerTick) < CONSTANT(toleranceName.c_str()));
}

void Arm::SetPosition(float position)
{
	//if(position < m_DownLimit)
	//{
	//	position = m_DownLimit;
	//}
	//else if(position > m_UpLimit)
	//{
//		position = m_UpLimit;
//	}
	//position = position / m_DegreesPerTick;
    //m_CalculateGain = true;
	m_Position = position;
}

float Arm::GetSetpoint()
{
	return m_Position;
}

float Arm::GetPosition()
{
    return 0;
	//return m_Motor->GetPosition()*m_DegreesPerTick;
}

void Arm::ResetConstants(double upLimit, double downLimit, double peakOutput)
{
	m_Motor->SetPIDGains(CONSTANT("ARM_P")*CONSTANT("DEBUG_PID"), CONSTANT("ARM_I")*CONSTANT("DEBUG_PID"), CONSTANT("ARM_D")*CONSTANT("DEBUG_PID"), 0, 1);
	m_Motor->SetMotionMagic(CONSTANT("ARM_ACCEL"), CONSTANT("ARM_VELOCITY"));
	std::cout << "In the arm reset constants" << std::endl;
}


void Arm::handle()
{
    if(m_Motor)
    {
        m_Motor->Set(m_Position);
    }
    //SmartDashboard::PutNumber("Arm", (m_Motor->GetPosition()-m_PlanetaryHardstop));
	std::cout << m_Name << " position: " << m_Position << std::endl;
}
void Arm::SetCurrentLimit(float peakAmps, float continuousAmps, int peakDuration, int ms)
{
	//m_Motor->GetInternalMotor()->ConfigPeakCurrentLimit(peakAmps, ms);
	//m_Motor->GetInternalMotor()->ConfigPeakCurrentDuration(peakDuration, ms);
	//m_Motor->GetInternalMotor()->ConfigContinuousCurrentLimit(continuousAmps, ms);
	//m_Motor->GetInternalMotor()->EnableCurrentLimit(true);
}

Arm::~Arm()
{
	delete m_Motor;
}

