#pragma once

#include "Effects/IEffect.h"

class IAudioCallbackWrapper
{
public:
    virtual StereoSample AudioEffectHandler(const StereoSample &input) = 0;
};
