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
    ~Application();

    void run();

private:
    void getImage();
    void render(std::vector<DetectedCard> cards);

    bool useCamera;
    std::string inputImage, outputFile;

    cv::Mat frame, renderedFrame;
    cv::VideoCapture camera;

    std::fstream output;

    Detector detector;

    int cardGrid[3][3], previousGrid[3][3];
};
