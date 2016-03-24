#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>

int main()
{
    const std::string filename = "imgs/image.png";
    cv::Mat image{ cv::imread(filename, CV_RGB2RGBA) };

    if (!image.data)
    {
        std::cerr << "Could not open or find the image" << std::endl;
        return -1;
    }

    const std::string imageWindow{ "openCV window" };
    cv::namedWindow(imageWindow, cv::WINDOW_AUTOSIZE); // Create a window for display.
    cv::imshow(imageWindow, image); // Show our image inside it.

    cv::waitKey(0); // Wait for a keystroke in the window
    return 0;
}