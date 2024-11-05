#pragma once

#include "CoreMinimal.h"
#include "FMODBlueprintStatics.h"
#include "FMODEvent.h"
#include "FMODStudioModule.h"

/**
 * Handles the FMOD car sound events.
 */
 
class FmodCarSoundManager
{
public:
    // Constructor
    FmodCarSoundManager(const FString& fmodEvent);

    // Get the FMOD event
    FString GetFmodEvent() const;

    // Set the FMOD event

    // Start the sound event
    void StartEventSound();

    // Set the sound play position
    void SetSoundPlayPosition(const FVector& position);

    // Pause the sound event
    void PauseEventSound();

    // Resume the sound event
    void ResumeEventSound();

    // Check if the event is playing
    bool IsEventPlaying() const;

    // Destructor
    ~FmodCarSoundManager();

private:
    // Create an instance of the FMOD event
    void CreateInstance();

protected:
    FString fmodEvent;
    FMOD::Studio::EventInstance eventInstance;
	void SetFmodEvent(const FString& newFmodEvent);

};
