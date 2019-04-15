#include "AutoModes.h"
#include <frc/WPILib.h>

AutoModes *AutoModes::m_SingletonInstance = NULL;

AutoModes *AutoModes::GetInstance()
{
	if(m_SingletonInstance == NULL)
	{
		m_SingletonInstance = new AutoModes();
	}
	return m_SingletonInstance;
}

AutoModes::AutoModes()
{
	// Set up our selection order
	m_Modes["Nothing"];
	m_Modes["Nothing"].push_back(RobotCommand(CMD_WAIT, 0, 0, 0, 0, false, 0));

	m_Modes["Test"];
	m_Modes["Test"].push_back(RobotCommand(CMD_PRESTART, 0, 0, 0, 0, true, 0.375));
	m_Modes["Test"].push_back(RobotCommand(CMD_VISION_HATCH_INTAKE, 0, 0, 0, 0, true, 0.25));

	m_Modes["Two Hatch Rocket - Right"];
	m_Modes["Two Hatch Rocket - Right"].push_back(RobotCommand(CMD_RIGHT_ENCODER, 0, 0, 0, 5, true, 0.01));
	m_Modes["Two Hatch Rocket - Right"].push_back(RobotCommand(CMD_PRESTART, 0, 0, 0, 0, true, 0.6));
	m_Modes["Two Hatch Rocket - Right"].push_back(RobotCommand(CMD_ARM_DOWN, 0, 0, 0, 0, true, 0.25));
	m_Modes["Two Hatch Rocket - Right"].push_back(RobotCommand(CMD_HOLD_DISTANCE, 30, 0, 0.5, CONSTANT("HATCH_ELV_LVL1"), false, 0.5));
	m_Modes["Two Hatch Rocket - Right"].push_back(RobotCommand(CMD_DRIVE_DISTANCE, 45, 60, 0.5, CONSTANT("HATCH_ELV_LVL1"), false, 1));
	m_Modes["Two Hatch Rocket - Right"].push_back(RobotCommand(CMD_HOLD_DISTANCE, 70, 45, 0.3, CONSTANT("HATCH_ELV_LVL1"), false, 0.5));
	m_Modes["Two Hatch Rocket - Right"].push_back(RobotCommand(CMD_VISION_ALIGN, 0, 45, -0.3, CONSTANT("HATCH_ELV_LVL1"), false, 7));
	m_Modes["Two Hatch Rocket - Right"].push_back(RobotCommand(CMD_INTAKE_EXHAUST, 0, 45, 0, CONSTANT("HATCH_ELV_LVL1"), false, 0.25));
	m_Modes["Two Hatch Rocket - Right"].push_back(RobotCommand(CMD_TURN, 0, 170, 0, CONSTANT("HATCH_ELV_LVL1"), false, 0.187));
	m_Modes["Two Hatch Rocket - Right"].push_back(RobotCommand(CMD_DRIVE_DISTANCE, 40, 170, 0.5, CONSTANT("HATCH_ELV_LVL1"), false, 3));
	m_Modes["Two Hatch Rocket - Right"].push_back(RobotCommand(CMD_VISION_HATCH_INTAKE, 0, 0, -0.2, CONSTANT("HATCH_ELV_LVL1"), false, 2.25));
	m_Modes["Two Hatch Rocket - Right"].push_back(RobotCommand(CMD_DRIVE_DISTANCE, -155, 165, 0.8, CONSTANT("HATCH_ELV_LVL1"), false, 3));
	m_Modes["Two Hatch Rocket - Right"].push_back(RobotCommand(CMD_HOLD_DISTANCE, -270, 200, 0.35, CONSTANT("HATCH_ELV_LVL1"), false, 2.25));
	m_Modes["Two Hatch Rocket - Right"].push_back(RobotCommand(CMD_TURN, 0, 140, 0, CONSTANT("HATCH_ELV_LVL1"), false, 0.7));
	m_Modes["Two Hatch Rocket - Right"].push_back(RobotCommand(CMD_VISION_ALIGN, 0, 140, -0.2, CONSTANT("HATCH_ELV_LVL1"), false, 7));
	m_Modes["Two Hatch Rocket - Right"].push_back(RobotCommand(CMD_INTAKE_EXHAUST, 0, 140, 0, CONSTANT("HATCH_ELV_LVL1"), false, 0.5));
	m_Modes["Two Hatch Rocket - Right"].push_back(RobotCommand(CMD_HOLD_DISTANCE, -24, 140, 0.35, CONSTANT("HATCH_ELV_LVL1"), false, 2));
	m_Iterator = m_Modes.begin();

	m_Modes["One Hatch Rocket - Left"];
	m_Modes["One Hatch Rocket - Left"].push_back(RobotCommand(CMD_LEFT_ENCODER, 0, 0, 0, 5, true, 0.01));
	m_Modes["One Hatch Rocket - Left"].push_back(RobotCommand(CMD_PRESTART, 0, 0, 0, 0, true, 0.6));
	m_Modes["One Hatch Rocket - Left"].push_back(RobotCommand(CMD_ARM_DOWN, 0, 0, 0, 0, true, 0.25));
	m_Modes["One Hatch Rocket - Left"].push_back(RobotCommand(CMD_HOLD_DISTANCE, 30, 0, 0.5, CONSTANT("HATCH_ELV_LVL1"), false, 0.5));
	m_Modes["One Hatch Rocket - Left"].push_back(RobotCommand(CMD_DRIVE_DISTANCE, 45, -60, 0.5, CONSTANT("HATCH_ELV_LVL1"), false, 1));
	m_Modes["One Hatch Rocket - Left"].push_back(RobotCommand(CMD_HOLD_DISTANCE, 70, -45, 0.3, CONSTANT("HATCH_ELV_LVL1"), false, 0.5));
	m_Modes["One Hatch Rocket - Left"].push_back(RobotCommand(CMD_VISION_ALIGN, 0, -45, -0.3, CONSTANT("HATCH_ELV_LVL1"), false, 7));
	m_Modes["One Hatch Rocket - Left"].push_back(RobotCommand(CMD_INTAKE_EXHAUST, 0, -45, 0, CONSTANT("HATCH_ELV_LVL1"), false, 0.25));
	m_Modes["One Hatch Rocket - Left"].push_back(RobotCommand(CMD_HOLD_DISTANCE, 68, -45, 0.3, CONSTANT("HATCH_ELV_LVL1"), false, 0.5));
	m_Modes["One Hatch Rocket - Left"].push_back(RobotCommand(CMD_TURN, 0, -170, 0, CONSTANT("HATCH_ELV_LVL1"), false, 0.187));
	m_Modes["One Hatch Rocket - Left"].push_back(RobotCommand(CMD_DRIVE_DISTANCE, 40, -170, 0.25, CONSTANT("HATCH_ELV_LVL1"), false, 4));
	m_Modes["One Hatch Rocket - Left"].push_back(RobotCommand(CMD_VISION_HATCH_INTAKE, 0, 0, -0.2, CONSTANT("HATCH_ELV_LVL1"), false, 4));

	m_Modes["Two Hatch Rocket - Left"];
	m_Modes["Two Hatch Rocket - Left"].push_back(RobotCommand(CMD_LEFT_ENCODER, 0, 0, 0, 5, true, 0.01));
	m_Modes["Two Hatch Rocket - Left"].push_back(RobotCommand(CMD_PRESTART, 0, 0, 0, 0, true, 0.6));
	//m_Modes["Two Hatch Rocket - Left"].push_back(RobotCommand(CMD_VISION_HATCH_INTAKE, 0, 0, 0, 0, true, 0.25));
	m_Modes["Two Hatch Rocket - Left"].push_back(RobotCommand(CMD_ARM_DOWN, 0, 0, 0, 0, true, 0.25));
	m_Modes["Two Hatch Rocket - Left"].push_back(RobotCommand(CMD_HOLD_DISTANCE, 30, 0, 0.5, CONSTANT("HATCH_ELV_LVL1"), false, 0.5));
	m_Modes["Two Hatch Rocket - Left"].push_back(RobotCommand(CMD_DRIVE_DISTANCE, 45, -60, 0.5, CONSTANT("HATCH_ELV_LVL1"), false, 1));
	m_Modes["Two Hatch Rocket - Left"].push_back(RobotCommand(CMD_HOLD_DISTANCE, 70, -45, 0.3, CONSTANT("HATCH_ELV_LVL1"), false, 0.5));
	m_Modes["Two Hatch Rocket - Left"].push_back(RobotCommand(CMD_VISION_ALIGN, 0, -45, -0.3, CONSTANT("HATCH_ELV_LVL1"), false, 7));
	m_Modes["Two Hatch Rocket - Left"].push_back(RobotCommand(CMD_INTAKE_EXHAUST, 0, -45, 0, CONSTANT("HATCH_ELV_LVL1"), false, 0.25));
	m_Modes["Two Hatch Rocket - Left"].push_back(RobotCommand(CMD_TURN, 0, -170, 0, CONSTANT("HATCH_ELV_LVL1"), false, 0.187));
	m_Modes["Two Hatch Rocket - Left"].push_back(RobotCommand(CMD_DRIVE_DISTANCE, 40, -170, 0.5, CONSTANT("HATCH_ELV_LVL1"), false, 3));
	m_Modes["Two Hatch Rocket - Left"].push_back(RobotCommand(CMD_VISION_HATCH_INTAKE, 0, 0, -0.2, CONSTANT("HATCH_ELV_LVL1"), false, 2.25));
	m_Modes["Two Hatch Rocket - Left"].push_back(RobotCommand(CMD_DRIVE_DISTANCE, -155, -165, 0.8, CONSTANT("HATCH_ELV_LVL1"), false, 3));
	m_Modes["Two Hatch Rocket - Left"].push_back(RobotCommand(CMD_HOLD_DISTANCE, -270, -200, 0.35, CONSTANT("HATCH_ELV_LVL1"), false, 2.25));
	m_Modes["Two Hatch Rocket - Left"].push_back(RobotCommand(CMD_TURN, 0, -140, 0, CONSTANT("HATCH_ELV_LVL1"), false, 0.7));
	m_Modes["Two Hatch Rocket - Left"].push_back(RobotCommand(CMD_VISION_ALIGN, 0, -140, -0.2, CONSTANT("HATCH_ELV_LVL1"), false, 7));
	m_Modes["Two Hatch Rocket - Left"].push_back(RobotCommand(CMD_INTAKE_EXHAUST, 0, -140, 0, CONSTANT("HATCH_ELV_LVL1"), false, 0.5));
	m_Modes["Two Hatch Rocket - Left"].push_back(RobotCommand(CMD_HOLD_DISTANCE, -24, -140, 0.35, CONSTANT("HATCH_ELV_LVL1"), false, 2));
	m_Iterator = m_Modes.begin();


	m_Modes["Two Hatch Cargo Ship - Right"];
	m_Modes["Two Hatch Cargo Ship - Right"].push_back(RobotCommand(CMD_RIGHT_ENCODER, 0, 0, 0, 5, true, 0.01)); 
	m_Modes["Two Hatch Cargo Ship - Right"].push_back(RobotCommand(CMD_PRESTART, 0, 0, 0, 0, true, 0.375));
	m_Modes["Two Hatch Cargo Ship - Right"].push_back(RobotCommand(CMD_VISION_HATCH_INTAKE, 0, 0, 0, 0, true, 0.25));
	m_Modes["Two Hatch Cargo Ship - Right"].push_back(RobotCommand(CMD_ARM_DOWN, 0, 0, 0, 0, true, 0.25));
	m_Modes["Two Hatch Cargo Ship - Right"].push_back(RobotCommand(CMD_DRIVE_DISTANCE, 45, 0, 0.35, CONSTANT("HATCH_ELV_LVL1"), false, 1.5));
	m_Modes["Two Hatch Cargo Ship - Right"].push_back(RobotCommand(CMD_VISION_ALIGN, 0, 0, -0.2, CONSTANT("HATCH_ELV_LVL1"), false, 7));
	m_Modes["Two Hatch Cargo Ship - Right"].push_back(RobotCommand(CMD_INTAKE_EXHAUST, 0, 0, 0, CONSTANT("HATCH_ELV_LVL1"), false, 0.34));
	m_Modes["Two Hatch Cargo Ship - Right"].push_back(RobotCommand(CMD_DRIVE_DISTANCE, -18, 0, 0.7, CONSTANT("HATCH_ELV_LVL1"), false, 1.5));
	m_Modes["Two Hatch Cargo Ship - Right"].push_back(RobotCommand(CMD_TURN, -18, 100, 0.7, CONSTANT("HATCH_ELV_LVL1"), true, 0.7));
	m_Modes["Two Hatch Cargo Ship - Right"].push_back(RobotCommand(CMD_DRIVE_DISTANCE, 69, 100, 0.64, CONSTANT("HATCH_ELV_LVL1"), false, 3));
	m_Modes["Two Hatch Cargo Ship - Right"].push_back(RobotCommand(CMD_DRIVE_DISTANCE, 77, 155, 0.4, CONSTANT("HATCH_ELV_LVL1"), false, 1.5));
	m_Modes["Two Hatch Cargo Ship - Right"].push_back(RobotCommand(CMD_VISION_HATCH_INTAKE, 0, 180, -0.23, CONSTANT("HATCH_ELV_LVL1"), false, 3.7));
	m_Modes["Two Hatch Cargo Ship - Right"].push_back(RobotCommand(CMD_DRIVE_DISTANCE, -180, 170, 0.7, CONSTANT("HATCH_ELV_LVL1"), false, 5));
	m_Modes["Two Hatch Cargo Ship - Right"].push_back(RobotCommand(CMD_HOLD_DISTANCE, -250, 254, 0.7, CONSTANT("HATCH_ELV_LVL1"), false, 1.2));
	//m_Modes["Two Hatch Cargo Ship - Right"].push_back(RobotCommand(CMD_DRIVE_DISTANCE, -200, 270, 0.5, CONSTANT("HATCH_ELV_LVL1"), false, 5));
	m_Modes["Two Hatch Cargo Ship - Right"].push_back(RobotCommand(CMD_VISION_ALIGN, 0, 270, -0, CONSTANT("HATCH_ELV_LVL1"), false, .2));
	m_Modes["Two Hatch Cargo Ship - Right"].push_back(RobotCommand(CMD_VISION_ALIGN, 0, 270, -0.2, CONSTANT("HATCH_ELV_LVL1"), false, 2));
	m_Modes["Two Hatch Cargo Ship - Right"].push_back(RobotCommand(CMD_INTAKE_EXHAUST, 0, 270, 0, CONSTANT("HATCH_ELV_LVL1"), false, 0.34));
	m_Modes["Two Hatch Cargo Ship - Right"].push_back(RobotCommand(CMD_DRIVE_DISTANCE, -20, 270, 0.7, CONSTANT("HATCH_ELV_LVL1"), false, 5));
	//m_Modes["Two Hatch Cargo Ship - Right"].push_back(RobotCommand(CMD_DRIVE_DISTANCE, 70, 0, 0.7, CONSTANT("HATCH_ELV_LVL1"), false, 5)); 
	m_Iterator = m_Modes.begin();

	m_Modes["Two Hatch Cargo and Rocket - Right"];
	m_Modes["Two Hatch Cargo and Rocket - Right"].push_back(RobotCommand(CMD_RIGHT_ENCODER, 0, 0, 0, 5, true, 0.01));
	m_Modes["Two Hatch Cargo and Rocket - Right"].push_back(RobotCommand(CMD_PRESTART, 0, 0, 0, 0, true, 0.375)); 
	m_Modes["Two Hatch Cargo and Rocket - Right"].push_back(RobotCommand(CMD_ARM_DOWN, 0, 0, 0, 0, true, 0.25));
	m_Modes["Two Hatch Cargo and Rocket - Right"].push_back(RobotCommand(CMD_DRIVE_DISTANCE, 45, 0, 0.7, CONSTANT("HATCH_ELV_LVL1"), false, 1.5));
	m_Modes["Two Hatch Cargo and Rocket - Right"].push_back(RobotCommand(CMD_VISION_ALIGN, 0, 0, -0.2, CONSTANT("HATCH_ELV_LVL1"), false, 7));
	m_Modes["Two Hatch Cargo and Rocket - Right"].push_back(RobotCommand(CMD_INTAKE_EXHAUST, 0, 0, 0, CONSTANT("HATCH_ELV_LVL1"), false, 0.34));
	m_Modes["Two Hatch Cargo and Rocket - Right"].push_back(RobotCommand(CMD_DRIVE_DISTANCE, -18, 0, 0.7, CONSTANT("HATCH_ELV_LVL1"), false, 1.5));
	m_Modes["Two Hatch Cargo and Rocket - Right"].push_back(RobotCommand(CMD_TURN, -18, 95, 0.7, CONSTANT("HATCH_ELV_LVL1"), true, 0.7));
	m_Modes["Two Hatch Cargo and Rocket - Right"].push_back(RobotCommand(CMD_DRIVE_DISTANCE, 69, 100, 0.64, CONSTANT("HATCH_ELV_LVL1"), false, 3));
	m_Modes["Two Hatch Cargo and Rocket - Right"].push_back(RobotCommand(CMD_DRIVE_DISTANCE, 80, 155, 0.4, CONSTANT("HATCH_ELV_LVL1"), false, 1.5));
	m_Modes["Two Hatch Cargo and Rocket - Right"].push_back(RobotCommand(CMD_VISION_HATCH_INTAKE, 0, 180, -0.23, CONSTANT("HATCH_ELV_LVL1"), false, 3.7));
	m_Modes["Two Hatch Cargo and Rocket - Right"].push_back(RobotCommand(CMD_DRIVE_DISTANCE, -140, 165, 0.8, CONSTANT("HATCH_ELV_LVL1"), false, 3));
	m_Modes["Two Hatch Cargo and Rocket - Right"].push_back(RobotCommand(CMD_HOLD_DISTANCE, -280, 200, 0.35, CONSTANT("HATCH_ELV_LVL1"), false, 2.25));
	m_Modes["Two Hatch Cargo and Rocket - Right"].push_back(RobotCommand(CMD_TURN, 0, 133, 0, CONSTANT("HATCH_ELV_LVL1"), false, 0.7));
	m_Modes["Two Hatch Cargo and Rocket - Right"].push_back(RobotCommand(CMD_VISION_ALIGN, 0, 45, -0.2, CONSTANT("HATCH_ELV_LVL1"), false, 7));
	m_Modes["Two Hatch Cargo and Rocket - Right"].push_back(RobotCommand(CMD_INTAKE_EXHAUST, 0, 45, 0, CONSTANT("HATCH_ELV_LVL1"), false, 0.5));
	m_Modes["Two Hatch Cargo and Rocket - Right"].push_back(RobotCommand(CMD_HOLD_DISTANCE, -24, 133, 0.35, CONSTANT("HATCH_ELV_LVL1"), false, 2));
	m_Iterator = m_Modes.begin();
	
	m_Modes["Two Hatch Cargo and Rocket - Left"];
	m_Modes["Two Hatch Cargo and Rocket - Left"].push_back(RobotCommand(CMD_LEFT_ENCODER, 0, 0, 0, 5, true, 0.01));
	m_Modes["Two Hatch Cargo and Rocket - Left"].push_back(RobotCommand(CMD_PRESTART, 0, 0, 0, 0, true, 0.6)); 
	m_Modes["Two Hatch Cargo and Rocket - Left"].push_back(RobotCommand(CMD_ARM_DOWN, 0, 0, 0, 0, true, 0.25));
	m_Modes["Two Hatch Cargo and Rocket - Left"].push_back(RobotCommand(CMD_HOLD_DISTANCE, 45, 0, 0.5, CONSTANT("HATCH_ELV_LVL1"), false, 1.875));
	m_Modes["Two Hatch Cargo and Rocket - Left"].push_back(RobotCommand(CMD_VISION_ALIGN, 0, 0, -0.2, CONSTANT("HATCH_ELV_LVL1"), false, 7));
	m_Modes["Two Hatch Cargo and Rocket - Left"].push_back(RobotCommand(CMD_INTAKE_EXHAUST, 0, 0, 0, CONSTANT("HATCH_ELV_LVL1"), false, 0.34));
	m_Modes["Two Hatch Cargo and Rocket - Left"].push_back(RobotCommand(CMD_DRIVE_DISTANCE, -18, 0, 0.7, CONSTANT("HATCH_ELV_LVL1"), false, 1.5));
	m_Modes["Two Hatch Cargo and Rocket - Left"].push_back(RobotCommand(CMD_TURN, -18, -95, 0.7, CONSTANT("HATCH_ELV_LVL1"), true, 0.7));
	m_Modes["Two Hatch Cargo and Rocket - Left"].push_back(RobotCommand(CMD_DRIVE_DISTANCE, 82, -100, 0.64, CONSTANT("HATCH_ELV_LVL1"), false, 3));
	m_Modes["Two Hatch Cargo and Rocket - Left"].push_back(RobotCommand(CMD_DRIVE_DISTANCE, 100, -160, 0.4, CONSTANT("HATCH_ELV_LVL1"), false, 1.5));
	m_Modes["Two Hatch Cargo and Rocket - Left"].push_back(RobotCommand(CMD_DRIVE_DISTANCE, 120, -180, 0.2, CONSTANT("HATCH_ELV_LVL1"), false, 1.5));
	m_Modes["Two Hatch Cargo and Rocket - Left"].push_back(RobotCommand(CMD_VISION_HATCH_INTAKE, 0, -160, -0.23, CONSTANT("HATCH_ELV_LVL1"), false, 2.375));
	m_Modes["Two Hatch Cargo and Rocket - Left"].push_back(RobotCommand(CMD_DRIVE_DISTANCE, -140, -165, 0.8, CONSTANT("HATCH_ELV_LVL1"), false, 3));
	m_Modes["Two Hatch Cargo and Rocket - Left"].push_back(RobotCommand(CMD_HOLD_DISTANCE, -280, -200, 0.35, CONSTANT("HATCH_ELV_LVL1"), false, 2.25));
	m_Modes["Two Hatch Cargo and Rocket - Left"].push_back(RobotCommand(CMD_TURN, 0, -133, 0, CONSTANT("HATCH_ELV_LVL1"), false, 0.7));
	m_Modes["Two Hatch Cargo and Rocket - Left"].push_back(RobotCommand(CMD_VISION_ALIGN, 0, -45, -0.2, CONSTANT("HATCH_ELV_LVL1"), false, 7));
	m_Modes["Two Hatch Cargo and Rocket - Left"].push_back(RobotCommand(CMD_INTAKE_EXHAUST, 0, -45, 0, CONSTANT("HATCH_ELV_LVL1"), false, 0.5));
	m_Modes["Two Hatch Cargo and Rocket - Left"].push_back(RobotCommand(CMD_HOLD_DISTANCE, -24, -133, 0.35, CONSTANT("HATCH_ELV_LVL1"), false, 2));
	m_Iterator = m_Modes.begin();

}

std::deque<RobotCommand> AutoModes::GetCommandList()
{
	return m_Iterator->second;
}

const char *AutoModes::GetName()
{
	return m_Iterator->first;
}

void AutoModes::NextMode()
{
	++m_Iterator;
	if(m_Iterator == m_Modes.end())
	{
		m_Iterator = m_Modes.begin();
	}
	std::string str(GetName());
	std::string temp = "Auto mode: " + str;
	frc::DriverStation::GetInstance().ReportError(temp);
}
