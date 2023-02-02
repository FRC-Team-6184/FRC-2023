#include "Robot.h"

void Robot::RobotInit() {}
void Robot::RobotPeriodic() {}
void Robot::AutonomousInit() {}
void Robot::AutonomousPeriodic() {}

void Robot::TeleopInit() {
  shooter.Set(ctre::phoenix::motorcontrol::ControlMode::PercentOutput, 0);
}

void Robot::TeleopPeriodic() {
  frontRight.Set(ctre::phoenix::motorcontrol::ControlMode::Follower, Robot::motorControllerPort::backRight);
  frontLeft.Set(ctre::phoenix::motorcontrol::ControlMode::Follower, Robot::motorControllerPort::backLeft);
  backRight.Set(
    ctre::phoenix::motorcontrol::ControlMode::PercentOutput,
    -((driverController.GetLeftY() - driverController.GetRightX()) * driverController.GetRightTriggerAxis())
  );
  backLeft.Set(
    ctre::phoenix::motorcontrol::ControlMode::PercentOutput,
    (driverController.GetLeftY() + driverController.GetRightX()) * driverController.GetRightTriggerAxis()
  );
  if(driverController.GetAButton()){
    shooter.Set(ctre::phoenix::motorcontrol::ControlMode::PercentOutput, 1);
  }
  if(driverController.GetBButton()){
    shooter.Set(ctre::phoenix::motorcontrol::ControlMode::PercentOutput, 0);
  }
  if(driverController.GetRightBumper()){
    feeder.Set(ctre::phoenix::motorcontrol::ControlMode::PercentOutput, .2);
  }
  else{
    feeder.Set(ctre::phoenix::motorcontrol::ControlMode::PercentOutput, 0);
  }

  if(driverController.GetLeftBumper()){
    feeder.Set(ctre::phoenix::motorcontrol::ControlMode::PercentOutput, -.2);
  }
}

void Robot::DisabledInit() {
  shooter.Set(ctre::phoenix::motorcontrol::ControlMode::PercentOutput, 0);
}

void Robot::DisabledPeriodic() {}
void Robot::TestInit() {}

void Robot::TestPeriodic() {
  if(driverController.GetAButtonPressed()) {
    shooter.Set(ctre::phoenix::motorcontrol::ControlMode::PercentOutput, 1);
  }
  if(driverController.GetBButtonPressed()) {
    shooter.Set(ctre::phoenix::motorcontrol::ControlMode::PercentOutput, 0);
  }
}

void Robot::SimulationInit() {}
void Robot::SimulationPeriodic() {}

#ifndef RUNNING_FRC_TESTS
int main() {
  return frc::StartRobot<Robot>();
}
#endif
