#! /usr/bin/env python3

import roslib
roslib.load_manifest('mycatkinactionpypkg')
import rospy
import actionlib
import sys

from mycatkinactionpypkg.msg import DoDishesAction, DoDishesGoal

if __name__ == '__main__':
    rospy.init_node('do_dishes_client')
    client = actionlib.SimpleActionClient('do_dishes', DoDishesAction)
    client.wait_for_server()
    
    goal = DoDishesGoal()
    goal.dishwasher_id = int(sys.argv[1])
    client.send_goal(goal)
    print (" goal.dishwasher %d, Duration %f"%(goal.dishwasher_id, float(sys.argv[2])))
    
    finishedbto = client.wait_for_result(rospy.Duration(float(sys.argv[2])))
    
    if finishedbto:
      state = client.get_state()      
      rospy.loginfo("Accion terminada: " + str(actionlib.GoalStatus.to_string(state)))
      
    else:
      print ("La Accion no ha terminado antes del tieme out")
    
    if client.get_state() == actionlib.GoalStatus.SUCCEEDED:
      print ("Yay! Los platos ahora estan limpios")
    rospy.loginfo("Estado actual: " + str(actionlib.GoalStatus.to_string(client.get_state())))
