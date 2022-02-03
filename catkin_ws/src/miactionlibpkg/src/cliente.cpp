#include "ros/ros.h"
#include <iostream>
#include <actionlib/client/simple_action_client.h>
#include <actionlib/client/terminal_state.h>
#include "miactionlibpkg/varaccionAction.h"

int main (int argc, char **argv)
{
 ros::init(argc, argv, "cliente");

 if(argc != 3){
   ROS_INFO("%d",argc);
   ROS_WARN("Usage: cliente <goal> <tiempo_en_segundos>");
   return 1;
 }

 // creadión del cliente
 // true causes the client to spin its own thread
 actionlib::SimpleActionClient<miactionlibpkg::varaccionAction> ac("enlace_de_accion", true);

 ROS_INFO("Esperando la acción del servidor para comenzar.");

 // Esperando la acción del servidor para comenzar
 ac.waitForServer(); //Esperará por un tiempo infinito

 ROS_INFO("Accion del servidor iniciada, enviando el goal.");

 // Enviando el goal a la acción
 miactionlibpkg::varaccionGoal goal;
 goal.contador = atoi(argv[1]);

 ROS_INFO("Enviando el Goal [%d] y proponiendo el tiempo [%d]",goal.contador, atoi(argv[2]));
 ac.sendGoal(goal);

 //Esperando la acción de retorno
 bool finished_before_timeout = ac.waitForResult(ros::Duration(atoi(argv[2])));
 //Prevaciando la tarea
 ac.cancelGoal();

 if (finished_before_timeout){
   actionlib::SimpleClientGoalState state = ac.getState();
   ROS_INFO("Accion terminada: %s",state.toString().c_str());
   //Prevaciando el proceso
   ac.cancelGoal();
 }
 else{
   ROS_INFO("La acción no terminará antes de el tiempo final.");
 }

 //Salir
 return 0;
}
