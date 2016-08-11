cmake_minimum_required(VERSION 2.8.3)
project(test_bite_rate_audio_play_server)

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


add_executable(test_bite_rate_audio_play_server src/test_bite_rate_audio_play_server.cpp)  
target_link_libraries(test_bite_rate_audio_play_server ${catkin_LIBRARIES})
add_dependencies(test_bite_rate_audio_play_server test_bite_rate_audio_play_gencpp) 

#add_executable(test_audio_content_publish_server src/test_audio_content_publish_server.cpp)  
#target_link_libraries(test_audio_content_publish_server ${catkin_LIBRARIES})
#add_dependencies(test_audio_content_publish_server test_audio_content_publish_gencpp)  
#add_executable(test_audio_content_publish_server src/test_audio_content_publish_server.cpp)  
#target_link_libraries(test_audio_content_publish_server ${catkin_LIBRARIES})
#add_dependencies(test_audio_content_publish_server test_audio_content_publish_gencpp)  
