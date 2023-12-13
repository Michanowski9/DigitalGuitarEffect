#pragma once

#include "IAlgorithm.h"

#include <deque>
#include <vector>

namespace Delay
{
    class MultiTap : public IAlgorithm
    {
    public:
        MultiTap(){
            SetTaps(3);
        }
        ~MultiTap() = default;

        void AddToBuffor(const StereoSample &input) override
        {
            buffor.push_back(input);
            while(buffor.size() > bufforMaxSize)
            {
                buffor.pop_front();
            }
        };

        StereoSample Calculate(const StereoSample &input) override
        {
            StereoSample result = input;
            if(buffor.size() >= bufforMaxSize){
                for (int i = 0; i < taps.size(); i++) {
                    result = result + buffor[taps[i].first * bufforMaxSize] * taps[i].second * alpha;
                }
            }
            return result;
        }

        void ResetBuffer() override {
            buffor.clear();
        }

        std::string GetName() override
        {
            return "Multi-Tap";
        }

        void SetDelay(const int value) override { bufforMaxSize = value; };
        void SetFeedback(const float value) override {
            feedback = value;
            SetTaps(taps.size());
        }
        void SetAlpha(const float value) override {
            alpha = value;
            SetTaps(taps.size());
        };
        void SetTaps(const int tapsNo) override {
            taps.clear();
            for(int i = 0; i < tapsNo; i++){
                taps.push_back( {
                        1.0f / tapsNo * i,
                        1.0f - (1.0f - feedback) * static_cast<float>(tapsNo - i - 1) / (tapsNo - 1)
                    } );
            }
        }

        bool IsUsingDelay() override { return true; }
        bool IsUsingAlpha() override { return true; }
        bool IsUsingFeedback() override { return true; }
        bool IsUsingTaps() override { return true; }
    private:
        std::vector<std::pair<float,float>> taps;

        std::deque<StereoSample> buffor;
        float alpha = 0.5;
        float feedback = 0.5;
        int bufforMaxSize = 1;
    };
}
