#include "ros/ros.h"
#include "nodoercpp/mensaje.h"
#include "nodoercpp/mensajec.h"

void funcion1(const nodoercpp::mensajec::ConstPtr& msg){
    ROS_INFO("Mensaje recibido dato1 = %f dato2 = %f",msg->a1.dato1, msg->a1.dato2);
}

int main(int argc, char **argv){
    ros::init(argc, argv, "Receptor");
    ros::NodeHandle nodo;
    ROS_INFO("Receptor creado");
    
    ros::Subscriber subscriptor = nodo.subscribe("Topico", 0, funcion1);
    ros::spin();
    return 0;
}


