// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "APIClient.h"
#include "APIBase.h"
#include "APIDataTypes.h"
#include "HttpManager.h"
#include "HttpModule.h"
#include "Runtime/Online/HTTP/Public/Http.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "Runtime/JsonUtilities/Public/JsonUtilities.h"
#include <string>
#include "Kismet/BlueprintAsyncActionBase.h"
#include "Runtime/JsonUtilities/Public/JsonObjectConverter.h"
#include "Kismet/GameplayStatics.h"
#include "UnlistProductAPI.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FUnlistProductDelegate, const FTxResult&, Result, bool, bWasSuccessful);

UCLASS()
class SUISDK_API UUnlistProductAPI : public UAPIBase
{
    GENERATED_BODY()

public:
    UPROPERTY(BlueprintAssignable, Category = "TransactionsAPI")
        FUnlistProductDelegate OnUnlistProduct;

    UFUNCTION(BlueprintCallable, Category = "TransactionsAPI", meta = (BlueprintInternalUseOnly = "true"))
        static UUnlistProductAPI* UnlistProduct(const FString& ProductId);

    virtual void Activate() override;

private:

	UPROPERTY()
    FString ProductId;
};
