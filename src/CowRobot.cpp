#include "CowRobot.h"
#include "CowBase.h"
#include <iostream>
#include "frc/smartdashboard/Smartdashboard.h"
#include <networktables/NetworkTable.h>
#include <networktables/NetworkTableInstance.h>

CowRobot::CowRobot()
{    
    m_DSUpdateCount = 0;
        
    m_Controller = NULL;
    m_ControllerBackup = NULL;

    // Set up drive motors
    m_LeftDriveA = new CowLib::CowMotorController(DRIVE_LEFT_A);
    m_LeftDriveB = new CowLib::CowMotorController(DRIVE_LEFT_B);
    m_LeftDriveC = new CowLib::CowMotorController(DRIVE_LEFT_C);

    m_RightDriveA = new CowLib::CowMotorController(DRIVE_RIGHT_A);
    m_RightDriveB = new CowLib::CowMotorController(DRIVE_RIGHT_B);
    m_RightDriveC = new CowLib::CowMotorController(DRIVE_RIGHT_C);

    m_LeftDriveA->SetNeutralMode(CowLib::CowMotorController::BRAKE);
    m_LeftDriveB->SetNeutralMode(CowLib::CowMotorController::BRAKE);
    m_LeftDriveC->SetNeutralMode(CowLib::CowMotorController::BRAKE);

    m_RightDriveA->SetNeutralMode(CowLib::CowMotorController::BRAKE);
    m_RightDriveB->SetNeutralMode(CowLib::CowMotorController::BRAKE);
    m_RightDriveC->SetNeutralMode(CowLib::CowMotorController::BRAKE);

    m_DriveEncoderRight = new frc::Encoder(MXP_QEI_5_A, MXP_QEI_5_B, false, frc::Encoder::k1X);
    m_DriveEncoderRight->SetDistancePerPulse(0.052359916666667); // 6*pi/360

    m_DriveEncoderLeft = new frc::Encoder(MXP_QEI_4_A, MXP_QEI_4_B, true, frc::Encoder::k1X);
    m_DriveEncoderLeft->SetDistancePerPulse(0.052359916666667); // 6*pi/360

    m_DriveEncoder = m_DriveEncoderRight;

    m_Elevator = new Elevator (2, 3, MXP_QEI_3_A, MXP_QEI_3_B);
    m_Arm = new Arm(6, CONSTANT("ARM_PEAK_OUTPUT"), CONSTANT("ARM_UP_LIMIT"), CONSTANT("ARM_DOWN"), "ARM", true, 0, CONSTANT("ARM_PEAK_OUTPUT"));
    m_CargoIntake = new Intake(14, true, CONSTANT("CARGO_AUTOHOLD_SPEED"), CONSTANT("CARGO_INTAKE_CURRENT_LPF"), CONSTANT("CARGO_CURRENT_THRESHOLD"));
    m_CargoIntake_B = new CowLib::CowMotorController(7);
    m_CargoIntake_B->SetControlMode(CowLib::CowMotorController::FOLLOWER);
    m_CargoIntake_B->GetInternalMotor()->SetInverted(true);

    m_HatchIntake = new Intake(5, true, CONSTANT("HATCH_AUTOHOLD_SPEED"), CONSTANT("HATCH_INTAKE_CURRENT_LPF"), CONSTANT("HATCH_CURRENT_THRESHOLD"));

    m_RightJack = new Jack(1, true);
    m_LeftJack = new Jack(4, true);

    m_DetectLoadingStation = false;
    m_LoadDetect_LPF = new CowLib::CowLPF(CONSTANT("LOAD_DETECT_LPF"));

    m_MatchTime = 0;
    m_StartTime = 0;

    m_LEDDisplay = new CowLib::CowAlphaNum(0x70);

    m_Gyro = CowLib::CowGyro::GetInstance();

    //m_Gyro->Reset();
    m_PowerDistributionPanel = new frc::PowerDistributionPanel();
    m_WebServer = new CowLib::CowLogger();

    m_Canifier = new CowLib::CowCanifier(15);

    m_LeftDriveValue = 0;
    m_RightDriveValue = 0;
    
    m_PreviousGyroError = 0;
    m_PreviousDriveError = 0;

    m_Accelerometer = new frc::BuiltInAccelerometer(frc::Accelerometer::kRange_4G);
    m_AccelY_LPF = new CowLib::CowLPF(CONSTANT("TIP_LPF"));
    m_TipTime = 0;
    m_Tipping = false;

    m_LimelightForward = nt::NetworkTableInstance::GetDefault().GetTable("limelight-front");
    m_CameraServer = frc::CameraServer::GetInstance();
    cs::UsbCamera temp = m_CameraServer->StartAutomaticCapture();
    
    std::cout << "Set pixelformat: " << temp.SetPixelFormat(cs::VideoMode::kYUYV) << std::endl;
    std::cout << "Set resolution: " << temp.SetResolution(CONSTANT("CAMERA_W"), CONSTANT("CAMERA_H")) << std::endl;
    std::cout << "Set framerate: " << temp.SetFPS(CONSTANT("CAMERA_FPS")) << std::endl;

    m_Limelight_PID = new CowLib::CowPID(CONSTANT("LIMELIGHT_X_KP"), 0, CONSTANT("LIMELIGHT_X_KD"), 0);
}

