#include "ros/ros.h"
#include "nodoercpp/mensaje.h"
#include "nodoercpp/mensajec.h"

int main(int argc, char **argv)
{
    ros::init(argc, argv, "Emisor");
    ros::NodeHandle nodo;

    ROS_INFO("Nodo emisor creado");

    ros::Publisher publicador = nodo.advertise<nodoercpp::mensajec>("Topico", 0);

    ros::Duration dormir(1);
    float contador = 0.0;
    while (ros::ok()){
    nodoercpp::mensajec mensaje1;
    mensaje1.a1.dato1=contador;
    mensaje1.a1.dato2=contador*2;
    ROS_INFO("Dentro del ciclo dato1 = %f, dato2 = %f",mensaje1.a1.dato1, mensaje1.a1.dato2);
    publicador.publish(mensaje1);
    ros::spinOnce();
    ROS_DEBUG("Silencio de 1 segundo");
    dormir.sleep();
    contador++;
    }
}
