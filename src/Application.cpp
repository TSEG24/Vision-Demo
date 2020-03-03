//
// Created by connor on 03/03/2020.
//
#include "Application.h"

Application::Application(bool useCamera, std::string outputFile) : camera(0) {
    this->useCamera = useCamera;
    this->outputFile = std::move(outputFile);
    output.open(this->outputFile);
}

Application::Application(bool useCamera, std::string outputFile, std::string inputImage) {
    // This constructor is used to load a file from the input file instead of camera,
    // if useCamera is true then this will cause problems so we will exit here instead
    if (useCamera) {
        std::cerr << "Use camera is true and an input file has been added. Only one of these can be used at a time" << std::endl;
        assert(!useCamera);
    }

    this->useCamera = useCamera;
    this->outputFile = std::move(outputFile);
    this->inputImage = std::move(inputImage);
    output.open(this->outputFile);
}

Application::~Application() {
    output.close();
}

void Application::run() {
    while (true) {
        getImage();

        cv::imshow("Output", frame);

        if (cv::waitKey(30) >= 0) break;
    }
}

void Application::getImage() {
    if (useCamera) {
        camera >> frame;
        return;
    }

    // We only want to read this file once so will only read it if the image object
    // is detected as empty
    if (frame.empty()) {
        std::cout << "Reading input file" << std::endl;
        frame = cv::imread(inputImage);
    }
}