void CowRobot::Reset()
{
    ResetEncoders();

    m_PreviousGyroError = 0;
    m_PreviousDriveError = 0;

    m_LeftDriveValue = 0;
    m_RightDriveValue = 0;
    m_MatchTime = 0;
    m_AccelY_LPF->UpdateBeta(CONSTANT("TIP_LPF"));
    m_LoadDetect_LPF->UpdateBeta(CONSTANT("LOAD_DETECT_LPF"));
    m_Elevator->ResetConstants();
    m_Arm->ResetConstants(CONSTANT("ARM_UP_LIMIT"), CONSTANT("ARM_DOWN"), CONSTANT("ARM_PEAK_OUTPUT"));
    m_CargoIntake->ResetConstants(CONSTANT("CARGO_INTAKE_CURRENT_LPF"), CONSTANT("CARGO_AUTO_HOLD_SPEED"), CONSTANT("CARGO_CURRENT_THRESHOLD"));
    m_HatchIntake->ResetConstants(CONSTANT("HATCH_INTAKE_CURRENT_LPF"), CONSTANT("HATCH_AUTO_HOLD_SPEED"), CONSTANT("HATCH_CURRENT_THRESHOLD"));
    m_Limelight_PID->UpdateConstants(CONSTANT("LIMELIGHT_X_KP"), 0, CONSTANT("LIMELIGHT_X_KD"), 0);
}

void CowRobot::SetController(GenericController *controller)
{
    m_Controller = controller;
}

void CowRobot::SetBackupController(GenericController *controller)
{
    m_ControllerBackup = controller;
}

void CowRobot::UseBackupController()
{
    if(m_ControllerBackup)
    {
	m_Controller = m_ControllerBackup;
    }
}

void CowRobot::PrintToDS()
{
    if(m_DSUpdateCount % 10 == 0)
    {
        m_DSUpdateCount = 0;
    }
}

bool CowRobot::DoVisionTracking(float speed, float threshold)
{
	GetLimelight()->PutNumber("pipeline", 0);
	GetLimelight()->PutNumber("ledMode", 3);

	float limelightX = GetLimelight()->GetNumber("tx",0.0);
	float pidOutput = m_Limelight_PID->Calculate(-limelightX);
	
	DriveSpeedTurn(CowLib::LimitMix(speed, CONSTANT("LIMELIGHT_MAX_SPEED")), pidOutput, 1);

	//Limelight has valid targets
	if(GetLimelight()->GetNumber("tv", 0) == 1)
	{
		//If the target area is larger than the threshold, we likely have the gamepiece or scored
		if(GetLimelight()->GetNumber("ta", 0) >= threshold)
		{
			return true;
		}  
		return false;
	}
}

