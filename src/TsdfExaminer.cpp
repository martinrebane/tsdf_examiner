#include "TsdfExaminer.h"

namespace tsdf_examiner {

TsdfExaminer::TsdfExaminer(const ros::NodeHandle& nh,
		const ros::NodeHandle& nh_private):
			nh_(nh),
			nh_private_(nh_private),
			tsdf_server_(nh_, nh_private_),
			step(0)
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

void TsdfExaminer::continuousScanTsdfSaver(const sensor_msgs::PointCloud2::Ptr& pointcloud) {
	ROS_INFO("--------------- INTEGRATING POINTCLOUD ----------------");
	// insert pointcloud to TSDF
	// arg: const sensor_msgs::PointCloud2::Ptr& pointcloud
	tsdf_server_.insertPointcloud(pointcloud);

	// save off the TSDF map
	tsdf_server_.saveMap("/home/martin/jtmp/map/tsdf_" + std::to_string(step) + ".vxblx");
	step++;
}

void TsdfExaminer::oneScanTsdfSaver(const sensor_msgs::PointCloud2::Ptr& pointcloud) {
	ROS_INFO("--------------- MAPPING SINGLE POINTCLOUD ----------------");
	// clear TSDF map
	tsdf_server_.clear();
	tsdf_server_.insertPointcloud(pointcloud);
	tsdf_server_.saveMap("/home/martin/jtmp/map/tsdf_tmp_" + std::to_string(step) + ".vxblx");
	step++;
}

}


int main(int argc, char** argv) {
	ros::init(argc, argv, "tsdf_examiner");
	ros::NodeHandle n;
	ros::NodeHandle nh_private("~");

	ros::Rate rate(10); // frequency in Hz

	ROS_INFO("Alles klar! Args .%s.", argv[1]);

	tsdf_examiner::TsdfExaminer examiner(n, nh_private);

	std::string map_mode = argv[1];

	//ros::Duration(5.0).sleep();
	ros::Subscriber sub;
	// listen to incoming pointcloud and register callback for it
	if (map_mode == "single") {
		// save only one scan
		ROS_INFO("subscribe oneScanTsdfSaver");
		sub = n.subscribe("/velodyne_points", 1000, &tsdf_examiner::TsdfExaminer::oneScanTsdfSaver, &examiner);
	} else {
		// integrate scans
		ROS_INFO("subscribe continuousScanTsdfSaver");
		sub = n.subscribe("/velodyne_points", 1000, &tsdf_examiner::TsdfExaminer::continuousScanTsdfSaver, &examiner);
	}

	int i = 0;
	while(ros::ok()) {
		ros::spinOnce();
		rate.sleep();
		if (i == 100 || i == 101) {
			//examiner.initialDebug(i);
		}
		ROS_ERROR("Line: %d", i);
		i++;
	}

	return 0;

}
