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
	UPROPERTY()
	bool bHasWarned = false;
	
	// FTickableEditorObject
	virtual void Tick(float DeltaTime) override;
	virtual TStatId GetStatId() const override { RETURN_QUICK_DECLARE_CYCLE_STAT(UTickEditorLightVector, STATGROUP_Tickables); }
	virtual bool IsTickable() const override;
};
