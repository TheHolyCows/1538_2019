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
    if(m_CB->GetOperatorButton(2))
    {
    	bot->GetArm()->SetPosition(CONSTANT("ARM_DOWN"));

    }
    if(m_CB->GetOperatorButton(1))
    {
    	bot->GetArm()->SetPosition(CONSTANT("ARM_UP"));
    }
     if(m_CB->GetOperatorButton(3))
    {
    	bot->GetArm()->SetPosition(CONSTANT("ARM_LOADING_STATION"));
        bot->GetWrist()->SetPosition(CONSTANT("WRIST_LOADING_STATION"));
        bot->GetElevator()->SetPosition(CONSTANT("ELEVATOR_LOADING_STATION"));
    }
    if(m_CB->GetSteeringButton(12))
    {
        bot->ResetLoadingStation();
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

    if(m_CB->GetOperatorButton(6))
    {
        bot->GetElevator()->SetPosition(CONSTANT("HATCH_POS_ELEVATOR"));
        bot->GetWrist()->SetPosition(CONSTANT("HATCH_POS_WRIST"));
        bot->GetArm()->SetPosition(CONSTANT("HATCH_POS_ARM"));
    }

    if(m_CB->GetOperatorButton(9))
    {
        bot->GetElevator()->SetPosition(CONSTANT("BALL_POS_ELEVATOR"));
        bot->GetWrist()->SetPosition(CONSTANT("BALL_POS_WRIST"));
        bot->GetArm()->SetPosition(CONSTANT("BALL_POS_ARM"));
    }
    float wristJoystickDeadband = CowLib::Deadband(m_CB->GetOperatorGamepadAxis(1), 0.2);
    float manualWristPosition = bot->GetWrist()->GetSetpoint() + (wristJoystickDeadband * 28);
    bot->GetWrist()->SetPosition(manualWristPosition);

    float armJoystickDeadband = CowLib::Deadband(m_CB->GetOperatorGamepadAxis(0), 0.2);
    float manualArmPosition = bot->GetArm()->GetSetpoint() + (armJoystickDeadband * 18);
    bot->GetArm()->SetPosition(manualArmPosition);

    float elevatorJoystickDeadband = CowLib::Deadband(m_CB->GetDriveAxis(0), 0.2);
    float manualElevatorPosition = bot->GetElevator()->GetSetPoint() + (elevatorJoystickDeadband * .75);
    bot->GetElevator()->SetPosition(manualElevatorPosition);
}

