#include "CowStateMachine.h"
#include <iostream>
using namespace std;

CowStateMachine::CowStateMachine(Elevator *elevator, Arm *arm, Arm *wrist)
{
    m_Elevator = elevator; 
    m_Arm = arm;
    m_Wrist = wrist;
    m_CurrentState = CowState::IDLE;
    m_TargetState = CowState::IDLE;
    // m_WristState = WristState::IDLE;
    // m_ArmState = ArmState::IDLE;
    // m_ElevatorState = ElevatorState::IDLE;
    m_InTransit = false;

    m_Elevator->SetPosition(GetElevatorSP(m_TargetState));
    m_Arm->SetPosition(GetArmSP(m_TargetState));
    m_Wrist->SetPosition(GetWristSP(m_TargetState));
}

double CowStateMachine::GetElevatorSP(CowState state)
{
    double constantValue = 0;
    if(state == CowState::CARGO_1_B)
    {
        constantValue = CONSTANT("CARGO_LVL_1_ELV");
    }
    else if(state == CowState::CARGO_1_F)
    {
        constantValue = CONSTANT("CARGO_LVL_1_ELV");
    }
    else if(state == CowState::CARGO_2)
    {
        constantValue = CONSTANT("CARGO_LVL_2_ELV");
    }
    else if(state == CowState::CARGO_3)
    {
        constantValue = CONSTANT("CARGO_LVL_3_ELV");
    }
    else if(state == CowState::CARGO_GP_B)
    {
        constantValue = CONSTANT("CARGO_GP_ELV");
    }
    else if(state == CowState::CARGO_GP_F)
    {
        constantValue = CONSTANT("CARGO_GP_ELV");
    }
    else if(state == CowState::CARGO_HP_B)
    {
        constantValue = CONSTANT("CARGO_HP_ELV");
    }
    else if(state == CowState::CARGO_HP_F)
    {
        constantValue = CONSTANT("CARGO_HP_ELV");
    }
    else if(state == CowState::HATCH_1_B)
    {
        constantValue = CONSTANT("HATCH_LVL_1_ELV");
    }
    else if(state == CowState::HATCH_1_F)
    {
        constantValue = CONSTANT("HATCH_LVL_1_ELV");
    }
    else if(state == CowState::HATCH_2)
    {
        constantValue = CONSTANT("HATCH_LVL_2_ELV");
    }
    else if(state == CowState::HATCH_3)
    {
        constantValue = CONSTANT("HATCH_LVL_3_ELV");
    }
    else if(state == CowState::HATCH_GP_B)
    {
        constantValue = CONSTANT("HATCH_GP_ELV");
    }
    else if(state == CowState::HATCH_GP_F)
    {
        constantValue = CONSTANT("HATCH_GP_ELV");
    }
    else if(state == CowState::HATCH_HP_B)
    {
        constantValue = CONSTANT("HATCH_HP_ELV");
    }
    else if(state == CowState::HATCH_HP_F)
    {
        constantValue = CONSTANT("HATCH_HP_ELV");
    }
    else if(state == CowState::IDLE)
    {
        constantValue = CONSTANT("IDLE_ELV");
    }
    return constantValue;
}

double CowStateMachine::GetArmSP(CowState state)
{
    double constantValue = 0;
    if(state == CowState::CARGO_1_B)
    {
        constantValue = CONSTANT("CARGO_LVL_1_ARM");
    }
    else if(state == CowState::CARGO_1_F)
    {
        constantValue = CONSTANT("CARGO_LVL_1_ARM");
    }
    else if(state == CowState::CARGO_2)
    {
        constantValue = CONSTANT("CARGO_LVL_2_ARM");
    }
    else if(state == CowState::CARGO_3)
    {
        constantValue = CONSTANT("CARGO_LVL_3_ARM");
    }
    else if(state == CowState::CARGO_GP_B)
    {
        constantValue = CONSTANT("CARGO_GP_ARM");
    }
    else if(state == CowState::CARGO_GP_F)
    {
        constantValue = CONSTANT("CARGO_GP_ARM");
    }
    else if(state == CowState::CARGO_HP_B)
    {
        constantValue = CONSTANT("CARGO_HP_ARM");
    }
    else if(state == CowState::CARGO_HP_F)
    {
        constantValue = CONSTANT("CARGO_HP_ARM");
    }
    else if(state == CowState::HATCH_1_B)
    {
        constantValue = CONSTANT("HATCH_LVL_1_ARM");
    }
    else if(state == CowState::HATCH_1_F)
    {
        constantValue = CONSTANT("HATCH_LVL_1_ARM");
    }
    else if(state == CowState::HATCH_2)
    {
        constantValue = CONSTANT("HATCH_LVL_2_ARM");
    }
    else if(state == CowState::HATCH_3)
    {
        constantValue = CONSTANT("HATCH_LVL_3_ARM");
    }
    else if(state == CowState::HATCH_GP_B)
    {
        constantValue = CONSTANT("HATCH_GP_ARM");
    }
    else if(state == CowState::HATCH_GP_F)
    {
        constantValue = CONSTANT("HATCH_GP_ARM");
    }
    else if(state == CowState::HATCH_HP_B)
    {
        constantValue = CONSTANT("HATCH_HP_ARM");
    }
    else if(state == CowState::HATCH_HP_F)
    {
        constantValue = CONSTANT("HATCH_HP_ARM");
    }
    else if(state == CowState::IDLE)
    {
        constantValue = CONSTANT("IDLE_ARM");
    }
    return constantValue;
}

