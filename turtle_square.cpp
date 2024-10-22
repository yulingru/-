#include "rclcpp/rclcpp.hpp"
#include "geometry_msgs/msg/twist.hpp"
#include <chrono>
using namespace std::chrono_literals;

class TurtleCircleNode : public rclcpp::Node {
private:
    rclcpp::TimerBase::SharedPtr timer_;
    rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr publisher_;
    int i = 0;

public:
    explicit TurtleCircleNode(const std::string& node_name) : Node(node_name) {
        publisher_ = this->create_publisher<geometry_msgs::msg::Twist>("/turtle1/cmd_vel", 10);
        timer_ = this->create_wall_timer(1000ms, std::bind(&TurtleCircleNode::timer_callback, this));
    }

private:
    void timer_callback() {
        i++;
        auto msg = geometry_msgs::msg::Twist();

        
        switch (i % 4) {
            case 1:
                msg.linear.x = 1.0;
                msg.linear.y = 0.0;
                break;
            case 2:
                msg.linear.x = 0.0;
                msg.linear.y = 1.0;
                break;
            case 3:
                msg.linear.x = -1.0;
                msg.linear.y = 0.0;
                break;
            case 0:
                msg.linear.x = 0.0;
                msg.linear.y = -1.0;
                break;
        }

        publisher_->publish(msg);
    }
};

int main(int argc, char* argv[]) {
    rclcpp::init(argc, argv);
    auto node = std::make_shared<TurtleCircleNode>("turtle_square");
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}
