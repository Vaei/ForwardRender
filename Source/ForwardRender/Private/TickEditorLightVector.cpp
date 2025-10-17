// Copyright (c) Jared Taylor


#include "TickEditorLightVector.h"

#include "EngineUtils.h"
#include "Components/LightComponent.h"
#include "Engine/DirectionalLight.h"
#include "Materials/MaterialParameterCollection.h"
#include "Materials/MaterialParameterCollectionInstance.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(TickEditorLightVector)

void UTickEditorLightVector::Tick(float DeltaTime)
{
	if (!GEditor)
	{
		return;
	}

	const UWorld* World = GEditor->GetEditorWorldContext().World();
	if (!World || World->WorldType != EWorldType::Editor)
	{
		return;
	}

	const ADirectionalLight* DirectionalLight = nullptr;
	int32 NumLights = 0;
	for (TActorIterator<ADirectionalLight> It(World); It; ++It)
	{
		DirectionalLight = *It;
		NumLights++;
		break;
	}

	if (!DirectionalLight)
	{
		return;
	}

	if (NumLights > 1)
	{
		FMessageLog("TickEditorLightVector").Warning()
			->AddToken(FTextToken::Create(FText::FromString(TEXT("Multiple Directional Lights found in the scene. TickEditorLightVector will only use the first one found."))))
			->AddToken(FTextToken::Create(FText::FromString(World->GetMapName())));
	}

	const FVector LightDirWS = DirectionalLight->GetLightComponent()->GetForwardVector();

	const UMaterialParameterCollection* MPC = Cast<UMaterialParameterCollection>(MPCPath.TryLoad());
	if (!MPC)
	{
		return;
	}

	UMaterialParameterCollectionInstance* Instance = World->GetParameterCollectionInstance(MPC);
	if (Instance)
	{
		Instance->SetVectorParameterValue(ParameterName, FLinearColor(LightDirWS));
	}
}
