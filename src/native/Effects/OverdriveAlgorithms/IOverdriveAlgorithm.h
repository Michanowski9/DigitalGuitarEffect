#pragma once

#include "../../IEffect.h"
#include <string>

class IOverdriveAlgorithm
{
    public:
        virtual void operator()(StereoSample &output, const StereoSample &input) = 0;
        virtual std::string GetName() = 0;
};
