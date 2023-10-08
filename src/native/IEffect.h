#pragma once

struct StereoSample{
    float left;
    float right;
};

class IEffect {
public:
   virtual void Calculate(StereoSample &output, const StereoSample &input) = 0;
   virtual void SetOn(const bool value) = 0;
};

