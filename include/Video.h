//
// Created by toadkarter on 07/09/22.
//

#ifndef FILMANALYSIS_VIDEO_H
#define FILMANALYSIS_VIDEO_H

#include <opencv2/core/matx.hpp>
#include <opencv2/videoio.hpp>
#include <filesystem>
#include <map>
#include "Frame.h"


class Video {
public:
    explicit Video(const std::filesystem::path& video_path);

    std::map<std::array<int, 3>, double> color_frequencies();
    int total_pixels() const;

private:
    void GenerateColorFrequencies();
    void GenerateAllColorFrequencies();
    void GenerateColorsFromFrame(cv::Mat current_frame);
    void UpdateColorFrequencies(Frame frame, int x, int y);
    void DeleteRareColors();

    cv::VideoCapture video_;
    std::map<std::array<int, 3>, double> color_frequencies_;
    int total_pixels_;
};

#endif //FILMANALYSIS_VIDEO_H
