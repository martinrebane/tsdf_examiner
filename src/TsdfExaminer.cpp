#include "TsdfExaminer.h"

namespace tsdf_examiner {

TsdfExaminer::TsdfExaminer(const ros::NodeHandle& nh,
		const ros::NodeHandle& nh_private):
			nh_(nh),
			nh_private_(nh_private),
			tsdf_server_(nh_, nh_private_)
				{
	nh_private.getParam("mesh_filename", mesh_filename_);
}

TsdfExaminer::~TsdfExaminer() {
	// TODO Auto-generated destructor stub
}

void TsdfExaminer::initialDebug(int iteration) {
	ROS_INFO("DEBUG STARTED");
	// lae salvestatud TSDF
	//tsdf_server_.loadMap("/home/martin/jtmp/map/oxpath.vxblx");

	// generate mesh sellest
	//tsdf_server_.mesh_filename_ = "/home/martin/jtmp/map/saved_mesh.ply";
	// wait for output to be started
	//ros::Duration(12.0).sleep();

	try {
		tsdf_server_.updateMesh();
		tsdf_server_.generateMesh();
		// rename .ply file to include iteration number
		rename(mesh_filename_.c_str(), (mesh_filename_ + std::to_string(iteration) + ".ply").c_str());
	} catch (std::exception& ex){
		ROS_ERROR("Something wrong with generating mesh! %s", ex.what());
	}
	ROS_ERROR("Mesh generated!");
}

} /* namespace tsdf_examiner */

int main(int argc, char** argv) {
	ros::init(argc, argv, "coll_avoid_detector");
	ros::NodeHandle n;
	ros::NodeHandle nh_private("~");

	ros::Rate rate(10); // frequency in Hz

	ROS_INFO("Alles klar!");

	tsdf_examiner::TsdfExaminer examiner(n, nh_private);
	//examiner.initialDebug();
	int i = 0;
	while(ros::ok()) {
		ros::spinOnce();
		rate.sleep();
		if (i == 100 || i == 101) {
			examiner.initialDebug(i);
		}
		ROS_ERROR("Line: %d", i);
		i++;
	}

}
