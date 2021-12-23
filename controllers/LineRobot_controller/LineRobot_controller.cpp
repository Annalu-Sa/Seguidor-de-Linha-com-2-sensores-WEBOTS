// File:          LineRobot_controller.cpp
// Date: 15-23/12/2021
// Description: Capacitação na modalidade Seguidor de Linha da equipe de robótica Minervabots
// Author: Anna Luisa Sá dos Santos

#include <webots/Robot.hpp>
#include <webots/Motor.hpp>
#include<webots/DistanceSensor.hpp>

#define TIME_STEP 64
#define MAX_SPEED 6.28//6.28 = 1 rotation per second

using namespace webots;

int main(int argc, char **argv) {
  // create the Robot instance.
  Robot *robot = new Robot();

Motor *left_motor = robot->getMotor("left wheel motor");
Motor *right_motor = robot->getMotor("right wheel motor");

left_motor->setPosition(INFINITY);
right_motor->setPosition(INFINITY);

left_motor-> setVelocity(0.0);
right_motor-> setVelocity(0.0);

DistanceSensor *left_ir = robot->getDistanceSensor("ir0");
DistanceSensor *right_ir = robot->getDistanceSensor("ir1");

left_ir -> enable(TIME_STEP);
right_ir -> enable(TIME_STEP);

double left_speed = MAX_SPEED;
double right_speed = MAX_SPEED;

  while (robot->step(TIME_STEP) != -1) {

    double left_ir_val = left_ir->getValue();
    double right_ir_val = right_ir->getValue();

    left_speed = MAX_SPEED;
    right_speed = MAX_SPEED;

//sempre mantendo a linha preta embaixo do robô:
//se sensor esquerdo identificar preto, roda esquerda roda mais rapido q direita
//se sensor direito identificar preto, roda direita roda mais rapido q esquerda
bool left_line = (4<left_ir_val) && (left_ir_val<16);
bool right_line = (4<right_ir_val) && (right_ir_val<16);

//se a linha esta na esquerda, vire esquerda
if((left_ir_val > right_ir_val) && left_line){
  left_speed = MAX_SPEED * 0.30;
}
//se a linha esta na direita, vira direita
else if((right_ir_val > left_ir_val) && right_line){
  right_speed = MAX_SPEED * 0.30;
}

    // Enter here functions to send actuator commands, like:

    //  motor->setPosition(10.0);
    left_motor-> setVelocity(left_speed);
    right_motor-> setVelocity(right_speed);
  };

  // Enter here exit cleanup code.

  delete robot;
  return 0;
}
