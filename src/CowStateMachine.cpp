#include "CowStateMachine.h"

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
    return constantValue * 0.45833333;
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

    return constantValue;
}

void CowStateMachine::handle()
{
    double elevatorPV = m_Elevator->GetDistance();
    double armPV = m_Arm->GetPosition();
    double wristPV = m_Wrist->GetPosition();

    if (m_CurrentState != m_TargetState)
    {
        if (m_Elevator->AtTarget() && m_Arm->AtTarget() && m_Wrist->AtTarget())
        {
            if(m_InTransit)
            {
                m_CurrentState = CowState::IDLE;
                m_InTransit = false;
            }
            else
            {
                m_CurrentState = m_TargetState;
            }
            return;
        }
        if (m_CurrentState == CowState::CARGO_1_F ||
        m_CurrentState == CowState::CARGO_2 ||
        m_CurrentState == CowState::CARGO_3 ||
        m_CurrentState == CowState::CARGO_GP_F ||
        m_CurrentState == CowState::CARGO_HP_F ||
        m_CurrentState == CowState::HATCH_HP_F ||
        m_CurrentState == CowState::HATCH_1_F ||
        m_CurrentState == CowState::HATCH_2 ||
        m_CurrentState == CowState::HATCH_3 ||
        m_CurrentState == CowState::HATCH_GP_F ||
        m_CurrentState == CowState::IDLE)
        {
            if((armPV > CONSTANT("ARM_ELEVATOR_KEEPOUT_MIN") && armPV < CONSTANT("ARM_ELEVATOR_KEEPOUT_MAX")) || m_CurrentState == CowState::IDLE)
            {
                if(m_TargetState == CowState::CARGO_2 ||
                m_TargetState == CowState::CARGO_3 ||
                m_TargetState == CowState::CARGO_GP_F ||
                m_TargetState == CowState::CARGO_HP_F ||
                m_TargetState == CowState::HATCH_1_F ||
                m_TargetState == CowState::HATCH_2 ||
                m_TargetState == CowState::HATCH_3 ||
                m_TargetState == CowState::HATCH_GP_F ||
                m_TargetState == CowState::HATCH_HP_F ||
                m_TargetState == CowState::IDLE)
                {
                    m_Elevator->SetPosition(GetElevatorSP(m_TargetState));
                    m_Arm->SetPosition(GetArmSP(m_TargetState));
                    m_Wrist->SetPosition(GetWristSP(m_TargetState) + m_Arm->GetPosition());
                    return;
                }
                else if (m_CurrentState != CowState::IDLE)
                {
                    m_Elevator->SetPosition(GetElevatorSP(CowState::IDLE));
                    m_Arm->SetPosition(GetArmSP(CowState::IDLE));
                    m_Wrist->SetPosition(GetWristSP(CowState::IDLE));
                    m_InTransit = true;
                    return;
                }
            }
            else
            {
                m_Elevator->SetPosition(GetElevatorSP(CowState::IDLE));
                m_Arm->SetPosition(GetArmSP(CowState::IDLE));
                m_Wrist->SetPosition(GetWristSP(CowState::IDLE));
                m_InTransit = true;
                return;
            }
        }
        // if (m_CurrentState == CowState::CARGO_HP_B ||
        // m_CurrentState == CowState::CARGO_1_B ||
        // m_CurrentState == CowState::CARGO_GP_B ||
        // m_CurrentState == CowState::HATCH_1_B ||
        // m_CurrentState == CowState::HATCH_GP_B ||
        // m_CurrentState == CowState::HATCH_HP_B ||
        // m_CurrentState == CowState::IDLE)
        // {
        //     if(armPV < CONSTANT("ARM_ELEVATOR_KEEPOUT_MIN") || m_CurrentState == CowState::IDLE)
        //     {
        //         if(m_TargetState == CowState::CARGO_HP_B ||
        //         m_TargetState == CowState::CARGO_1_B ||
        //         m_TargetState == CowState::CARGO_GP_B ||
        //         m_TargetState == CowState::HATCH_1_B ||
        //         m_TargetState == CowState::HATCH_GP_B ||
        //         m_TargetState == CowState::HATCH_HP_B ||
        //         m_TargetState == CowState::IDLE)
        //         {
        //             m_Elevator->SetPosition(GetElevatorSP(m_TargetState));
        //             m_Arm->SetPosition(GetArmSP(m_TargetState));
        //             m_Wrist->SetPosition(GetWristSP(m_TargetState));
        //         }
        //         else
        //         {
        //             m_Elevator->SetPosition(GetElevatorSP(CowState::IDLE));
        //             m_Arm->SetPosition(GetArmSP(CowState::IDLE));
        //             m_Wrist->SetPosition(GetWristSP(CowState::IDLE));
        //             m_InTransit = true;
        //             return;
        //         }
        //     }
        //     else
        //     {
        //         m_Elevator->SetPosition(GetElevatorSP(CowState::IDLE));
        //         m_Arm->SetPosition(GetArmSP(CowState::IDLE));
        //         m_Wrist->SetPosition(GetWristSP(CowState::IDLE));
        //         m_InTransit = true;
        //     }
        // }
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