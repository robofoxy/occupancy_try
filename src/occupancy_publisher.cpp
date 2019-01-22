#include <ros/ros.h>
#include "std_msgs/String.h"

#include <sstream>
#include "nav_msgs/OccupancyGrid.h"

#define WIDTH 100
#define HEIGHT 100
#define RESOLUTION 0.2



int main(int argc, char **argv)
{
  ros::init(argc, argv, "talker");

  ros::NodeHandle n;

  ros::Publisher occ_pub = n.advertise<nav_msgs::OccupancyGrid>("map", 1);

  ros::Rate loop_rate(10);

  int count = 0;
  while (ros::ok())
  {

    nav_msgs::OccupancyGrid map;

    map.header.frame_id = "world";

    map.info.resolution = RESOLUTION;

    map.info.height = HEIGHT;
    map.info.width = WIDTH;

    map.info.origin.position.x = 0;
    map.info.origin.position.y = 0;
    map.info.origin.position.z = 0;

    map.data.resize(WIDTH * HEIGHT);

    for(int i = 0; i < WIDTH; i++){
        for(int j = i; j < HEIGHT; j++)
            map.data[i*HEIGHT + j] = 100;
    }


    occ_pub.publish(map);

    ros::spinOnce();

    loop_rate.sleep();
    ++count;
  }


  return 0;
}