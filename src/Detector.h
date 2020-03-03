//
// Created by connor on 03/03/2020.
//
#pragma once
#include <vector>
#include <string>
#include <opencv.h>

struct DetectedCard {
    cv::Point2f coords;
    cv::Rect outline;
    std::string colour;
};

class Detector {
public:
    std::vector<DetectedCard> findCards(cv::Mat image);

private:
    DetectedCard addCardData(cv::Rect roi, cv::Mat image);
    std::string detectCardColour(cv::Rect card, cv::Mat image);

};