// Used to handle the recurring logic funtions inside the robot.
// Please call this once per update cycle.
void CowRobot::handle()
{    
    m_MatchTime = frc::Timer::GetFPGATimestamp() - m_StartTime;

    if(m_Controller == NULL)
    {
        printf("No controller for CowRobot!!\n");
        return;
    }

    //printf("Handling...\n");
    m_Controller->handle(this);

    // Default drive
    float tmpLeftMotor = m_LeftDriveValue;
    float tmpRightMotor = m_RightDriveValue;

    SetLeftMotors(tmpLeftMotor);
    SetRightMotors(tmpRightMotor);

    if(m_DSUpdateCount % 10 == 0)
    {
        //5 is drive
        //4 s1
        //3 s2
        //2 arm
        //1 unused

        //std::cout << "Gyro: " <<  m_Gyro->GetAngle() << std::endl;
        //std::cout << std::dec
        //          << m_DriveEncoder->Get() << " "
        //      << m_Gyro->GetAngle() << std::endl;std::cout << "Heading: " << m_Gyro->GetAngle() << " " << m_DriveEncoder->GetDistance() << std::endl;

    }

    frc::SmartDashboard::PutNumber("Elevator SP", m_Elevator->GetSetPoint());
    frc::SmartDashboard::PutNumber("Elevator PV", m_Elevator->GetDistance());
    frc::SmartDashboard::PutNumber("Arm PV", m_Arm->GetPosition());
    frc::SmartDashboard::PutNumber("Arm SP", m_Arm->GetSetpoint() * m_Arm->GetDegreesPerTick());
    frc::SmartDashboard::PutNumber("Elevator At Target:", m_Elevator->AtTarget());
    frc::SmartDashboard::PutNumber("Arm At Target:", m_Arm->AtTarget());
    frc::SmartDashboard::PutNumber("Drive distance", GetDriveDistance());
    frc::SmartDashboard::PutNumber("lEnc", m_DriveEncoderLeft->GetDistance());
    frc::SmartDashboard::PutNumber("rEnc", m_DriveEncoderRight->GetDistance());
    frc::SmartDashboard::PutNumber("Gyro", m_Gyro->GetAngle());

    m_Elevator->handle();
    m_Arm->handle();
    m_CargoIntake->handle();
    m_CargoIntake_B->Set(14);
    m_HatchIntake->handle();
    m_RightJack->handle();
    m_LeftJack->handle();
    //m_Canifier->Handle();

    if(m_CargoIntake->BlinkLED() || m_HatchIntake->BlinkLED())
    {
	GetLimelight()->PutNumber("ledMode", 2);
    }

    m_DSUpdateCount++;
}

double CowRobot::GetDriveDistance()
{
    return m_DriveEncoder->GetDistance();
}

bool CowRobot::DriveDistance(double distance)
{
    double PID_P = CONSTANT("DRIVE_P");
    double PID_D = CONSTANT("DRIVE_D");
    double error = distance - m_DriveEncoder->GetDistance();
    double dError = error - m_PreviousDriveError;
    double output = PID_P*error + PID_D*dError;

    double speed = CONSTANT("PTO_DRIVE_SPEED");
    DriveLeftRight(speed-output, speed+output);


    m_PreviousDriveError = error;

    return (fabs(error) < 4 && CowLib::UnitsPerSecond(fabs(dError)) < 1);
}

bool CowRobot::DriveDistanceWithHeading(double heading, double distance, double speed)
{
    double PID_P = CONSTANT("DRIVE_P");
    double PID_D = CONSTANT("DRIVE_D");
    double error = distance - m_DriveEncoder->GetDistance();
    double dError = error - m_PreviousDriveError;
    double output = PID_P*error + PID_D*dError;
    
    double throttle = CowLib::LimitMix(output, speed);
    //throttle *= -1;
    //std::cout << "Drive request speed: " << throttle << std::endl;

    bool headingResult = DriveWithHeading(heading, throttle);
    
    m_PreviousDriveError = error;
    
    return (fabs(error) < 4 && headingResult);
}

