#include <ros/ros.h>
#include "move_server.h"

/**
 * The main function. Create an object of the class and load the yaml file. 
 * Then waits for the client's goal. 
 */
int main(int argc, char** argv)
{
  ros::init(argc, argv, "move_server_node");
  ros::NodeHandle nh;

  MoveAction move(&nh, "move_server");

  // ready to receive goal from client 
  ROS_INFO("Started");
  ros::spin();

  return 0;
}
