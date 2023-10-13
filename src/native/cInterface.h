#ifndef C_INTERFACE_H
#define C_INTERFACE_H

#include <memory>
#include <vector>

#include "mainProgram.h"
#include "Effects/overdrive.h"
#include "IEffect.h"
#include <memory>

std::unique_ptr<MainProgram> mainProgram;

extern "C"
{
    __declspec(dllexport)
        void InitPA();

    __declspec(dllexport)
        void FreePA();

    __declspec(dllexport)
        int GetDeviceNumber();

    __declspec(dllexport)
        const char* GetDeviceName(int device);

    __declspec(dllexport)
        int GetInputChannelsCount(int device);

    __declspec(dllexport)
        int GetOutputChannelsCount(int device);

    __declspec(dllexport)
        double GetInputLowLatency(int inputDevice);

    __declspec(dllexport)
        double GetOutputLowLatency(int outputDevice);

    __declspec(dllexport)
        double GetInputHighLatency(int inputDevice);

    __declspec(dllexport)
        double GetOutputHighLatency(int outputDevice);

    __declspec(dllexport)
        int* GetSampleRates(int inputDevice, int outputDevice);

    __declspec(dllexport)
        void FreeArray(int* ptr);

    __declspec(dllexport)
        void Start(int inputDevice, int outputDevice, int sampleRate);

    __declspec(dllexport)
        void Stop();

    __declspec(dllexport)
        void BypassSwitch(bool value);

    __declspec(dllexport)
        void* AddEffectOverdrive();

    __declspec(dllexport)
        void SetEffectOn(void* ptr, bool value);

    __declspec(dllexport)
        void CalculateExampleData(void* ptr, int size, float* data);

    __declspec(dllexport)
        void RemoveEffect(void* ptr);

    __declspec(dllexport)
        void Overdrive_SetGain(void* ptr, float data);

    __declspec(dllexport)
        void Overdrive_SetMinMaxValue(void* ptr, float minValue, float maxValue);

    __declspec(dllexport)
        void Overdrive_SetSoftCutValue(void* ptr, float value);

    __declspec(dllexport)
        void Overdrive_SetAlgorithm(void* ptr, int algorithm);
}

#endif
