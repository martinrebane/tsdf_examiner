#include <ros/ros.h>
#include <voxblox_ros/tsdf_server.h>
#include <string>
#include <stdio.h>

#ifndef TSDFEXAMINER
#define TSDFEXAMINER

namespace tsdf_examiner {

class TsdfExaminer {
public:
	TsdfExaminer(const ros::NodeHandle& nh,
				const ros::NodeHandle& nh_private);
	virtual ~TsdfExaminer();
	void initialDebug(int interation);

private:
	ros::NodeHandle nh_;
	ros::NodeHandle nh_private_;
	voxblox::TsdfServer tsdf_server_;
	std::string mesh_filename_;
};

} /* namespace tsdf_examiner */

#endif /* TSDFEXAMINER */
