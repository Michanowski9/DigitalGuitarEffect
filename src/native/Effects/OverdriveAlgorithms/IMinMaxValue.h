#pragma once

class IMinMaxValue
{
    public:
        virtual void SetMinValue(const float value){
            this->minValue = value;
        };
        virtual void SetMaxValue(const float value){
            this->maxValue = value;
        };

    protected:
        float minValue = -1.0f;
        float maxValue = 1.0f;
};
