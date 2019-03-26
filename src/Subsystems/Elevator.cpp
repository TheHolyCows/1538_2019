/*
 * Elevator.cpp
 *
 *  Created on: Feb 18, 2018
 *      Author: theholycows
 */

#include <Subsystems/Elevator.h>
#include <String>
#include <iostream>
#include "../CowLib/Utility.h"

Elevator::Elevator(int motorRight, int motorLeft, int encoderA, int encoderB)
{
    m_MotorLeftID = motorLeft;
	m_MotorRight = new CowLib::CowMotorController(motorRight);
	m_MotorLeft = new CowLib::CowMotorController(motorLeft);
	m_Speed = 0;
    m_Position = 0;
    m_MotorLeft->SetControlMode(CowLib::CowMotorController::MOTIONMAGIC);
    m_EncoderInchPerTick = CONSTANT("ELEVATOR_INCH_PER_TICK");
    ResetConstants();
    m_MotorLeft->SetInverted(false);
    m_MotorRight->SetControlMode(CowLib::CowMotorController::FOLLOWER);
    //m_MotorRight->GetInternalMotor()->SetInverted(true);
    m_MotorRight->GetInternalMotor()->SetInverted(true);
}

void Elevator::SetSpeed(float speed)
{
	m_Speed = speed;
}

void Elevator::SetPosition(float position)
{
	m_Position = position;
	if(m_Position < CONSTANT("ELEVATOR_MIN"))
	{
		m_Position = CONSTANT("ELEVATOR_MIN");
	}
	else if(m_Position > CONSTANT("ELEVATOR_MAX"))
	{
		m_Position = CONSTANT("ELEVATOR_MAX");
	}
}

float Elevator::GetDistance()
{
	//return m_Encoder->GetDistance();
}

void Elevator::ResetConstants()
{
	m_MotorLeft->SetPIDGains(CONSTANT("ELEVATOR_P")*CONSTANT("DEBUG_PID"), CONSTANT("ELEVATOR_I")*CONSTANT("DEBUG_PID"), CONSTANT("ELEVATOR_D")*CONSTANT("DEBUG_PID"), 0, 1);
	m_MotorLeft->SetMotionMagic(CONSTANT("ELEVATOR_ACCEL"), CONSTANT("ELEVATOR_VELOCITY"));
	std::cout << "In the elevator reset constants" << std::endl;
    m_EncoderInchPerTick = CONSTANT("ELEVATOR_INCH_PER_TICK");
}
bool Elevator::AtTarget()
{
    return true;
	//return (fabs(m_Position - m_Encoder->GetDistance()) < CONSTANT("ELEVATOR_TOLERANCE"));
}
void Elevator::handle()
{
	//float currentPosition = m_Encoder->GetDistance();
	//m_MotorRight->Set(-pidOutput);
    m_MotorLeft->Set(m_Position / m_EncoderInchPerTick);
    m_MotorRight->Set(m_MotorLeftID);

	//std::cout << "Current elevator: " << currentPosition << " PID: " << pidOutput << std::endl;
}


Elevator::~Elevator()
{
	delete m_MotorRight;
	delete m_MotorLeft;
	//delete m_Encoder;
}