double CowStateMachine::GetWristSP(CowState state)
{
    double constantValue = 0;
    if(state == CowState::CARGO_1_B)
    {
        constantValue = CONSTANT("CARGO_LVL_1_WRIST");
    }
    else if(state == CowState::CARGO_1_F)
    {
        constantValue = CONSTANT("CARGO_LVL_1_WRIST");
    }
    else if(state == CowState::CARGO_2)
    {
        constantValue = CONSTANT("CARGO_LVL_2_WRIST");
    }
    else if(state == CowState::CARGO_3)
    {
        constantValue = CONSTANT("CARGO_LVL_3_WRIST");
    }
    else if(state == CowState::CARGO_GP_B)
    {
        constantValue = CONSTANT("CARGO_GP_WRIST");
    }
    else if(state == CowState::CARGO_GP_F)
    {
        constantValue = CONSTANT("CARGO_GP_WRIST");
    }
    else if(state == CowState::CARGO_HP_B)
    {
        constantValue = CONSTANT("CARGO_HP_WRIST");
    }
    else if(state == CowState::CARGO_HP_F)
    {
        constantValue = CONSTANT("CARGO_HP_WRIST");
    }
    else if(state == CowState::HATCH_1_B)
    {
        constantValue = CONSTANT("HATCH_LVL_1_WRIST");
    }
    else if(state == CowState::HATCH_1_F)
    {
        constantValue = CONSTANT("HATCH_LVL_1_WRIST");
    }
    else if(state == CowState::HATCH_2)
    {
        constantValue = CONSTANT("HATCH_LVL_2_WRIST");
    }
    else if(state == CowState::HATCH_3)
    {
        constantValue = CONSTANT("HATCH_LVL_3_WRIST");
    }
    else if(state == CowState::HATCH_GP_B)
    {
        constantValue = CONSTANT("HATCH_GP_WRIST");
    }
    else if(state == CowState::HATCH_GP_F)
    {
        constantValue = CONSTANT("HATCH_GP_WRIST");
    }
    else if(state == CowState::HATCH_HP_B)
    {
        constantValue = CONSTANT("HATCH_HP_WRIST");
    }
    else if(state == CowState::HATCH_HP_F)
    {
        constantValue = CONSTANT("HATCH_HP_WRIST");
    }
    else if(state == CowState::IDLE)
    {
        constantValue = CONSTANT("IDLE_WRIST");
    }

    return constantValue + m_Arm->GetPosition();
}

void CowStateMachine::MoveSafe(CowState state, int direction)
{
    double armSafeZone = CONSTANT("ARM_SAFE_SWING") - CONSTANT("ARM_TOLERANCE");
    if(fabs(m_Elevator->GetDistance() - GetElevatorSP(state)) < CONSTANT("ELEVATOR_TOLERANCE"))
    {
        m_Elevator->SetPosition(GetElevatorSP(state));
        m_Wrist->SetPosition(GetWristSP(state) * direction);
        m_Arm->SetPosition(GetArmSP(state) * direction);
        return;
    }
    if (GetElevatorSP(state) >= m_Elevator->GetDistance())
    {
        if (m_Elevator->GetDistance() < CONSTANT("ELV_SAFE_SWING"))
        {
            if (GetArmSP(state) < CONSTANT("ARM_SAFE_SWING"))
            {
                m_Arm->SetPosition(CONSTANT("ARM_SAFE_SWING") * direction);
            }
            else
            {
                m_Arm->SetPosition(GetArmSP(state) * direction);
            }
        }
        else
        {
            m_Arm->SetPosition(GetArmSP(state) * direction);
        }
        m_Elevator->SetPosition(GetElevatorSP(state));
    }
    else
    {
        if (fabs(m_Arm->GetPosition()) < armSafeZone)
        {
            if (GetArmSP(state) >= CONSTANT("ARM_SAFE_SWING") || m_InTransit)
            {
                m_Arm->SetPosition(GetArmSP(state) * direction);
            }
            else
            {
                m_Arm->SetPosition(CONSTANT("ARM_SAFE_SWING") * direction);
            }
            m_Elevator->SetPosition(CONSTANT("IDLE_ELV"));
        }
        else
        {
            if (fabs(GetArmSP(state)) >= CONSTANT("ARM_SAFE_SWING"))
            {
                m_Arm->SetPosition(GetArmSP(state) * direction);
            }
            else
            {
                m_Arm->SetPosition(CONSTANT("ARM_SAFE_SWING") * direction);
            }
            m_Elevator->SetPosition(GetElevatorSP(state));
        }
        m_Wrist->SetPosition(GetWristSP(state) * direction);
    }
}

