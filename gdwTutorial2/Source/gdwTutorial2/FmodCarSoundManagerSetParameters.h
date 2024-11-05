// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "FmodCarSoundManager.h"

class FmodCarSoundManagerSetParameters : public FmodCarSoundManager
{
public:
    // Constructor with default parameter ranges
    FmodCarSoundManagerSetParameters(const FString& fmodEvent, const FString& parameterName);

    // Constructor with custom parameter ranges
    FmodCarSoundManagerSetParameters(const FString& fmodEvent, const FString& parameterName, float min, float max);

    // Getters for parameter details
    FString GetParameterName() const;
    float GetMinParameterRange() const;
    float GetMaxParameterRange() const;

    // Setters for parameter name
    void SetParameterName(const FString& parameterName);

    // Set discrete and continuous parameter values
    void SetDiscreteParameter(int value);
    void SetContinuousValue(float value);

    // Set labeled parameter
    void SetLabeledParameter(const FString& label);

    // Get parameter values
    int GetDiscreteParameterValue() const;
    float GetContinuousParameterValue() const;

protected:
    // Protected setters for min/max range
    void SetMinParameterRange(float min);
    void SetMaxParameterRange(float max);

private:
    // Utility to set the FMOD parameter value
    void SetParameterValue(float value);

    // Private members
    float MinParameterRange;
    float MaxParameterRange;
    FString ParameterName;

};
