//
// Created by connor on 03/03/2020.
//
#include <opencv.h>

int main() {
    cv::VideoCapture camera(0);
    cv::Mat frame;

    while (true) {
        camera >> frame;

        cv::imshow("Camera", frame);
        if (cv::waitKey(30) >= 0) break;
    }

    return 0;
}
