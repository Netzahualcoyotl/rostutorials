#!/usr/bin/env python

from servpy.srv import servicios, serviciosResponse
import rospy

def sumar(req):
    return serviciosResponse(req.a + req.b)

def suma_servidor():
    rospy.init_node('sumar_servidor')
    s = rospy.Service('sumar', servicios, sumar)
    print("Listo para sumar dos variables")
    rospy.spin()

if __name__ == "__main__":
    suma_servidor()
