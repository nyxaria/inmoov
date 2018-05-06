#!/usr/bin/env python
import rospy
from std_msgs.msg import String

to_send = 0;
def talker():
	global to_send;
	pub = rospy.Publisher('chatter', String, queue_size=10)
	rospy.init_node('talker', anonymous=True)
	rate = rospy.Rate(1) # 10hz

	while not rospy.is_shutdown():
		if(to_send == 0):
			to_send = 1;
		else:
			to_send = 0;
		
		hello_str = str(to_send);
		#rospy.loginfo(hello_str)
		pub.publish(hello_str)
		rate.sleep()

if __name__ == '__main__':
	try:
		talker()
	except rospy.ROSInterruptException:
		pass
