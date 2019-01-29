#include "move_callback_client.h"

// usage: rosrun my_action move_callback_client _param:=____


/* Construct an action client that listen to "move_server" node. */
MoveActionClient::MoveActionClient() : action_client_("move_server", true)
{
  ROS_INFO("Waiting for action server to start.");
  action_client_.waitForServer();
  ROS_INFO("Action server started, sending goal.");
}

MoveActionClient::~MoveActionClient(void){};

void MoveActionClient::sendGoal(std::string location_name)
{
  my_action::MoveGoal goal;
  goal.location_name = location_name;

  // Need boost::bind to pass in the 'this' pointer.
  // _1, _2 stands for the function arguments.
  action_client_.sendGoal(goal,
                          boost::bind(&MoveActionClient::doneCb, this, _1, _2),
                          boost::bind(&MoveActionClient::activeCb, this),
                          boost::bind(&MoveActionClient::feedbackCb, this, _1));
  //                          actionlib::SimpleActionClient<my_action::MoveAction>::SimpleActiveCallback(),
//                          actionlib::SimpleActionClient<my_action::MoveAction>::SimpleFeedbackCallback());
}

// Called once when the goal completes
void MoveActionClient::doneCb(const actionlib::SimpleClientGoalState& state, 
            const my_action::MoveResultConstPtr& result)
{
  ROS_INFO_STREAM("Finished in state " << state.toString().c_str() << " " << result->res);
  ros::shutdown();
}

// Called once when the goal becomes active
void MoveActionClient::activeCb()
{
  ROS_INFO("Goal just went active");
}

// Called every time feedback is received for the goal
void MoveActionClient::feedbackCb(const my_action::MoveFeedbackConstPtr& feedback)
{
  ROS_INFO_STREAM("Got feedback: " << feedback->name);
}