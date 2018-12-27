#include <iostream>
#include <string>
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <pcl/io/pcd_io.h>
#include <pcl/point_types.h>
#include <pcl/io/ply_io.h>
#include <pcl/PCLPointCloud2.h>

using namespace std;
using namespace cv;


// 定义点云类型
typedef pcl::PointXYZ PointT;
typedef pcl::PointCloud<PointT> PointCloud;

// 相机内参
const double camera_factor = 1000;
const double camera_cx = 325.5;
const double camera_cy = 253.5;
const double camera_fx = 518.0;
const double camera_fy = 519.0;


int PCDtoPLYconvertor(string & input_filename, string& output_filename)
{
	pcl::PCLPointCloud2 cloud;
	if (pcl::io::loadPCDFile(input_filename, cloud) < 0)
	{
		cout << "Error: cannot load the PCD file!!!" << endl;
		return -1;
	}
	pcl::PLYWriter writer;
	writer.write(output_filename, cloud, Eigen::Vector4f::Zero(), Eigen::Quaternionf::Identity(), true, true);
	return 0;

}

int main(int argc, char** argv)
{
	// 图像矩阵
	cv::Mat a;

	// 点云变量
	// 使用智能指针，创建一个空点云。这种指针用完会自动释放。
	PointCloud::Ptr cloud(new PointCloud);

	//循环处理每张二值图
	int i, m, n;
	for (i = 270; i <= 424; ++i) {
		// 使用cv::imread()来读取图像 8UC1
		a = cv::imread("0"+ to_string(i) +".png", -1);

		//cout << i << " " << a.rows << " " << a.cols << endl;

		// 遍历图片
		for (m = 0; m < 256; m++) {
			for (n = 0; n < 256; n++)
			{
				// 获取深度图中(m,n)处的值
				ushort d = a.ptr<ushort>(m)[n];

				// d 可能没有值，若如此，跳过此点
				if (d == 0) {
					continue;
				}

				// d 存在值，则向点云增加一个点
				PointT p;

				// 计算这个点的空间坐标
				p.z = (424-i)/320.0;
				p.x = n /100.0;
				p.y = m /100.0;

				// 把p加入到点云中
				cloud->points.push_back(p);

			}
		}
		//减少待处理图像的数量
		//count--;
	}

	// 设置并保存点云
	cloud->height = 1;
	cloud->width = cloud->points.size();
	std::cout << "point cloud size = " << cloud->points.size() << endl;
	cloud->is_dense = false;
	pcl::io::savePCDFile("pointcloud.pcd", *cloud);

	string input_filename = ".//pointcloud.pcd";
	string output_filename = ".//pc.ply";
	PCDtoPLYconvertor(input_filename, output_filename);

	// 清除数据并退出c
	cloud->points.clear();
	std::cout << "Point cloud saved." << endl;
	return 0;
}