#include <ros/ros.h>
#include <sensor_msgs/Image.h>
#include <message_filters/subscriber.h>
#include <message_filters/synchronizer.h>
#include <message_filters/sync_policies/approximate_time.h>

// using namespace message_filters;

class Node
{
 public:
  Node()
  {
    sub_1_.subscribe(nh_, "/camera1/color/image_raw", 1);
    sub_2_.subscribe(nh_, "/camera2/fisheye1/image_raw", 1);
    sub_3_.subscribe(nh_, "/camera2/fisheye2/image_raw", 1);

		pub_1_ = nh_.advertise<sensor_msgs::Image>("camera1/color/image_raw/sync", 5);
		pub_2_ = nh_.advertise<sensor_msgs::Image>("camera2/fisheye1/image_raw/sync", 5);
		pub_3_ = nh_.advertise<sensor_msgs::Image>("camera2/fisheye2/image_raw/sync", 5);

    sync_.reset(new Sync(MySyncPolicy(100), sub_1_, sub_2_, sub_3_));
    sync_->registerCallback(boost::bind(&Node::callback, this, _1, _2, _3));
  }

  void callback(const sensor_msgs::ImageConstPtr &in1, const sensor_msgs::ImageConstPtr &in2, const sensor_msgs::ImageConstPtr &in3)
  {
    ROS_INFO("Synchronization successful!!!!");
		pub_1_.publish(in1);
		pub_2_.publish(in2);
		pub_3_.publish(in3);
  }

 private:
  ros::NodeHandle nh_;
  message_filters::Subscriber<sensor_msgs::Image> sub_1_;
  message_filters::Subscriber<sensor_msgs::Image> sub_2_;
  message_filters::Subscriber<sensor_msgs::Image> sub_3_;
	ros::Publisher pub_1_;
	ros::Publisher pub_2_;
	ros::Publisher pub_3_;

  typedef message_filters::sync_policies::ApproximateTime<sensor_msgs::Image, sensor_msgs::Image, sensor_msgs::Image> MySyncPolicy;
  typedef message_filters::Synchronizer<MySyncPolicy> Sync;
  boost::shared_ptr<Sync> sync_;
};

int main(int argc, char **argv)
{
  ros::init(argc, argv, "synchronizer");

  Node synchronizer;

  ros::spin();
}
