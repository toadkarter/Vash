//
// Created by toadkarter on 08/09/22.
//

#include "Mosaic.h"
#include <iostream>

cv::Mat CreateMosaicFromVideo(Video video) {
    auto color_frequencies = video.color_frequencies();
    int total_pixels = video.total_pixels();

    cv::Mat mosaic(5000, 5000, CV_8UC3, cv::Vec3b(0, 0, 0));

    int current_column_counter = 0;

    for (auto const& current_color: color_frequencies) {
        int number_of_pixels_to_occupy = (int)(current_color.second / total_pixels * 5000);
        cv::Vec3b color_to_insert(current_color.first[0], current_color.first[1], current_color.first[2]);

        for (int i = 0; i < number_of_pixels_to_occupy; i++) {
            for (int j = 0; j < mosaic.rows; j++) {
                mosaic.at<cv::Vec3b>(j, current_column_counter + i) = color_to_insert;
            }
            current_column_counter++;
        }

    }
    return mosaic;
}

void SaveMosaic(const cv::Mat& mosaic, const std::string& filepath) {
    cv::imwrite(filepath, mosaic);
}