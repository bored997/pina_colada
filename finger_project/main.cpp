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
	const std::string filename = "imgs/buck_family.jpg";//"imgs/static1.png";
    cv::Mat image{ cv::imread(filename) };
	
    if (!image.data)
    {
        std::cerr << "Could not open or find the image" << std::endl;
        return -1;
    }

    cv::Mat proc = image;
	skinDetect(&proc);
    //cv::cvtColor(image, proc, cv::COLOR_BGR2GRAY); // convert to gray

    /*
    Naive method. Doesn't work too well since fingers are multicolored.
    cv::GaussianBlur(proc, proc, cv::Size(25, 25), 0);
    cv::threshold(proc, proc, 160, 255, cv::ThresholdTypes::THRESH_BINARY);
    */

    //cv::Canny(proc, proc, 100, 130);
    
    const std::string imageWindow{ "openCV window" };
	cv::namedWindow(imageWindow, 200);//cv::WINDOW_AUTOSIZE); // Create a window for display.
    cv::imshow(imageWindow, proc); // Show our image inside it.

    cv::waitKey(0); // Wait for a keystroke in the window
    return 0;
}