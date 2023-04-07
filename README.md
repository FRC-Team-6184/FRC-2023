# FRC 2023 Robot

This project hosts the code for the 2023 FRC Competition.

## Defining Controller Ports

Each motor on the robot is assigned a port number. The device that the motor controls is mapped to the port in the `Robot.h` file in the `motorControllerPort` enum. After this is defined, the motor controller needs to be instantiated with the correct class, with the port number being passed in to the construct.

```cpp
enum motorControllerPort
{
  …
  turretPort = 6
  …
}

…

TalonSRX turret{motorControllerPort::turretPort};
```

If the motor controller is ever assigned a different port, simply update the reference in the `motorControllerPort` enum.

## Defining Gaming Controllers

Gaming controller ports are defined by the operating system. Port number starts at 0, and is incremented for each additional controller plugged in. Define each controller we will support in the `Robot.h` file in the `gameControllerPort` enum. After this is defined, instantiate the controller using the proper class for the type of controller used.

```cpp
  enum gameControllerPort
  {
    driver = 0
  }

…

XboxController driverController{gameControllerPort::driver};
```

The available classes are `Joystick`, `PS4Controller`, and `XBoxController`.

## Driving Speeds

Simply controlling the speed of the robot by how far the stick is extended makes the robot controls very touchy. For this reason we support three speeds; turtle, regular, and turbo. With turtle mode the robot crawls very slowly. With turbo mode the robots speed is at 100% of the speed indiciated by how far the stick is pressed. With regular mode the robot travels at a brisk pace. The slowing factor of each mode is defined in `Robot.capp` constants TURTLE_SPEED, REGULAR_SPEED, TURBO_SPEED.

## Robot Modes

The two most important modes the robot can be in is autonomous, and teleop. These correspond to the AutonomousPeriodic and TeleopPeriodic methods in `Robot.cpp`. The code in these methods will be executed multiple times a second when the robot is in the corresponding mode. It is in these methods that we define the robots behavior. There are also corresponding `AutonomousInit` and `TeleopInit` methods. When the robot first enters the corresponding mode, these methods will be called exactly once. This allows us to initialize the state of the robot when these modes are first started.
