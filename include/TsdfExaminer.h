#include <ros/ros.h>
#include <voxblox_ros/tsdf_server.h>
#include <string>
#include <stdio.h>
#include "voxblox_ros/tsdf_server.h"
#include <nav_msgs/Odometry.h>

#ifndef TSDFEXAMINER
#define TSDFEXAMINER

namespace tsdf_examiner {

class TsdfExaminer {
public:
	TsdfExaminer(const ros::NodeHandle& nh,
				const ros::NodeHandle& nh_private);
	virtual ~TsdfExaminer();
	void initialDebug(int interation);
	void oneScanTsdfSaver(const sensor_msgs::PointCloud2::Ptr& pointcloud);
	void continuousScanTsdfSaver(const sensor_msgs::PointCloud2::Ptr& pointcloud);

private:
	int step;
	ros::NodeHandle nh_;
	ros::NodeHandle nh_private_;
	voxblox::TsdfServer tsdf_server_;
	std::string mesh_filename_;
	void createTsdfIntegrator();
	void registerPclCallback();
};

} /* namespace tsdf_examiner */

#endif /* TSDFEXAMINER */
