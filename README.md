# Udacity Robotics Nanodegree Project #3: Where Am I?

![Screenshot](img.png)

## Introduction
This is a project for Udacity's Robotics NanoDegree. It's a robot that uses a Hokuyo laser scanner and Monte Carlo Localization to localize itself inside a simulated environment.

## Getting Started

With the dependencies installed, download/clone the repository, navigate up to the root level directory, and execute:
```
$ catkin_make
$ source devel/setup.bash
$ roslaunch my_robot world.launch
```

To operate the robot via the keyboard, open a second terminal, navigate to the root level directory, and execute:
```
$ source devel/setup.bash
$ rosrun teleop_twist_keyboard teleop_twist_keyboard.py
```

You can then command the robot to move using the keys indicated by the teleop node.
