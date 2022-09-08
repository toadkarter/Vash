//
// Created by toadkarter on 07/09/22.
//

#include "Video.h"
#include "Mosaic.h"

int main() {
    Video video("/home/toadkarter/videoplayback.mp4");

    cv::Mat mosaic = CreateMosaicFromVideo(video);
    SaveMosaic(mosaic, "mosaic.png");

    return 0;
}