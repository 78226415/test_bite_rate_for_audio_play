cmake_minimum_required(VERSION 2.8.3)
project(audio_server)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  rospy
  std_msgs
  message_generation
  audio_common_msgs
)

generate_messages(
   DEPENDENCIES
   std_msgs
 )


catkin_package(

)

include_directories(
  ${catkin_INCLUDE_DIRS}
  include
)

add_executable(audio_content_publish_server src/audio_content_publish_server.cpp)  
target_link_libraries(audio_content_publish_server ${catkin_LIBRARIES})
add_dependencies(audio_content_publish_server audio_content_publish_gencpp)  

