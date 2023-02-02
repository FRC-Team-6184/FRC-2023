#pragma once

#include "ctre/Phoenix.h"
#include "ctre/phoenix/motorcontrol/can/VictorSPX.h"
#include "ctre/phoenix/motorcontrol/can/TalonSRX.h"
#include "frc/XboxController.h"
#include <frc/TimedRobot.h>

class Robot: public frc::TimedRobot {

 public:
  const enum motorControllerPort {
    frontRight = 14,
    backRight = 20,
    frontLeft = 13,
    backLeft = 41,
    shooter = 12, // TODO: VERIFY CAN ADDRESSES
    feeder = 15 // TODO: VERIFY CAN ADDRESSES
  };
  const enum gameControllerPort {
    driver = 0
  };

  ctre::phoenix::motorcontrol::can::TalonSRX frontRight{motorControllerPort::frontRight};
  ctre::phoenix::motorcontrol::can::TalonSRX backRight{motorControllerPort::backRight};
  ctre::phoenix::motorcontrol::can::TalonSRX frontLeft{motorControllerPort::frontLeft};
  ctre::phoenix::motorcontrol::can::TalonSRX backLeft{motorControllerPort::backLeft};
  ctre::phoenix::motorcontrol::can::TalonFX shooter{motorControllerPort::shooter};
  ctre::phoenix::motorcontrol::can::TalonFX feeder{motorControllerPort::feeder};
  frc::XboxController driverController{gameControllerPort::driver};

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
