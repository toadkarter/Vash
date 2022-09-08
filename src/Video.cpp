//
// Created by toadkarter on 07/09/22.
//

#include "Video.h"
#include "Frame.h"
#include <iostream>
#include <utility>
#include <array>

Video::Video(const std::filesystem::path& video_path) {
    video_ = cv::VideoCapture(video_path);

    double length = video_.get(cv::VideoCaptureProperties::CAP_PROP_FRAME_COUNT);
    double width = video_.get(cv::VideoCaptureProperties::CAP_PROP_FRAME_WIDTH);
    double height = video_.get(cv::VideoCaptureProperties::CAP_PROP_FRAME_HEIGHT);

    total_pixels_ = (int)(length * width * height);
}

void Video::GenerateColorFrequencies() {
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

void Video::GetAllColors() {
    GenerateColorFrequencies();

    int final_color_count = total_pixels_;

    for (auto const& current_color: color_frequencies_) {
        double number_of_pixels_to_occupy = current_color.second / total_pixels_ * 5000;
        if (number_of_pixels_to_occupy < 1) {
            final_color_count -= current_color.second;
            color_frequencies_.erase(current_color.first);
        }
    }

    cv::Mat new_mat(5000, 5000, CV_8UC3, cv::Vec3b(0, 0, 0));

    int current_column_counter = 0;

    for (auto const& current_color: color_frequencies_) {
        double number_of_pixels_to_occupy = current_color.second / final_color_count * 5000;
        if (number_of_pixels_to_occupy > 1) {

            cv::Vec3b color_to_insert(current_color.first[0], current_color.first[1], current_color.first[2]);

            for (int i = 0; i < (int)number_of_pixels_to_occupy; i++) {
                for (int j = 0; j < new_mat.rows; j++) {
                    new_mat.at<cv::Vec3b>(j, current_column_counter + i) = color_to_insert;
                }
                current_column_counter++;
            }

            std::cout << current_column_counter << std::endl;
        }
    }
    std::cout << "Saving Pic" << std::endl;
    cv::imwrite("pic.png", new_mat);
}


