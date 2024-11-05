#include "FmodCarSoundManagerSetParameters.h"

// Constructor with default parameter ranges
FmodCarSoundManagerSetParameters::FmodCarSoundManagerSetParameters(const FString& fmodEvent, const FString& parameterName)
    : FmodCarSoundManager(fmodEvent), MinParameterRange(0.0f), MaxParameterRange(100.0f), ParameterName(parameterName)
{
}

// Constructor with custom parameter ranges
FmodCarSoundManagerSetParameters::FmodCarSoundManagerSetParameters(const FString& fmodEvent, const FString& parameterName, float min, float max)
    : FmodCarSoundManager(fmodEvent), MinParameterRange(min), MaxParameterRange(max), ParameterName(parameterName)
{
}

// Get the parameter name
FString FmodCarSoundManagerSetParameters::GetParameterName() const
{
    return ParameterName;
}

// Set the parameter name
void FmodCarSoundManagerSetParameters::SetParameterName(const FString& parameterName)
{
    ParameterName = parameterName;
}

// Get minimum parameter range
float FmodCarSoundManagerSetParameters::GetMinParameterRange() const
{
    return MinParameterRange;
}

// Get maximum parameter range
float FmodCarSoundManagerSetParameters::GetMaxParameterRange() const
{
    return MaxParameterRange;
}

// Set minimum parameter range
void FmodCarSoundManagerSetParameters::SetMinParameterRange(float min)
{
    MinParameterRange = min;
}

// Set maximum parameter range
void FmodCarSoundManagerSetParameters::SetMaxParameterRange(float max)
{
    MaxParameterRange = max;
}

// Set discrete parameter value
void FmodCarSoundManagerSetParameters::SetDiscreteParameter(int value)
{
    float discVal = static_cast<float>(value);
    SetParameterValue(discVal);
}

// Set continuous parameter value
void FmodCarSoundManagerSetParameters::SetContinuousValue(float value)
{
    SetParameterValue(value);
}

// Set labeled parameter
void FmodCarSoundManagerSetParameters::SetLabeledParameter(const FString& label)
{
    if (eventInstance.isValid())
    {
        FMOD_RESULT result = eventInstance.setParameterByNameWithLabel(TCHAR_TO_ANSI(*ParameterName), TCHAR_TO_ANSI(*label));
        if (result != FMOD_OK)
        {
            UE_LOG(LogTemp, Error, TEXT("Failed to set labeled parameter %s: %s"), *ParameterName, UTF8_TO_TCHAR(FMOD_ErrorString(result)));
        }
    }
}

// Set FMOD parameter value with clamping
void FmodCarSoundManagerSetParameters::SetParameterValue(float value)
{
    value = FMath::Clamp(value, MinParameterRange, MaxParameterRange);

    if (eventInstance.isValid())
    {
        FMOD_RESULT result = eventInstance.setParameterByName(TCHAR_TO_ANSI(*ParameterName), value);
        if (result != FMOD_OK)
        {
            UE_LOG(LogTemp, Error, TEXT("Failed to set parameter %s: %s"), *ParameterName, UTF8_TO_TCHAR(FMOD_ErrorString(result)));
        }
    }
}

// Get discrete parameter value
int FmodCarSoundManagerSetParameters::GetDiscreteParameterValue() const
{
    float parameterValue = 0.0f;
    if (eventInstance.isValid())
    {
        FMOD_RESULT result = eventInstance.getParameterByName(TCHAR_TO_ANSI(*ParameterName), &parameterValue);
        if (result == FMOD_OK)
        {
            return static_cast<int>(parameterValue);
        }
    }
    return 0;
}

// Get continuous parameter value
float FmodCarSoundManagerSetParameters::GetContinuousParameterValue() const
{
    float parameterValue = 0.0f;
    if (eventInstance.isValid())
    {
        FMOD_RESULT result = eventInstance.getParameterByName(TCHAR_TO_ANSI(*ParameterName), &parameterValue);
        if (result != FMOD_OK)
        {
            UE_LOG(LogTemp, Error, TEXT("Failed to get parameter value for %s: %s"), *ParameterName, UTF8_TO_TCHAR(FMOD_ErrorString(result)));
        }
    }
    return parameterValue;
}
