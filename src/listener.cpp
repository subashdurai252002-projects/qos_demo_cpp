#include <memory>
#include <string>

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"
#include "rclcpp/subscription_options.hpp"
#include "rclcpp/qos.hpp"
#include "rclcpp/qos_event.hpp"

class Listener : public rclcpp::Node
{
public:
  Listener()
  : Node("listener")
  {
    auto qos = rclcpp::QoS(rclcpp::KeepLast(10));
    qos.reliable();
    qos.deadline(rclcpp::Duration::from_seconds(1.0));
    qos.liveliness(RMW_QOS_POLICY_LIVELINESS_AUTOMATIC);
    qos.liveliness_lease_duration(rclcpp::Duration::from_seconds(1.0));

    rclcpp::SubscriptionOptions options;

    options.event_callbacks.deadline_callback =
      [this](rclcpp::QOSDeadlineRequestedInfo & event) {
        RCLCPP_WARN(
          this->get_logger(),
          "PANIC: deadline missed | total_count=%d total_count_change=%d",
          event.total_count,
          event.total_count_change);
      };

    options.event_callbacks.liveliness_callback =
      [this](rclcpp::QOSLivelinessChangedInfo & event) {
        RCLCPP_WARN(
          this->get_logger(),
          "liveliness changed | alive_count=%d not_alive_count=%d alive_count_change=%d not_alive_count_change=%d",
          event.alive_count,
          event.not_alive_count,
          event.alive_count_change,
          event.not_alive_count_change);
      };

    subscription_ = this->create_subscription<std_msgs::msg::String>(
      "chatter",
      qos,
      std::bind(&Listener::topic_callback, this, std::placeholders::_1),
      options);
  }

private:
  void topic_callback(const std_msgs::msg::String::SharedPtr msg) const
  {
    RCLCPP_INFO(this->get_logger(), "I heard: %s", msg->data.c_str());
  }

  rclcpp::Subscription<std_msgs::msg::String>::SharedPtr subscription_;
};

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<Listener>());
  rclcpp::shutdown();
  return 0;
}
