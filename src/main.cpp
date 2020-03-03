//
// Created by connor on 03/03/2020.
//
#include <string>
#include <cstring>
#include "Application.h"

int main(int argc, char** argv) {
    bool useCamera = false;
    std::string outputFile, inputFile;

    // Start at one as the first arg will always be the executable name
    for (size_t i = 1; i < argc; i++) {
        // Detect if we should use camera
        if (std::strcmp("-camera" , argv[i]) == 0) {
            useCamera = true;
        }
        else if (std::strcmp("-o", argv[i]) == 0) {
            outputFile = argv[++i];
        }
        else if (std::strcmp("-i", argv[i]) == 0) {
            inputFile = argv[++i];
        }
    }

    if (useCamera) {
        assert(!outputFile.empty());

        Application app(true, outputFile);
        app.run();
    } else {
        assert(!outputFile.empty());
        assert(!inputFile.empty());

        Application app(false, outputFile, inputFile);
        app.run();
    }

    return 0;
}
