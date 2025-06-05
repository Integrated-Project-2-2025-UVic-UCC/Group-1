# Group-1: Spider robot
Group 1: Maria Schreiber, Sergi Piguillem, Roger Camps & Òscar Guerrero

![image](https://github.com/user-attachments/assets/d90659f4-8e80-40b2-b10a-3623ff47a08b)

This project focuses on the implementation of the modern ESP32 variant, the ESP32-CAM, to develop a low-cost, multifunctional robotic system named SiderRobot. The system is designed to control eight servo motors,  those required for legged or articulated robotic motion. In addition to motor control, the ESP32-CAM is used to provide a live video stream, allowing real-time visual feedback through its built-in camera module.

To facilitate remote interaction, the ESP32-CAM hosts a web server that provides a user interface for sending commands to the servos. These commands include real-time manual control inputs. The integration of video streaming and motor control within a single microcontroller makes this system a compact and efficient solution for tasks such as remote surveillance, inspection, or mobile robotics in constrained environments.

The following components are necessary for the construction of the SiderRobot project:

- 4 3D-printed legs
- 1 3D-printed base
- 8 servo motors (SG90 or preferably MG90S for better performance due to their metal gears)
- 2 XL4015 voltage regulators (used to separate and stabilize the power supply for the ESP32-CAM and the servo driver board)
- 1 solderable breadboard
- 1 ESP32-CAM module (Model: AI Thinker ESP32-CAM, used in our case)
