// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "Robot.h"


void Robot::RobotInit() {}
void Robot::RobotPeriodic() {}

void Robot::AutonomousInit() {}
void Robot::AutonomousPeriodic() {}

void Robot::TeleopInit() {
  shooter.Set(ctre::phoenix::motorcontrol::ControlMode::PercentOutput,0);
}
void Robot::TeleopPeriodic() {
fr.Set(ctre::phoenix::motorcontrol::ControlMode::Follower,20);
fl.Set(ctre::phoenix::motorcontrol::ControlMode::Follower,41);
br.Set(ctre::phoenix::motorcontrol::ControlMode::PercentOutput,-((( drivecon.GetLeftY()-drivecon.GetRightX()))*drivecon.GetRightTriggerAxis()) );
bl.Set(ctre::phoenix::motorcontrol::ControlMode::PercentOutput,(( drivecon.GetLeftY()+drivecon.GetRightX()))*drivecon.GetRightTriggerAxis() );
if(drivecon.GetAButton()){
  shooter.Set(ctre::phoenix::motorcontrol::ControlMode::PercentOutput,1);
}
if(drivecon.GetBButton()){
  shooter.Set(ctre::phoenix::motorcontrol::ControlMode::PercentOutput,0);
}
if(drivecon.GetRightBumper()){
  feeder.Set(ctre::phoenix::motorcontrol::ControlMode::PercentOutput,.2);
}
else{
  feeder.Set(ctre::phoenix::motorcontrol::ControlMode::PercentOutput,0);
}

if(drivecon.GetLeftBumper()){
  feeder.Set(ctre::phoenix::motorcontrol::ControlMode::PercentOutput,-.2);
}

}

void Robot::DisabledInit() {
  shooter.Set(ctre::phoenix::motorcontrol::ControlMode::PercentOutput,0);
}
void Robot::DisabledPeriodic() {}

void Robot::TestInit() {}
void Robot::TestPeriodic() {

if(drivecon.GetAButtonPressed()){
  shooter.Set(ctre::phoenix::motorcontrol::ControlMode::PercentOutput,1);
}
if(drivecon.GetBButtonPressed()){
  shooter.Set(ctre::phoenix::motorcontrol::ControlMode::PercentOutput,0);
}

}

void Robot::SimulationInit() {}
void Robot::SimulationPeriodic() {}

#ifndef RUNNING_FRC_TESTS
int main() {
  return frc::StartRobot<Robot>();
}
#endif
