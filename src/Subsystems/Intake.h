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
    CowLib::CowLPF* m_CurrentLPF; 
    CowLib::CowPID* m_PID;
    bool m_Hold;

public:
    Intake(int morotController);
    void SetSpeed(float speed, bool limitCurrent);
    double GetCurrent()
    {
        return m_Current;
    }
    void ReleaseHold()
    {
        m_Hold = false;
        m_CurrentLPF->UpdateBeta(CONSTANT("INTAKE_CURRENT_LPF"));
    }
    void handle();
    void ResetConstants();
    virtual ~Intake();
};


#endif
