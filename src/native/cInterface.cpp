#include "cInterface.h"
#include "Effects/Modulation/LFO/TriangleGenerator.h"
#include "Effects/Modulation/Algorithms/Chorus.h"
#include "Effects/Modulation/Algorithms/Flanger.h"
#include "Effects/Modulation/Modulation.h"
#include "Effects/OverdriveAlgorithms/HyperbolicTangent.h"
#include "Effects/OverdriveAlgorithms/HardClipping.h"
#include "Effects/OverdriveAlgorithms/IOverdriveAlgorithm.h"
#include "Effects/overdrive.h"
#include "Settings.h"
#include <memory>

void InitPA()
{
    mainProgram = std::make_shared<MainProgram>();
}

void FreePA()
{
    mainProgram.reset();
}

int GetDeviceNumber()
{
    return mainProgram->GetDevicesNumber();
}

const char* GetDeviceName(int deviceId)
{
    return mainProgram->GetDevice(deviceId).name.c_str();
}

int GetInputChannelsCount(int deviceId)
{
    return mainProgram->GetDevice(deviceId).inChannels;
}

int GetOutputChannelsCount(int deviceId)
{
    return mainProgram->GetDevice(deviceId).outChannels;
}

double GetInputLowLatency(int deviceId)
{
    return mainProgram->GetDevice(deviceId).inLowLatency;
}

double GetInputHighLatency(int deviceId)
{
    return mainProgram->GetDevice(deviceId).inHighLatency;
}

double GetOutputLowLatency(int deviceId)
{
    return mainProgram->GetDevice(deviceId).outLowLatency;
}

double GetOutputHighLatency(int deviceId)
{
    return mainProgram->GetDevice(deviceId).outLowLatency;
}

int* GetSampleRates(int inputDeviceId, int outputDeviceId)
{
    auto sampleRates = mainProgram->GetSampleRates(inputDeviceId, outputDeviceId);

    int* result = new int[sampleRates.size() + 1];
    result[0] = sampleRates.size();
    for(int i = 0; i < sampleRates.size(); i++)
    {
        result[i + 1] = sampleRates[i];
    }
    return result;
}

void FreeArray(int* ptr)
{
    delete[] ptr;
}

void Start(int inputDeviceId, int outputDeviceId, int sampleRate)
{
    mainProgram->StartStream(inputDeviceId, outputDeviceId, sampleRate);
}

void Stop()
{
    mainProgram->StopStream();
}

void BypassSwitch(bool value)
{
    mainProgram->SetBypass(value);
}

void* AddEffectOverdrive()
{
    auto effect = std::make_shared<Overdrive>();

    effect->AddAlgorithm(std::make_shared<HardClipping>());
    effect->AddAlgorithm(std::make_shared<HyperbolicTangent>());

    return mainProgram->AddEffect(effect);
}

void* AddEffectDelay()
{
    return mainProgram->AddEffect(
            std::make_shared<Delay>(Delay(
                {
                    { std::make_shared<CombFilter>(), std::make_shared<CombFilter>() },
                    { std::make_shared<RecursiveCombFilter>(), std::make_shared<RecursiveCombFilter>() }
                }
                )));
}

void* AddEffectChorus()
{
    auto visualisationSettings = std::make_shared<Settings>();
    visualisationSettings->SetCurrentSampleRate(1000);
    return mainProgram->AddEffect(
            std::make_shared<Modulation>(Modulation(
                {
                    { std::make_shared<Flanger>(), std::make_shared<Flanger>() },
                    { std::make_shared<Chorus>(), std::make_shared<Chorus>() }
                },
                {
                    { std::make_shared<TriangleGenerator>(mainProgram->GetSettings()), std::make_shared<TriangleGenerator>(visualisationSettings) }
                }
                )));
}


void SetEffectOn(void* ptr, bool value)
{
    static_cast<IEffect*>(ptr)->SetOn(value);
}

void CalculateExampleData(void* ptr, int size, float* data)
{
    static_cast<IEffect*>(ptr)->ResetEffect();
    for(auto i = 0; i < size; i++)
    {
        StereoSample input{data[i], 0};
        StereoSample output{0, 0};
        static_cast<IEffect*>(ptr)->CalculateForVisualization(output,input);
        data[i] = output.left;
    }
}

void RemoveEffect(void* ptr)
{
    mainProgram->RemoveEffect(ptr);
}

void SwapEffects(int firstId, int secondId)
{
    mainProgram->SwapEffects(firstId, secondId);
}

int Overdrive_GetAlgorithmsNo(void* ptr)
{
    return static_cast<Overdrive*>(ptr)->GetAlgorithmsNo();
}

const char* Overdrive_GetAlgorithmName(void* ptr, int id)
{
    result = std::make_shared<std::string>(static_cast<Overdrive*>(ptr)->GetAlgorithmName(id));
    return result->c_str();
}

void Overdrive_SetGain(void* ptr, float value)
{
    static_cast<Overdrive*>(ptr)->SetGain(value);
}

void Overdrive_SetMinMaxValue(void* ptr, float minValue, float maxValue)
{
    static_cast<Overdrive*>(ptr)->SetMinValue(minValue);
    static_cast<Overdrive*>(ptr)->SetMaxValue(maxValue);
}

void Overdrive_SetAlgorithm(void* ptr, int algorithm)
{
    static_cast<Overdrive*>(ptr)->SetAlgorithm(algorithm);
}

void Delay_SetDelay(void* ptr, int value)
{
    static_cast<Delay*>(ptr)->SetDelayInMilliseconds(value);
}

void Delay_SetAlpha(void* ptr, float value)
{
    static_cast<Delay*>(ptr)->SetAlpha(value);
}

int Effect_GetAlgorithmsNo(void* ptr)
{
    return static_cast<IEffect*>(ptr)->GetAlgorithmsNo();
}

const char* Effect_GetAlgorithmName(void* ptr, int id)
{
    result = std::make_shared<std::string>(static_cast<IEffect*>(ptr)->GetAlgorithmName(id));
    return result->c_str();
}

void Effect_SetAlgorithm(void* ptr, int algorithm)
{
    static_cast<IEffect*>(ptr)->SetAlgorithm(algorithm);
}

void Chorus_SetDelay(void* ptr, int value)
{
    static_cast<Modulation*>(ptr)->SetDelayInMilliseconds(value);
}

void Chorus_SetAlpha(void* ptr, float value)
{
    static_cast<Modulation*>(ptr)->SetAlpha(value);
}

void Chorus_SetDepth(void* ptr, float value)
{
    static_cast<Modulation*>(ptr)->SetDepth(value);
}

void Chorus_SetLFOFrequency(void* ptr, float value)
{
    static_cast<Modulation*>(ptr)->SetLFOFrequency(value);
}



