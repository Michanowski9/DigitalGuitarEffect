#pragma once

#include <queue>
#include "IAlgorithm.h"

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


        void SetDelay(const int value) override
        {
            bufforMaxSize = value;
        };

        void SetAlpha(const float value) override
        {
            alpha = value;
        };

        std::string GetName() override
        {
            return "Comb filter";
        }
    private:
        float alpha = 0.5f;
        std::queue<StereoSample> buffor;
        int bufforMaxSize = 1;
    };
}
