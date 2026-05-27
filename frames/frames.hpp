#pragma once
#include <string_view>
#include <unordered_map>
#include <string>

using GetFrameFn = std::string_view(*)(int);
using GetLengthFn = int(*)();
using GetSleepFn = int(*)();

struct FrameType {
    GetFrameFn GetFrame;
    GetLengthFn GetLength;
    GetSleepFn GetSleep;

    constexpr FrameType(GetFrameFn gf, GetLengthFn gl, GetSleepFn gs)
        : GetFrame(gf), GetLength(gl), GetSleep(gs) {}
};

extern std::unordered_map<std::string, FrameType> FrameMap;