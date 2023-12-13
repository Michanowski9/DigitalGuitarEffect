#pragma once

#include "IAlgorithm.h"

#include <queue>

namespace Delay
{
    class PingPong : public IAlgorithm
    {
    public:
        PingPong() = default;
        ~PingPong() = default;

        void AddToBuffor(const StereoSample &input) override
        {
            buffor.push( { input.left * leftInputVolume, input.right * rightInputVolume});
            while(buffor.size() > bufforMaxSize)
            {
                StereoSample reversedFront = { buffor.front().right, buffor.front().left};
                buffor.back() = buffor.back() + feedback * reversedFront;
                buffor.pop();
            }
        }

        StereoSample Calculate(const StereoSample &input) override
        {
            return input + (buffor.size() >= bufforMaxSize ? alpha * buffor.front() : StereoSample{ 0, 0 } );
        }

        void ResetBuffer() override {
            while(buffor.size() > 0){
                buffor.pop();
            }
        }

        std::string GetName() override
        {
            return "Ping Pong";
        }

        void SetDelay(const int value) override { bufforMaxSize = value; }
        void SetAlpha(const float value) override { alpha = value; }
        void SetFeedback(const float value) override { feedback = value; }
        void SetLeftInputVolume(const float value) override { leftInputVolume = value; }
        void SetRightInputVolume(const float value) override { rightInputVolume = value; }

        bool IsUsingDelay() override { return true; }
        bool IsUsingAlpha() override { return true; }
        bool IsUsingFeedback() override { return true; }
        bool IsUsingLeftInputVolume() override { return true; }
        bool IsUsingRightInputVolume() override { return true; }
    private:
        float leftInputVolume = 1.0f;
        float rightInputVolume = 0.0f;
        float alpha = 0.5f;
        float feedback = 0.5f;
        std::queue<StereoSample> buffor;
        int bufforMaxSize = 1;
    };
}
