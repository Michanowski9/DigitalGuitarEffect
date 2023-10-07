#pragma once

#include "portaudioWrapper.h"

#include "IAudioCallbackWrapper.h"
#include "IEffect.h"

#include <vector>

class MainProgram : public IAudioCallbackWrapper
{
public:
    MainProgram();
    MainProgram(MainProgram &&) = default;
    MainProgram(const MainProgram &) = default;
    MainProgram &operator=(MainProgram &&) = default;
    MainProgram &operator=(const MainProgram &) = default;
    ~MainProgram() = default;

    int GetDevicesNumber();
    Device GetDevice(int deviceId);
    std::vector<int> GetSampleRates(int inputDeviceId, int outputDeviceId);

    void StartStream(int inputDeviceId, int outputDeviceId, int sampleRates);
    void StopStream();
    StereoSample AudioEffectHandler(const StereoSample &input) override;
    void SetBypass(bool value);

private:
    bool IsBypassOn();

    PortaudioWrapper paWrapper;
    bool bypass = false;
    std::vector<IEffect*> loadedEffects;
};
