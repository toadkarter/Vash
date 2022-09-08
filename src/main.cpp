//
// Created by toadkarter on 07/09/22.
//

#include "Frame.h"
#include "Video.h"
#include <iostream>

int main() {
    Video video("/home/toadkarter/videoplayback.mp4");
    video.GetAllColors();
    return 0;
}