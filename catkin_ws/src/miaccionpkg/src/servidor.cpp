#include "ros/ros.h"
#include "miaccionpkg/DoDishesAction.h"
#include <actionlib/server/simple_action_server.h>

typedef actionlib::SimpleActionServer<miaccionpkg::DoDishesAction> Server;

miaccionpkg::DoDishesFeedback feedback;
miaccionpkg::DoDishesResult result;
int goal;
int progress;

void execute(const miaccionpkg::DoDishesGoalConstPtr& goal, Server* as)
{ 
  ROS_INFO(" goal %d",goal->dishwasher_id);
  if(!as->isActive() || as->isPreemptRequested()) return;
  ros::Rate rate(5);
  
  for(int i=1;i <= goal->dishwasher_id;i++)
  {
    if(!ros::ok()){result.total_dishes_cleaned = i; break; }
    
    if(!as->isActive() || as->isPreemptRequested()) return;
    
    if(goal->dishwasher_id <= i){
      ROS_INFO(" %s Exito con goal %d","do_dishes", goal->dishwasher_id);
      result.total_dishes_cleaned = i;
      as->setSucceeded(result);
     }else{
       ROS_INFO("Estableciendo el goal %f / %d",feedback.percent_complete, goal->dishwasher_id);
      feedback.percent_complete = i;
      as->publishFeedback(feedback);
      }
      rate.sleep();
  }
}

int main(int argc, char** argv)
{
  ros::init(argc, argv, "do_dishes_server");
  ros::NodeHandle n;
  Server server(n, "do_dishes", boost::bind(&execute, _1, &server), false);
  server.start();
  ros::spin();
  return 0;
}
