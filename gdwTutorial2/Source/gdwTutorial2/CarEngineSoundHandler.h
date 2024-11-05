// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FmodCarSoundManagerSetParameters.h"
#include "CarEngineSoundHandler.generated.h"

UCLASS(Blueprintable)  // This makes the class accessible to Blueprints
class GDWTUTORIAL2_API CarEngineSoundHandler : public UObject
{
    GENERATED_BODY()

public:
    // Constructor
    CarEngineSoundHandler();
    

    // Blueprint callable constructor with parameter for max speed
    UFUNCTION(BlueprintCallable, Category = "Car Sound")
    void Initialize(float maxSpeed);

    // Getter for FMOD Engine Sound Manager
    UFUNCTION(BlueprintCallable, Category = "Car Sound")
    FmodCarSoundManager* GetFmodEngineObject() const;

    // Speed accessors
    UFUNCTION(BlueprintCallable, Category = "Car Sound")
    float GetCurrentSpeed() const;

    UFUNCTION(BlueprintCallable, Category = "Car Sound")
    void SetCurrentSpeed(float speed);

    // Getter for max speed
    UFUNCTION(BlueprintCallable, Category = "Car Sound")
    float GetMaxSpeed() const;

    // Update the car engine sound based on the speed
    UFUNCTION(BlueprintCallable, Category = "Car Sound")
    void UpdateCarEngineSound();

private:
    // Calculate speed fraction (currentSpeed / maxSpeed)
    float GetSpeedFraction() const;

    // Check for significant difference between values
    bool HasSignificantDifference(float a, float b, float tolerance = 0.01f) const;

    // Variables
    UPROPERTY(BlueprintReadWrite, Category = "Car Sound", meta = (AllowPrivateAccess = "true"))
    float currentSpeed;

    UPROPERTY(BlueprintReadOnly, Category = "Car Sound", meta = (AllowPrivateAccess = "true"))
    float maxSpeed;

    // FMOD sound manager
    UPROPERTY(BlueprintReadOnly, Category = "Car Sound", meta = (AllowPrivateAccess = "true"))
    FmodCarSoundManagerSetParameters* setEngineParameters;

    // Sound settings
    const FString parameterName = "InstrumentIndex";
    const FString bankPath = "bank:/Master";
    const FString eventPath = "event:/CarEngineMulti";
};
