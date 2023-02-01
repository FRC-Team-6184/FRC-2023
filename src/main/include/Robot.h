// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include "ctre/Phoenix.h"
#include "ctre/phoenix/motorcontrol/can/VictorSPX.h"
#include "ctre/phoenix/motorcontrol/can/TalonSRX.h"
#include "frc/XboxController.h"
#include <frc/TimedRobot.h>

class Robot : public frc::TimedRobot {

 public:
 ctre::phoenix::motorcontrol::can::TalonSRX  fr{14};
 ctre::phoenix::motorcontrol::can::TalonSRX  br{20};
 ctre::phoenix::motorcontrol::can::TalonSRX  fl{13};
 ctre::phoenix::motorcontrol::can::TalonSRX  bl{41};
 ctre::phoenix::motorcontrol::can::TalonFX  shooter{12};/// TODO: VERIFY CAN ADDRESSES
 ctre::phoenix::motorcontrol::can::TalonFX  feeder{15};    /// TODO: VERIFY CAN ADDRESSES
 frc::XboxController drivecon{0};
 frc::XboxController opcon{1};

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
