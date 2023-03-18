#pragma once

#include <iostream>
#include <ctre/Phoenix.h>
#include <ctre/phoenix/motorcontrol/can/VictorSPX.h>
#include <ctre/phoenix/motorcontrol/can/TalonSRX.h>
#include <frc/smartdashboard/SmartDashboard.h>
#include <frc/smartdashboard/SendableChooser.h>
#include <frc/XboxController.h>
#include <frc/TimedRobot.h>

using ctre::phoenix::motorcontrol::ControlMode;
using ctre::phoenix::motorcontrol::can::TalonFX;
using ctre::phoenix::motorcontrol::can::TalonSRX;
using ctre::phoenix::motorcontrol::can::VictorSPX;
using frc::SendableChooser;
using frc::SmartDashboard;
using frc::StartRobot;
using frc::TimedRobot;
using frc::XboxController;
using std::string;

class Robot : public TimedRobot
{

public:
  enum motorControllerPort
  {
    frontRightPort = 2,
    backRightPort = 0,
    frontLeftPort = 3,
    backLeftPort = 1,
    turretPort = 6,
    intakePort = 16,
    turretArm1Port = 18,
    turretArm2Port = 7,
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
  TalonSRX turret{motorControllerPort::turretPort};
  TalonSRX turretIntake{motorControllerPort::intakePort};
  TalonSRX turretArm1{motorControllerPort::turretArm1Port};
  TalonSRX turretArm2{motorControllerPort::turretArm2Port};
  VictorSPX hWheel{motorControllerPort::hWheelPort};
  XboxController driverController{gameControllerPort::driver};
  XboxController turretController{gameControllerPort::turretCon};

  SendableChooser<string> m_chooser;
  const string kAutoNameDefault = "Default";
  const string kAutoNameCustom = "My Auto";
  string m_autoSelected;

  float layer = 0;
  float type = 0;
  // float kDriveTick2Feet = 0.000310842175066;
  // double rightPosition = backRight.GetSelectedSensorPosition() * kDriveTick2Feet;
  // double leftPosition = backLeft.GetSelectedSensorPosition() * kDriveTick2Feet;
  // double distance = (rightPosition + leftPosition) / 2;

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
