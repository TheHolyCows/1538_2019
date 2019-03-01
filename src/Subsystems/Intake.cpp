#include <Subsystems/Intake.h>
#include <String>
#include <iostream>
#include <frc/Timer.h>

Intake::Intake(int motorController)
{
    m_Motor = new CowLib::CowMotorController(motorController);
    m_Speed = 0;
    m_LimitCurrent = false;
    m_Current = 0;
    m_CurrentLPF = new CowLib::CowLPF(CONSTANT("INTAKE_CURRENT_LPF"));
    m_Hold = false;
	m_PID = new CowLib::CowPID(CONSTANT("INTAKE_P"), CONSTANT("INTAKE_I"), CONSTANT("INTAKE_D"), CONSTANT("INTAKE_F"));
    //m_Motor->SetPeakCurrent(CONSTANT("INTAKE_PEAK_CURRENT"), CONSTANT("INTAKE_PEAK_DURATION"));
}

void Intake::SetSpeed(float speed, bool limitCurrent)
{
    m_LimitCurrent = limitCurrent;
    m_Speed = speed;
}

void Intake::handle()
{
    float latestCurrent = m_Motor->GetOutputCurrent();
    m_Current = m_CurrentLPF->Calculate(latestCurrent);
    if (m_Current > CONSTANT("INTAKE_CURRENT_THRESHOLD") && m_LimitCurrent)
    {
        m_Hold = true;
    }
    if (m_Hold)
    {
        m_PID->SetSetpoint(CONSTANT("INTAKE_CURRENT"));
        m_Motor->Set(-m_PID->Calculate(latestCurrent));
    }
    else
    {
        m_Motor->Set(m_Speed);
    }
}

void Intake::ResetConstants()
{
    //m_Motor->SetPeakCurrent(CONSTANT("INTAKE_PEAK_CURRENT"), CONSTANT("INTAKE_PEAK_DURATION"));
    m_CurrentLPF->UpdateBeta(CONSTANT("INTAKE_CURRENT_LPF"));
    m_PID->UpdateConstants(CONSTANT("INTAKE_P"), CONSTANT("INTAKE_I"), CONSTANT("INTAKE_D"), CONSTANT("INTAKE_F"));
}

Intake::~Intake()
{
    delete m_Motor;
}
