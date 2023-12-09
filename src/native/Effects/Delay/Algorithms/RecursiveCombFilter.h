#pragma once

#include "IAlgorithm.h"

#include <queue>

namespace Delay
{
    class RecursiveCombFilter : public IAlgorithm
    {
    public:
        RecursiveCombFilter() = default;
        ~RecursiveCombFilter() = default;

        void AddToBuffor(const StereoSample &input) override
        {
            buffor.push(input);
            while(buffor.size() > bufforMaxSize)
            {
                buffor.back() = buffor.back() + feedback * buffor.front();
                buffor.pop();
            }
        }

        StereoSample Calculate(const StereoSample &input) override
        {
            return input + (buffor.size() >= bufforMaxSize ? alpha * buffor.front() : StereoSample{ 0, 0 } );
        }

        std::string GetName() override
        {
            return "Recursive comb filter";
        }

        void SetDelay(const int value) override { bufforMaxSize = value; }
        void SetAlpha(const float value) override { alpha = value; }
        void SetFeedback(const float value) override { feedback = value; }

        bool IsUsingDelay() override { return true; }
        bool IsUsingAlpha() override { return true; }
        bool IsUsingFeedback() override { return true; }
    private:
        float alpha = 0.5f;
        float feedback = 0.5f;
        std::queue<StereoSample> buffor;
        int bufforMaxSize = 1;
    };
}
