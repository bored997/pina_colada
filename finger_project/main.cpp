#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>

using namespace cv;

void skinDetect(Mat * in) {
    Mat out;
    cvtColor(*in, out, COLOR_BGR2HSV);
    int threshold1 = 2;
    int threshold2 = 45;
    for (int i = 0; i < out.cols; i++) {
        for (int j = 0; j < out.rows; j++) {
            Vec3b & color = in->at<Vec3b>(Point(i, j));
            int h = out.at<Vec3b>(Point(i, j))[0]; 
            if (threshold1 <= h && h <= threshold2) {
                color[0] = 255;
                color[1] = 255;
                color[2] = 255;
            }
            else {
                color[0] = 0;
                color[1] = 0;
                color[2] = 0;
            }
        }
    }
}

int main()
{
    const std::string filename = "imgs/static4.png";
    cv::Mat image{ cv::imread(filename) };
    
    if (!image.data)
    {
        std::cerr << "Could not open or find the image" << std::endl;
        return -1;
    }

    cv::Mat hsv;
    cv::cvtColor(image, hsv, cv::COLOR_BGR2HSV);
    cv::GaussianBlur(hsv, hsv, cv::Size(7, 7), 0);

    cv::Mat outLow;
    cv::Mat outHigh;
    cv::inRange(hsv, cv::Scalar(0, 70, 0), cv::Scalar(21, 255, 255), outLow);
    cv::inRange(hsv, cv::Scalar(160, 70, 0), cv::Scalar(180, 255, 255), outHigh);

    cv::Mat out;
    cv::addWeighted(outLow, 1.0, outHigh, 1.0, 0.0, out);
    cv::dilate(out, out, 0);
   
    const std::string windowOne = "test one";
    const std::string windowTwo = "test two";
    cv::namedWindow(windowOne, cv::WINDOW_AUTOSIZE);
    cv::imshow(windowOne, out);
    cv::namedWindow(windowTwo, cv::WINDOW_AUTOSIZE);

    cv::waitKey(0);
    return 0;
}