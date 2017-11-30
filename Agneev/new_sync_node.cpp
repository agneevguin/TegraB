#include <message_filters/subscriber.h>
#include <message_filters/synchronizer.h>
#include <message_filters/sync_policies/approximate_time.h>
#include <sensor_msgs/Image.h>
#include <sensor_msgs/CameraInfo.h>

using namespace sensor_msgs;
using namespace message_filters;

ros::Publisher image_mono_pub;
ros::Publisher image_color_pub;
ros::Publisher camera_info_pub1;


void callback(const Image::ConstPtr& image1, const Image::ConstPtr& image2, const CameraInfo::ConstPtr& info)
{
  // Solve all of perception here...
  ROS_INFO("Sync_Callback");

  image_mono_pub.publish(image1);
  image_color_pub.publish(image2);
  camera_info_pub1.publish(info);

}

int main(int argc, char** argv)
{
  ros::init(argc, argv, "new_sync_node");

  std::string img_mono_topic = "/camera/0/0/image_mono";
  std::string img_color_topic = "/camera/0/0/image_color";
  std::string camera_info_topic = "/camera/0/0/camera_info";

  ros::NodeHandle nh;
  message_filters::Subscriber<Image> image_mono_sub(nh, img_mono_topic, 1);
  message_filters::Subscriber<Image> image_color_sub(nh, img_color_topic, 1);
  message_filters::Subscriber<CameraInfo> camera_info_sub(nh, camera_info_topic, 1);

  image_mono_pub = nh.advertise<Image>(img_mono_topic, 10);
  image_color_pub = nh.advertise<Image>(img_color_topic, 10);
  camera_info_pub1 = nh.advertise<CameraInfo>(camera_info_topic, 10);

  typedef sync_policies::ApproximateTime<Image, Image, CameraInfo> MySyncPolicy;
  // ApproximateTime takes a queue size as its constructor argument, hence MySyncPolicy(10)
  Synchronizer<MySyncPolicy> sync(MySyncPolicy(10), image_mono_sub, image_color_sub, camera_info_sub);
  sync.registerCallback(boost::bind(&callback, _1, _2, _3));

  ros::spin();

  return 0;
}



/*
#include <message_filters/subscriber.h>
#include <message_filters/synchronizer.h>
#include <message_filters/sync_policies/approximate_time.h>
#include <sensor_msgs/Image.h>
#include <sensor_msgs/CameraInfo.h>

#include "image_transport/image_transport.h"
#include "ros/ros.h"
//ros::Publisher Image_sub;
//ros::Publisher Info_sub;

using namespace sensor_msgs;
using namespace message_filters;

void callback(const sensor_msgs::Image::ConstPtr& image, const sensor_msgs::CameraInfo::ConstPtr& info)
{
    ROS_ERROR("Enter Publish");
    //Image_pub.publish(image);
    //Info_pub.publish(info);
}
int main(int argc, char** argv)
{
  ros::init(argc, argv, "camera_info_node");
  ros::Time::init();
  ros::NodeHandle nh;
  ROS_INFO("start message filter");
  message_filters::Subscriber<Image> Image_sub(nh, "/camera/0/0/image_raw", 1);
  message_filters::Subscriber<CameraInfo> Info_sub(nh,"/camera/0/0/camera_info" , 1);
  typedef sync_policies::ApproximateTime<Image, CameraInfo> MySyncPolicy;
  // ApproximateTime takes a queue size as its constructor argument, hence MySyncPolicy(10)
  Synchronizer<MySyncPolicy> sync(MySyncPolicy(10), Image_sub, Info_sub);
  sync.registerCallback(boost::bind(&callback, _1, _2));

  ros::spin();
  return 0;
}*/
