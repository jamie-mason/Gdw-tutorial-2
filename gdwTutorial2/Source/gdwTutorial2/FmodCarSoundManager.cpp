#include "FmodCarSoundManager.h"

// Constructor
FmodCarSoundManager::FmodCarSoundManager(const FString& fmodEvent)
{
    this->fmodEvent = fmodEvent;
    CreateInstance();
}

// Get the FMOD event
FString FmodCarSoundManager::GetFmodEvent() const
{
    return fmodEvent;
}

// Set the FMOD event
void FmodCarSoundManager::SetFmodEvent(const FString& newFmodEvent)
{
    fmodEvent = newFmodEvent;
}

// Start the sound event
void FmodCarSoundManager::StartEventSound()
{
    if (!eventInstance.isValid())
    {
        CreateInstance();
    }
    eventInstance.start();
}

// Set the sound play position
void FmodCarSoundManager::SetSoundPlayPosition(const FVector& position)
{
    eventInstance.set3DAttributes(UFMODBlueprintStatics::ToFMODVector(position));
    
    FMOD_3D_ATTRIBUTES attributes;
    eventInstance.get3DAttributes(&attributes);

    FVector pos = FVector(attributes.position.x, attributes.position.y, attributes.position.z);
}

// Pause the sound event
void FmodCarSoundManager::PauseEventSound()
{
    if (eventInstance.isValid() && IsEventPlaying())
    {
        eventInstance.setPaused(true);
    }
}

// Resume the sound event
void FmodCarSoundManager::ResumeEventSound()
{
    if (eventInstance.isValid() && !IsEventPlaying())
    {
        eventInstance.setPaused(false);
    }
}

// Check if the event is playing
bool FmodCarSoundManager::IsEventPlaying() const
{
    if (eventInstance.isValid())
    {
        FMOD_STUDIO_PLAYBACK_STATE playbackState;
        eventInstance.getPlaybackState(&playbackState);
        return playbackState == FMOD_STUDIO_PLAYBACK_STATE_PLAYING;
    }
    return false;
}

// Destructor
FmodCarSoundManager::~FmodCarSoundManager()
{
    if (eventInstance.isValid())
    {
        eventInstance.release();
    }
}

// Create an instance of the FMOD event
void FmodCarSoundManager::CreateInstance()
{
    if (!eventInstance.isValid())
    {
        UFMODBlueprintStatics::EventInstanceCreate(eventInstance, fmodEvent);
    }
}
