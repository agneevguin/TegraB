#!/usr/bin/env python

import rospy
import message_filters
from sensor_msgs.msg import Image, CameraInfo

def callback(image, camera_info):
	print 'test'

try:
	# Initialize ROS
	rospy.init_node('publish_camera_info')

	# look up camera topics
	# image_sub = message_filters.Subscriber('/camera/0/0/image', Image)
	image_sub = message_filters.Subscriber('/camera/0/0/image_raw', Image)
	info_sub = message_filters.Subscriber('/camera/0/0/camera_info', CameraInfo)

	ts = message_filters.ApproximateTimeSynchronizer([image_sub, info_sub], 10, 1, allow_headerless=True)
	ts.registerCallback(callback)
	rospy.spin()

except rospy.ROSInterruptException:
	pass

