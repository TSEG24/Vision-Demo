//
// Created by connor on 03/03/2020.
// This file is required to bring opencv into the project as the
// include headers will be different depending on how opencv was
// installed. This is most noticeable when ran on different operating
// systems. e.g. linux includes are likely to be different from windows
//

#pragma once

#ifdef _WIN32
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/videoio.hpp>
#else
#include <opencv2/opencv.hpp>
#endif