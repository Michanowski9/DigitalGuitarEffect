#include "mainProgram.h"

int MainProgram::GetCurrentSampleRate(){
    if(currentSampleRate == 0)
    {
        return 192000;
    }
    return currentSampleRate;
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
    currentSampleRate = sampleRate;
    paWrapper.StartStream(inputDeviceId, outputDeviceId, currentSampleRate, this);
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
    auto output = input;

    if(IsBypassOn()){
        return output;
    }

    StereoSample temp_input{};
    for(auto effect : loadedEffects){
        temp_input = output;
        (*effect)(output, temp_input);
    }
    return output;
}

void MainProgram::SetBypass(bool value)
{
    bypass = value;
}

void* MainProgram::AddEffect(std::shared_ptr<IEffect> effect)
{
    loadedEffects.push_back(effect);
    return effect.get();
}

void MainProgram::SwapEffects(int firstId, int secondId)
{
    std::swap(loadedEffects[firstId], loadedEffects[secondId]);
}

void MainProgram::RemoveEffect(void* effectPtr)
{
    for(auto i = 0; i < loadedEffects.size(); i++)
    {
        if(loadedEffects[i].get() == effectPtr)
        {
            loadedEffects.erase(loadedEffects.begin() + i);
            return;
        }
    }
}
