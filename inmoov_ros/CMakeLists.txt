cmake_minimum_required(VERSION 2.8.3)

project(inmoov_urdf)

find_package(catkin REQUIRED COMPONENTS actionlib_msgs message_generation std_msgs)

add_message_files(
	DIRECTORY msg
	FILES
	JointAngles.msg
)

generate_messages(
	DEPENDENCIES
	std_msgs
)


catkin_package(CATKIN_DEPENDS message_runtime std_msgs)


find_package(roslaunch)

foreach(dir config launch meshes urdf)
	install(DIRECTORY ${dir}/
		DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION}/${dir})
endforeach(dir)
