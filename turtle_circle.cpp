#include "rclcpp/rclcpp.hpp"
#include "geometry_msgs/msg/twist.hpp"
#include<chrono>
#include<string>
#include<memory>
using namespace std;
using namespace std::chrono_literals;

class TurtleControlNode: public rclcpp::Node
{
    private:
    rclcpp::TimerBase::SharedPtr timer_;
    rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr Publisher_;
    
    
    public:
        explicit TurtleControlNode(const string& node_name):Node(node_name)
        {
            Publisher_ = this->create_publisher<geometry_msgs::msg::Twist>("turtle1/cmd_vel",10);
            timer_=this->create_wall_timer(1000ms,std::bind(&TurtleControlNode::timer_callback,this));
        }
    
    void timer_callback(){
        auto msg =geometry_msgs::msg::Twist();
        msg.linear.x=1.0;
        msg.angular.z=0.5;
        Publisher_->publish(msg);
    }
};

int main(int argc,char*argv[])
{
    rclcpp::init(argc,argv);
    auto node = make_shared<TurtleControlNode>("turtle_square");
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}