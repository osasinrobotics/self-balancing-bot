# Self-Balancing Bot using MPU6050, L298N, and Arduino

This project is a two-wheeled self-balancing robot built using an Arduino, MPU6050 IMU sensor, and L298N motor driver.

The bot uses **PID control** to continuously measure its tilt angle and drive the motors in a way that helps it maintain balance similar to the **inverted pendulum problem** in control systems.

## Components Used

- Arduino Uno/Nano
- MPU6050 IMU
- L298N Motor Driver
- 2 DC geared motors
- Wheels
- Chassis made with plywood
- 2 3.7 V batteries

## How It Works

The MPU6050 provides the robot’s tilt angle.

The Arduino reads the angle, compares it to the desired upright position, and calculates an error.

A PID controller then determines how much motor correction is needed:

- **P (Proportional):** reacts to how far the robot is leaning
- **I (Integral):** reacts to accumulated leaning over time
- **D (Derivative):** reacts to how fast the robot is falling

The resulting control signal is sent to the motors through the L298N motor driver.

## PID Values Used

```cpp
kp = 30
ki = 0
kd = 6

## Challenges Faced

Some of the major issues during development included:

- Incorrect balance angle reference
- Derivative term behaving too aggressively
- Motors spinning but not correcting properly
- One-sided falling due to tuning and motor behavior
- Stop condition not triggering correctly at first

These were solved through debugging, calibration, and PID tuning.
