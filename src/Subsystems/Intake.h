#ifndef SRC_SUBSYSTEMS_INTAKE_H_
#define SRC_SUBSYSTEMS_INTAKE_H_

#include "../CowLib/CowMotorController.h"
#include "../CowConstants.h"
#include <frc/WPILib.h>
#include <frc/Timer.h>
#include "../CowLib/CowLPF.h"
#include "../CowLib/CowPID.h"

class Intake
{
private:
    CowLib::CowMotorController *m_Motor;
    float m_Speed;
    bool m_LimitCurrent;
    double m_Current;
    float m_CurrentThreshold;
    CowLib::CowLPF* m_CurrentLPF;
    float m_LpfBeta;
    bool m_DetectObject; 
    bool m_AutoHold;
    float m_AutoHoldSpeed;
    bool m_HasBlinkedLed;

public:
    Intake(int motorController, bool autoHold, float autoHoldSpeed, float lpfBeta, float currentThreshold);
    void SetSpeed(float speed, bool clearObject);
    double GetCurrent()
    {
        return m_Current;
    }
    bool DetectedObject();
    bool BlinkLED()
    {
	if(!m_HasBlinkedLed)
	{
		m_HasBlinkedLed = true;
		return true;
	}
	return false;
    }
    void handle();
    void ResetConstants(float lpfBeta, float autoHoldSpeed, float currentThreshold);
    virtual ~Intake();
};


#endif
