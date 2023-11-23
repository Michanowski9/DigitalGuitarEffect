#pragma once

#include "StereoSample.h"

class IAudioCallbackWrapper
{
public:
    virtual StereoSample AudioEffectHandler(const StereoSample &input) = 0;
};
