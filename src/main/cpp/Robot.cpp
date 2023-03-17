#include "Robot.h"

#define TURTLE_SPEED 0.25
#define REGULAR_SPEED 0.50
#define TURBO_SPEED 1.0

void Robot::RobotInit()
{
  // backLeft.ConfigSelectedFeedbackSensor(FeedbackDevice.QuadEncoder, 0, 10);
  // backRight.ConfigSelectedFeedbackSensor(FeedbackDevice.QuadEncoder, 0, 10);
  m_chooser.SetDefaultOption(kAutoNameDefault, kAutoNameDefault);
  m_chooser.AddOption(kAutoNameCustom, kAutoNameCustom);
  frc::SmartDashboard::PutData("Auto Modes", &m_chooser);
}
void Robot::RobotPeriodic() {}

void Robot::AutonomousInit()
{
  // backLeft.SetSelectedSensorPosition(0, 0, 10);
  // backRight.SetSelectedSensorPosition(0, 0, 10);
  m_autoSelected = m_chooser.GetSelected();
  fmt::print("Auto selected: {}\n", m_autoSelected);

  if (m_autoSelected == kAutoNameCustom)
  {
    frontRight.SetNeutralMode(Brake);
    frontLeft.SetNeutralMode(Brake);
    backRight.SetNeutralMode(Brake);
    backLeft.SetNeutralMode(Brake);

    frontRight.Set(TalonSRXControlMode::Follower, Robot::motorControllerPort::backRightPort);
    frontLeft.Set(TalonSRXControlMode::Follower, Robot::motorControllerPort::backLeftPort);
  }
  else
  {
    frontRight.SetNeutralMode(Brake);
    frontLeft.SetNeutralMode(Brake);
    backRight.SetNeutralMode(Brake);
    backLeft.SetNeutralMode(Brake);

    frontRight.Set(TalonSRXControlMode::Follower, Robot::motorControllerPort::backRightPort);
    frontLeft.Set(TalonSRXControlMode::Follower, Robot::motorControllerPort::backLeftPort);
  }
}
void Robot::AutonomousPeriodic()
{

  /*  while (distance < 0.6) {
      double rightPosition = backRight.GetSelectedSensorPosition() * kDriveTick2Feet;
      double leftPosition = backLeft.GetSelectedSensorPosition() * kDriveTick2Feet;
      double distance = (rightPosition + leftPosition) / 2;
      backRight.Set(TalonSRXControlMode::PercentOutput, -.15);
      backLeft.Set(TalonSRXControlMode::PercentOutput, .15);
    } */

  // backRight.Set(TalonSRXControlMode::PercentOutput, 0);
  // backLeft.Set(TalonSRXControlMode::PercentOutput, 0);

  if (m_autoSelected == kAutoNameCustom)
  {
    backRight.Set(TalonSRXControlMode::PercentOutput, -.15);
    backLeft.Set(TalonSRXControlMode::PercentOutput, .15);
    sleep(5);
    backRight.Set(TalonSRXControlMode::PercentOutput, -0);
    backLeft.Set(TalonSRXControlMode::PercentOutput, 0);
    hWheel.Set(VictorSPXControlMode::PercentOutput, .3);
    sleep(2);
    hWheel.Set(VictorSPXControlMode::PercentOutput, 0);
    sleep(8);
  }
  else
  {
    backRight.Set(TalonSRXControlMode::PercentOutput, -.15);
    backLeft.Set(TalonSRXControlMode::PercentOutput, .15);
    sleep(5);
    backRight.Set(TalonSRXControlMode::PercentOutput, -0);
    backLeft.Set(TalonSRXControlMode::PercentOutput, 0);
    sleep(10);
  }

  frontRight.SetNeutralMode(Brake);
  frontLeft.SetNeutralMode(Brake);
  backRight.SetNeutralMode(Brake);
  backLeft.SetNeutralMode(Brake);

  frontRight.Set(TalonSRXControlMode::Follower, Robot::motorControllerPort::backRightPort);
  frontLeft.Set(TalonSRXControlMode::Follower, Robot::motorControllerPort::backLeftPort);

  backRight.Set(TalonSRXControlMode::PercentOutput, -.15);
  backLeft.Set(TalonSRXControlMode::PercentOutput, .15);
  sleep(5);
  backRight.Set(TalonSRXControlMode::PercentOutput, -0);
  backLeft.Set(TalonSRXControlMode::PercentOutput, 0);
  hWheel.Set(VictorSPXControlMode::PercentOutput, .3);
  sleep(2);
  hWheel.Set(VictorSPXControlMode::PercentOutput, 0);
  sleep(8);
}

void Robot::TeleopInit() {}

void Robot::TeleopPeriodic()
{
  float speedMultiplier = REGULAR_SPEED;
  if (turretController.GetPOV() == 0 && layer < 2)
  {
    layer++;
    std::cout << layer;
  }
  else if (turretController.GetPOV() == 90)
  {
    type = 0;
    std::cout << "cube";
  }
  else if (turretController.GetPOV() == 180 && layer > 0)
  {
    layer--;
    std::cout << layer;
  }
  else if (turretController.GetPOV() == 270)
  {
    type = 1;
    std::cout << "cone";
  }

  // Driver Controls

  frontRight.SetNeutralMode(Brake);
  frontLeft.SetNeutralMode(Brake);
  backRight.SetNeutralMode(Brake);
  backLeft.SetNeutralMode(Brake);
  turret.SetNeutralMode(Brake);
  frontRight.Set(TalonSRXControlMode::Follower, Robot::motorControllerPort::backRightPort);
  frontLeft.Set(TalonSRXControlMode::Follower, Robot::motorControllerPort::backLeftPort);
  // backRight.Set(
  //   TalonSRXControlMode::PercentOutput,
  //   -(driverController.GetLeftY() + driverController.GetRightX()) * (driverController.GetRightTriggerAxis() / 2)
  // );
  // backLeft.Set(
  //   TalonSRXControlMode::PercentOutput,
  //   ((driverController.GetLeftY() - driverController.GetRightX()) * (driverController.GetRightTriggerAxis() / 2))
  // );
  if (driverController.GetRightBumper())
  {
    speedMultiplier = TURBO_SPEED;
  }
  else if (driverController.GetLeftBumper())
  {
    speedMultiplier = TURTLE_SPEED;
  }
  backRight.Set(TalonSRXControlMode::PercentOutput, -driverController.GetLeftY() * speedMultiplier);
  backLeft.Set(TalonSRXControlMode::PercentOutput, driverController.GetRightY() * speedMultiplier);
  hWheel.Set(
      VictorSPXControlMode::PercentOutput,
      (driverController.GetLeftTriggerAxis() - driverController.GetRightTriggerAxis()) * speedMultiplier);

  // Turret controls
  turret.Set(
      TalonSRXControlMode::PercentOutput,
      turretController.GetRightTriggerAxis() - turretController.GetLeftTriggerAxis());
  turretIntake.Set(
      TalonSRXControlMode::PercentOutput,
      turretController.GetYButtonPressed() - turretController.GetAButtonPressed());
  turretArm1.Set(TalonSRXControlMode::PercentOutput, turretController.GetLeftY());
  turretArm2.Set(TalonSRXControlMode::PercentOutput, turretController.GetRightY());
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
