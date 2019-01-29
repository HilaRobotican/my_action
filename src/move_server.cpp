#include "move_server.h"

// usage: rosrun my_action move_server
// or: roslaunch my_action my_action.launch location_name:=___

/* Construct an action server. */
MoveAction::MoveAction(std::string name) : //action_server_(nh_, name, boost::bind(&MoveAction::executeCB, this, _1), false),
                                           action_name_(name)
{
  action_server_ = new actionlib::SimpleActionServer<my_action::MoveAction>(nh_, name, boost::bind(&MoveAction::executeCB, this, _1), false);
  action_server_->start();

  // load the locations yaml file
  fetchParams();
  loadLocations();
}

MoveAction::~MoveAction(){}

// Check if the yaml file is valid. If not, exit.
void MoveAction::validateYamlType(XmlRpc::XmlRpcValue::Type actual_type, XmlRpc::XmlRpcValue::Type wanted_type,
                                  const char *error_msg, std::string i)
{
  if (actual_type != wanted_type)
  {
    ROS_ERROR(error_msg, i);
    ros::shutdown();
    exit(EXIT_FAILURE);
  }
}

void MoveAction::fetchParams()
{
  /* LOCATIONS_CONFIG_PARAM */
  if (!nh_.hasParam(LOCATIONS_CONFIG_PARAM))
  {
    ROS_ERROR(ERROR_MSG_MISSING_PARAM, LOCATIONS_CONFIG_PARAM);
    ros::shutdown();
    exit(EXIT_FAILURE);
  }
  nh_.getParam(LOCATIONS_CONFIG_PARAM, locations_);
  validateYamlType(locations_.getType(), XmlRpc::XmlRpcValue::TypeArray, ERROR_MSG_INVALID_PARAM, LOCATIONS_CONFIG_PARAM);
}

/* Parse yaml file and load the locations */
void MoveAction::loadLocations()
{
  ROS_INFO("Loading yaml file...");
  /* Create locations_map */
  for (int i = 0; i < locations_.size(); i++)
  {
    std::string str_i = std::to_string(i).c_str();
    // ROS_INFO("errrrrrorrrrrr: %s", str_i.c_str());
    validateYamlType(locations_[i].getType(), XmlRpc::XmlRpcValue::TypeStruct, ERROR_MSG_YAML, str_i);

    std::string location_name; // the key
    point p;                   // the value

    /* location name */
    validateYamlType(locations_[i]["location_name"].getType(), XmlRpc::XmlRpcValue::TypeString, ERROR_MSG_YAML, str_i);
    location_name = static_cast<std::string>(locations_[i]["location_name"]);

    /* x coordinate */
    validateYamlType(locations_[i]["x"].getType(), XmlRpc::XmlRpcValue::TypeDouble, ERROR_MSG_YAML, str_i);
    p.x = static_cast<double>(locations_[i]["x"]);

    /* y coordinate */
    validateYamlType(locations_[i]["y"].getType(), XmlRpc::XmlRpcValue::TypeDouble, ERROR_MSG_YAML, str_i);
    p.y = static_cast<double>(locations_[i]["y"]);

    /* Y coordinate */
    validateYamlType(locations_[i]["Y"].getType(), XmlRpc::XmlRpcValue::TypeDouble, ERROR_MSG_YAML, str_i);
    p.Y = static_cast<double>(locations_[i]["Y"]);

    // Add the location to the map
    locations_map_[location_name] = p;
  }
}

/*
   * The callback function. Called when the client send a goal. 
   */
void MoveAction::executeCB(const my_action::MoveGoalConstPtr &goal)
{
  ros::Rate r(10);
  bool success = true;

  // Publish info to the console for the user
  std::cout << "Executing, the loaction name is: " << goal->location_name << std::endl;

//  if (action_server_.isPreemptRequested() || !ros::ok())
//  {
//    ROS_INFO("%s: Preempted", action_name_.c_str());
//    action_server_.setPreempted();
//    success = false;
//  }

  // Check if the client's goal exists. If not, exit.
  bool location_name_found = locations_map_.find(goal->location_name) != locations_map_.end();
  if (!location_name_found)
  {
    ROS_ERROR(ERROR_MSG_LOCATION_DOESNT_EXIST, goal->location_name.c_str());
    ros::shutdown();
    exit(EXIT_FAILURE);
  }

  feedback_.name = "found";
  // TODO - to send it to move base.

  //action_server_.publishFeedback(feedback_); // publish the feedback
  // this sleep is not necessary, the sequence is computed at 1 Hz for demonstration purposes
  r.sleep();

  if (success)
  {
    result_.res = goal->location_name;
    ROS_INFO("%s: Succeeded", action_name_.c_str());
    //action_server_.setSucceeded(result_);
  }
}