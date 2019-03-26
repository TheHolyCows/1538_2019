#include "OperatorController.h"
#include <iostream>

OperatorController::OperatorController(CowControlBoard *controlboard)
    :
    m_CB(controlboard)
{
}

void OperatorController::handle(CowRobot *bot)
{
    bool forwardDirection = m_CB->GetOperatorButton(8);
    float r_color = m_CB->GetOperatorGamepadAxis(2);
    r_color = fabs(r_color*254);
    float g_color = m_CB->GetDriveAxis(2);
    g_color = fabs(g_color*254);
    float b_color = m_CB->GetDriveAxis(0);
    b_color = fabs(b_color*254);
    bot->GetCanifier()->SetLEDColor(r_color, g_color, b_color);
    if(m_CB->GetDriveButton(1))
    {
        //bot->TurnToHeading(90);
        bot->DriveDistanceWithHeading(0, 12, 0.5);
    }
    else
    {
       if(m_CB->GetSteeringButton(3))
       {
            if(!m_CB->GetOperatorButton(10))
            {
                bot->GetLimelight(forwardDirection)->PutNumber("pipeline", 0);
            }
            else
            {
                bot->GetLimelight(forwardDirection)->PutNumber("pipeline", 2);
            }
           bot->DriveSpeedTurn(m_CB->GetDriveStickY(),
                               (bot->GetLimelight(forwardDirection)->GetNumber("tx",0.0)*CONSTANT("LIMELIGHT_X_KP")),
                               0);
       }
       else if(m_CB->GetSteeringButton(1))
       {
           bot->GetLimelight(forwardDirection)->PutNumber("pipeline", 1);
           bot->DriveSpeedTurn(m_CB->GetDriveStickY(),
                               (bot->GetLimelight(forwardDirection)->GetNumber("tx",0.0)*CONSTANT("LIMELIGHT_X_KP")),
                               0);
       }
       else
       { 
        bot->GetLimelight(forwardDirection)->PutNumber("pipeline", 3);
         bot->DriveSpeedTurn(m_CB->GetDriveStickY(),
                             m_CB->GetSteeringX(),
                             m_CB->GetSteeringButton(FAST_TURN));
      }
    }

    
    if(m_CB->GetSteeringButton(4))
    {
        bot->GetStateMachine()->SetState(CowStateMachine::CowState::IDLE);
    }
    //if switch is on for forward arm placement
    if(!m_CB->GetOperatorButton(8))
    {
        //if cargo or hatch - on for cargo
        if(m_CB->GetOperatorButton(10))
        {
            if(m_CB->GetOperatorButton(4))
            {
                bot->GetStateMachine()->SetState(CowStateMachine::CowState::CARGO_1_F);
            }

            if(m_CB->GetOperatorButton(6))
            {
                bot->GetStateMachine()->SetState(CowStateMachine::CowState::CARGO_2);
            }

            if(m_CB->GetOperatorButton(5))
            {
                bot->GetStateMachine()->SetState(CowStateMachine::CowState::CARGO_3);
            }

            if(m_CB->GetOperatorButton(7))
            {
                bot->GetStateMachine()->SetState(CowStateMachine::CowState::CARGO_GP_F);
            }

            if(m_CB->GetOperatorButton(9))
            {
                bot->GetStateMachine()->SetState(CowStateMachine::CowState::CARGO_HP_F);
            }
            if (m_CB->GetOperatorButton(3))
            {
                bot->GetStateMachine()->SetState(CowStateMachine::CowState::CARGO_CS_F);
            }
            bot->GetStateMachine()->SetHatchMode(false);
        }
        else 
        {
            bot->GetStateMachine()->SetHatchMode(true);
            if (m_CB->GetOperatorButton(3))
            {
                bot->GetStateMachine()->SetState(CowStateMachine::CowState::HATCH_SCORE);
            }
            if(m_CB->GetOperatorButton(4))
            {
                bot->GetStateMachine()->SetState(CowStateMachine::CowState::HATCH_1_F);
            }

            if(m_CB->GetOperatorButton(6))
            {
                bot->GetStateMachine()->SetState(CowStateMachine::CowState::HATCH_2);
            }

            if(m_CB->GetOperatorButton(5))
            {
                bot->GetStateMachine()->SetState(CowStateMachine::CowState::HATCH_3);
            }

            if(m_CB->GetOperatorButton(7))
            {
                bot->GetStateMachine()->SetState(CowStateMachine::CowState::HATCH_GP_F);
            }

            if(m_CB->GetOperatorButton(9))
            {
                bot->GetStateMachine()->SetState(CowStateMachine::CowState::HATCH_HP_F);
            }
            bot->GetStateMachine()->SetHatchMode(true);
        }
    }
    else 
    {
        //same stuff but for backwards facing (less positions since crossbar smashy)
        if(m_CB->GetOperatorButton(10))
        {
            //cargo
            if(m_CB->GetOperatorButton(4))
            {
                bot->GetStateMachine()->SetState(CowStateMachine::CowState::CARGO_1_B);
            }

            if(m_CB->GetOperatorButton(7))
            {
                bot->GetStateMachine()->SetState(CowStateMachine::CowState::CARGO_GP_B);
            }

            if(m_CB->GetOperatorButton(9))
            {
                bot->GetStateMachine()->SetState(CowStateMachine::CowState::CARGO_HP_B);
            }

            if (m_CB->GetOperatorButton(3))
            {
                bot->GetStateMachine()->SetState(CowStateMachine::CowState::CARGO_CS_B);
            }
            bot->GetStateMachine()->SetHatchMode(false);
        }
        else 
        {
            if (m_CB->GetOperatorButton(3))
            {
                bot->GetStateMachine()->SetState(CowStateMachine::CowState::HATCH_SCORE);
            }
            if(m_CB->GetOperatorButton(4))
            {
                bot->GetStateMachine()->SetState(CowStateMachine::CowState::HATCH_1_B);
            }

            if(m_CB->GetOperatorButton(7))
            {
                bot->GetStateMachine()->SetState(CowStateMachine::CowState::HATCH_GP_B);
            }

            if(m_CB->GetOperatorButton(9))
            {
                bot->GetStateMachine()->SetState(CowStateMachine::CowState::HATCH_HP_B);
            }
            bot->GetStateMachine()->SetHatchMode(true);
        }

    }


    //Intake
    if (m_CB->GetOperatorButton(2))
    {
        //Switch 10 on = cargo
        if (m_CB->GetOperatorButton(10))
        {
            bot->GetIntake()->SetSpeed(-1, true);
        }
        else
        {
            bot->GetIntake()->SetSpeed(1, false);
        }
    }
    //Exhaust
    else if (m_CB->GetOperatorButton(1))
    {
        if (m_CB->GetOperatorButton(10))
        {
            bot->GetIntake()->SetSpeed(1, true);
        }
        else
        {
            bot->GetIntake()->SetSpeed(-1, false);
        }
        bot->GetIntake()->ReleaseHold();
    }
    else
    {
        if (m_CB->GetOperatorButton(10))
        {
            bot->GetIntake()->SetSpeed(0, true);
        }
        else
        {
            bot->GetIntake()->SetSpeed(0, false);
        }
    }
    
    // if(m_CB->GetOperatorButton(6))
    // {
    //     bot->GetElevator()->SetPosition(CONSTANT("HATCH_POS_ELEVATOR"));
    //     bot->GetWrist()->SetPosition(CONSTANT("HATCH_POS_WRIST"));
    //     bot->GetArm()->SetPosition(CONSTANT("HATCH_POS_ARM"));
    // }

    // if(m_CB->GetOperatorButton(9))
    // {
    //     bot->GetElevator()->SetPosition(CONSTANT("BALL_POS_ELEVATOR"));
    //     bot->GetWrist()->SetPosition(CONSTANT("BALL_POS_WRIST"));
    //     bot->GetArm()->SetPosition(CONSTANT("BALL_POS_ARM"));
    // }
    // float wristJoystickDeadband = CowLib::Deadband(m_CB->GetOperatorGamepadAxis(1), 0.2);
    // float manualWristPosition = bot->GetWrist()->GetSetpoint() + (wristJoystickDeadband * 28);
    // bot->GetWrist()->SetPosition(manualWristPosition);

    // float armJoystickDeadband = CowLib::Deadband(m_CB->GetOperatorGamepadAxis(0), 0.2);
    // float manualArmPosition = bot->GetArm()->GetSetpoint() + (armJoystickDeadband * 18);
    // bot->GetArm()->SetPosition(manualArmPosition);

    float elevatorJoystickDeadband = CowLib::Deadband(m_CB->GetOperatorGamepadAxis(1), 0.2);
    if(elevatorJoystickDeadband != 0)
    {
        bot->GetStateMachine()->SetState(CowStateMachine::CowState::MANUAL_CONTROL);
        float manualElevatorPosition = bot->GetElevator()->GetSetPoint() + (elevatorJoystickDeadband * .4);
        bot->GetElevator()->SetPosition(manualElevatorPosition);
    }

}

