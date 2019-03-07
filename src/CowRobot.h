//==================================================
// Copyright (C) 2018 Team 1538 / The Holy Cows
//==================================================

#ifndef __COW_ROBOT_H__
#define __COW_ROBOT_H__

#include <CowLib/CowLogger.h>
#include <frc/WPILib.h>
#include "Controllers/GenericController.h"
#include "CowLib/CowLib.h"
#include "CowControlBoard.h"
#include "frc/CounterBase.h"
#include "CowConstants.h"
#include "CowLib/CowAlphaNum.h"
#include "CowGyro.h"
#include "CowLib/CowMotorController.h"
#include "CowLib/CowCanifier.h"
#include "CowLib/CowLPF.h"
#include "frc/smartdashboard/Smartdashboard.h"
#include "networktables/NetworkTable.h"
#include "Subsystems/Elevator.h"
#include "Subsystems/Arm.h"
#include "Subsystems/Intake.h"
#include "CowStateMachine.h"

class CowRobot
{
private:
    int m_DSUpdateCount;
    
    GenericController *m_Controller;
    
    // Drive Motors
    CowLib::CowMotorController *m_LeftDriveA;
    CowLib::CowMotorController *m_LeftDriveB;
    CowLib::CowMotorController *m_LeftDriveC;

    CowLib::CowMotorController *m_RightDriveA;
    CowLib::CowMotorController *m_RightDriveB;
    CowLib::CowMotorController *m_RightDriveC;

    CowLib::CowCanifier *m_Canifier;

    CowLib::CowGyro *m_Gyro;
    frc::Encoder *m_DriveEncoder;
    frc::Encoder *m_DriveEncoderLeft;
    frc::Encoder *m_DriveEncoderRight;

    frc::PowerDistributionPanel *m_PowerDistributionPanel;

    CowLib::CowAlphaNum *m_LEDDisplay;
    CowLib::CowLogger *m_WebServer;

    Elevator *m_Elevator;
    Arm *m_Arm;
    Arm *m_Wrist;
    Intake *m_Intake;
    CowStateMachine *m_StateMachine;

    bool m_DetectLoadingStation;

    float m_LeftDriveValue;
    float m_RightDriveValue;

    double m_PreviousGyroError;
    double m_PreviousDriveError;

    double m_MatchTime;
    double m_StartTime;

    void SetLeftMotors(float val);
    void SetRightMotors(float val);

    frc::Accelerometer *m_Accelerometer;

    CowLib::CowLPF *m_AccelY_LPF;
    CowLib::CowLPF *m_LoadDetect_LPF;

    float m_TipTime;
    bool m_Tipping;
    std::shared_ptr<nt::NetworkTable> m_LimelightForward;
    std::shared_ptr<nt::NetworkTable> m_LimelightBackward;
    frc::CameraServer *m_CameraServer;
    cs::UsbCamera *m_UsbCamera;


public:
    CowRobot();
    void Reset();
    void GyroHandleCalibration();
    void GyroFinalizeCalibration();
    void SetController(GenericController *controller);
    void PrintToDS();
    double GetDriveDistance();
    bool DriveDistance(double distance);
    bool DriveDistanceWithHeading(double heading, double distance, double speed);
    bool DriveWithHeading(double heading, double speed);
    bool DriveWithHeading(double heading, double speed, double maxSpeed);
    void DriveSpeedTurn(float speed, float turn, bool quickTurn);
    void DriveLeftRight(float leftDriveValue, float rightDriveValue);
    bool TurnToHeading(double heading);
    void DetectLoadingStation()
    {
        m_DetectLoadingStation = true;
    }
    void ResetLoadingStation()
    {
        m_DetectLoadingStation = false;
    }

    std::shared_ptr<nt::NetworkTable> GetLimelight(bool direction)
    {
        if (!direction)
        {   
            return m_LimelightForward;
        }
        else
        {
            return m_LimelightBackward;
        }
    }
    void QuickTurn(float turn);
    
    void StartTime();



    CowLib::CowAlphaNum *GetDisplay()
    {
        return m_LEDDisplay;
    }

    frc::PowerDistributionPanel *GetPowerDistributionPanel()
    {
        return m_PowerDistributionPanel;
    }

    CowLib::CowGyro *GetGyro()
    {
        return CowLib::CowGyro::GetInstance();
    }

    frc::Encoder *GetEncoder()
    {
        return m_DriveEncoder;
    }

    Elevator* GetElevator()
    {
        return m_Elevator;
    }
    Arm* GetArm()
    {
        return m_Arm;
    }

    Arm* GetWrist()
    {
        return m_Wrist;
    }
    Intake* GetIntake()
    {
        return m_Intake;
    }
    
    CowStateMachine* GetStateMachine()
    {
        return m_StateMachine;
    }

    CowLib::CowCanifier* GetCanifier()
    {
        return m_Canifier;
    }

    void UseLeftEncoder()
    {
        m_DriveEncoder = m_DriveEncoderLeft;
    }

    void UseRightEncoder()
    {
        m_DriveEncoder = m_DriveEncoderRight;
    }

    void ResetEncoders()
    {
        m_DriveEncoderLeft->Reset();
        m_DriveEncoderRight->Reset();
    }

    void handle();
};

#endif
