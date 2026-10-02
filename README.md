# Collaborative Delta Robot 

### A 3-DOF Parallel Manipulator featuring Custom Inverse Kinematics, Closed-Loop Magnetic Encoder Feedback, and Pneumatic End-Effector Control

A three-arm parallel robot developed as part of my **Level-3, Term-1 coursework at Bangladesh University of Engineering and Technology (BUET)**. The robot was designed to position a common end-effector within a three-dimensional workspace and perform tasks such as picking and grabbing objects.

## Project Overview

The robot consists of hree symmetrically arranged arms, spaced 120° apart. Each arm is composed of two links connected through universal joints. Three stepper motors, driven by DRV8825 drivers, actuate the upper links, while the lower links are connected to a common moving platform.

Three magnetic encoders measure the angles of the upper links with respect to the horizontal plane, providing feedback on the robot's actual configuration. A 12 V vacuum pump, controlled through an L298N driver, is incorporated into the end-effector for picking objects.

## How It Works

The robot receives a desired 3D coordinate, with the center of the upper plate taken as the origin. The inverse-kinematic model calculates the angular configuration required for the three arms to bring the end-effector to the target position.

The magnetic encoders measure the actual angular positions of the upper links and provide feedback to the control algorithm. Based on the kinematic solution and encoder feedback, the three stepper motors are coordinated to move the arms and position the common end-effector at the desired location. Once positioned, the vacuum pump can be activated to pick up an object.

The process can then be repeated for a new target coordinate.

## My Contribution

My primary contribution focused on the **mathematical modeling and computational control** of the robot.

* Studied the **forward and inverse kinematics** of the parallel mechanism in depth.
* Formulated the mathematical relationships governing the robot's geometry and motion.
* Converted the kinematic formulation into **computational algorithms**.
* Developed and implemented a **custom positioning and trajectory-control algorithm**.
* Integrated **magnetic encoder feedback** into the control process.
* Implemented coordinated stepper-motor motion for physical end-effector positioning.

The project therefore connected **mathematical modeling → computational algorithms → sensor feedback → motor control → physical robotic motion**.

## Repository Contents

| Directory        | Description                                            |
| ---------------- | ------------------------------------------------------ |
| `Arduino Codes/` | Arduino code used for robot control and implementation |
| `Kinematics/`    | Forward and inverse kinematics documentation           |
| `Media/`         | Photographs and demonstration media                    |
| `Recognition/`   | Project award/certificate                              |

## Recognition

🏆 **Most Innovative Project Award**
Selected among **45 project groups** during the final project evaluation.

## Project Context

**Course:** Level-3, Term-1
**Institution:** Bangladesh University of Engineering and Technology (BUET)
**Project Type:** Robotics / Kinematic Modeling / Motion Control
