#!/usr/bin/env python
import rospy
import importlib
import math

from sensor_msgs.msg import JointState  
from inmoov_urdf.msg import JointAngles
from std_msgs.msg import Int16MultiArray
from std_msgs.msg import MultiArrayDimension


global pub, sub;

def main():
	global pub, sub;
	rospy.init_node('joint_angle_handler')  
	sub = rospy.Subscriber('/joint_states', JointState, callback)
   
	pub = rospy.Publisher('/joint_angle', Int16MultiArray)  
	rospy.spin()

def callback(msg):  
	global pub, sub;
	#out.header = msg.header  
	#out = JointAngles();
	#out.angles = ;
	pub.publish(normalise(msg.position));
	#joint_angles = msg.position;
	#rospy.loginfo("joints={}".format(str(joint_angles)));

def normalise(pos):
	to_return = Int16MultiArray();
	to_return.layout.dim.append(MultiArrayDimension())
	to_return.layout.dim[0].label = "dim"
	to_return.layout.dim[0].size = 40
	to_return.layout.dim[0].stride = 1
	to_return.layout.data_offset = 0
	to_return.data = []
	for i, val in enumerate(pos):
		if(i == 0 or i == 3 or i == 4 or i == 22 or i == 23): # shift by +pi/2
			to_return.data += [math.degrees(val+1.5707)];
		elif(i == 1): # shift by +pi/4
			to_return.data += [math.degrees(val+0.7854)];
		elif(i == 2 or i == 5 or i == 24 or i == 25): # abs
			to_return.data += [abs(math.degrees(val))];
		else:
			to_return.data += [math.degrees(val)];
	return to_return;
		


		

if __name__ == "__main__":
	main();