bool CowRobot::TurnToHeading(double heading)
{
    double PID_P = CONSTANT("TURN_P");
    double PID_D = CONSTANT("TURN_D");
    double error = m_Gyro->GetAngle() - heading;
    double dError = error - m_PreviousGyroError;
    double output = PID_P*error + PID_D*dError;

    //speed *= -speed;

    DriveLeftRight(-output, output);

    m_PreviousGyroError = error;

    return (fabs(error) < 1 && CowLib::UnitsPerSecond(fabs(dError)) < 0.5);
}

bool CowRobot::DriveWithHeading(double heading, double speed)
{
    double PID_P = CONSTANT("TURN_P");
    double PID_D = CONSTANT("TURN_D");
    double error = m_Gyro->GetAngle() - heading;
    double dError = error - m_PreviousGyroError;
    double output = PID_P*error + PID_D*dError;

    //speed *= -speed;
                
    DriveLeftRight(speed-output, speed+output);
    
    m_PreviousGyroError = error;
    
    return (fabs(error) < 1 && CowLib::UnitsPerSecond(fabs(dError)) < 0.5);
}

bool CowRobot::DriveWithHeading(double heading, double speed, double maxSpeed)
{
    double PID_P = CONSTANT("TURN_P");
    double PID_D = CONSTANT("TURN_D");
    double error = heading - m_Gyro->GetAngle();
    double dError = error - m_PreviousGyroError;
    double output = PID_P*error + PID_D*dError;
    output = CowLib::LimitMix(output, maxSpeed);

    DriveLeftRight(speed-output, speed+output);

    m_PreviousGyroError = error;

    return (fabs(error) < 1 && CowLib::UnitsPerSecond(fabs(dError)) < 0.5);
}


// Allows skid steer robot to be driven using tank drive style inputs
void CowRobot::DriveLeftRight(float leftDriveValue, float rightDriveValue)
{
    m_LeftDriveValue = leftDriveValue;
    m_RightDriveValue = rightDriveValue;
}

void CowRobot::DriveSpeedTurn(float speed, float turn, bool quickTurn)
{
    // Linear degredation of steeering based off of velocity

    //velocity *= 0.003;
    float temp_vel = speed;
    float sensitivity = 0;

    if (temp_vel < 0)
        temp_vel = -temp_vel;

    //printf("Velocity: %f, stick: %f\r\n", velocity, temp_vel);
    
    if(speed < 0.10 && speed > -0.10)
        speed = 0;
    if (((turn < 0.02) && (turn > -0.02)) || ((speed == 0) && !quickTurn))
        turn = 0;

    if(quickTurn)
    {
        if(speed == 0.0)
        {
            sensitivity = 1;
        }
        else
        {
            sensitivity = 0.9;
        }

    }
    else
    {
        sensitivity = 0.25;
    }

    turn *= sensitivity;
    turn = -turn;
    

    float left_power = CowLib::LimitMix(-speed - turn);
    float right_power = CowLib::LimitMix(-speed + turn);

    DriveLeftRight(left_power, right_power);
}

// Allows robot to spin in place
void CowRobot::QuickTurn(float turnRate)
{
    // When provided with + turn, quick turn right

    float left = -1 * turnRate;
    float right = turnRate;

    DriveLeftRight(left, right);
}

// Sets the left side motors
void CowRobot::SetLeftMotors(float val)
{
    if (val > 1.0)
        val = 1.0;
    if (val < -1.0)
        val = -1.0;

    m_LeftDriveA->Set(val);
    m_LeftDriveB->Set(val);
    m_LeftDriveC->Set(val);
}

// Sets the left side motors
void CowRobot::SetRightMotors(float val)
{
    if (val > 1.0)
        val = 1.0;
    if (val < -1.0)
        val = -1.0;

    m_RightDriveA->Set(-val);
    m_RightDriveB->Set(-val);
    m_RightDriveC->Set(-val);
}

void CowRobot::StartTime()
{
    m_StartTime = frc::Timer::GetFPGATimestamp();
}

