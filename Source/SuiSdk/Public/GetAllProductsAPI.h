// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "APIClient.h"
#include "APIBase.h"
#include "HttpManager.h"
#include "HttpModule.h"
#include "Runtime/Online/HTTP/Public/Http.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "Runtime/JsonUtilities/Public/JsonUtilities.h"
#include <string>
#include "Kismet/BlueprintAsyncActionBase.h"
#include "Runtime/JsonUtilities/Public/JsonObjectConverter.h"
#include "Kismet/GameplayStatics.h"
#include "APIDataTypes.h"
#include "GetAllProductsAPI.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGetAllProductsDelegate, const TArray<FProductItem>&, Products, bool, bWasSuccessful);

UCLASS()
class SUISDK_API UGetAllProductsAPI : public UAPIBase
{
    GENERATED_BODY()

public:
    UPROPERTY(BlueprintAssignable, Category = "ProductsAPI")
        FGetAllProductsDelegate OnGetAllProducts;

    UFUNCTION(BlueprintCallable, Category = "SuiMarketProductsAPI", meta = (BlueprintInternalUseOnly = "true"))
        static UGetAllProductsAPI* GetAllProducts(const FString& CollectionId);

    virtual void Activate() override;

private:
    UPROPERTY()
    FString CollectionId;
};
