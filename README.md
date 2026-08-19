# AeroSim

A C++ flight simulation project centered around a PID (Proportional-Integral-Derivative) controller applied to aircraft altitude control. Built as a hands-on way to learn C++, control systems theory, and aerospace engineering concepts.

---

## What is a PID Controller?

A PID controller is a feedback control algorithm used in everything from aircraft autopilots to industrial robots. It continuously calculates the difference between a desired target (setpoint) and the current measured value (error), then applies a corrective output based on three terms:

```
output = (Kp × error) + (Ki × integral) + (Kd × derivative)
```

| Term | Name | What it does |
|------|------|--------------|
| `Kp × error` | Proportional | Reacts to the current error — bigger error, bigger push |
| `Ki × integral` | Integral | Reacts to accumulated past error — eliminates steady-state offset |
| `Kd × derivative` | Derivative | Reacts to the rate of change — dampens overshoot |

---

## Simulation

The simulation models an **F-35 fighter jet** climbing from sea level to a target altitude of **30,000 ft** using a PID controller running at `dt = 0.1s` clock cycles.

Each iteration the controller:
1. Computes the error between target and current altitude
2. Updates and clamps the integral term
3. Computes the derivative (rate of error change)
4. Outputs a corrective force applied to the aircraft's altitude

Telemetry data (cycle, altitude, error, PID output) is exported to a CSV file and visualized with Python/matplotlib.

---

## Features

### Integral Windup Protection
When a system is far from its target for a long time, the integral term can grow unbounded — causing massive overshoot when the system finally responds. This is called **integral windup**.

Fixed by clamping the integral between configurable limits:
```cpp
integral += error * dt;
integral = std::clamp(integral, minIntegral, maxIntegral);
```

### Derivative Kick Fix
On the first iteration, `previousError` is `0`, so the derivative term sees an artificial spike:
```
derivative = (error - 0) / dt  →  enormous value
```
Fixed with a `firstCall` flag that skips the derivative on the first cycle, letting the controller start smoothly.

---

## Project Structure

```
AeroSim/
├── include/
│   ├── Aircraft.h        # Base class: model, speed, altitude
│   ├── Fighter.h         # Derived class: adds missile count
│   └── PIDController.h   # PID controller with windup + kick protection
├── src/
│   ├── Aircraft.cpp
│   ├── Fighter.cpp
│   ├── PIDController.cpp
│   └── main.cpp          # Simulation loop + CSV export
├── aviation_graph.py     # Python script to plot telemetry data
└── CMakeLists.txt
```

---

## C++ Concepts Covered

- Classes, inheritance, and polymorphism (`Aircraft` → `Fighter`)
- Virtual functions and method overriding
- Smart pointers (`std::unique_ptr`)
- `std::clamp` from `<algorithm>`
- File I/O with `std::ofstream`
- Constructors and initializer lists

---

## How to Build

Requires CMake 4.1+ and a C++20 compiler.

```bash
mkdir cmake-build-debug && cd cmake-build-debug
cmake ..
make
./RadarTech
```

Telemetry is written to `cmake-build-debug/PID_F35_DATA.csv`.

---

## Visualizing Results

Install dependencies:
```bash
pip install matplotlib pandas
```

Run the plotting script:
```bash
python3 aviation_graph.py
```

This produces two charts — altitude climbing toward the 30,000 ft target, and tracking error converging toward zero.

---

## Planned Expansions

- 2D flight path simulation (X position + altitude)
- Multiple aircraft objects with independent controllers
- Real-time terminal visualization
- Pitch and heading control (6-DOF)
