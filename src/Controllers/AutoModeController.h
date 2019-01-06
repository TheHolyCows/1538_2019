//==================================================
// Copyright (C) 2018 Team 1538 / The Holy Cows
//==================================================

#ifndef __AUTO_MODE_CONTROLLER_H__
#define __AUTO_MODE_CONTROLLER_H__

#include "../CowConstants.h"
#include <frc/Timer.h>
#include <deque>

typedef enum
{
    CMD_NULL = 0,
    CMD_TURN,
    CMD_TURN_INTAKE,
    CMD_DRIVE_DISTANCE,
	CMD_DRIVE_DISTANCE_INTAKE,
    CMD_HOLD_DISTANCE,
	CMD_HOLD_DISTANCE_INTAKE,
	CMD_ARM_UP,
	CMD_ARM_DOWN,
	CMD_AUTO_FWD_LOW,
	CMD_AUTO_FWD,
	CMD_AUTO_REV,
    CMD_LEFT_ENCODER,
    CMD_RIGHT_ENCODER,
    CMD_WAIT
} e_RobotCommand;

class RobotCommand
{
public:
    
    e_RobotCommand m_Command;
    double m_EncoderCount;
    double m_Heading;
    double m_Speed;
    double m_ElevatorPos;
    double m_Timeout;
    
    RobotCommand() :
        m_Command(CMD_NULL),
        m_EncoderCount(0),
        m_Heading(0),
        m_Speed(0),
		m_ElevatorPos(0),
        m_Timeout(0)
    {
    }
    
    RobotCommand(e_RobotCommand cmd,
            double encoder, double heading,
                 double speed, double elevatorPos, double timeout) :
        m_Command(cmd),
        m_EncoderCount(encoder),
        m_Heading(heading),
        m_Speed(speed),
		m_ElevatorPos(elevatorPos),
        m_Timeout(timeout)
    {
    }
};

#include "../CowRobot.h"
#include "../CowLib/CowLib.h"

class AutoModeController : public GenericController
{
private:
    frc::Timer *m_Timer; //TODO: standardize timing
    std::deque<RobotCommand> m_CommandList;
    RobotCommand m_CurrentCommand;
    
    void doNothing(CowRobot *bot);
    float m_OriginalEncoder;

public:
    AutoModeController();
    void SetCommandList(std::deque<RobotCommand> list);

    void handle(CowRobot *bot);
    void reset();
};

#endif /* __AUTO_MODE_CONTROLLER_H__ */
