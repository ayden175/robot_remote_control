#pragma once

#include <string>
#include <robot_remote_control/Types/RobotRemoteControl.pb.h>
#include <geometry_msgs/TwistStamped.h>
#include "../Header.hpp"

namespace robot_remote_control {
namespace RosConversion {

    inline static void convert(const robot_remote_control::Twist &from, geometry_msgs::TwistStamped *to) {
        convert(from.header(), &to->header);
        
        to->twist.angular.x = from.angular().x();
        to->twist.angular.y = from.angular().y();
        to->twist.angular.z = from.angular().z();

        to->twist.linear.x = from.linear().x();
        to->twist.linear.y = from.linear().y();
        to->twist.linear.z = from.linear().z();
    }

    inline static void convert(const robot_remote_control::Twist &from, geometry_msgs::Twist *to ) {
        to->angular.x = from.angular().x();
        to->angular.y = from.angular().y();
        to->angular.z = from.angular().z();

        to->linear.x = from.linear().x();
        to->linear.y = from.linear().y();
        to->linear.z = from.linear().z();
    }

}  // namespace RosConversion
}  // namespace robot_remote_control
