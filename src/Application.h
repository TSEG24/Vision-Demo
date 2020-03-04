//
// Created by connor on 03/03/2020.
//
#pragma once
#include <string>
#include <fstream>
#include <utility>
#include <opencv.h>
#include <iostream>

#include "Detector.h"

class Application {
public:
    Application(bool useCamera, std::string outputFile);
    Application(bool useCamera, std::string outputFile, std::string inputImage);

    void run();

private:
    void getImage();
    void render(std::vector<DetectedCard> cards);

    void writeToFile(std::vector<DetectedCard> cards);

    bool useCamera;
    std::string inputImage, outputFile;

    cv::Mat frame, renderedFrame;
    cv::VideoCapture camera;

    std::ofstream output;

    Detector detector;

    int cardGrid[3][3], nextGrid[3][3];
};
