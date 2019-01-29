cmake_minimum_required(VERSION 2.8.3)
project(my_action)

## Compile as C++11, supported in ROS Kinetic and newer
add_compile_options(-std=c++11)

## Find catkin macros and libraries
## if COMPONENTS list like find_package(catkin REQUIRED COMPONENTS xyz)
## is used, also find other catkin packages
find_package(
    catkin REQUIRED COMPONENTS 
    roscpp
    actionlib 
    actionlib_msgs
)

find_package(Boost REQUIRED COMPONENTS)

## Add actions
add_action_files(
    DIRECTORY action
    FILES Move.action)

## Generate messages
generate_messages(DEPENDENCIES actionlib_msgs)

## Define catkin exports
catkin_package(
  INCLUDE_DIRS include
  CATKIN_DEPENDS actionlib_msgs
  DEPENDS Boost
)

## Setup include dirs
include_directories(
 include
 ${catkin_INCLUDE_DIRS} ${yaml-cpp_INCLUDE_DIRS} ${Boost_INCLUDE_DIRS}
 )


add_executable(move_server_node
		src/move_server_node.cpp
		src/move_server.cpp
		include/move_server.h
		include/point.h)

target_link_libraries(
	move_server_node
	${catkin_LIBRARIES}
)

add_dependencies(move_server_node ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})

add_executable(move_client_node
                src/move_client_node.cpp
                src/move_callback_client.cpp
                include/move_callback_client.h)

target_link_libraries(
	move_client_node
	${catkin_LIBRARIES}
)

add_dependencies(move_client_node ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})

        

