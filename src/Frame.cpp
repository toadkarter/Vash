//
// Created by toadkarter on 07/09/22.
//

#include "Frame.h"
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <iostream>
#include <utility>

Frame::Frame(cv::Mat frame) {
    pixels_ = ReduceColors(std::move(frame));
}

// https://stackoverflow.com/questions/34734379/is-there-a-formula-to-determine-overall-color-given-bgr-values-opencv-and-c/34734939#34734939
cv::Mat Frame::ReduceColors(cv::Mat frame) {
    int k = 8;
    int n = frame.rows * pixels_.cols;
    cv::Mat data = frame.reshape(1, n);
    data.convertTo(data, CV_32F);

    std::vector<int> labels;
    cv::Mat1f colors;

    cv::kmeans(data, k, labels, cv::TermCriteria(), 1, cv::KMEANS_PP_CENTERS, colors);

    for (int i = 0; i < n; ++i) {
        data.at<float>(i, 0) = colors(labels[i], 0);
        data.at<float>(i, 1) = colors(labels[i], 1);
        data.at<float>(i, 2) = colors(labels[i], 2);
    }

    cv::Mat reduced = data.reshape(3, frame.rows);
    reduced.convertTo(reduced, CV_8U);

    return reduced;
}

cv::Mat Frame::pixels() {
    return pixels_;
}

std::array<int, 3> Frame::GetColorAtPixel(int x, int y) {
    int r = pixels_.at<cv::Vec3b>(x, y)[0];
    int g = pixels_.at<cv::Vec3b>(x, y)[1];
    int b = pixels_.at<cv::Vec3b>(x, y)[2];

    return {r, g, b};
}
