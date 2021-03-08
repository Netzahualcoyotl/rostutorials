#!/usr/bin/env python

import rospy
from nodoerpy.msg import *
from std_msgs.msg import String


def emisor():
    contador = 0.0
    a = mensajec()
    pub1 = rospy.Publisher('Topico', mensajec, queue_size = 1)
    pub2 = rospy.Publisher('Topico1', String, queue_size = 1)
    rospy.init_node('Emisor_python', anonymous = True)
    rate = rospy.Rate(10)
    
    while not rospy.is_shutdown():      
        m = str([contador, contador*2])
        a.a1.dato1 = contador
        a.a1.dato2 = contador*2
        print(m)
        print(a)
        pub2.publish(m)
        pub1.publish(a)
        rate.sleep()
        contador = contador + 0.1

if __name__ == '__main__':
    try:
        emisor()
    except rospy.ROSInterruptException:
        pass
