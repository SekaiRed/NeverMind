#pragma once

#include <vector>
#include <fstream>
#include <nlohmann/json.hpp>
#include "Animation.hpp"

using json = nlohmann::json;

namespace Loader {
    static json frameToJson(const Animation::Frame& f) {
        json j;
        if(f.duration.has_value()) j["delay"] = f.duration.value();
        if(f.u.has_value()) j["u"] = f.u.value();
        if(f.v.has_value()) j["v"] = f.v.value();
        if(f.w.has_value()) j["w"] = f.w.value();
        if(f.h.has_value()) j["h"] = f.h.value();
        if(f.x.has_value()) j["x"] = f.x.value();
        if(f.y.has_value()) j["y"] = f.y.value();
        return j;
    }

    static Animation::Frame frameFromJson(const json& j) {
        Animation::Frame f;
        //ifj.contains("delay")
        auto jiter = j.begin();
        while (jiter != j.end()) {
            if(jiter.key() == "delay") f.duration = jiter.value().get<sf::Int64>();
            if(jiter.key() == "u") f.u = jiter.value().get<int>();
            if(jiter.key() == "v") f.v = jiter.value().get<int>();
            if(jiter.key() == "w") f.w = jiter.value().get<int>();
            if(jiter.key() == "h") f.h = jiter.value().get<int>();
            if(jiter.key() == "x") f.x = jiter.value().get<float>();
            if(jiter.key() == "y") f.y = jiter.value().get<float>();
            jiter++;
        }
        return f;
    }

    static json animationToJson(Animation& a) {
        json j;
        j["delay"] = a.getGlobalDuration();
        //auto frames = j["frames"].array();
        for(int i = 0; i < a.getLength(); i++) {
            //frames.push_back(frameToJson(a.getFrame(i)));
            j["frames"].push_back(frameToJson(a.getFrame(i)));
        }
        return j;
    }

    static Animation animationFromJson(json& j) {
        //Animation a(sf::microseconds(j["delay"].get<unsigned int>()));
        Animation a(j["delay"].get<sf::Int64>());
        auto jiter = j["frames"].begin();
        while (jiter != j["frames"].end()) {
            a.addFrame(frameFromJson(jiter.value()));
            jiter++;
        }
        return a;
    }

    /*static void debug() {
        Animation::Frame fram;
        fram.u = 64;
        json j = {
            {"delay", 20},
            {"frames", {
                    frameToJson(Animation::Frame{sf::milliseconds(0),0,0,32,32,0,0}),
                    frameToJson(Animation::Frame{sf::milliseconds(0),32,0,32,32,0,0}),
                    frameToJson(fram)
                }
            }
        };
        Animation anim(sf::microseconds(20));
        anim.addFrame(Animation::Frame{sf::milliseconds(0),0,0,32,32,0,0});
        anim.addFrame(Animation::Frame{sf::milliseconds(0),32,0,32,32,0,0});
        Animation::Frame fram;
        fram.u = 64;
        anim.addFrame(fram);
        json j = animationToJson(anim);
        Animation anim2 = animationFromJson(j);
        json j2 = animationToJson(anim2);
        std::cout << std::setw(4) << j2 << std::endl;
        //std::vector<Animation::Frame> frames;
        Animation::Frame f{sf::milliseconds(0),0,0,0,0,0,0};
        jframes.push_back(f);
        j["delay"] = 140;
        //j["frames"] = frames;
        std::cout << std::setw(4) << j << std::endl;
    }*/

    static Animation loadAnimation(std::string filename) {
        std::ifstream file;
        file.open(filename);
        json j = json::parse(file);
        Animation anim = animationFromJson(j);
        return anim;
    }
}

/*{
    "delay": 20,
    "frames": [
        {
            "delay": 0,
            "h": 32,
            "u": 0,
            "v": 0,
            "w": 32,
            "x": 0.0,
            "y": 0.0
        },
        {
            "delay": 0,
            "h": 32,
            "u": 32,
            "v": 0,
            "w": 32,
            "x": 0.0,
            "y": 0.0
        },
        {
            "u": 64
        }
    ]
}*/