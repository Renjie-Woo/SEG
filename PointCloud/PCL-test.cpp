#include<iostream>
#include<pcl/io/pcd_io.h>
#include<pcl/point_types.h>
#include<pcl/point_cloud.h>
#include <pcl/visualization/cloud_viewer.h>

//查看pcd文件

int main(int argc, char *argv[])
{
	pcl::PointCloud<pcl::PointXYZ>::Ptr  cloud(new pcl::PointCloud<pcl::PointXYZ>);
	pcl::io::loadPCDFile<pcl::PointXYZ>("pointcloud.pcd", *cloud);

	if (pcl::io::loadPCDFile<pcl::PointXYZ>("pointcloud.pcd", *cloud) == -1)
	{
		std::cout << "Cloud reading failed." << std::endl;
		return (-1);
	}

	//std::cout << cloud->width << std::endl;
	//std::cout << cloud->height;

	pcl::visualization::CloudViewer viewer("Simple Cloud Viewer");
	viewer.showCloud(cloud);
	while (!viewer.wasStopped())
	{
	}
	system("pause");
	return (0);
}