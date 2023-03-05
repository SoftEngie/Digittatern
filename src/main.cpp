#include <opencv2/opencv.hpp>
#include <fstream>
#include <iostream>

int main()
{
    // Read in lena_gray.raw as a grayscale image
    cv::Mat lena = cv::imread("resources/lena_gray.bmp", cv::IMREAD_GRAYSCALE);
    
    if (lena.empty()){
        std::cout << "Image lena_gray.raw could not be found" << std::endl;
        return -1;  
    }
    // Apply Canny edge detection algorithm
    cv::Mat edges;
    cv::Canny(lena, edges, 50, 200);

    // Display the edge image
    cv::imshow("Edges", edges);
    cv::waitKey();

    return 0;
}
