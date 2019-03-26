#ifndef SRC_SUBSYSTEMS_JACK_H_
#define SRC_SUBSYSTEMS_JACK_H_

#include "../CowLib/CowMotorController.h"
#include "../CowConstants.h"
#include <frc/WPILib.h>
#include <frc/Timer.h>
#include "../CowLib/CowLPF.h"
#include "../CowLib/CowPID.h"

class Jack
{
private:
    CowLib::CowMotorController *m_Motor;
    float m_Position;

public:
    Jack(int motorController, bool flipDirection);
    void SetPosition(float position);
    void handle();
    void ResetConstants();
    virtual ~Jack();
};


#endif
