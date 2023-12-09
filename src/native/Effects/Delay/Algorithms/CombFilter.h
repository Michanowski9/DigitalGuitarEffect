#pragma once

#include "IAlgorithm.h"

#include <queue>

namespace Delay
{
    class CombFilter : public IAlgorithm
    {
    public:
        CombFilter() = default;
        ~CombFilter() = default;

        void AddToBuffor(const StereoSample &input) override
        {
            buffor.push(input);
            while(buffor.size() > bufforMaxSize)
            {
                buffor.pop();
            }
        };

        StereoSample Calculate(const StereoSample &input) override
        {
            return input + (buffor.size() >= bufforMaxSize ? alpha * buffor.front() : StereoSample{ 0, 0 } );
        }

        std::string GetName() override
        {
            return "Comb filter";
        }

        void SetDelay(const int value) override { bufforMaxSize = value; };
        void SetAlpha(const float value) override { alpha = value; };

        bool IsUsingDelay() override { return true; }
        bool IsUsingAlpha() override { return true; }
    private:
        float alpha = 0.5f;
        std::queue<StereoSample> buffor;
        int bufforMaxSize = 1;
    };
}
