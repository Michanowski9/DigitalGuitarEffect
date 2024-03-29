#pragma once

#include "portaudioWrapper.h"

#include "IAudioCallbackWrapper.h"
#include "Effects/IEffect.h"
#include "Settings.h"

#include <memory>
#include <vector>

class MainProgram : public IAudioCallbackWrapper
{
public:
    MainProgram() {
        settings = std::make_shared<Settings>();
    };
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

    void* AddEffect(std::shared_ptr<IEffect> effect);
    void RemoveEffect(void* effectPtr);

    void SwapEffects(int firstId, int secondId);
    std::shared_ptr<Settings> GetSettings(){
        return settings;
    };
private:
    bool IsBypassOn();
    std::shared_ptr<Settings> settings;

    PortaudioWrapper paWrapper;
    bool bypass = false;
    std::vector<std::shared_ptr<IEffect>> loadedEffects;
};
