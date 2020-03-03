//
// Created by connor on 03/03/2020.
//
#include <opencv.h>
#include "Application.h"

int main() {
    Application app(true, "output.txt");
    app.run();

    return 0;
}
