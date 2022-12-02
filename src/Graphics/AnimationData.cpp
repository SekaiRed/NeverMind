#include "AnimationData.hpp"

#include <iostream>

AnimationDataFrame::AnimationDataFrame(int offset_x, int offset_y, int u, int v, int w, int h) {
    this->offset_x = offset_x;
    this->offset_y = offset_y;
    this->u = u;
    this->v = v;
    this->w = w;
    this->h = h;
}

AnimationDataFrame::~AnimationDataFrame() {
    //std::cout << "free " << u << "," << v << "," << w << "," << h << "," << offset_x << "," << offset_y << "\n";
}

void AnimationData::addFrame(int offset_x, int offset_y, int u, int v, int w, int h) {
    frames.push_back(AnimationDataFrame(offset_x, offset_y, u, v, w, h));
    frame_count++;
}
void AnimationData::addFrames(int u, int v, int w, int h, int frame_h, int frame_c) {
    //std::cout << u << "," << v << "," << w << "," << h << "," << frame_h << "," << frame_c << "\n";
    for(int i = 0; i < frame_c; i++) {
        //std::cout << "\t" << i << " : " << u + (i%frame_h) * w << " and " << v + (i/frame_h) * h << "\n";
        addFrame(0, 0, u + (i%frame_h) * w, v + (i/frame_h) * h, w, h);
        //std::cout << "\t" << getFrame(i).u << " and " << getFrame(i).v << "\n";
    }
}
AnimationDataFrame* AnimationData::getFrameData(int i) {
    return &frames.at(i);
}
AnimationDataFrame AnimationData::getFrame(int i) {
    return frames.at(i);
}
int AnimationData::getFrameAmount() {
    return frame_count;
}