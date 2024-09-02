/***  Node Instance to publish temperature data to the topic "Temperature"  ***/

#include <rclcpp/rclcpp.hpp>
#include <std_msgs/msg/string.hpp>
#include "temp_sensor.h"
#include <chrono>
#include <utility>

class PublisherNode : public rclcpp::Node
{
public:
    PublisherNode() : Node("Temperature_Sensor"), temp_sensor_(0x66) /* 0x66 is the I2C address of the temperature sensor */
    {
        publisher_ = this->create_publisher<std_msgs::msg::String>("Temperature", 10);
        timer_ = this->create_wall_timer(std::chrono::seconds(1), std::bind(&PublisherNode::publishMessage, this));
    }

private:
    void publishMessage()
    {
        temp_sensor_.read();
        std::pair<float, std::chrono::system_clock::time_point> temp_data = temp_sensor_.getTemp();
        auto message = std_msgs::msg::String();
        message.data = "Temperature: " + std::to_string(temp_data.first) + " °C";
        publisher_->publish(message);
    }

    rclcpp::Publisher<std_msgs::msg::String>::SharedPtr publisher_;
    rclcpp::TimerBase::SharedPtr timer_;
    Temp_Sensor temp_sensor_;
};

int main(int argc, char** argv)
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<PublisherNode>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}