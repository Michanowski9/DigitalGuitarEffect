#pragma once

#include "portaudioWrapper.h"

#include "IAudioCallbackWrapper.h"
#include "IEffect.h"
#include "ISettings.h"

#include <memory>
#include <vector>

class MainProgram : public IAudioCallbackWrapper, public ISettings
{
public:
    MainProgram() = default;
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

    int GetCurrentSampleRate() override;

    void* AddEffect(std::shared_ptr<IEffect> effect);
    void RemoveEffect(void* effectPtr);

    void SwapEffects(int firstId, int secondId);
private:
    bool IsBypassOn();
    int currentSampleRate = 0;

    PortaudioWrapper paWrapper;
    bool bypass = false;
    std::vector<std::shared_ptr<IEffect>> loadedEffects;
};
