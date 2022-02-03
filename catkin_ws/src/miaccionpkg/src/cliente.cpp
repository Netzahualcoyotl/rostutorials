#include "ros/ros.h"
#include "miaccionpkg/DoDishesAction.h"
#include <actionlib/client/simple_action_client.h>

typedef actionlib::SimpleActionClient<miaccionpkg::DoDishesAction> Client;

int main(int argc, char** argv)
{
  ros::init(argc, argv, "do_dishes_client");
  Client client("do_dishes", true);
  client.waitForServer();
  miaccionpkg::DoDishesGoal goal;
  // LLenado de la tarea goal
  goal.dishwasher_id = atoi(argv[1]);
  client.sendGoal(goal);
  bool finished_before_timeout = client.waitForResult(ros::Duration(atoi(argv[2])));
  //Adelantando la tarea
  client.cancelGoal();
  if (finished_before_timeout){
    actionlib::SimpleClientGoalState state = client.getState();
    ROS_INFO("Accion terminada: %s",state.toString().c_str());
    //Adelantando la tarea
    client.cancelGoal();
  }
  else ROS_INFO("La Accion no ha terminado antes del time out.");
  
  if (client.getState() == actionlib::SimpleClientGoalState::SUCCEEDED)
    printf("Yay! Los platos ahora estan limpios");
  printf("Estado actual: %s \n", client.getState().toString().c_str());
  return 0;
}
