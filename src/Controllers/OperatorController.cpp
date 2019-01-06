#include "OperatorController.h"
#include <iostream>

OperatorController::OperatorController(CowControlBoard *controlboard)
    :
    m_CB(controlboard)
{
}

void OperatorController::handle(CowRobot *bot)
{
    if(m_CB->GetDriveButton(1))
    {
        bot->TurnToHeading(90);
        //bot->DriveDistanceWithHeading(0, 12, 0.5);
    }
    else
    {
        bot->DriveSpeedTurn(m_CB->GetDriveStickY(),
                            m_CB->GetSteeringX(),
                            m_CB->GetSteeringButton(FAST_TURN));
    }

}

