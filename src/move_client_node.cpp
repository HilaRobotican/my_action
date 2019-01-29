#include <ros/ros.h>
#include "move_callback_client.h"

/**
 * The main function. Create an object of the class and send the goal - location name
 * according to the param "location_param". 
 */
int main(int argc, char **argv)
{
  ros::init(argc, argv, "move_client_node");
  
  // Create node handler for getting the name of the desired location
  std::string location_name_;
  ros::NodeHandle nh("~");
  nh.getParam("location_param", location_name_);
  ROS_INFO_STREAM("got param: " << location_name_);

  // Create move action client object that will send the goal to the action server.
  MoveActionClient client;
  client.sendGoal(location_name_);

  ros::spin();
  return 0;
}