#include "ros/ros.h"
#include "servcpp/servicios.h"

int main(int argc, char **argv)
{
    ros::init(argc, argv, "sumar_cliente");
    if (argc != 3)
    {
        ROS_INFO("Modo de uso: ~$sumar_cliente a b");
        return 1;
    }
    
    ros::NodeHandle n;
    ros::ServiceClient cliente = n.serviceClient<servcpp::servicios>("suma");

    servcpp::servicios srv;
    srv.request.a = atof(argv[1]);
    srv.request.b = atof(argv[2]);
    if (cliente.call(srv))
    {
        ROS_INFO("Suma: %f +  %f = %f",srv.request.a,srv.request.b, srv.response.c);
    }
    else
    {
        ROS_ERROR("Falla al llamar al servidor Sumador ");
        return 1;
    }

    return 0;
} 
