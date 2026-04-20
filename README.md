# qos_demo_cpp

ROS 2 Humble C++ demo for publisher-subscriber QoS monitoring.

## Requirements
- Ubuntu 22.04
- ROS 2 Humble

## Build
cd ~/ros2_ws
source /opt/ros/humble/setup.bash
colcon build --packages-select qos_demo_cpp
source install/setup.bash

## Run

Terminal 1:
cd ~/ros2_ws
source /opt/ros/humble/setup.bash
source install/setup.bash
ros2 run qos_demo_cpp listener

Terminal 2:
cd ~/ros2_ws
source /opt/ros/humble/setup.bash
source install/setup.bash
ros2 run qos_demo_cpp talker
