#include "AutoModeController.h"
#include <iostream>
#include <frc/Timer.h>

AutoModeController::AutoModeController()
:
m_Timer(new frc::Timer()),
m_CurrentCommand(RobotCommand())
{
	m_Timer->Start();
	reset();

	m_OriginalEncoder = 0;
}

void AutoModeController::SetCommandList(std::deque<RobotCommand> list)
{
	m_CommandList = list;
}

void AutoModeController::reset()
{
	CowConstants::GetInstance();

	m_CommandList.clear();
	m_CurrentCommand = RobotCommand();
}

void AutoModeController::handle(CowRobot *bot)
{
	bool result = false;
        bot->GetLimelight()->PutNumber("pipeline", 0);
        bot->GetLimelight()->PutNumber("ledMode", 1);

	// Run the command
	switch(m_CurrentCommand.m_Command)
	{
	case CMD_NULL:
	{
		doNothing(bot);
		result = true;
		break;
	}
	case CMD_WAIT:
	{
		bot->DriveWithHeading(m_CurrentCommand.m_Heading, 0);
		doNothing(bot);
		break;
	}
	case CMD_TURN:
	{
		result = bot->TurnToHeading(m_CurrentCommand.m_Heading);
		break;
	}
	case CMD_TURN_INTAKE:
	{
		result = bot->TurnToHeading(m_CurrentCommand.m_Heading);
		//bot->GetArm()->SetModulatedSpeed(CONSTANT("INTAKE_SPEED"));

		break;
	}
	case CMD_VISION_HATCH_INTAKE:
	{
		bot->DoVisionTracking(m_CurrentCommand.m_Speed);
		bot->GetElevator()->SetPosition(m_CurrentCommand.m_ElevatorPos);
                bot->GetHatchIntake()->SetSpeed(1, false);
		//bot->GetArm()->SetIntakeSpeed(-0.2);

		//result = false;
		result = bot->GetHatchIntake()->BlinkLED();
		break;
	}
	case CMD_VISION_ALIGN:
	{
		bot->DoVisionTracking(m_CurrentCommand.m_Speed,4.5);
		bot->GetElevator()->SetPosition(m_CurrentCommand.m_ElevatorPos);
                //bot->GetHatchIntake()->SetSpeed(1, false);
		//bot->GetArm()->SetIntakeSpeed(-0.2);

		result = bot->DoVisionTracking(m_CurrentCommand.m_Speed);
		break;
	}
	case CMD_PRESTART:
	{
		bot->DriveLeftRight(0, 0);
		bot->GetElevator()->SetPosition(CONSTANT("ELEVATOR_PRESTART"));
		bot->GetArm()->SetPosition(CONSTANT("ARM_PRESTART"));
        	bot->GetHatchIntake()->SetSpeed(1, false);

		result = false;
		break;
	}
case CMD_HOLD_DISTANCE:
	{
		bot->DriveDistanceWithHeading(m_CurrentCommand.m_Heading, m_CurrentCommand.m_EncoderCount, m_CurrentCommand.m_Speed);
		bot->GetElevator()->SetPosition(m_CurrentCommand.m_ElevatorPos);
                bot->GetHatchIntake()->SetSpeed(0, false);
		//bot->GetArm()->SetIntakeSpeed(-0.2);

		result = false;
		break;
	}
	case CMD_HOLD_DISTANCE_INTAKE:
	{
		bot->DriveDistanceWithHeading(m_CurrentCommand.m_Heading, m_CurrentCommand.m_EncoderCount, m_CurrentCommand.m_Speed);
		bot->GetElevator()->SetPosition(m_CurrentCommand.m_ElevatorPos);
//		bot->GetArm()->SetPosition(CONSTANT("ARM_DOWN"));
		//bot->GetArm()->SetModulatedSpeed(CONSTANT("INTAKE_SPEED"));

		result = false;
		break;
	}
	case CMD_ARM_UP:
	{
		bot->DriveLeftRight(0, 0);
		bot->GetArm()->SetPosition(CONSTANT("ARM_UP"));
		//bot->GetArm()->SetIntakeSpeed(-0.6);

		result = false;
		break;
	}
	case CMD_ARM_DOWN:
	{
		bot->DriveLeftRight(0, 0);
		bot->GetArm()->SetPosition(CONSTANT("ARM_DOWN"));
		//bot->GetArm()->SetIntakeSpeed(-0.2);

		result = false;
		break;
	}

	case CMD_DRIVE_DISTANCE:
	{
		float direction = 1;
		if(m_OriginalEncoder > m_CurrentCommand.m_EncoderCount)
		{
			//We want to go backward
			direction = -1;
		}

		bot->DriveWithHeading(m_CurrentCommand.m_Heading, m_CurrentCommand.m_Speed * direction);
		bot->GetElevator()->SetPosition(m_CurrentCommand.m_ElevatorPos);
		//bot->GetArm()->SetIntakeSpeed(-0.2);

		if(direction == 1) //Going forward
		{
			if(bot->GetDriveDistance()  > m_CurrentCommand.m_EncoderCount)
			{
				result = true;
			}
		}
		else //Going backward
		{
			if(bot->GetDriveDistance()  < m_CurrentCommand.m_EncoderCount)
			{
				result = true;
			}
		}

		break;
	}
	case CMD_DRIVE_DISTANCE_INTAKE:
	{
		float direction = 1;
		if(m_OriginalEncoder > m_CurrentCommand.m_EncoderCount)
		{
			//We want to go backward
			direction = -1;
		}

		bot->DriveWithHeading(m_CurrentCommand.m_Heading, m_CurrentCommand.m_Speed * direction);
		bot->GetElevator()->SetPosition(m_CurrentCommand.m_ElevatorPos);
//		bot->GetArm()->SetPosition(CONSTANT("ARM_DOWN"));
		//bot->GetArm()->SetModulatedSpeed(CONSTANT("INTAKE_SPEED"));

		if(direction == 1) //Going forward
		{
			if(bot->GetDriveDistance()  > m_CurrentCommand.m_EncoderCount)
			{
				result = true;
			}
		}
		else //Going backward
		{
			if(bot->GetDriveDistance()  < m_CurrentCommand.m_EncoderCount)
			{
				result = true;
			}
		}
		break;
	}
	case CMD_LEFT_ENCODER:
	{
		std::cout << "Using the left encoder" << std::endl;
		doNothing(bot);
		bot->UseLeftEncoder();
		bot->ResetEncoders();
		break;
	}
	case CMD_RIGHT_ENCODER:
	{
		std::cout << "Using the right encoder" << std::endl;
		doNothing(bot);
		bot->UseRightEncoder();
		bot->ResetEncoders();

		break;
	}
	case CMD_INTAKE_EXHAUST:
	{
		doNothing(bot);
		bot->ResetEncoders();
                bot->GetHatchIntake()->SetSpeed(-1, true);

		break;
	}
	default:
	{
		doNothing(bot);
		result = true;
		break;
	}
	}

	//Check if this command is done
	if(result == true || m_CurrentCommand.m_Command == CMD_NULL || m_Timer->Get() > m_CurrentCommand.m_Timeout)
	{
		// This command is done, go get the next one
		if(m_CommandList.size() > 0 )
		{
			if(m_CurrentCommand.m_Command == CMD_TURN || 
				m_CurrentCommand.m_Command == CMD_VISION_HATCH_INTAKE)
			{
				bot->ResetEncoders();
			}
			m_CurrentCommand = m_CommandList.front();
			m_OriginalEncoder = bot->GetDriveDistance();
			m_CommandList.pop_front();
			//bot->GetEncoder()->Reset();

			if(!m_CurrentCommand.m_Command == CMD_NULL)
			{
				printf("Time elapsed: %f\n", m_Timer->Get());
			}
		}
		else
		{
			// We're done clean up
			m_CurrentCommand = RobotCommand();
		}
		m_Timer->Reset();
	}
}

// Drive Functions
void AutoModeController::doNothing(CowRobot *bot)
{
	bot->DriveLeftRight(0, 0);
}
