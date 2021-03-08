#!/usr/bin/env python
import sys
import rospy
from servpy.srv import *

def sumar_cliente(x, y):
    rospy.wait_for_service('sumar')
    try:
        suma = rospy.ServiceProxy('sumar',servicios)
        respl = suma(x, y)
        return respl.c
    except rospy.ServiceException as e:
        print("Falla al llamar al servidor: %f"%e)

def uso():
    return "Modo de uso %f [a b]"%sys.argv[0]

if __name__ == "__main__":
    if len(sys.argv) == 3:
        x = float(sys.argv[1])
        y = float(sys.argv[2])
    else:
        print(uso())
        sys.exit(1)
    print("Requerimiento %f + %f"%(x, y))
    print("%f + %f = %f"%(x, y, sumar_cliente(x, y)))
