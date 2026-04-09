# Self-Balancing Robot Using PID Control

This project is a two-wheeled self-balancing robot built using an Arduino Uno, MPU6050 IMU, and L298N motor driver.

The robot maintains its balance using a **PID controller**, similar to the classic **inverted pendulum problem** in control systems.

---

## Components Used

- Arduino Uno
- MPU6050 IMU (Gyroscope + Accelerometer)
- L298N Motor Driver
- 2 DC geared motors
- Wheels
- Plywood chassis
- 2 × 3.7V Li-ion batteries

---

## System Concept (Inverted Pendulum)

This robot behaves like an inverted pendulum:

- The upright position is **unstable**
- Any small tilt will cause it to fall
- The system must **continuously correct itself**

Instead of falling, the robot:
**moves its wheels under its center of mass** to regain balance

---

## Control System (PID)

The controller computes:

\[
error = setpoint - angle
\]

Where:
- `setpoint = 0°` (upright position)
- `angle` = current tilt from MPU6050

The control output is:

$$
U = K_p \cdot error + K_i \cdot \sum error + K_d \cdot (error - prev\_ error)
$$


Where:
- **P (Proportional):** reacts to tilt angle
- **I (Integral):** corrects long-term drift
- **D (Derivative):** reacts to falling speed

This output `U` determines:
- **motor direction** (forward/backward)
- **motor speed** (PWM)



## How It Works

1. MPU6050 measures tilt angle (`getAngleX()`)
2. Arduino calculates error from upright position
3. PID controller computes correction (`output`)
4. Output is sent to motors via L298N:
   - Sign → direction
   - Magnitude → speed
5. Robot moves to stay balanced

## PID Values Used

```cpp
kp = 30;
ki = 0;
kd = 6;
```



### Pin Configuration

#### Motor Driver (L298N → Arduino)


| Function | Arduino Pin |
| :--- | :--- |
| ENA (Left PWM) | 10 |
| IN1 | 4 |
| IN2 | 5 |
| ENB (Right PWM) | 11 |
| IN3 | 6 |
| IN4 | 7 |

#### MPU6050 (I2C)


| MPU6050 | Arduino |
| :--- | :--- |
| VCC | 5V |
| GND | GND |
| SDA | A4 |
| SCL | A5 |


### Safety Condition

If the robot tilts too far:
```cpp
if (abs(angle) > 45.0)
```

- Motors stop immediately
- PID resets
- Prevents runaway behavior

## Challenges Faced

Some of the major issues during development included:

- Incorrect balance angle reference
- Derivative term behaving too aggressively
- Motors spinning but not correcting properly
- One-sided falling due to tuning and motor behavior
- Stop condition not triggering correctly at first

These were solved through debugging, calibration, and PID tuning.
