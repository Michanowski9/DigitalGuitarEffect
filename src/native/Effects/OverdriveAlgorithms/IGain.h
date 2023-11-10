#pragma once

class IGain
{
    public:
        virtual void SetGain(const float value){
            this->gain = value;
        };
    protected:
        float gain = 1.0f;
};