void CowStateMachine::handle()
{
    double elevatorPV = m_Elevator->GetDistance();
    double armPV = m_Arm->GetPosition();
    double wristPV = m_Wrist->GetPosition();

    
    if (m_TargetState == CowState::MANUAL_CONTROL)
    {
        std::cout << "In manual control for state machine" << std::endl;
        m_CurrentState = CowState::MANUAL_CONTROL;
        return;
    }

    if (m_CurrentState != m_TargetState)
    {
        //Make a temp direction to use for testing our position
        int tempDirection = 0;
        if (m_TargetState < CowState::BACKWARD_STATES)
        {
            tempDirection = 1;
        }
        else
        {
            tempDirection = -1;
        }
        //If our current encoder values are within their tolerance of the target states values, we are at target
        if (fabs(m_Elevator->GetDistance() - GetElevatorSP(m_TargetState)) < CONSTANT("ELEVATOR_TOLERANCE") && fabs(m_Arm->GetPosition() -  (GetArmSP(m_TargetState) * tempDirection)) < CONSTANT("ARM_TOLERANCE") && fabs(m_Wrist->GetPosition() - (GetWristSP(m_TargetState) * tempDirection)) < CONSTANT("WRIST_TOLERANCE"))
        {
            m_CurrentState = m_TargetState;
        }
        //If our pid tells us we are in position and we are in transit, it means we are in the idle position
        if (m_Elevator->AtTarget() && m_Arm->AtTarget() && m_InTransit)
        {
            m_InTransit = false;
            m_CurrentState = CowState::IDLE;
        }
        
        //If we are in idle position or moving to idle position, let us go anywhere
        if(m_CurrentState == CowState::IDLE || m_TargetState == CowState::IDLE)
        {
            //Check to see if  we are going towards front or back, then move accordingly
            if (m_TargetState < CowState::BACKWARD_STATES)
            {
                MoveSafe(m_TargetState, 1);
            }
            else
            {
                MoveSafe(m_TargetState, -1);
            }
        }
        //Check if we are in the front or back
        else if (m_CurrentState < BACKWARD_STATES)
        {
            // Check to see if target is in front or back
            if (m_TargetState < CowState::BACKWARD_STATES)
            {
                //We are in the front and going to the front so it is safe to proceed
                MoveSafe (m_TargetState, 1);
            }
            // If we are moving to the back from the front, make sure we return to idle first
            else
            {
                MoveSafe(CowState::IDLE, 1);
                m_InTransit = true;
            }
        }
        //Arm is in back:
        else
        {
            //Check if target is in front or back
            if (m_TargetState >= BACKWARD_STATES)
            {
                //We are in the back and going to the back so it is safe to proceed
                MoveSafe (m_TargetState, -1);
            }
            //If we are moving from the back to the front, make sure we return to idle first
            else
            {
                MoveSafe(CowState::IDLE, -1);
                m_InTransit = true;
            }
        }
    }
    else if(armPV > 0)
    {
        MoveSafe(m_TargetState, 1);
    }
    else
    {
        MoveSafe(m_TargetState, -1);
    }
    //get positions of other subsystems
    // switch (m_TargetState)
    // {
    //     case CowState::IDLE:
    //         if((m_CurrentState != CowState::HATCH_GP_B) && (m_CurrentState != CowState::HATCH_GP_F))
    //         {
    //             m_CurrentState = m_TargetState;
    //         }
    //         else if (m_CurrentState == CowState::HATCH_GP_F)
    //         {
    //             m_CurrentState = CowState::HATCH_1_F;
    //         }
    //         else if (m_CurrentState == CowState::HATCH_GP_B)
    //         {
    //             m_CurrentState = CowState::HATCH_1_B;
    //         }
    //         break;
    //     case CowState::CARGO_1_F:

    //         break;
    //     case CowState::CARGO_1_B:
    //         break;
    //     case CowState::CARGO_2:
    //         break;
    //     case CowState::CARGO_3:
    //         break;
    //     case CowState::CARGO_GP_B:
    //         break;
    //     case CowState::CARGO_GP_F:
    //         break;
    //     case CowState::CARGO_HP_B:
    //         break;
    //     case CowState::CARGO_HP_F:
    //         break;
    //     case CowState::HATCH_1_F:
    //         break;
    //     case CowState::HATCH_2:
    //         break;
    //     case CowState::HATCH_3:
    //         break;
    //     case CowState::HATCH_HP_B:
    //         break;
    //     case CowState::HATCH_HP_F:
    //         break;
    //     case CowState::HATCH_GP_B:
    //         break;
    //     case CowState::HATCH_GP_F:
    //         break;
    // }
}

CowStateMachine::~CowStateMachine()
{

}
