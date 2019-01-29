#include "move_action_server.h"

// usage: rosrun my_action move_server
// or: roslaunch my_action my_action.launch location_name:=___

/* Construct an action server. */
MoveActionServer::MoveActionServer(ros::NodeHandle *nh, std::string name) : //action_server_(nh_, name, boost::bind(&MoveActionServer::executeCB, this, _1), false),
                                       nh_(nh), action_name_(name)
{
  action_server_ = new actionlib::SimpleActionServer<my_action::MoveAction>(*nh_, name,
                        boost::bind(&MoveActionServer::executeCB, this, _1), false);
  action_server_->start();

  // load the locations yaml file
  fetchParams();
  loadLocations();
}

MoveActionServer::~MoveActionServer(){
  delete action_server_;
}

// Check if the yaml file is valid. If not, exit.
bool MoveActionServer::validateYamlType(XmlRpc::XmlRpcValue::Type actual_type, XmlRpc::XmlRpcValue::Type wanted_type)
{
  return actual_type == wanted_type;
}

void MoveActionServer::fetchParams()
{
  /* LOCATIONS_CONFIG_PARAM */
  if (!nh_->hasParam(LOCATIONS_CONFIG_PARAM))
  {
    ROS_ERROR("[MoveActionServer]: %s param is missing on param server. "
              "Make sure that your launch includes this param file. "
              "shutting down...", LOCATIONS_CONFIG_PARAM);
    ros::shutdown();
    exit(EXIT_FAILURE);
  }
  nh_->getParam(LOCATIONS_CONFIG_PARAM, locations_);
  if (!validateYamlType(locations_.getType(), XmlRpc::XmlRpcValue::TypeArray))
  {
    ROS_ERROR("[MoveActionServer]: %s param is invalid (needs to be of an array type) or missing."
              "Make sure that this param exist in locations.yaml and that your launch includes this param file. "
              "shutting down...", LOCATIONS_CONFIG_PARAM);
    ros::shutdown();
    exit(EXIT_FAILURE);
  }
}

/* Parse yaml file and load the locations */
void MoveActionServer::loadLocations()
{
  ROS_INFO("Loading yaml file...");
  /* Create locations_map */
  for (int i = 0; i < locations_.size(); i++)
  {
    bool valid = true;
    valid = valid && validateYamlType(locations_[i].getType(), XmlRpc::XmlRpcValue::TypeStruct);

    std::string location_name; // the key
    point p;                   // the value

    /* location name */
    valid = valid && validateYamlType(locations_[i]["location_name"].getType(), XmlRpc::XmlRpcValue::TypeString);
    location_name = static_cast<std::string>(locations_[i]["location_name"]);

    /* x coordinate */
    valid = valid && validateYamlType(locations_[i]["x"].getType(), XmlRpc::XmlRpcValue::TypeDouble);
    p.x = static_cast<double>(locations_[i]["x"]);

    /* y coordinate */
    valid = valid && validateYamlType(locations_[i]["y"].getType(), XmlRpc::XmlRpcValue::TypeDouble);
    p.y = static_cast<double>(locations_[i]["y"]);

    /* Y coordinate */
    valid = valid && validateYamlType(locations_[i]["Y"].getType(), XmlRpc::XmlRpcValue::TypeDouble);
    p.Y = static_cast<double>(locations_[i]["Y"]);

    // Add the location to the map
    locations_map_[location_name] = p;

    if (!valid)
    {
      ROS_ERROR("[MoveActionServer]: load locations at index %d param data type is invalid or missing."
                "Make sure that this param exist in locations.yaml and that your launch includes "
                "this param file. shutting down...", i);
      ros::shutdown();
      exit(EXIT_FAILURE);
    }
  }
}

/*
   * The callback function. Called when the client send a goal. 
   */
void MoveActionServer::executeCB(const my_action::MoveGoalConstPtr &goal)
{
  ros::Rate r(10);
  bool success = true;

  // Publish info to the console for the user
  std::cout << "Executing, the loaction name is: " << goal->location_name << std::endl;

  if (action_server_->isPreemptRequested() || !ros::ok())
  {
    ROS_INFO("%s: Preempted", action_name_.c_str());
    action_server_->setPreempted();
    success = false;
  }

  // Check if the client's goal exists. If not, exit.
  bool location_name_found = locations_map_.find(goal->location_name) != locations_map_.end();
  if (!location_name_found)
  {
    ROS_ERROR( "[MoveActionServer]: couldn't locate model specification for location name %s. "
               "Make sure locations.yaml contains all the necessary locations. shutting down...",
               goal->location_name.c_str());
    ros::shutdown();
    exit(EXIT_FAILURE);
  }

  feedback_.name = "found";
  // TODO - to send it to move base.

  action_server_->publishFeedback(feedback_); // publish the feedback
  // this sleep is not necessary, the sequence is computed at 1 Hz for demonstration purposes
  r.sleep();

  if (success)
  {
    result_.res = goal->location_name;
    ROS_INFO("%s: Succeeded", action_name_.c_str());
    action_server_->setSucceeded(result_);
  }
}