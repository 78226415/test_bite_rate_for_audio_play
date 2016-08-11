
#include <ros/ros.h>
#include "std_msgs/String.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include "hlf_common_srv/AudioPublishData.h"  
#include "audio_common_msgs/AudioData.h"
#include <string>
using namespace std;

/*
发布语音
此service，把传过来语音发布出去。
需要播放到音频统一在这个服务发布出去。
*/
//这里定义一些全局变量，以便在会话里使用
static ros::Publisher _pub;


bool audio_content_publish(hlf_common_srv::AudioPublishData::Request  &req, hlf_common_srv::AudioPublishData::Response &res)
{
	int totalLength = req.audioPlayContent.length();
	//printf("\n audio data length: %d \n", totalLength);
	audio_common_msgs::AudioData msg;
	msg.data.resize( totalLength );
	memcpy(&msg.data[0], (char*)req.audioPlayContent.c_str(), totalLength );
	_pub.publish(msg);
	res.audioPlayTotalMiliseconds = totalLength * 8 / 262144 * 1000;//音频到播放比特率所：256kbps
	return true;
}

int main (int argc, char **argv)
{
	ros::init(argc, argv, "audio_play_server");
	ros::NodeHandle _nh;
	_pub = _nh.advertise<audio_common_msgs::AudioData>("audio_content_publisher", 1000);
	ros::ServiceServer service = _nh.advertiseService("audio_content_publish_server", audio_content_publish);
	ROS_INFO("Audio content publish service is ready.");
	ros::spin();
}

