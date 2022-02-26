#! /usr/bin/env python3

import rospy
import roslib
roslib.load_manifest('mycatkinactionpypkg')
import actionlib
from mycatkinactionpypkg.msg import DoDishesAction, DoDishesFeedback, DoDishesResult

class DoDishesServer:
  def __init__(self):
    self.feedback = DoDishesFeedback()
    self.result = DoDishesResult()
    self.server = actionlib.SimpleActionServer('do_dishes', DoDishesAction, self.execute, False)    
    self.server.start()
    rospy.loginfo(": Ready to accept goals")
        
  def execute(self, goal):
    # Do lots of awsome groundbreaking robot stuff here
    if(not self.server.is_active or self.server.is_preempt_requested()): 
      return
    for g in range(goal.dishwasher_id):
      if(not self.server.is_active or self.server.is_preempt_requested()):
        self.server.cancel_goal() 
        return
      g=g+1
      rospy.loginfo("Exito con goal %d"%goal.dishwasher_id)
      if goal.dishwasher_id <= g:
        self.result.total_dishes_cleaned = g
        self.server.set_succeeded(self.result)
        
      else:              
        self.feedback.percent_complete = g
        self.server.publish_feedback(self.feedback)
        rospy.loginfo("Estableciendo el goal %f / %d"%(self.feedback.percent_complete,goal.dishwasher_id))
      rospy.sleep(0.001)   

if __name__ == '__main__':
  rospy.init_node('do_dishes_server')
  server = DoDishesServer()
  rospy.spin()       
