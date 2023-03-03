# Rescue-Robot

A simple robot designed to rescue people from buildings

----
## About

A rescue robot that navigates a maze or "Building" by 2/3 different modes of control.

- Manual
- Semi-Automatic
- Automatic

The robot utilises various different sensors to detect it's surroundings and act accordingly depending on what these sensors report, to locate people in a building and report this back to the operator. The robot can be controlled remotely using XBee Communication modules back to the computer and the operator so that they know what is going on.

----
## Sensors
----

The robot utilises the following sensors to detect it's surroundings and makes judgements based on this (or just reports the findings back to the operator).

### GyroScope
----
The gyroScope is used to calculate the angle turned/turn the robot by a specific angle when navigating the maze, this allows the robot to roughly turn by a set degrees when the robot is instructed to turn left/right. Although these sensors are not perfectly tuned and do present a margin of error when trying to perform precise manouvers.

### Proximity Sensors
----
The proximity sensors allow the robot to detect any people or obstacles that may be around or in front of the robot, they scan after each manouver and ensure that if the roboot encounters anything as it is navigating it will stop the robot and alert the operator, or adjust it's course when it encounters an object.

### Line Sensors
----
The Line sensors are used to detect the walls of the maze and allow the robot to stick between these lines or allow the robot to detect what position the robot is in as it navigates the maze and what move it should make depending on the lines it detects.

----
## Use
----
This code must be uploaded to the Zumo robot using either Arduino.ide or an alternative IDE editor with an appropriate robot uploading plugin/extension (such as Platform.IO, recommended).

- To use the robot place it within the maze and turn it on using the switch.
- Ensure the XBee Tranceiver is connected to the USB port of the computer & Zumo.
- Using XCTU or other Serial Wireless communication to communicate and connect to the Zumo to transmit commands, or use the GUI (in the seperate Repo).
- Press the Zumo A button to enable the Modes and to start Manual Mode.
- Use the XCTU or GUI to Communicate with the Zumo once the "Calibration Complete" message is transmitted from the Zumo.
- WASD allows for movement (or appropriate buttons).
- G/H allows you to turn On/Off the Automatic mode as needed.

----
## Libraries & Sources
----

Pololu Documentation for Zumo Robot:
 - https://www.pololu.com/docs/0J63

Pololu Library Documentation and Github with Code Examples:
- https://pololu.github.io/zumo-32u4-arduino-library/
- https://github.com/pololu/zumo-32u4-arduino-library

Professor Craven Github Code (Videos also from Youtube on these Examples):
- https://github.com/pvcraven/zumo_32u4_examples



