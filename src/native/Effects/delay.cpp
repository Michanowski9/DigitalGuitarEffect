#include "delay.h"

Delay::Delay(std::weak_ptr<ISettings> settings) : settings(settings)
{

}

void Delay::SetOn(const bool value)
{
    this->isOn = value;
}

void Delay::operator()(StereoSample &output, const StereoSample &input)
{
    AddToBuffor(input, this->buffor, this->bufforMaxSize);
    if(isOn)
    {
        Calculate(output, input, this->buffor, this->bufforMaxSize);
    }
    else
    {
        output = {input.left, input.right};
    }
}

void Delay::CalculateForVisualization(StereoSample &output, const StereoSample &input)
{
    static std::queue<StereoSample> _buffor;
    auto settingsLocked = settings.lock();
    int _bufforMaxSize = this->bufforMaxSize * 1000 / settingsLocked->GetCurrentSampleRate();

    AddToBuffor(input, _buffor, _bufforMaxSize);
    Calculate(output, input, _buffor, _bufforMaxSize);
}

void Delay::AddToBuffor(const StereoSample &input, std::queue<StereoSample> &buffor, const int &bufforMaxSize)
{
    buffor.push(input);
    while(buffor.size() > bufforMaxSize)
    {
        buffor.pop();
    }
}

void Delay::Calculate(StereoSample &output, const StereoSample &input, std::queue<StereoSample> &buffor, const int &bufforMaxSize)
{
    auto calc = [](const auto obj, auto& output, auto& input, auto& buffor, auto& bufforMaxSize) {
        output = input + (buffor.size() < bufforMaxSize ? 0 : obj->alpha * buffor.front().left);
    };

    calc(this, output.left, input.left, buffor, bufforMaxSize);
    calc(this, output.right, input.right, buffor, bufforMaxSize);
}

void Delay::SetDelay(const int value)
{
    auto settingsLocked = settings.lock();
    this->bufforMaxSize = static_cast<float>(value) / 1000 * settingsLocked->GetCurrentSampleRate();
}

void Delay::SetAlpha(const float value)
{
    this->alpha = value;
}
