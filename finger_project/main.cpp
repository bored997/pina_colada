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

    cv::Mat proc;
    cv::cvtColor(image, proc, cv::COLOR_BGR2GRAY); // convert to gray

    /*
    Naive method. Doesn't work too well since fingers are multicolored.
    cv::GaussianBlur(proc, proc, cv::Size(25, 25), 0);
    cv::threshold(proc, proc, 160, 255, cv::ThresholdTypes::THRESH_BINARY);
    */

    cv::Canny(proc, proc, 100, 130);
    
    const std::string imageWindow{ "openCV window" };
    cv::namedWindow(imageWindow, cv::WINDOW_AUTOSIZE); // Create a window for display.
    cv::imshow(imageWindow, proc); // Show our image inside it.

    cv::waitKey(0); // Wait for a keystroke in the window
    return 0;
}