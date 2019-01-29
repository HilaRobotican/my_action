#ifndef MY_ACTION_MOVE_CALLBACK_CLIENT_H
#define MY_ACTION_MOVE_CALLBACK_CLIENT_H

#include <ros/ros.h>
#include <actionlib/client/simple_action_client.h>
#include <my_action/MoveAction.h> // This is a header generated automatically from the FibonacciAction.msg file.


class MoveActionClient
{
public:

  /* Construct an action client. */
  MoveActionClient();

  ~MoveActionClient(void); 

  void sendGoal(std::string location_name);
  
  // Called once when the goal completes
  void doneCb(const actionlib::SimpleClientGoalState& state, const my_action::MoveResultConstPtr& result);
  
  // Called once when the goal becomes active
  void activeCb();

  // Called every time feedback is received for the goal
  void feedbackCb(const my_action::MoveFeedbackConstPtr& feedback);

private:

  //actionlib::SimpleActionClient<my_action::MoveAction> action_client_;

}; 
#endif // MY_ACTION_MOVE_CALLBACK_CLIENT_H
