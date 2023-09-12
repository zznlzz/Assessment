#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

Mat mask(Mat src);
Mat ColorProcess(Mat _frame);

int main(int argc,char** argv)
{
    Mat src, dst;
    src = imread("../assets/src.jpg");
    resize(src, src, Size(0, 0), 0.25, 0.25);
    imshow("src", src);
    dst = mask(src);
    imshow("dst", dst);
    waitKey(0);
    return 0;
}

Mat mask(Mat src)
{
    Mat dst, img;
    img = src.clone();

    dst = ColorProcess(src);
    Mat element_open = getStructuringElement(MORPH_ELLIPSE, Point(3,3));
    // Mat element_close = getStructuringElement(MORPH_ELLIPSE, Point(15,15));
    morphologyEx (dst, dst, MORPH_OPEN,  element_open);// 开运算
    // imshow("开运算", dst);
    // // morphologyEx (dst, dst, MORPH_CLOSE, element_close);// 闭运算
    // imshow("闭运算", dst);
    // // img = detectAndDrawCorners(dst);

    // 找轮廓
    vector<vector<Point>> contours;
    vector<Vec4i> hierarchy;
    findContours(dst,contours,hierarchy,RETR_CCOMP,CHAIN_APPROX_NONE);

    // 找凸包
    std::vector<std::vector<cv::Point> > hull(contours.size());
    for (int i = 0; i < contours.size(); i++)
    {
        double lengh = arcLength(contours[i], true);
        // std::cout << lengh << endl;
        if (lengh > 900){
            cv::convexHull(cv::Mat(contours[i]), hull[0], false);
        }
    }

    //多边形拟合
    approxPolyDP(hull[0], hull[0], 1, true); 

    drawContours(img, hull, 0, cv::Scalar(255,0,0), 2);

    // 计算每个点与相邻点之间的角度
    vector<Point> points = hull[0];
    vector<double> angles;
    for(int j=0;j<points.size();j++)
    {
        Point p1 = points[j];
        Point p2 = points[(j+1)%points.size()];
        Point p3 = points[(j+2)%points.size()];
        double angle = atan2(p2.y-p1.y,p2.x-p1.x)-atan2(p3.y-p2.y,p3.x-p2.x);
        if(angle<0) angle = 2*CV_PI+angle;
        angles.push_back(angle);
    }

    vector<pair<double, int>> angleIndexPairs;

    for (int i = 0; i < angles.size(); i++) {
        angleIndexPairs.push_back(make_pair(angles[i], i));
    }

    sort(angleIndexPairs.begin(), angleIndexPairs.end());

    vector<int> smallestIndices;
    for (int i = 0; i < 4; i++) {
        smallestIndices.push_back(angleIndexPairs[i].second);
    }

    // 角度最小四个点;
    vector<Point2f>result(4);
    for (int i = 0; i < 4; i++) {
        result[i] = points[smallestIndices[i]];
        circle(img,result[i],3,Scalar(0,80*i,80*i),-1);
    }
    // imshow("1", img);

    cv::Mat image;

    vector<Point2f>dst_coners(4);
	dst_coners[0] = Point2f(0, 0);
	dst_coners[1] = Point2f(90*4, 170*4-10);
	dst_coners[2] = Point2f(0, 170*4);
	dst_coners[3] = Point2f(90*4-5, 0);
	Mat warpMatrix = getPerspectiveTransform(result, dst_coners);
	warpPerspective(src, image, warpMatrix, dst.size(), INTER_LINEAR, BORDER_CONSTANT);
    image = image(cv::Rect(0,0,90*4,170*4));
    
    return image;
}


Mat ColorProcess(Mat _frame)
{
	Mat imgHsv;
	cvtColor(_frame, imgHsv, COLOR_BGR2HSV);
	vector<Mat> splitHSV;
	split(imgHsv, splitHSV);
	equalizeHist(splitHSV[2], splitHSV[2]);
	merge(splitHSV, imgHsv);
	Mat mask;
	Scalar low = Scalar(0, 0, 200); // H S V
	Scalar high = Scalar(180, 150, 255);
	inRange(imgHsv, low, high, mask);
	return mask;
}
