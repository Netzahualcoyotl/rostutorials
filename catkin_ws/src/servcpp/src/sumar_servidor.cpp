#include "ros/ros.h"
#include "servcpp/servicios.h"

bool sumar(servcpp::servicios::Request &req, servcpp::servicios::Response &res)
{
    res.c = req.a + req.b;
    ROS_INFO("Requerimientos: a = %f, b = %f", req.a, req.b);
    ROS_INFO("Respuesta obtenida: [%f]", res.c);
    return true;
}

int main(int argc, char **argv)
{
    ros::init(argc, argv, "sumar_servidor");
    ros::NodeHandle n;
    
    ros::ServiceServer servicio = n.advertiseService("suma", sumar);
    ROS_INFO("Listo para sumar");
    ros::spin();
    return 0;
}
