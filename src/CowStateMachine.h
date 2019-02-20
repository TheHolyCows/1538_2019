#ifndef __COWSTATEMACHINE_H__
#define __COWSTATEMACHINE_H__

#include "CowConstants.h"
#include "Subsystems/Elevator.h"
#include "Subsystems/Arm.h"
#include <string>

class CowStateMachine
{
public:
    enum CowState
    {
        IDLE = 0,
        MANUAL_CONTROL,
        FORWARD_STATES,
        CARGO_1_F = FORWARD_STATES,
        CARGO_2,
        CARGO_3,
        HATCH_1_F,
        HATCH_2,
        HATCH_3,
        HATCH_GP_F,
        CARGO_HP_F,
        HATCH_HP_F,
        CARGO_GP_F,
        BACKWARD_STATES,
        HATCH_1_B = BACKWARD_STATES,
        CARGO_1_B,
        CARGO_HP_B,
        CARGO_GP_B,
        HATCH_HP_B,
        HATCH_GP_B
    };
private:
    // enum ElevatorState 
    // {  
    //     IDLE = 0,
    //     CARGO_1,
    //     CARGO_2,
    //     CARGO_3,
    //     CARGO_GP,
    //     CARGO_HP,
    //     HATCH_1,
    //     HATCH_2,
    //     HATCH_3,
    //     HATCH_GP,
    //     HATCH_HP
    // };
    // enum ArmState
    // {
    //     IDLE = 0,
    //     HATCH_SCORE_F,
    //     CARGO_SCORE_F,
    //     HATCH_HP_F,
    //     CARGO_HP_F,
    //     HACTH_GP_F,
    //     CARGO_GP_F,
    //     HATCH_HP_B,
    //     CARGO_HP_B,
    //     HATCH_SCORE_B,
    //     CARGO_SCORE_B,
    //     HATCH_GP_B,
    //     CARGO_GP_B
    // };
    // enum WristState
    // {
    //     IDLE = 0,
    //     HATCH_SCORE_F,
    //     CARGO_SCORE_F,
    //     HATCH_HP_F,
    //     CARGO_HP_F,
    //     HACTH_GP_F,
    //     CARGO_GP_F,
    //     HATCH_SCORE_B,
    //     CARGO_SCORE_B,
    //     HATCH_HP_B,
    //     CARGO_HP_B,
    //     HATCH_GP_B,
    //     CARGO_GP_B
    //     //If we score different on lvl 3 we make another wrist state
    // };

    Elevator *m_Elevator;
    Arm *m_Arm;
    Arm *m_Wrist;
    void MoveSafe(CowState state, int direction);

    std::string m_CowStateString [18] = 
    {"IDLE",
    "CARGO_1_F",
    "CARGO_1_B",
    "CARGO_2",
    "CARGO_3",
    "HATCH_1_F",
    "HATCH_1_B",
    "HATCH_2",
    "HATCH_3",
    "CARGO_HP_F",
    "CARGO_HP_B",
    "HATCH_HP_F",
    "HATCH_HP_B",
    "CARGO_GP_F",
    "CARGO_GP_B",
    "HATCH_GP_F",
    "HATCH_GP_B",
    "MANUAL_CONTROL"};

    CowState m_CurrentState;
    CowState m_TargetState;
    // WristState m_WristState;
    // ArmState m_ArmState;
    // ElevatorState m_ElevatorState;
    bool m_InTransit;

    double GetElevatorSP(CowState state);
    double GetArmSP(CowState state);
    double GetWristSP(CowState state);
public:
    CowStateMachine(Elevator *elevator, Arm *arm, Arm *wrist);

    void SetState(CowState state)
    {
        m_TargetState = state;
    }
    std::string GetTargetStateString()
    {
        return m_CowStateString [m_TargetState];
    }
    std::string GetCurrentStateString()
    {
        return m_CowStateString [m_CurrentState];
    }
    bool InTransit()
    {
        return m_InTransit;
    }

    void handle();

    virtual ~CowStateMachine();
};

#endif
