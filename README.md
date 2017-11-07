# Tegra B for Copper and Silver

## Steps to setup TEGRA B for ROS environment

### Tegra B Installing

* Flash Tegra B using DriveInstall 

### Installing ROS
* Install DW steps from [DevTalk](https://devtalk.nvidia.com/default/topic/1011002/general/cross-compiling-driveworks-on-the-px2-with-ros/)
* Follow steps 4 to 7 except step 6.
* Follow ROS installation from [RosWiki](http://wiki.ros.org/kinetic/Installation/Ubuntu)
* Prepare catkin_ws from [tutorials](http://wiki.ros.org/ROS/Tutorials/InstallingandConfiguringROSEnvironment)
* Follow steps 10 & 11 from DevTalk.

### Installing OpenCV
* (I was installing OpenCV but then I flashed the Tegra B firmware and did not install OpenCV again. So my assumption: It's not required)

### Install GMSL Driver
* Clone [GMSL Driver](https://github.com/cshort101/gmsl_driver to catkin_ws/src)
* Install `sudo apt-get install ros-kinetic-image-transport ros-kinetic-cv-bridge glew-utils libglew-dev`
* Replace `/usr/include/xf86drmMode.h` by this [code](https://www.apt-browse.org/browse/ubuntu/trusty/main/i386/libdrm-dev/2.4.52-1/file/usr/include/xf86drmMode.h)

### Run ROS
* `cd ~/catkin_ws`
* `catkin_make`
* `source /opt/ros/kinetic/setup.bash`
* `source ~/catkin_ws/devel/setup.bash`
* `export LD_LIBRARY_PATH=/usr/lib`
* `roslaunch ~/catkin_ws/src/gmsl_driver/launch/gmsl_n_cameras.launch selector-mask:=1111`
* Try visualization : `rosrun image_view image_view image:=/camera/0/0/image theora` (Doesnt work yet)

### Run Velodyne
* 

## Debugging

### Error Type 1:
```
StreamProducerNvMediaImage: could not create NvMedia Image stream producer!
Driveworks exception thrown: DW_CANNOT_CREATE_OBJECT: could not create NvMedia Image stream producer
```
* Perform `export LD_LIBRARY_PATH=/usr/lib`

### Error Type 2:
```
Driveworks exception thrown: DW_INVALID_ARGUMENT: nvmediaImage == nullptr dwImageNvMedia_setFromImage(dwImageNvMedia*, const NvMediaImage*)::<lambda()>:382
```
* Cameras not initiated from Tegra A. Run camera_gmsl sample programs in Tegra A.

### Error Type 3: 
```
ERROR: cannot launch node of type [gmsl_n_cameras/gmsl_n_cameras_node]: gmsl_n_cameras
ROS path [0]=/opt/ros/kinetic/share/ros
ROS path [1]=/opt/ros/kinetic/share
```
* Perform devel source again. 
* Need to add it to bash (Added to ~/.bashrc).

### Error Type 4:
```
[gmsl_n_cameras.launch] requires the 'selector-mask' arg to be set
The traceback for the exception was written to the log file
```
* Need to add the selector mask argument with the roslaunch step.

