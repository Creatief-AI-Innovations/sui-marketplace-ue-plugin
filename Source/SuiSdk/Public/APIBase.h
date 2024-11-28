// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "APIClient.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "APIBase.generated.h"

/**
 * 
 */
UCLASS()
class SUISDK_API UAPIBase : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()


private:
	UFUNCTION()
		void init();

protected:

	UPROPERTY()
		UAPIClient* APIClient;


public:
	virtual void Activate() override;

};
