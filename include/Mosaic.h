//
// Created by toadkarter on 08/09/22.
//

#ifndef FILMANALYSIS_MOSAIC_H
#define FILMANALYSIS_MOSAIC_H

#include "Video.h"

cv::Mat CreateMosaicFromVideo(Video video);
void SaveMosaic(const cv::Mat& mosaic, const std::string& filepath);

#endif //FILMANALYSIS_MOSAIC_H
