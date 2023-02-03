#include "Robot.h"

void Robot::RobotInit() {}
void Robot::RobotPeriodic() {}

void Robot::AutonomousInit() {}
void Robot::AutonomousPeriodic() {}

void Robot::TeleopInit() {}

void Robot::TeleopPeriodic() {
  frontRight.Set(ControlMode::Follower, Robot::motorControllerPort::backRightPort);
  frontLeft.Set(ControlMode::Follower, Robot::motorControllerPort::backLeftPort);
  backRight.Set(
    ControlMode::PercentOutput,
    ((driverController.GetLeftY() + driverController.GetRightX()) * driverController.GetRightTriggerAxis())
  );
  backLeft.Set(
    ControlMode::PercentOutput,
    -(driverController.GetLeftY() - driverController.GetRightX()) * driverController.GetRightTriggerAxis()
  );
  hWheel.Set(
    ControlMode::PercentOutput,
    driverController.GetLeftX() * driverController.GetRightTriggerAxis()
  );
}

void Robot::DisabledInit() {}
void Robot::DisabledPeriodic() {}

void Robot::TestInit() {}
void Robot::TestPeriodic() {}

void Robot::SimulationInit() {}
void Robot::SimulationPeriodic() {}

#ifndef RUNNING_FRC_TESTS
int main() {
  return StartRobot<Robot>();
}
#endif
