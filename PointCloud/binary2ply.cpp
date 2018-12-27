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


// �����������
typedef pcl::PointXYZ PointT;
typedef pcl::PointCloud<PointT> PointCloud;

// ����ڲ�
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
	// ͼ�����
	cv::Mat a;

	// ���Ʊ���
	// ʹ������ָ�룬����һ���յ��ơ�����ָ��������Զ��ͷš�
	PointCloud::Ptr cloud(new PointCloud);

	//ѭ������ÿ�Ŷ�ֵͼ
	int i, m, n;
	for (i = 270; i <= 424; ++i) {
		// ʹ��cv::imread()����ȡͼ�� 8UC1
		a = cv::imread("0"+ to_string(i) +".png", -1);

		//cout << i << " " << a.rows << " " << a.cols << endl;

		// ����ͼƬ
		for (m = 0; m < 256; m++) {
			for (n = 0; n < 256; n++)
			{
				// ��ȡ���ͼ��(m,n)����ֵ
				ushort d = a.ptr<ushort>(m)[n];

				// d ����û��ֵ������ˣ������˵�
				if (d == 0) {
					continue;
				}

				// d ����ֵ�������������һ����
				PointT p;

				// ���������Ŀռ�����
				p.z = (424-i)/320.0;
				p.x = n /100.0;
				p.y = m /100.0;

				// ��p���뵽������
				cloud->points.push_back(p);

			}
		}
		//���ٴ�����ͼ�������
		//count--;
	}

	// ���ò��������
	cloud->height = 1;
	cloud->width = cloud->points.size();
	std::cout << "point cloud size = " << cloud->points.size() << endl;
	cloud->is_dense = false;
	pcl::io::savePCDFile("pointcloud.pcd", *cloud);

	string input_filename = ".//pointcloud.pcd";
	string output_filename = ".//pc.ply";
	PCDtoPLYconvertor(input_filename, output_filename);

	// ������ݲ��˳�c
	cloud->points.clear();
	std::cout << "Point cloud saved." << endl;
	return 0;
}