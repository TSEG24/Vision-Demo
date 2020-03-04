//
// Created by connor on 03/03/2020.
//
#include "Application.h"

Application::Application(bool useCamera, std::string outputFile) : camera(0) {
    this->useCamera = useCamera;
    this->outputFile = std::move(outputFile);

    std::memset(nextGrid, -1, sizeof nextGrid);
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

    std::memset(nextGrid, -1, sizeof nextGrid);
}

void Application::run() {
    while (true) {
        // set every index in cardGrid to -1 so we know it is not pointing to a valid
        // array index when we save the detected cards to the text file
        std::memset(cardGrid, -1, sizeof cardGrid);

        getImage();

        std::vector<DetectedCard> cards = detector.findCards(frame.clone());
        writeToFile(cards);
        render(cards);

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

void Application::render(std::vector<DetectedCard> cards) {
    renderedFrame = frame.clone();

    for (DetectedCard card : cards) {
        cv::rectangle(renderedFrame, card.outline, cv::Scalar(0, 0, 255));
    }

    // make the image smaller when displaying if it is large, wont affect any detection or output
    if (frame.cols > 1000) {
        cv::resize(renderedFrame, renderedFrame, cv::Size(), 0.5, 0.5);
    }
    cv::imshow("Output", renderedFrame);
}

void Application::writeToFile(std::vector<DetectedCard> cards) {
    bool shouldRightToFile = false;
    std::string outputText = "";

    for (size_t i = 0; i < cards.size(); i++) {
        int x = cards[i].gridLocation.x;
        int y = cards[i].gridLocation.y;

        if (cardGrid[x][y] != i) {
            nextGrid[x][y] = i;
            shouldRightToFile = true;
        }

        outputText += std::to_string(x) + "," + std::to_string(y) + "," + cards[i].colour + "\n";
    }

    std::copy(&nextGrid[0][0], &nextGrid[0][0] + 3 * 3, &cardGrid[0][0]);

    if (shouldRightToFile) {
        if (!output) {
            std::cerr << "File could not be opened: " << std::strerror(errno) << std::endl;
            return;
        }

        std::cout << "writing to file" << std::endl;
        output.open(this->outputFile, std::ofstream::out | std::ofstream::trunc);
        output << outputText;
        output.close();
    }
}
