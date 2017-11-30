#include <message_filters/subscriber.h>
#include <message_filters/synchronizer.h>
#include <message_filters/sync_policies/approximate_time.h>
#include <sensor_msgs/Image.h>
#include <sensor_msgs/CameraInfo.h>

#include "image_transport/image_transport.h"
#include "ros/ros.h"
//ros::Publisher Velodyne_pub;
void callback(const sensor_msgs::Image::ConstPtr& image, const sensor_msgs::CameraInfo::ConstPtr& info)
{
    ROS_ERROR("Enter Publish");
   // Velodyne_pub.publish(point_cloud2);
   // Hokuyo_pub.publish(laser_scan);
}
int main(int argc, char** argv)
{
  ros::init(argc, argv, "message_filter_node");
  ros::Time::init();
  ros::NodeHandle nh;
  ROS_INFO("start message filter");
  message_filters::Subscriber<sensor_msgs::Image> Image_sub(nh, "/camera/0/0/image_color", 1);
  message_filters::Subscriber<sensor_msgs::CameraInfo> Info_sub(nh,"/camera/0/0/camera_info" , 1);
  typedef message_filters::sync_policies::ApproximateTime<sensor_msgs::Image, sensor_msgs::CameraInfo> MySyncPolicy;
  // ApproximateTime takes a queue size as its constructor argument, hence MySyncPolicy(10)
  message_filters::Synchronizer<MySyncPolicy> sync(MySyncPolicy(10), Image_sub, Info_sub);
  sync.registerCallback(boost::bind(&callback, _1, _2));

  ros::spin();
  return 0;
}
