#pragma once

#include "../../../StereoSample.h"

#include <string>

namespace Overdrive
{
    class IAlgorithm
    {
        public:
            virtual StereoSample Calculate(const StereoSample &input) = 0;
            virtual std::string GetName() = 0;


            virtual void SetGain(const float value){ };
            virtual bool IsUsingGain(){ return false; };

            virtual void SetMinValue(const float value){ };
            virtual bool IsUsingMinValue(){ return false; };

            virtual void SetMaxValue(const float value){ };
            virtual bool IsUsingMaxValue(){ return false; };

            virtual void SetOffset(const float value){ };
            virtual bool IsUsingOffset(){ return false; };
    };
}
