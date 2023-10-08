#include "mainProgram.h"

MainProgram::MainProgram(){
}

int MainProgram::GetDevicesNumber()
{
    return paWrapper.GetDeviceCount();
}

Device MainProgram::GetDevice(int deviceId)
{
    return paWrapper.GetDeviceInfo(deviceId);
}

std::vector<int> MainProgram::GetSampleRates(int inputDeviceId, int outputDeviceId)
{
    return paWrapper.GetSampleRates(inputDeviceId, outputDeviceId);
}

void MainProgram::StartStream(int inputDeviceId, int outputDeviceId, int sampleRate)
{
    paWrapper.StartStream(inputDeviceId, outputDeviceId, sampleRate, this);
}

void MainProgram::StopStream()
{
    paWrapper.StopStream();
}

bool MainProgram::IsBypassOn()
{
    return this->bypass;
}

StereoSample MainProgram::AudioEffectHandler(const StereoSample &input){

    StereoSample output{input.left, input.right};

    if(IsBypassOn()){
        return output;
    }

    for(auto effect : loadedEffects){
        effect->Calculate(output, input);
    }
    return output;
}

void MainProgram::SetBypass(bool value)
{
    bypass = value;
}

void* MainProgram::AddEffect(IEffect* effect)
{
    loadedEffects.push_back(effect);
    return effect;
}
