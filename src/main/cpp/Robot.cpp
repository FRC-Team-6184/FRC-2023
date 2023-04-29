#include "Robot.h"

#define TURTLE_SPEED 0.15
#define REGULAR_SPEED 0.35
#define TURBO_SPEED 1.0

#include <cscore_oo.h>
#include <cameraserver/CameraServer.h>

void Robot::RobotInit()
{
  frc::CameraServer::StartAutomaticCapture();
}
void Robot::RobotPeriodic() {}

void Robot::AutonomousInit()
{

  autonomousStart = time(0);

  frontRight.Set(TalonSRXControlMode::Follower, Robot::motorControllerPort::backRightPort);
  frontLeft.Set(TalonSRXControlMode::Follower, Robot::motorControllerPort::backLeftPort);

  // backLeft.Reset();
}

void Robot::AutonomousPeriodic()
{
  if (time(0) - autonomousStart < 2)
  {
    // Extend the arm at 40% power for two seconds.
    verticalArm.Set(TalonSRXControlMode::PercentOutput, .4);
  }
  else if (time(0) - autonomousStart < 4)
  {
    // Stop the arm motor and release the intake.
    verticalArm.Set(TalonSRXControlMode::PercentOutput, 0);
    turretIntake.Set(TalonSRXControlMode::PercentOutput, -.5);
  }
  else if (time(0) - autonomousStart < 6.5)
  {
    // Stop the intake and move backwards.
    turretIntake.Set(TalonSRXControlMode::PercentOutput, 0);
    backRight.Set(TalonSRXControlMode::PercentOutput, .3);
    backLeft.Set(TalonSRXControlMode::PercentOutput, -.3);
  }
  else
  {
    // Stop all motors.
    backRight.Set(TalonSRXControlMode::PercentOutput, 0);
    backLeft.Set(TalonSRXControlMode::PercentOutput, 0);
    turretIntake.Set(TalonSRXControlMode::PercentOutput, 0);
    verticalArm.Set(TalonSRXControlMode::PercentOutput, 0);
  }
}

void Robot::TeleopInit() {}

void Robot::TeleopPeriodic()
{
  float speedMultiplier = REGULAR_SPEED;
  float turnDifference;
  float leftWheelModifier = 0;
  float rightWheelModifier = 0;
  float turretMultiplier = 0.7;

  // Driver Controls

  frontRight.SetNeutralMode(Brake);
  frontLeft.SetNeutralMode(Brake);
  backRight.SetNeutralMode(Brake);
  backLeft.SetNeutralMode(Brake);
  horizontalArm.SetNeutralMode(Brake);
  verticalArm.SetNeutralMode(Brake);
  frontRight.Set(TalonSRXControlMode::Follower, Robot::motorControllerPort::backRightPort);
  frontLeft.Set(TalonSRXControlMode::Follower, Robot::motorControllerPort::backLeftPort);

  if (driverController.GetRightBumper())
  {
    speedMultiplier = TURBO_SPEED;
  }
  else if (driverController.GetLeftBumper())
  {
    speedMultiplier = TURTLE_SPEED;
  }
  else
  {
    speedMultiplier = REGULAR_SPEED;
  }

  backLeft.Set(TalonSRXControlMode::PercentOutput, -(driverController.GetLeftY()) * speedMultiplier);
  backRight.Set(TalonSRXControlMode::PercentOutput, (driverController.GetRightY()) * speedMultiplier);

  if (turretController.GetLeftBumper() || turretController.GetRightBumper())
  {
    turretMultiplier = 0.9;
  }
  turretIntake.Set(TalonSRXControlMode::PercentOutput, (turretController.GetLeftTriggerAxis() - turretController.GetRightTriggerAxis()) * turretMultiplier);

  horizontalArm.Set(TalonSRXControlMode::PercentOutput, turretController.GetLeftY() * 0.4);

  verticalArm.Set(TalonSRXControlMode::PercentOutput, -(turretController.GetRightY() * 0.25)); // Lower speed going downwards

  if (turretController.GetPOV() == 0)
  {
  }
  else if (turretController.GetPOV() == 90)
  {
    // horizontalEncoder
  }
  else if (turretController.GetPOV() == 180)
  {
  }
  else if (turretController.GetPOV() == 270)
  {
  }
  else
  {
  }
}

void Robot::DisabledInit() {}
void Robot::DisabledPeriodic() {}

void Robot::TestInit() {}
void Robot::TestPeriodic() {}

void Robot::SimulationInit() {}
void Robot::SimulationPeriodic() {}

#ifndef RUNNING_FRC_TESTS
int main()
{
  return StartRobot<Robot>();
}
#endif
