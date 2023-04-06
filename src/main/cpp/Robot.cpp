#include "Robot.h"

#define TURTLE_SPEED 0.15
#define REGULAR_SPEED 0.30
#define TURBO_SPEED 1.0

#include <cscore_oo.h>
#include <cameraserver/CameraServer.h>

void Robot::RobotInit()
{
  frc::CameraServer::StartAutomaticCapture();
  // m_chooser.SetDefaultOption(kAutoNameDefault, kAutoNameDefault);
  // m_chooser.AddOption(kAutoNameCustom, kAutoNameCustom);
  // SmartDashboard::PutData("Auto Modes", &m_chooser);
}
void Robot::RobotPeriodic() {}

void Robot::AutonomousInit()
{
  // m_autoSelected = m_chooser.GetSelected();
  // fmt::print("Auto selected: {}\n", m_autoSelected);
  autonomousStart = time(0);

  frontRight.SetNeutralMode(Brake);
  frontLeft.SetNeutralMode(Brake);
  backRight.SetNeutralMode(Brake);
  backLeft.SetNeutralMode(Brake);

  frontRight.Set(TalonSRXControlMode::Follower, Robot::motorControllerPort::backRightPort);
  frontLeft.Set(TalonSRXControlMode::Follower, Robot::motorControllerPort::backLeftPort);
}

void Robot::AutonomousPeriodic()
{
  if (time(0) - autonomousStart < 5)
  {
    backRight.Set(TalonSRXControlMode::PercentOutput, -.15);
    backLeft.Set(TalonSRXControlMode::PercentOutput, .15);
  }
  else
  {
    backRight.Set(TalonSRXControlMode::PercentOutput, 0);
    backLeft.Set(TalonSRXControlMode::PercentOutput, 0);
  }
}

void Robot::TeleopInit() {}

void Robot::TeleopPeriodic()
{
  float speedMultiplier = REGULAR_SPEED;
  float turnDifference;
  float leftWheelModifier = 0;
  float rightWheelModifier = 0;
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

  // if (driverController.GetRightY() - driverController.GetLeftY() > ) {}
  /* turnDifference = driverController.GetLeftY() - driverController.GetRightY();
  if (turnDifference > 0 && driverController.GetLeftY() - turnDifference * 0.25 > 0)
  {
    leftWheelModifier = turnDifference * 0.25;
  }
  else if (driverController.GetRightY() - abs(turnDifference) * 0.25 > 0)
  {
    rightWheelModifier = abs(turnDifference) * 0.25;
  } */

  /*if (driverController.GetRightX() > 0 && driverController.GetLeftY() != 0) {
    backLeft.Set(TalonSRXControlMode::PercentOutput, -(driverController.GetLeftY() - driverController.GetRightX()) * speedMultiplier);
    backRight.Set(TalonSRXControlMode::PercentOutput, driverController.GetLeftY() * speedMultiplier);
  } else if (driverController.GetRightX() < 0 && driverController.GetLeftY() != 0) {
    backRight.Set(TalonSRXControlMode::PercentOutput, (driverController.GetLeftY() + driverController.GetRightX()) * speedMultiplier);
    backLeft.Set(TalonSRXControlMode::PercentOutput, -driverController.GetLeftY() * speedMultiplier);
  } else if (driverController.GetLeftY() == 0 && driverController.GetRightX() != 0) {
    backRight.Set(TalonSRXControlMode::PercentOutput, driverController.GetRightX());
    backLeft.Set(TalonSRXControlMode::PercentOutput, -driverController.GetRightX());
  }*/

  backLeft.Set(TalonSRXControlMode::PercentOutput, -(driverController.GetLeftY() - driverController.GetRightX() * 0.6) * speedMultiplier);
  backRight.Set(TalonSRXControlMode::PercentOutput, (driverController.GetLeftY() + driverController.GetRightX() * 0.6) * speedMultiplier);

  // if (driverController.GetRightX() < 0)
  /* } else if (driverController.GetLeftY() == 0 && driverController.GetRightX() != 0) {

   } */

  // backLeft.Set(TalonSRXControlMode::PercentOutput, (-driverController.GetLeftY() + leftWheelModifier) * speedMultiplier);
  // backRight.Set(TalonSRXControlMode::PercentOutput, (driverController.GetRightY() - rightWheelModifier) * speedMultiplier);

  // Turret controls
  turretIntake.Set(TalonSRXControlMode::PercentOutput, turretController.GetLeftTriggerAxis() - turretController.GetRightTriggerAxis());

  if (!horizontalLimit.Get())
  {
    horizontalArm.Set(TalonSRXControlMode::PercentOutput, 0);
  }
  else
  {
    horizontalArm.Set(TalonSRXControlMode::PercentOutput, turretController.GetLeftY() *0.4);
  }
  verticalArm.Set(TalonSRXControlMode::PercentOutput, turretController.GetRightY() * 0.25);
}

// Arm Controls


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
