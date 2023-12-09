#pragma once

#include "../../../StereoSample.h"

#include <string>

namespace Modulation
{
    class IAlgorithm
    {
        public:
            virtual StereoSample Calculate(const StereoSample &input, const float lfoValue) = 0;
            virtual void AddToBuffor(const StereoSample &input) = 0;
            virtual std::string GetName() = 0;

            virtual void ResetBuffor() = 0;

            virtual void SetDelay(const int value){ };
            virtual bool IsUsingDelay(){ return false; };

            virtual void SetAlpha(const float value){ };
            virtual bool IsUsingAlpha(){ return false; };

            virtual void SetDepth(const float value){ };
            virtual bool IsUsingDepth(){ return false; };

            virtual void SetFeedback(const float value){ };
            virtual bool IsUsingFeedback(){ return false; };
    };
}
