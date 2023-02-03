#include "Robot.h"

void Robot::RobotInit() {}
void Robot::RobotPeriodic() {}

void Robot::AutonomousInit() {}
void Robot::AutonomousPeriodic() {}

void Robot::TeleopInit() {
  shooter.Set(ControlMode::PercentOutput, 0);
}

void Robot::TeleopPeriodic() {
  frontRight.Set(ControlMode::Follower, Robot::motorControllerPort::backRight);
  frontLeft.Set(ControlMode::Follower, Robot::motorControllerPort::backLeft);
  backRight.Set(
    ControlMode::PercentOutput,
    -((driverController.GetLeftY() - driverController.GetRightX()) * driverController.GetRightTriggerAxis())
  );
  backLeft.Set(
    ControlMode::PercentOutput,
    (driverController.GetLeftY() + driverController.GetRightX()) * driverController.GetRightTriggerAxis()
  );
  if(driverController.GetAButton()) {
    shooter.Set(ControlMode::PercentOutput, 1);
  }
  if(driverController.GetBButton()) {
    shooter.Set(ControlMode::PercentOutput, 0);
  }
  if(driverController.GetRightBumper()) {
    feeder.Set(ControlMode::PercentOutput, .2);
  }
  else {
    feeder.Set(ControlMode::PercentOutput, 0);
  }

  if(driverController.GetLeftBumper()) {
    feeder.Set(ControlMode::PercentOutput, -.2);
  }
}

void Robot::DisabledInit() {
  shooter.Set(ControlMode::PercentOutput, 0);
}

void Robot::DisabledPeriodic() {}

void Robot::TestInit() {}

void Robot::TestPeriodic() {
  if(driverController.GetAButtonPressed()) {
    shooter.Set(ControlMode::PercentOutput, 1);
  }
  if(driverController.GetBButtonPressed()) {
    shooter.Set(ControlMode::PercentOutput, 0);
  }
}

void Robot::SimulationInit() {}
void Robot::SimulationPeriodic() {}

#ifndef RUNNING_FRC_TESTS
int main() {
  return StartRobot<Robot>();
}
#endif
