//==================================================
// Copyright (C) 2018 Team 1538 / The Holy Cows
//==================================================

#ifndef __COWLIB_COWMOTORCONTROLLER_H__
#define __COWLIB_COWMOTORCONTROLLER_H__

#include <frc/WPILib.h>
#include "ctre/Phoenix.h"

namespace CowLib
{
    class CowMotorController
    {
    public:
        enum CowNeutralMode {
            JUMPER,
            BRAKE,
            COAST,
        };

        enum CowControlMode {
            PERCENTVBUS,
            CURRENT,
            SPEED,
            POSITION,
            VOLTAGE,
            FOLLOWER,
            MOTIONPROFILE,
        };

        CowMotorController(int deviceNum);
        virtual ~CowMotorController();

        void SetNeutralMode(CowNeutralMode);
        enum CowNeutralMode GetNeutralMode();
        void SetControlMode(CowControlMode);
        enum CowControlMode GetControlMode();
        float GetPosition();
        void SetPIDGains(float pGain, float iGain, float dGain, float fGain);
        void Set(float);
        void SetInverted();
        TalonSRX *GetInternalMotor();
    private:
        TalonSRX *m_MotorController;
        int m_DeviceNum;
        enum CowNeutralMode m_CowNeutralMode;
        enum CowControlMode m_CowControlMode;

        ControlMode TranslateControlMode(enum CowControlMode);
    };
}

#endif /* __COWLIB_COWMOTORCONTROLLER_H__ */
