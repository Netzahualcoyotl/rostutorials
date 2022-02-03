#include "ros/ros.h"
#include "std_msgs/Int32.h"
#include <actionlib/server/simple_action_server.h>
#include "miactionlibpkg/varaccionAction.h"
#include <iostream>
#include <sstream>

class varaccionAction
{
protected:
 ros::NodeHandle nh_;
 // Creando la instancia NodeHandle, para evitar un error inesperado.
 actionlib::SimpleActionServer<miactionlibpkg::varaccionAction> as;
 // Creando los mensajes que serán publicados como feedback/result
 miactionlibpkg::varaccionFeedback feedback;
 miactionlibpkg::varaccionResult result;

 std::string action_name;
 int goal;
 int progress;

public:
 varaccionAction(std::string name) :
   as(nh_, name, boost::bind(&varaccionAction::executeCB, this, _1), false),
   action_name(name)
 {
     as.registerPreemptCallback(boost::bind(&varaccionAction::preemptCB, this));
     as.start();
 }

 ~varaccionAction(void)
 {
 }

 void preemptCB()
 {
   ROS_WARN("%s se consiguió el prevaciado!", action_name.c_str());
   result.contador_final = progress;
   as.setPreempted(result,"Conseguí el prevaciado");
 }

 void executeCB(const miactionlibpkg::varaccionGoalConstPtr &goal)
 {
   if(!as.isActive() || as.isPreemptRequested()) return;
   ros::Rate rate(5);
   ROS_INFO("%s Se está procesando el goal %d", action_name.c_str(), goal->contador);
   for(progress = 1 ; progress <= goal->contador; progress++){
     //Revisión que ROS esté activo
     if(!ros::ok()){
       result.contador_final = progress;
       as.setAborted(result,"He fallado !");
       ROS_INFO("%s Cerrando",action_name.c_str());
       break;
     }

     if(!as.isActive() || as.isPreemptRequested()){
       return;
     }

     if(goal->contador <= progress){
       ROS_INFO("%s Exito al conseguir el goal %d", action_name.c_str(), goal->contador);
       result.contador_final = progress;
       as.setSucceeded(result);
     }else{
       ROS_INFO("Estableciendo el goal %d / %d",feedback.numero_actual,goal->contador);
       feedback.numero_actual = progress;
       as.publishFeedback(feedback);
     }
     rate.sleep();
   }
 }
};

int main(int argc, char** argv)
{
 ros::init(argc, argv, "enlace_de_accion");
 ROS_INFO("Iniciando el Servidor");
 varaccionAction demo_action_obj(ros::this_node::getName());
 ros::spin();
 return 0;
}
