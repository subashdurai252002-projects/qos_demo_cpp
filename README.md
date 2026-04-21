# qos_demo_cpp

ROS 2 Humble C++ demo for publisher-subscriber communication with QoS (Quality of Service) monitoring.

---

## Requirements

- Ubuntu 22.04  
- ROS 2 Humble  

---

## QoS Concepts Covered

- Reliability (Reliable vs Best Effort)  
- History (Keep Last)  
- Depth (Queue size)  
- Liveliness monitoring  
- Message delivery behavior under different QoS settings  

---

## Build

```bash
cd ~/ros2_ws
source /opt/ros/humble/setup.bash
colcon build --packages-select qos_demo_cpp
source install/setup.bash
```

---

## Run

### Terminal 1 (Listener / Subscriber)

```bash
cd ~/ros2_ws
source /opt/ros/humble/setup.bash
source install/setup.bash
ros2 run qos_demo_cpp listener
```

### Terminal 2 (Talker / Publisher)

```bash
cd ~/ros2_ws
source /opt/ros/humble/setup.bash
source install/setup.bash
ros2 run qos_demo_cpp talker
```

---

## Features

- Demonstrates ROS 2 publisher-subscriber communication  
- Implements QoS profiles for message exchange  
- Shows behavior under different reliability settings  
- Helps understand DDS-based communication in ROS 2  

---

## Example Output

```text
[listener]: I heard: Hello ROS 2
```

---

## Project Structure

```
qos_demo_cpp/
├── src/
│   ├── talker.cpp
│   └── listener.cpp
├── CMakeLists.txt
└── package.xml
```

---

## Notes

- This project demonstrates how QoS policies affect communication between nodes.
- Useful for understanding real-time and reliable communication in ROS 2 systems.
