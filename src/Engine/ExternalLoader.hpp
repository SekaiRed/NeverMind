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
        if(f.flipX.has_value()) j["flipX"] = f.flipX.value();
        if(f.flipY.has_value()) j["flipY"] = f.flipY.value();
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
        auto jiter = j.begin();
        while (jiter != j.end()) {
            if(jiter.key() == "delay") f.duration = jiter.value().get<sf::Int64>();
            if(jiter.key() == "flipX") f.flipX = jiter.value().get<bool>();
            if(jiter.key() == "flipY") f.flipY = jiter.value().get<bool>();
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
        j["loop"] = a.isLoop();
        j["uv_relative"] = a.usesRelativeUV();
        for(int i = 0; i < a.getLength(); i++) {
            j["frames"].push_back(frameToJson(a.getFrame(i)));
        }
        return j;
    }

    static Animation animationFromJson(json& j) {
        Animation a(j["delay"].get<sf::Int64>());
        if(j.contains("loop")) a.setLoop(j.at("loop").get<bool>());
        if(j.contains("uv_relative")) a.setRelativeUV(j.at("uv_relative").get<bool>());
        if(j.contains("frames")) {
            auto jiter = j["frames"].begin();
            while (jiter != j["frames"].end()) {
                a.addFrame(frameFromJson(jiter.value()));
                jiter++;
            }
        }
        if(j.contains("auto")) {
            int u = 0, v = 0, w = 1, h = 1, count = 1, limit = -1;
            if(j["auto"].contains("u")) u = j["auto"].at("u").get<int>();
            if(j["auto"].contains("v")) v = j["auto"].at("v").get<int>();
            if(j["auto"].contains("w")) w = j["auto"].at("w").get<int>();
            if(j["auto"].contains("h")) h = j["auto"].at("h").get<int>();
            if(j["auto"].contains("count")) count = j["auto"].at("count").get<int>();
            if(j["auto"].contains("limit")) limit = j["auto"].at("limit").get<int>();
            for(int i = 0; i < count; i++) {
                Animation::Frame frame;
                frame.u = u + w * (i%limit);
                frame.v = v + h * (i/limit);
                frame.w = w;
                frame.h = h;
                a.addFrame(frame);
            }
        }
        
        return a;
    }

    static Animation loadAnimation(std::string filename) {
        std::ifstream file;
        file.open(filename);
        json j = json::parse(file);
        Animation anim = animationFromJson(j);
        return anim;
    }
}
