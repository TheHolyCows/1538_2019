#include <Subsystems/Intake.h>
#include <String>
#include <iostream>
#include <frc/Timer.h>

Intake::Intake(int motorController, bool autoHold, float autoHoldSpeed, float lpfBeta, float currentThreshold)
{
    m_Motor = new CowLib::CowMotorController(motorController);
    m_Speed = 0;
    m_LimitCurrent = false;
    m_Current = 0;
    m_CurrentThreshold = currentThreshold;
    m_CurrentLPF = new CowLib::CowLPF(lpfBeta);
    m_DetectObject = false;
    m_AutoHoldSpeed = autoHoldSpeed;
    m_AutoHold = autoHold;
}

void Intake::SetSpeed(float speed, bool clearObject)
{
    if(clearObject)
    {
	m_DetectObject = false;
	m_CurrentLPF->UpdateBeta(m_LpfBeta);
    }

    m_Speed = speed;
}

bool Intake::DetectedObject()
{
   return m_DetectObject;
}

void Intake::handle()
{
    float latestCurrent = m_Motor->GetOutputCurrent();
    m_Current = m_CurrentLPF->Calculate(latestCurrent);
    if (m_Current > m_CurrentThreshold)
    {
        m_DetectObject = true;
    }
    if(m_AutoHold && m_DetectObject)
    {
    	m_Speed = m_AutoHoldSpeed;
    }
    m_Motor->Set(m_Speed);
}

void Intake::ResetConstants(float lpfBeta, float autoHoldSpeed, float currentThreshold)
{
    m_LpfBeta = lpfBeta;
    m_CurrentLPF->UpdateBeta(m_LpfBeta);
    m_AutoHoldSpeed = autoHoldSpeed;
    m_CurrentThreshold = currentThreshold;
}

Intake::~Intake()
{
    delete m_Motor;
}
