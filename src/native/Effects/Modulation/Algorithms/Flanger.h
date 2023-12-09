#pragma once

#include "../../../StereoSample.h"
#include "../LFO/ILFO.h"
#include "IAlgorithm.h"

#include <cmath>
#include <deque>
#include <memory>

namespace Modulation
{
    class Flanger : public IAlgorithm
    {
    public:
        Flanger() = default;
        ~Flanger() = default;

        void AddToBuffor(const StereoSample &input) override
        {
            buffer.push_back(input);
            while(buffer.size() > bufferMaxSize && bufferMaxSize > 0)
            {
                buffer.pop_front();
            }
        };

        StereoSample LinearInterpolation(double x, StereoSample y0, StereoSample y1) {
            return y0 + x * (y1 - y0);
        }

        StereoSample Calculate(const StereoSample& input, const float lfoValue) override {
            if(buffer.size() < bufferMaxSize || bufferMaxSize <= 0)
                return input;

            auto currentDelay = (depth * bufferMaxSize-1) * (lfoValue+1) / 2;

            auto index1 = static_cast<int>(floor(currentDelay)) % buffer.size();
            auto index2 = static_cast<int>(ceil(currentDelay)) % buffer.size();

            auto delayed = LinearInterpolation(currentDelay - floor(currentDelay), buffer[index1], buffer[index2]) * alpha;

            buffer[buffer.size()-1] = buffer[buffer.size()-1] + delayed;

            return input + delayed;
        }


        void ResetBuffor() override {
            buffer.clear();
        }

        void SetDelay(const int value) override
        {
            bufferMaxSize = value;
        };

        void SetAlpha(const float value) override
        {
            alpha = value;
        };

        void SetDepth(const float value) override
        {
            depth = value;
        };

        std::string GetName() override
        {
            return "Flanger";
        }

    private:
        float alpha = 0.5f;
        float depth = 0.1f;
        int bufferMaxSize = 2;

        std::deque<StereoSample> buffer;
    };
}
