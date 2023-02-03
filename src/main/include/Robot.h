#pragma once

#include "ctre/Phoenix.h"
#include "ctre/phoenix/motorcontrol/can/VictorSPX.h"
#include "ctre/phoenix/motorcontrol/can/TalonSRX.h"
#include "frc/XboxController.h"
#include <frc/TimedRobot.h>

using ctre::phoenix::motorcontrol::can::TalonSRX;
using ctre::phoenix::motorcontrol::can::TalonFX;
using ctre::phoenix::motorcontrol::ControlMode;
using frc::StartRobot;
using frc::TimedRobot;
using frc::XboxController;

class Robot: public TimedRobot {

 public:
  const enum motorControllerPort {
    frontRight = 1,
    backRight = 3,
    frontLeft = 0,
    backLeft = 2,
    hWheel = 5,
  };
  const enum gameControllerPort {
    driver = 0
  };

  TalonSRX frontRight{motorControllerPort::frontRight};
  TalonSRX backRight{motorControllerPort::backRight};
  TalonSRX frontLeft{motorControllerPort::frontLeft};
  TalonSRX backLeft{motorControllerPort::backLeft};
  TalonSRX hWheel{motorControllerPort::hWheel};
  XboxController driverController{gameControllerPort::driver};

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
