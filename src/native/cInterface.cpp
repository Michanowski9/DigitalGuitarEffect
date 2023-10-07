#include "cInterface.h"

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
