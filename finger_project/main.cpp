#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>

int main()
{
    const std::string filename = "imgs/static2.png";
    cv::Mat image{ cv::imread(filename) };

    if (!image.data)
    {
        std::cerr << "Could not open or find the image" << std::endl;
        return -1;
    }

    cv::Mat hsv;
    cv::cvtColor(image, hsv, cv::COLOR_BGR2HSV); // convert to hsv

    cv::Mat lowerSkinRange;
    cv::Mat upperSkinRange;
    cv::inRange(hsv, cv::Scalar(15, 53, 100), cv::Scalar(20, 255, 255), lowerSkinRange);
    cv::inRange(hsv, cv::Scalar(25, 100, 100), cv::Scalar(30, 255, 255), upperSkinRange);

    cv::Mat out;

    cv::addWeighted(lowerSkinRange, 1.0, upperSkinRange, 1.0, 0.0, out);
    /*
    Naive method. Doesn't work too well since fingers are multicolored.
    cv::GaussianBlur(proc, proc, cv::Size(25, 25), 0);
    cv::threshold(proc, proc, 160, 255, cv::ThresholdTypes::THRESH_BINARY);
    */
    
    const std::string imageWindow{ "openCV window" };
    cv::namedWindow(imageWindow, cv::WINDOW_AUTOSIZE); // Create a window for display.
    cv::imshow(imageWindow, out); // Show our image inside it.

    cv::waitKey(0); // Wait for a keystroke in the window
    return 0;
}