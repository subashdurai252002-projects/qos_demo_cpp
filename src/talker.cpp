#include <chrono>
#include <memory>
#include <string>

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"

using namespace std::chrono_literals;

class Talker : public rclcpp::Node
{
public:
  Talker()
  : Node("talker"), count_(0)
  {
    auto qos = rclcpp::QoS(rclcpp::KeepLast(10));
    qos.reliable();
    qos.deadline(rclcpp::Duration::from_seconds(1.0));
    qos.liveliness(RMW_QOS_POLICY_LIVELINESS_AUTOMATIC);
    qos.liveliness_lease_duration(rclcpp::Duration::from_seconds(1.0));

    publisher_ = this->create_publisher<std_msgs::msg::String>("chatter", qos);

    timer_ = this->create_wall_timer(
      500ms,
      std::bind(&Talker::timer_callback, this));
  }

private:
  void timer_callback()
  {
    auto message = std_msgs::msg::String();
    message.data = "Hello " + std::to_string(count_++);

    RCLCPP_INFO(this->get_logger(), "I sent: %s", message.data.c_str());
    publisher_->publish(message);
  }

  rclcpp::Publisher<std_msgs::msg::String>::SharedPtr publisher_;
  rclcpp::TimerBase::SharedPtr timer_;
  int count_;
};

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<Talker>());
  rclcpp::shutdown();
  return 0;
}
