#include <message_filters/subscriber.h>
#include <message_filters/synchronizer.h>
#include <message_filters/sync_policies/approximate_time.h>
#include <sensor_msgs/Image.h>
#include <sensor_msgs/CameraInfo.h>
#include <ros/callback_queue.h>
#include <boost/bind.hpp>
#include <image_transport/image_transport.h>

// https://answers.ros.org/question/9705/synchronizer-and-image_transportsubscriber/

using namespace sensor_msgs;
using namespace message_filters;

ros::Publisher image_raw_pub;
ros::Publisher image_mono_pub;
ros::Publisher image_color_pub;
ros::Publisher image_rect_pub;
ros::Publisher image_rect_color_pub;
ros::Publisher camera_info_pub;

//void callback(const Image::ConstPtr& image1, const Image::ConstPtr& image2, const Image::ConstPtr& image3, const Image::ConstPtr& image4, const Image::ConstPtr& image5, const CameraInfo::ConstPtr& info)
void callback(const Image::ConstPtr& image1, const Image::ConstPtr& image2, const CameraInfo::ConstPtr& info)
{
  // Solve all of perception here...
  ROS_INFO("Sync_Callback");

  image_raw_pub.publish(image1);
  image_mono_pub.publish(image2);
  //image_color_pub.publish(image3);
  //image_rect_pub.publish(image4);
  //image_rect_color_pub.publish(image5);
  camera_info_pub.publish(info);

}
/*
void imageCallback(const sensor_msgs::ImageConstPtr& msg)
{
  // Testing subscribe here
  ROS_INFO("Image_Subscribe_Callback");
}
*/
int main(int argc, char** argv)
{
  ros::init(argc, argv, "camera_info_node");

  std::string img_raw_topic = "/camera/0/0/image_raw";
  std::string img_mono_topic = "/camera/0/0/image_mono";
  //std::string img_color_topic = "/camera/0/0/image_color";
  //std::string img_rect_topic = "/camera/0/0/image_rect";
  //std::string img_rect_color_topic = "/camera/0/0/image_rect_color";
  std::string camera_info_topic = "/camera/0/0/camera_info";

  ros::NodeHandle nh;
  //image_transport::ImageTransport it(nh);

  message_filters::Subscriber<Image> image_raw_sub(nh, img_raw_topic, 100);
  message_filters::Subscriber<Image> image_mono_sub(nh, img_mono_topic, 100);
  //message_filters::Subscriber<Image> image_color_sub(nh, img_color_topic, 100);
  //message_filters::Subscriber<Image> image_rect_sub(nh, img_rect_topic, 100);
  //message_filters::Subscriber<Image> image_rect_color_sub(nh, img_rect_color_topic, 100);
  message_filters::Subscriber<CameraInfo> camera_info_sub(nh, camera_info_topic, 100);

  image_raw_pub = nh.advertise<Image>(img_raw_topic, 1000);
  image_mono_pub = nh.advertise<Image>(img_mono_topic, 1000);
  //image_color_pub = nh.advertise<Image>(img_color_topic, 1000);
  //image_rect_pub = nh.advertise<Image>(img_rect_topic, 1000);
  //image_rect_color_pub = nh.advertise<Image>(img_rect_color_topic, 1000);
  camera_info_pub = nh.advertise<CameraInfo>(camera_info_topic, 1000);

  typedef sync_policies::ApproximateTime<Image, Image, CameraInfo> MySyncPolicy;
  // ApproximateTime takes a queue size as its constructor argument, hence MySyncPolicy(10)
  Synchronizer<MySyncPolicy> sync(MySyncPolicy(10), image_raw_sub, image_mono_sub, camera_info_sub);
  sync.registerCallback(boost::bind(&callback, _1, _2, _3));
  
  
  ros::spin();

  return 0;
}

