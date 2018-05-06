#include <ros.h>
#include <inmoov_urdf/JointAngles.h>
#include <Servo.h>

/*  
 *  Constants
 */

//ros array index
#define ROS_NECK 0
#define ROS_HEAD 1

#define ROS_R_U_SHOULDER 2
#define ROS_R_L_SHOULDER 3
#define ROS_R_BICEP 4
#define ROS_R_FOREARM 5
#define ROS_R_THUMB 6
#define ROS_R_INDEX 9
#define ROS_R_MIDDLE 12
#define ROS_R_RING 15
#define ROS_R_PINKIE 18

#define ROS_L_U_SHOULDER 21
#define ROS_L_L_SHOULDER 22
#define ROS_L_BICEP 23
#define ROS_L_FOREARM 24
#define ROS_L_THUMB 25
#define ROS_L_INDEX 28
#define ROS_L_MIDDLE 31
#define ROS_L_RING 34
#define ROS_L_PINKIE 37

//servo pins
#define SERVO_OFFSET 22

#define SERVO_NECK 0
#define SERVO_HEAD 1

#define SERVO_R_U_SHOULDER 2
#define SERVO_R_L_SHOULDER 3
#define SERVO_R_BICEP 4
#define SERVO_R_FOREARM 5
#define SERVO_R_THUMB 6
#define SERVO_R_INDEX 7
#define SERVO_R_MIDDLE 8
#define SERVO_R_RING 9
#define SERVO_R_PINKIE 10

#define SERVO_L_U_SHOULDER 11
#define SERVO_L_L_SHOULDER 12
#define SERVO_L_BICEP 13
#define SERVO_L_FOREARM 14
#define SERVO_L_THUMB 15
#define SERVO_L_INDEX 16
#define SERVO_L_MIDDLE 17
#define SERVO_L_RING 18
#define SERVO_L_PINKIE 19


/*
 * Global Vars
 */
 
ros::NodeHandle nh;

inmoov_urdf::JointAngles::_angles_type* angles;
boolean refresh;
boolean debugging;

Servo servos[SERVO_L_PINKIE - SERVO_NECK + 1];


void messageCb( const inmoov_urdf::JointAngles& joint_msg){
  
  if(joint_msg.angles[0] > 90) { // test indicator
    digitalWrite(13, HIGH);
  } else {
    digitalWrite(13, LOW);
  }
  
  angles = joint_msg.angles;
  refresh = true;
  //nh.loginfo("ALIVE AND WELL");
}


ros::Subscriber<inmoov_urdf::JointAngles> s("joint_angles", &messageCb);

void setup()
{
  debugging = false;
  
  pinMode(13, OUTPUT);
  nh.getHardware()->setBaud(230400);

  nh.initNode();
  nh.subscribe(s);

  if(!debugging) {
    servos[SERVO_NECK].attach(SERVO_NECK+SERVO_OFFSET);
    servos[SERVO_HEAD].attach(SERVO_HEAD+SERVO_OFFSET);
    
    servos[SERVO_R_U_SHOULDER].attach(SERVO_R_U_SHOULDER+SERVO_OFFSET);
    servos[SERVO_R_L_SHOULDER].attach(SERVO_R_L_SHOULDER+SERVO_OFFSET);
    servos[SERVO_R_BICEP].attach(SERVO_R_BICEP+SERVO_OFFSET);
    servos[SERVO_R_FOREARM].attach(SERVO_R_FOREARM+SERVO_OFFSET);
    servos[SERVO_R_THUMB].attach(SERVO_R_THUMB+SERVO_OFFSET);
    servos[SERVO_R_INDEX].attach(SERVO_R_INDEX+SERVO_OFFSET);
    servos[SERVO_R_MIDDLE].attach(SERVO_R_MIDDLE+SERVO_OFFSET);
    servos[SERVO_R_RING].attach(SERVO_R_RING+SERVO_OFFSET);
    servos[SERVO_R_PINKIE].attach(SERVO_R_PINKIE+SERVO_OFFSET);
  
    servos[SERVO_L_U_SHOULDER].attach(SERVO_L_U_SHOULDER+SERVO_OFFSET);
    servos[SERVO_L_L_SHOULDER].attach(SERVO_L_L_SHOULDER+SERVO_OFFSET);
    servos[SERVO_L_BICEP].attach(SERVO_L_BICEP+SERVO_OFFSET);
    servos[SERVO_L_FOREARM].attach(SERVO_L_FOREARM+SERVO_OFFSET);
    servos[SERVO_L_THUMB].attach(SERVO_L_THUMB+SERVO_OFFSET);
    servos[SERVO_L_INDEX].attach(SERVO_L_INDEX+SERVO_OFFSET);
    servos[SERVO_L_MIDDLE].attach(SERVO_L_MIDDLE+SERVO_OFFSET);
    servos[SERVO_L_RING].attach(SERVO_L_RING+SERVO_OFFSET);
    servos[SERVO_L_PINKIE].attach(SERVO_L_PINKIE+SERVO_OFFSET);
  }
}


void loop()
{
  nh.spinOnce();

  if(refresh && !debugging) {
    servos[SERVO_NECK].write(angles[ROS_NECK]);
    servos[SERVO_HEAD].write(angles[ROS_HEAD]);
    
    servos[SERVO_R_U_SHOULDER].write(angles[ROS_R_U_SHOULDER]);
    servos[SERVO_R_L_SHOULDER].write(angles[ROS_R_L_SHOULDER]);
    servos[SERVO_R_BICEP].write(angles[ROS_R_BICEP]);
    servos[SERVO_R_FOREARM].write(angles[ROS_R_FOREARM]);
    servos[SERVO_R_THUMB].write(angles[ROS_R_THUMB]);
    servos[SERVO_R_INDEX].write(angles[ROS_R_INDEX]);
    servos[SERVO_R_MIDDLE].write(angles[ROS_R_MIDDLE]);
    servos[SERVO_R_RING].write(angles[ROS_R_RING]);
    servos[SERVO_R_PINKIE].write(angles[ROS_R_PINKIE]);
  
    servos[SERVO_L_U_SHOULDER].write(angles[ROS_L_U_SHOULDER]);
    servos[SERVO_L_L_SHOULDER].write(angles[ROS_L_L_SHOULDER]);
    servos[SERVO_L_BICEP].write(angles[ROS_L_BICEP]);
    servos[SERVO_L_FOREARM].write(angles[ROS_L_FOREARM]);
    servos[SERVO_L_THUMB].write(angles[ROS_L_THUMB]);
    servos[SERVO_L_INDEX].write(angles[ROS_L_INDEX]);
    servos[SERVO_L_MIDDLE].write(angles[ROS_L_MIDDLE]);
    servos[SERVO_L_RING].write(angles[ROS_L_RING]);
    servos[SERVO_L_PINKIE].write(angles[ROS_L_PINKIE]);
    
    refresh = false;
  }
  
}



