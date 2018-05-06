#!/usr/bin/env python
import rospy
import importlib
import math

from sensor_msgs.msg import JointState  
from inmoov_urdf.msg import JointAngles

global pub;

def main():
	global pub;
	rospy.init_node('joint_angle_publisher');
	sub = rospy.Subscriber('/joint_states', JointState, callback);
	pub = rospy.Publisher('/joint_angles', JointAngles, queue_size=5); 
	rospy.spin();

def callback(msg):  
	global pub;
	out = JointAngles();
	out.angles = normalise(msg.position);
	pub.publish(out);

def normalise(pos):
	to_return = [];
	for i, val in enumerate(pos):
		if(i == 0 or i == 3 or i == 4 or i == 22 or i == 23): # shift by +pi/2
			to_return += [int(math.degrees(val+1.5707))];
		elif(i == 1): # shift by +pi/4
			to_return += [int(math.degrees(val+0.7854))];
		elif(i == 2 or i == 5 or i == 24 or i == 25): # abs
			to_return += [int(abs(math.degrees(val)))];
		else:
			to_return += [int(math.degrees(val))];

		#temp for finger control
		if((i > 5 and i < 21) or (i > 24)):
			to_return[i] *= 2;
	return to_return;	

if __name__ == "__main__":
	main();
