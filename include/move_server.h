#ifndef MY_ACTION_MOVE_SERVER_H
#define MY_ACTION_MOVE_SERVER_H

#include <ros/ros.h>
#include <string> 
#include <actionlib/server/simple_action_server.h>
#include <XmlRpcValue.h>
#include "my_action/MoveAction.h" // This is a header generated automatically from the FibonacciAction.msg file.
#include "point.h"

// TODO to change my_action to mobilican_msgs

// Error Messages:
#define ERROR_MSG_YAML "[MoveAction]: load locations at index %s param data type is invalid or missing. \
make sure that this param exist in locations.yaml and that your launch includes this param file. shutting down..."

#define ERROR_MSG_LOCATION_DOESNT_EXIST "[MoveAction]: couldn't locate model specification for location name %s. \
Make sure locations.yaml contains all the necessary locations. shutting down..."

#define ERROR_MSG_MISSING_PARAM "[MoveAction]: %s param is missing on param server. \
Make sure that this param exist in locations.yaml and that your launch includes this param file. shutting down..."

#define ERROR_MSG_INVALID_PARAM "[MoveAction]: %s param is invalid (needs to be of an array type) or missing. \
Make sure that this param exist in locations.yaml and that your launch includes this param file. shutting down..."

#define LOCATIONS_CONFIG_PARAM "locations"

/* 
 * Represents an action sever that receives a name of a location from the action client,
 * and searches for its x, y, and Y coordinates (after loading this information from a Yaml file). 
 * If the location exists, sends it as a goal to move_base node (which is an action server). 
 */
class MoveAction
{
public:

  /* Construct an action server. */
  MoveAction(std::string name);

  ~MoveAction(void);  

private:
  
  // The node handle is constructed and passed into the action server during construction of the action.
  // The feedback and result messages are created for publishing in the action.
  ros::NodeHandle nh_;
  actionlib::SimpleActionServer<my_action::MoveAction> * action_server_;
  std::string action_name_;
  
  my_action::MoveFeedback feedback_;
  my_action::MoveResult result_;

  // variables for the yaml file parsing
  XmlRpc::XmlRpcValue locations_; // the name of the yaml file
  std::map<std::string, point> locations_map_;

  // Check if the yaml file is valid. If not, exit. 
  void validateYamlType(XmlRpc::XmlRpcValue::Type actual_type, XmlRpc::XmlRpcValue::Type wanted_type, 
                        const char* error_msg, std::string i);
  
  void fetchParams();
  
  /* Parse yaml file and load the locations */
  void loadLocations();

  /*
   * The callback function. Called when the client send a goal. 
   */
  void executeCB(const my_action::MoveGoalConstPtr &goal);

};
#endif // MY_ACTION_MOVE_SERVER_H
