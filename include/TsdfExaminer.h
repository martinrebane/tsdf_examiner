#include <ros/ros.h>
#include <voxblox_ros/tsdf_server.h>
#include <string>

#ifndef TSDFEXAMINER
#define TSDFEXAMINER

namespace tsdf_examiner {

class TsdfExaminer {
public:
	TsdfExaminer(const ros::NodeHandle& nh,
				const ros::NodeHandle& nh_private);
	virtual ~TsdfExaminer();
	void initialDebug();

private:
	ros::NodeHandle nh_;
	ros::NodeHandle nh_private_;
	voxblox::TsdfServer tsdf_server_;
};

} /* namespace tsdf_examiner */

#endif /* TSDFEXAMINER */
