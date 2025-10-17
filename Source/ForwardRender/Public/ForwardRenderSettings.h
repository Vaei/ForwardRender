// Copyright (c) Jared Taylor

#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettingsBackedByCVars.h"
#include "ForwardRenderSettings.generated.h"

/**
 * 
 */
UCLASS(Config=Editor)
class FORWARDRENDER_API UForwardRenderSettings : public UDeveloperSettingsBackedByCVars
{
	GENERATED_BODY()

public:
	/** Whether this feature is enabled */
	UPROPERTY(Config, EditAnywhere, Category="Light Vector")
	bool bLightVectorEnabled = true;

	/** Path to the Material Parameter Collection asset */
	UPROPERTY(Config, EditAnywhere, Category="Light Vector", meta=(DisplayName="Light Vector MPC Path"))
	FSoftObjectPath LightVectorMPCPath;

	/** Name of the vector parameter to update */
	UPROPERTY(Config, EditAnywhere, Category="Light Vector")
	FName LightVectorParameterName = TEXT("LightVector");

	/** Invert the light vector (-ForwardVector) */
	UPROPERTY(Config, EditAnywhere, Category="Light Vector")
	bool bInvertLightVector = false;
	
	/** Warn if multiple directional lights are found */
	UPROPERTY(Config, EditAnywhere, Category="Light Vector")
	bool bWarnOnMultipleDirectionalLights = true;
};
