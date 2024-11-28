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
#include "BuyProductAPI.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FBuyProductDelegate, const FTxResult&, Result, bool, bWasSuccessful);

UCLASS()
class SUISDK_API UBuyProductAPI : public UAPIBase
{
    GENERATED_BODY()

public:
    UPROPERTY(BlueprintAssignable, Category = "TransactionsAPI")
        FBuyProductDelegate OnBuyProduct;

    UFUNCTION(BlueprintCallable, Category = "TransactionsAPI", meta = (BlueprintInternalUseOnly = "true"))
        static UBuyProductAPI* BuyProduct(const FString& ProductId);

    virtual void Activate() override;

private:
    UPROPERTY()
    FString ProductId;
};
