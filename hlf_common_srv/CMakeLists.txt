cmake_minimum_required(VERSION 2.8.3)

project(hlf_common_srv)

find_package(catkin REQUIRED COMPONENTS message_generation)

add_service_files(
  FILES
  AsrData.srv
  AudioPublishData.srv
)

generate_messages()

catkin_package(CATKIN_DEPENDS message_runtime)
