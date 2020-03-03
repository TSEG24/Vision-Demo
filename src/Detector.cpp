//
// Created by connor on 03/03/2020.
//

#include "Detector.h"

std::vector<DetectedCard> Detector::findCards(cv::Mat image) {
    cv::Mat greyscaleImage, cannyOutput;
    cv::GaussianBlur(image, image, cv::Size(11,11), 0, 0);
    cv::cvtColor(image, greyscaleImage, cv::COLOR_BGR2GRAY);

    float threshold = 120.f;
    cv::Canny(greyscaleImage, cannyOutput, threshold, threshold * 2);
    std::vector<std::vector<cv::Point>> contours;
    cv::findContours(cannyOutput, contours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_NONE);

    // For each detected contour, create a rectangle object in its location and add it to the
    // detected card vector to be returned to renderer.
    std::vector<DetectedCard> detectedCards;
    for (auto contour : contours) {
        std::vector<cv::Point> contoursPoly;
        cv::approxPolyDP(contour, contoursPoly, 3, true);

        cv::Rect card = cv::boundingRect(contoursPoly);


        detectedCards.push_back(addCardData(card, image));
    }

    return detectedCards;
}

DetectedCard Detector::addCardData(cv::Rect roi, cv::Mat image) {
    return {
            cv::Point2i(
                    roi.tl().x + (roi.width / 2),
                    roi.br().y - (roi.height / 2)
            ),
            roi,
            detectCardColour(roi, image),
    };
}

std::string Detector::detectCardColour(cv::Rect card, cv::Mat image) {
    cv::Mat roi(image, card);
    cv::cvtColor(roi, roi, cv::COLOR_BGR2HSV);

    double redPercentage, blackPercentage;

    auto colourDetection = [](double& percentage, cv::Mat roi, std::vector<int> upperBound, std::vector<int> lowerBound) {
        cv::Mat mask;
        cv::inRange(roi, lowerBound, upperBound, mask);

        int imageSize = mask.rows * mask.cols;
        cv::threshold(mask, mask, 120, -1, cv::THRESH_TOZERO);

        percentage = 1 - (imageSize - cv::countNonZero(mask)) / (double )imageSize;
    };

    std::vector<int> lowerRed = { 0, 120, 70 }, upperRed = { 10, 255, 255 };
    colourDetection(redPercentage, roi, upperRed, lowerRed);

    std::vector<int> lowerBlack = { 0, 0, 0 }, upperBlack = { 180, 255, 125 };
    colourDetection(blackPercentage, roi, upperBlack, lowerBlack);

    if (redPercentage > blackPercentage) {
        return "Red";
    }

    return "Black";
}
