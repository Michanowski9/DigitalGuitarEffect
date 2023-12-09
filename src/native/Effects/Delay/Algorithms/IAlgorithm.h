#pragma once

#include "../../../StereoSample.h"

#include <string>

namespace Delay
{
    class IAlgorithm
    {
        public:
            virtual StereoSample Calculate(const StereoSample &input) = 0;
            virtual void AddToBuffor(const StereoSample &input) = 0;
            virtual std::string GetName() = 0;


            virtual void SetDelay(const int value){ };
            virtual bool IsUsingDelay(){ return false; };

            virtual void SetAlpha(const float value){ };
            virtual bool IsUsingAlpha(){ return false; };
    };
}
