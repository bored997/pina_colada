#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>

int main()
{
    const std::string filename = "imgs/static1.png";
    cv::Mat image{ cv::imread(filename) };

    if (!image.data)
    {
        std::cerr << "Could not open or find the image" << std::endl;
        return -1;
    }

    cv::Mat hsv;
    cv::cvtColor(image, hsv, cv::COLOR_BGR2HSV); // convert to hsv

    cv::Mat out;

    cv::inRange(hsv, cv::Scalar(0, 53, 100), cv::Scalar(21, 255, 255), out);
    
    const std::string imageWindow{ "openCV window" };
    cv::namedWindow(imageWindow, cv::WINDOW_AUTOSIZE); // Create a window for display.
    cv::imshow(imageWindow, out); // Show our image inside it.

    cv::waitKey(0); // Wait for a keystroke in the window
    return 0;
}