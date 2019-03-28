#include "OperatorController.h"
#include <iostream>

OperatorController::OperatorController(CowControlBoard *controlboard)
    :
    m_CB(controlboard)
{
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
    if(m_CB->GetDriveButton(1))
    {
        //bot->TurnToHeading(90);
        //bot->DriveDistanceWithHeading(0, 12, 0.5);
	bool acquired = bot->DoVisionTracking(0.375);
    	bot->GetCargoIntake()->SetSpeed(-1, true);
	if(acquired)
	{
		std::cout << "Got the hatch!" << std::endl;
	}
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
    }
    else
    {
        if(m_CB->GetOperatorButton(3))
        {
            bot->GetLeftJack()->SetPosition(-CONSTANT("JACK_DOWN"));
            bot->GetRightJack()->SetPosition(CONSTANT("JACK_DOWN"));
            bot->GetElevator()->SetPosition(-3);
        }   
    }

    //We need to hand over cargo intake controls to the driver stick
    if(bot->GetLeftJack()->IsExtended())
    {
	bot->GetCargoIntake()->SetSpeed(-m_CB->GetDriveStickY(), true);
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
    	        bot->GetHatchIntake()->SetSpeed(0, false);
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
    }
    if(bot->GetElevator()->GetSetPoint() == CONSTANT("HATCH_ELV_LVL3"))
    {
        bot->GetArm()->SetPosition(CONSTANT("HATCH_ARM_LVL3"));
        //if(!m_CB->GetOperatorButton(8))
        //{
        //    bot->GetArm()->SetPosition(CONSTANT("ARM_DOWN"));
        //}
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

