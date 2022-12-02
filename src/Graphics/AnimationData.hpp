#pragma once

#include <vector>

struct AnimationDataFrame {
    AnimationDataFrame(int offset_x, int offset_y, int u, int v, int w, int h);
    ~AnimationDataFrame();
    int offset_x, offset_y, u, v, w, h;
};

class AnimationData {
    public:
        void addFrame(int offset_x, int offset_y, int u, int v, int w, int h);
        void addFrames(int u, int v, int w, int h, int frame_h, int frame_c);
        AnimationDataFrame* getFrameData(int i); 
        AnimationDataFrame getFrame(int i); 
        int getFrameAmount();
    private:
        std::vector<AnimationDataFrame> frames;
        int frame_count = 0;
};