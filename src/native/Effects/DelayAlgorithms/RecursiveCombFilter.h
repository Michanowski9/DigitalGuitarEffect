#pragma once

#include <queue>
#include "IDelayAlgorithms.h"

class RecursiveCombFilter : public IDelayAlgorithm
{
public:
    RecursiveCombFilter() = default;
    ~RecursiveCombFilter() = default;

    void AddToBuffor(const StereoSample &input) override
    {
        buffor.push(input);
        while(buffor.size() > bufforMaxSize)
        {
            buffor.back() = buffor.back() + alpha * buffor.front();
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
        return "Recursive comb filter";
    }
private:
    float alpha = 0.5f;
    std::queue<StereoSample> buffor;
    int bufforMaxSize = 1;
};
