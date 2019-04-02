#include "OperatorController.h"
#include <iostream>

OperatorController::OperatorController(CowControlBoard *controlboard)
    :
    m_CB(controlboard)
{
	m_ClimbLatch = new CowLib::CowLatch();
	m_ClimbSetHeight = false;
}

void OperatorController::handle(CowRobot *bot)
{
    float r_color = m_CB->GetOperatorGamepadAxis(2);
    r_color = fabs(r_color*254);
    float g_color = m_CB->GetDriveAxis(2);
    g_color = fabs(g_color*254);
    float b_color = m_CB->GetDriveAxis(0);
    b_color = fabs(b_color*254);
    bot->GetCanifier()->SetLEDColor(r_color, g_color, b_color);
    bool doingTracking = false;
    if(m_CB->GetDriveButton(1))
    {
	doingTracking = true;
        //bot->TurnToHeading(90);
        //bot->DriveDistanceWithHeading(0, 12, 0.5);

	//	bool acquired = bot->DoVisionTracking(-CONSTANT("AUTO_TRACK_SPEED"));
	//	if(acquired)
	//	{
	//    		bot->GetHatchIntake()->SetSpeed(-1, true);
	//		std::cout << "Done!" << std::endl;
	//	}
    }
    else
    {
       if(m_CB->GetSteeringButton(3))
       {
	bot->DoVisionTracking(m_CB->GetDriveStickY());
       }
       else
       { 
        bot->GetLimelight()->PutNumber("pipeline", 3);
        bot->GetLimelight()->PutNumber("ledMode", 1);
         bot->DriveSpeedTurn(m_CB->GetDriveStickY(),
                             m_CB->GetSteeringX(),
                             m_CB->GetSteeringButton(FAST_TURN));
      }
    }
   
   //Handle the climb 
   if(m_CB->GetOperatorButton(8))
    {
        bot->GetLeftJack()->SetPosition(-CONSTANT("JACK_UP"));
        bot->GetRightJack()->SetPosition(CONSTANT("JACK_UP"));
	if(bot->GetLeftJack()->IsExtended())
	{
		bot->GetElevator()->SetPosition(0);
	}
    }
    else
    {
	//The full send button
        if(m_ClimbLatch->Latch(m_CB->GetOperatorButton(3)))
        {
	    if (!m_ClimbSetHeight)
	    {
		bot->GetElevator()->SetPosition(CONSTANT("ELEVATOR_CLIMB_POS"));
		m_ClimbSetHeight = true;
	    }
	    else
	    {
			m_ClimbSetHeight = false;
			bot->GetLeftJack()->SetPosition(-CONSTANT("JACK_DOWN"));
			bot->GetRightJack()->SetPosition(CONSTANT("JACK_DOWN"));
            		bot->GetArm()->SetPosition(CONSTANT("ARM_DOWN_CLIMB"));
			bot->GetElevator()->SetPosition(-3);
	    }
        }
	else if(!m_CB->GetOperatorButton(3))
	{
		m_ClimbLatch->ResetLatch();
	}
    }

    //We need to hand over cargo intake controls to the driver stick
    if(bot->GetLeftJack()->IsExtended())
    {
	bot->GetCargoIntake()->SetSpeed(m_CB->GetDriveStickY(), true);
    }
    else
    {
    	//Intake
    	if (m_CB->GetOperatorButton(2))
    	{   
    	    //10 on = cargo mode
    	    if (m_CB->GetOperatorButton(10))
    	    {
    	        bot->GetCargoIntake()->SetSpeed(1, false);
    	    }
    	    else
    	    {
    	        bot->GetHatchIntake()->SetSpeed(1, false);
    	    }
    	}
    	//Exhaust
    	else if (m_CB->GetOperatorButton(1))
    	{
    	     //10 on = cargo mode
    	     if (m_CB->GetOperatorButton(10))
    	     {
    	         bot->GetCargoIntake()->SetSpeed(-1, true);
    	     }
    	     else
    	     {
    	         bot->GetHatchIntake()->SetSpeed(-1, true);
    	     }
    	}
    	else
    	{
    	        bot->GetCargoIntake()->SetSpeed(0, false);
		if(!doingTracking)
		{
    	        	bot->GetHatchIntake()->SetSpeed(0, false);
		}
    	}
    }

    if(!m_CB->GetOperatorButton(10))
    {
        if(m_CB->GetOperatorButton(4))
        {
            bot->GetElevator()->SetPosition(CONSTANT("HATCH_ELV_LVL1"));
        }
        else if(m_CB->GetOperatorButton(6))
        {
            bot->GetElevator()->SetPosition(CONSTANT("HATCH_ELV_LVL2"));
        }
        else if(m_CB->GetOperatorButton(5))
        {
            bot->GetElevator()->SetPosition(CONSTANT("HATCH_ELV_LVL3"));
        }
        else if(m_CB->GetOperatorButton(9))
        {
            bot->GetElevator()->SetPosition(CONSTANT("HATCH_ELV_HP"));
        }
    }
    else
    {
        if(m_CB->GetOperatorButton(4))
        {
            bot->GetElevator()->SetPosition(CONSTANT("CARGO_ELV_LVL1"));
        }
        else if(m_CB->GetOperatorButton(6))
        {
            bot->GetElevator()->SetPosition(CONSTANT("CARGO_ELV_LVL2"));
        }
        else if(m_CB->GetOperatorButton(5))
        {
            bot->GetElevator()->SetPosition(CONSTANT("CARGO_ELV_LVL3"));
        }
        else if(m_CB->GetOperatorButton(9))
        {
            bot->GetElevator()->SetPosition(CONSTANT("CARGO_ELV_HP"));
        }
        else if(m_CB->GetOperatorButton(7))
        {
            bot->GetElevator()->SetPosition(CONSTANT("CARGO_ELV_HP"));
        }
    }
    if(bot->GetElevator()->GetSetPoint() == CONSTANT("HATCH_ELV_LVL3"))
    {
        bot->GetArm()->SetPosition(CONSTANT("HATCH_ARM_LVL3"));
    }
    else if(bot->GetElevator()->GetSetPoint() == CONSTANT("CARGO_ELV_LVL1") && !m_CB->GetOperatorButton(8))
    {
        bot->GetArm()->SetPosition(CONSTANT("CARGO_ARM_LVL1"));
    }
    else
    {

        if(m_CB->GetOperatorButton(8))
        {
            bot->GetArm()->SetPosition(CONSTANT("ARM_UP"));
        }
        else
        {
	    if(bot->GetLeftJack()->IsExtended())
	    {
            	bot->GetArm()->SetPosition(CONSTANT("ARM_DOWN_CLIMB"));
	    }
	    else
	    {
            	bot->GetArm()->SetPosition(CONSTANT("ARM_DOWN"));
	    }
        }
    }
    
    float elevatorJoystickDeadband = CowLib::Deadband(m_CB->GetOperatorGamepadAxis(1), 0.2);
    if(elevatorJoystickDeadband != 0)
    {
        float manualElevatorPosition = bot->GetElevator()->GetSetPoint() + (elevatorJoystickDeadband * .4);
        bot->GetElevator()->SetPosition(manualElevatorPosition);
    }

}

