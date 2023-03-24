// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <iostream>
#include <ctre/Phoenix.h>
#include <ctre/phoenix/motorcontrol/can/VictorSPX.h>
#include <ctre/phoenix/motorcontrol/can/TalonSRX.h>
#include <frc/smartdashboard/SmartDashboard.h>
#include <frc/smartdashboard/SendableChooser.h>
#include <frc/XboxController.h>
#include <frc/TimedRobot.h>
#include <frc/DigitalInput.h>

using ctre::phoenix::motorcontrol::ControlMode;
using ctre::phoenix::motorcontrol::can::TalonFX;
using ctre::phoenix::motorcontrol::can::TalonSRX;
using ctre::phoenix::motorcontrol::can::VictorSPX;
using frc::SendableChooser;
using frc::SmartDashboard;
using frc::StartRobot;
using frc::TimedRobot;
using frc::XboxController;
using frc::DigitalInput;

class Robot : public TimedRobot
{

public:
  enum motorControllerPort
  {
    frontRightPort = 2,
    backRightPort = 0,
    frontLeftPort = 3,
    backLeftPort = 1,
    intakePort = 5,
    horizontalArmPort = 6,
    verticalArmPort = 7,
    hWheelPort = 4
  };
  enum gameControllerPort
  {
    driver = 0,
    turretCon = 1
  };

  TalonSRX frontRight{motorControllerPort::frontRightPort};
  TalonSRX backRight{motorControllerPort::backRightPort};
  TalonSRX frontLeft{motorControllerPort::frontLeftPort};
  TalonSRX backLeft{motorControllerPort::backLeftPort};
  TalonSRX turretIntake{motorControllerPort::intakePort};
  TalonSRX horizontalArm{motorControllerPort::horizontalArmPort};
  TalonSRX verticalArm{motorControllerPort::verticalArmPort};
  VictorSPX hWheel{motorControllerPort::hWheelPort};
  XboxController driverController{gameControllerPort::driver};
  XboxController turretController{gameControllerPort::turretCon};

  SendableChooser<std::string> m_chooser;
  const std::string kAutoNameDefault = "Default";
  const std::string kAutoNameCustom = "My Auto";
  std::string m_autoSelected;

  //Limit Switches
  frc::DigitalInput horizontalLimit{0};

  void RobotInit() override;
  void RobotPeriodic() override;

  void AutonomousInit() override;
  void AutonomousPeriodic() override;

  void TeleopInit() override;
  void TeleopPeriodic() override;

  void DisabledInit() override;
  void DisabledPeriodic() override;

  void TestInit() override;
  void TestPeriodic() override;

  void SimulationInit() override;
  void SimulationPeriodic() override;
};