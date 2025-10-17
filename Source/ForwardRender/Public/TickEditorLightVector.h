// Copyright (c) Jared Taylor

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "TickableEditorObject.h"
#include "TickEditorLightVector.generated.h"

/**
 * Assigns the Directional Light's forward vector to a Material Parameter Collection vector parameter every editor tick.
 * The purpose of this is to not require simulating to preview lighting and materials that depend on light direction in the editor.
 */
UCLASS(Config=Editor)
class FORWARDRENDER_API UTickEditorLightVector : public UObject, public FTickableEditorObject
{
	GENERATED_BODY()

public:
	/** Path to the Material Parameter Collection asset */
	UPROPERTY(Config, EditAnywhere, Category="Light Vector")
	FSoftObjectPath MPCPath;

	/** Name of the vector parameter to update */
	UPROPERTY(Config, EditAnywhere, Category="Light Vector")
	FName ParameterName = TEXT("LightVector");

	/** Warn if multiple directional lights are found */
	UPROPERTY(Config, EditAnywhere, Category="Light Vector")
	bool bWarnOnMultipleLights = true;
	
	// FTickableEditorObject
	virtual void Tick(float DeltaTime) override;
	virtual TStatId GetStatId() const override { RETURN_QUICK_DECLARE_CYCLE_STAT(UTickEditorLightVector, STATGROUP_Tickables); }
	virtual bool IsTickable() const override { return true; }
};
