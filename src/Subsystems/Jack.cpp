#include <Subsystems/Jack.h>
#include <String>
#include <iostream>
#include <frc/Timer.h>

Jack::Jack(int motorController, bool flipDirection)
{
    m_Motor = new CowLib::CowMotorController(motorController);
    m_Motor->SetControlMode(CowLib::CowMotorController::POSITION);
    m_Position = 0;
    ResetConstants();
    m_Motor->SetInverted(flipDirection);
}

void Jack::handle()
{
    m_Motor->Set(m_Position);
}

void Jack::SetPosition(float position)
{
    m_Position = position;
}

void Jack::ResetConstants()
{
    m_Motor->SetPIDGains(CONSTANT("JACK_P"), 0, 0, 0, 1);
}

Jack::~Jack()
{
    delete m_Motor;
}
