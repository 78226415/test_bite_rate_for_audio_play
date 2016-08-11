
#include <ros/ros.h>
#include "std_msgs/String.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <string>
using namespace std;
#include "audio_common_msgs/AudioData.h"
#include "hlf_common_srv/AudioPublishData.h" 

int main (int argc, char **argv)
{
	ros::init(argc, argv, "test_bite_rate_audio_play_server");
	ros::NodeHandle _nh;
	ros::ServiceClient audioContentPublishClient = _nh.serviceClient<hlf_common_srv::AudioPublishData>("audio_content_publish_server"); 
	char* tts_receive_data = NULL;
	int total_count = 0;
	int read_size = 1000;
	char * ptr = (char *) malloc(read_size);  
	memset (ptr,'\0',read_size);
	//the next two lines, you should replace the file path for your local environment
	FILE *fp_test = fopen("/home/turtlebot/catkin_ws/src/test_bite_rate_audio_play_server/res/test2.wav", "r");  // this is no sound, it's bite rate is 256kbps 
	//FILE *fp_test = fopen("/home/turtlebot/catkin_ws/src/test_bite_rate_audio_play_server/res/test1.wav", "r"); // this is ok, the bite rate is 16kbps
	 
	if (fp_test == NULL) {  
		ROS_INFO("Open file failed");  
		return 1;  
	}  

	int read_count = fread(ptr, 1, read_size, fp_test); 

	while(read_count > 0)
	{
		total_count += read_count;

		if( tts_receive_data == NULL)
		{
			tts_receive_data = ptr;
		}
		else
		{
	    		strcat(tts_receive_data, ptr);
	    	}

		if(read_count != read_size)
		{
			break;
		}

		ptr = (char *) malloc(read_size);  
		memset (ptr,'\0',read_size);
		read_count = fread(ptr, 1, read_size, fp_test); 
	}

	fclose(fp_test);
	//printf("wav data : %s \n", tts_receive_data); 
	//printf("total_count : %d \n", total_count); 
	
	hlf_common_srv::AudioPublishData audio_publish_msg;
	audio_publish_msg.request.audioPlayContent = std::string( tts_receive_data, total_count );  
	audioContentPublishClient.call(audio_publish_msg);

	ROS_INFO("test server is over.");
	
	ros::spin();
}

