#pragma once

#include <string>

struct Device {
    std::string name = "Unknown Device";
    int inChannels = 0;
    int outChannels = 0;
    double inLowLatency = 0;
    double inHighLatency = 0;
    double outLowLatency = 0;
    double outHighLatency = 0;
};
