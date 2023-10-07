#ifndef C_INTERFACE_H
#define C_INTERFACE_H

#include <memory>
#include <vector>

#include "mainProgram.h"

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
}

#endif