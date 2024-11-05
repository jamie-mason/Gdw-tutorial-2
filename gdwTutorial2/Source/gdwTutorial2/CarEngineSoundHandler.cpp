#include "CarEngineSoundHandler.h"

// Constructor (empty, as we will use Initialize function for setup)
CarEngineSoundHandler::CarEngineSoundHandler()
    : currentSpeed(0.0f), maxSpeed(100.0f), setEngineParameters(nullptr)
{
}

// Initialize function to set up maxSpeed and the sound manager
void CarEngineSoundHandler::Initialize(float InMaxSpeed)
{
    maxSpeed = InMaxSpeed;
    currentSpeed = 0.0f;

    // Initialize the FMOD car engine parameters, using Unreal's memory management system
    setEngineParameters = NewObject<UFmodCarSoundManagerSetParameters>(this);
    if (setEngineParameters)
    {
        setEngineParameters->Initialize(eventPath, parameterName, 0.0f, 7.0f);
    }
}

// Get the FMOD engine sound object
FmodCarSoundManager* CarEngineSoundHandler::GetFmodEngineObject() const
{
    return setEngineParameters;
}

// Get current speed
float CarEngineSoundHandler::GetCurrentSpeed() const
{
    return currentSpeed;
}

// Set current speed with clamping
void CarEngineSoundHandler::SetCurrentSpeed(float speed)
{
    currentSpeed = FMath::Clamp(speed, 0.0f, maxSpeed);
}

// Get max speed
float CarEngineSoundHandler::GetMaxSpeed() const
{
    return maxSpeed;
}

// Calculate speed fraction
float CarEngineSoundHandler::GetSpeedFraction() const
{
    return FMath::Clamp(currentSpeed / maxSpeed, 0.0f, 1.0f);
}

// Check for significant difference between two float values
bool CarEngineSoundHandler::HasSignificantDifference(float a, float b, float tolerance) const
{
    return FMath::Abs(a - b) > tolerance;
}

// Update car engine sound based on current speed
void CarEngineSoundHandler::UpdateCarEngineSound()
{
    // Calculate the speed fraction
    float speedFraction = GetSpeedFraction();

    // Calculate the target parameter value
    if (setEngineParameters)
    {
        float targetParameterValue = speedFraction * setEngineParameters->GetMaxParameterRange();

        // Check if there's a significant difference between the current and target values
        if (HasSignificantDifference(setEngineParameters->GetContinuousParameterValue(), targetParameterValue))
        {
            // Set the new parameter value
            setEngineParameters->SetContinuousValue(targetParameterValue);
        }
    }
}
