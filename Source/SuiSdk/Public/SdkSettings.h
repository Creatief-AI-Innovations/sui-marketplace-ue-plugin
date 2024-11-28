// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "SdkSettings.generated.h"

/**
 * 
 */
UCLASS(config = SuiSdk, defaultconfig)
class SUISDK_API USdkSettings : public UObject
{
	GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, config, Category = "General")
        FString Hostname;

    UPROPERTY(EditAnywhere, config, Category = "General")
        FString ApiKey;

	USdkSettings()
	{
		Hostname = "";
		ApiKey = "";
	}
	
};
