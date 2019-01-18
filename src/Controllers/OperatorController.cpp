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
        if(m_CB->GetSteeringButton(3))
        {
            bot->DriveSpeedTurn(m_CB->GetDriveStickY(),
                                (bot->GetLimelight()->GetNumber("tx",0.0)*CONSTANT("LIMELIGHT_X_KP")),
                                1);
        }
        else
        { 
            bot->DriveSpeedTurn(m_CB->GetDriveStickY(),
                                m_CB->GetSteeringX(),
                                m_CB->GetSteeringButton(FAST_TURN));
        }
    }
    if(m_CB->GetSteeringButton(4))
    {
        //do something to go to the scale
        bot->GetElevator()->SetPosition(CONSTANT("ELEVATOR_SCALE"));
    }
    else if(m_CB->GetSteeringButton(1))
    {
        //go to switch
        bot->GetElevator()->SetPosition(CONSTANT("ELEVATOR_SWITCH"));
    }
    else if(m_CB->GetSteeringButton(2))
    {
        //go to ground
        bot->GetElevator()->SetPosition(CONSTANT("ELEVATOR_GROUND"));
    }
    if(m_CB->GetOperatorButton(6))
    {
    	bot->GetArm()->SetPosition(CONSTANT("ARM_DOWN"));

    }
    if(m_CB->GetOperatorButton(9))
    {
    	bot->GetArm()->SetPosition(CONSTANT("ARM_UP"));
    }
    if(m_CB->GetOperatorButton(7))
    {
        bot->GetIntake()->SetSpeed(1);
    }
    else if(m_CB->GetOperatorButton(4))
    {
        bot->GetIntake()->SetSpeed(-1);
    }
    else
    {
        bot->GetIntake()->SetSpeed(0);
    }
    float armJoystickDeadband = CowLib::Deadband(m_CB->GetOperatorGamepadAxis(1), 0.2);
    float manualArmPosition = bot->GetArm()->GetSetpoint() + (armJoystickDeadband * 28);
    bot->GetWrist()->SetPosition(manualArmPosition);
}

