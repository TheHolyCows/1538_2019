#ifndef SRC_SUBSYSTEMS_INTAKE_H_
#define SRC_SUBSYSTEMS_INTAKE_H_

#include "../CowLib/CowMotorController.h"
#include "../CowConstants.h"
#include <frc/WPILib.h>
#include <frc/Timer.h>

class Intake
{
private:
    CowLib::CowMotorController *m_Motor;
    float m_Speed;

public:
    Intake(int morotController);
    void SetSpeed(float speed);
    void handle();
    virtual ~Intake();
};


#endif