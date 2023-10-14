#include "cInterface.h"
#include "Effects/overdrive.h"

void InitPA()
{
    mainProgram = std::make_unique<MainProgram>();
}

void FreePA()
{
    mainProgram.reset(nullptr);
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
    return mainProgram->AddEffect(std::make_shared<Overdrive>());
}

void SetEffectOn(void* ptr, bool value)
{
    static_cast<IEffect*>(ptr)->SetOn(value);
}

void CalculateExampleData(void* ptr, int size, float* data)
{
    for(auto i = 0; i < size; i++)
    {
        StereoSample input{data[i], 0};
        StereoSample output{0, 0};
        static_cast<IEffect*>(ptr)->Calculate(output,input);
        data[i] = output.left;
    }
}

void RemoveEffect(void* ptr)
{
    mainProgram->RemoveEffect(ptr);
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
    static_cast<Overdrive*>(ptr)->SetMinMaxValue(minValue, maxValue);
}

void Overdrive_SetSoftCutValue(void* ptr, float value)
{
//    static_cast<Overdrive*>(ptr)->SetSoftCutValue(value);
}

void Overdrive_SetAlgorithm(void* ptr, int algorithm)
{
    static_cast<Overdrive*>(ptr)->SetAlgorithm(algorithm);
}
