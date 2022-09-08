//
// Created by toadkarter on 07/09/22.
//

#ifndef FILMANALYSIS_FRAME_H
#define FILMANALYSIS_FRAME_H

#include <filesystem>
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>

class Frame {
public:
    explicit Frame(cv::Mat frame);
    cv::Mat pixels();
    std::array<int, 3> GetColorAtPixel(int x, int y);
private:
    cv::Mat ReduceColors(cv::Mat frame);
    cv::Mat pixels_;
};


#endif //FILMANALYSIS_FRAME_H
