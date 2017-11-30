#!/usr/bin/python

'''
Determine the xyz coordinates from the lidar data by subscribing to the rostopic for lidar scans.
email: agneev@kth.se
'''

import rospy, math, random
import numpy as np
from sensor_msgs.msg import LaserScan
from laser_geometry import LaserProjection


def __init__(self, scan_topic="/velodyne_points"):
	self.scan_sub = rospy.Subscriber(scan_topic, LaserScan, self.on_scan)
	self.laser_projector = LaserProjection()
	print "Test"

def on_scan(self, scan):
	print scan
	rospy.loginfo("Got scan, projecting")
	cloud = self.laser_projector.projectLaser(scan)
	print cloud
	rospy.loginfo("Printed cloud")
	for p in pc2.read_points(point_cloud, field_names = ("x", "y", "z"), skip_nans=True):
		print " x : %f  y: %f  z: %f" %(p[0],p[1],p[2])
