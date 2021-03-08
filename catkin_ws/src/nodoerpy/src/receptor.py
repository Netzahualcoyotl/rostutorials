#!/usr/bin/env python
import rospy
from nodoerpy.msg import *
from std_msgs.msg import String

def funcion1(msg):
    #rospy.loginfo(msg.data)
    print(msg.data)

def funcion2(msg):
    print(msg)

def receptor():
    rospy.init_node('Receptor_python', anonymous = True)
    rospy.Subscriber("Topico1", String, funcion1)
    rospy.Subscriber("Topico", mensajec, funcion2)
    rospy.spin()

if __name__ == '__main__':
    receptor()
