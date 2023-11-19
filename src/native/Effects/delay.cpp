#include "delay.h"

void Delay::operator()(StereoSample &output, const StereoSample &input)
{
    auto bufforMaxSizeInProbes = bufforMaxSize / 1000 * settings->GetCurrentSampleRate();
    if(isOn)
    {
        Calculate(output, input, this->buffor, bufforMaxSizeInProbes);
    }
    else
    {
        output = {input.left, input.right};
    }
    AddToBuffor(input, this->buffor, bufforMaxSizeInProbes);
}

void Delay::CalculateForVisualization(StereoSample &output, const StereoSample &input)
{
    static std::queue<StereoSample> _buffor;
    int _bufforMaxSize = this->bufforMaxSize;

    Calculate(output, input, _buffor, _bufforMaxSize);
    AddToBuffor(input, _buffor, _bufforMaxSize);
}

void Delay::AddToBuffor(const StereoSample &input, std::queue<StereoSample> &buff, const int &maxSize)
{
    buff.push(input);
    while(buff.size() > maxSize)
    {
        buff.pop();
    }
}

void Delay::Calculate(StereoSample &output, const StereoSample &input, std::queue<StereoSample> &buff, const int &maxSize)
{
    auto calc = [](auto& out, const auto& in, auto buffSize, auto& buffFront, auto& maxSize, auto& alpha){
        out = in + (buffSize >= maxSize ? alpha * buffFront : 0);
    };

    calc(output.left, input.left, buff.size(), buff.front().left, maxSize, alpha);
    calc(output.right, input.right, buff.size(), buff.front().right, maxSize, alpha);
}

void Delay::SetDelayInMilliseconds(const int value)
{
    this->bufforMaxSize = value;
}

void Delay::SetAlpha(const float value)
{
    this->alpha = value;
}
