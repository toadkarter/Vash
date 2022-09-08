//
// Created by toadkarter on 07/09/22.
//

#include "Video.h"
#include "Frame.h"
#include <utility>
#include <array>
#include <iostream>

Video::Video(const std::filesystem::path& video_path) {
    video_ = cv::VideoCapture(video_path);

    double length = video_.get(cv::VideoCaptureProperties::CAP_PROP_FRAME_COUNT);
    double width = video_.get(cv::VideoCaptureProperties::CAP_PROP_FRAME_WIDTH);
    double height = video_.get(cv::VideoCaptureProperties::CAP_PROP_FRAME_HEIGHT);

    total_pixels_ = (int)(length * width * height);

    GenerateColorFrequencies();
}

std::map<std::array<int, 3>, double> Video::color_frequencies() {
    return color_frequencies_;
}

int Video::total_pixels() const {
    return total_pixels_;
}

void Video::GenerateColorFrequencies() {
    GenerateAllColorFrequencies();
    DeleteRareColors();
}

void Video::GenerateAllColorFrequencies() {
    while (video_.isOpened()) {
        cv::Mat current_frame;
        bool frameRead = video_.read(current_frame);

        if (frameRead) {
            GenerateColorsFromFrame(current_frame);
        } else {
            break;
        }
    }
}

void Video::GenerateColorsFromFrame(cv::Mat current_frame) {
    Frame frame(std::move(current_frame));
    cv::Mat pixels = frame.pixels();

    for (int i = 0; i < pixels.rows - 1; ++i) {
        for (int j = 0; j < pixels.cols - 1; ++j) {
            UpdateColorFrequencies(frame, i, j);
        }
    }
}

void Video::UpdateColorFrequencies(Frame frame, int x, int y) {
    std::array<int, 3> current_color = frame.GetColorAtPixel(x, y);
    if (color_frequencies_.find(current_color) == color_frequencies_.end()) {
        color_frequencies_[current_color] = 1;
    } else {
        color_frequencies_[current_color] += 1;
    }
}

void Video::DeleteRareColors() {
    int final_color_count = total_pixels_;

    for (auto const& current_color: color_frequencies_) {
        double number_of_pixels_to_occupy = current_color.second / total_pixels_ * 5000;
        if (number_of_pixels_to_occupy < 1) {
            final_color_count -= current_color.second;
            color_frequencies_.erase(current_color.first);
        }
    }
    total_pixels_ = final_color_count;
}




