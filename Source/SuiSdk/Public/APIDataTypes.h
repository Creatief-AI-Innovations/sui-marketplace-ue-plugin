// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HttpManager.h"
#include "HttpModule.h"
#include "Runtime/Online/HTTP/Public/Http.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "Runtime/JsonUtilities/Public/JsonUtilities.h"
#include <string>
#include "Kismet/BlueprintAsyncActionBase.h"
#include "Runtime/JsonUtilities/Public/JsonObjectConverter.h"
#include "Kismet/GameplayStatics.h"
#include "UObject/NoExportTypes.h"
#include "APIDataTypes.generated.h"

USTRUCT(BlueprintType)
struct FDynamicAttribute
{
    GENERATED_BODY()

        UPROPERTY(EditAnywhere, BlueprintReadWrite)
        TMap<FString, FString> Properties;
};

FString JsonValueToString(const TSharedPtr<FJsonValue>& JsonValue)
{
    if (!JsonValue.IsValid())
        return TEXT("");

    if (JsonValue->Type == EJson::String)
        return JsonValue->AsString();
    else if (JsonValue->Type == EJson::Number)
        return FString::SanitizeFloat(JsonValue->AsNumber());
    else if (JsonValue->Type == EJson::Boolean)
        return JsonValue->AsBool() ? TEXT("true") : TEXT("false");

    return TEXT("");
}

TMap<FString, FString> JsonObjectToMap(const TSharedPtr<FJsonObject>& JsonObject)
{
    TMap<FString, FString> ResultMap;

    if (!JsonObject.IsValid())
        return ResultMap;

    for (const auto& Pair : JsonObject->Values)
    {
        if (Pair.Value.IsValid())
        {
            ResultMap.Add(Pair.Key, JsonValueToString(Pair.Value));
        }
    }

    return ResultMap;
}

TArray<FDynamicAttribute> ParseAttributes(const TSharedPtr<FJsonObject>& JsonObject, const FString& FieldName)
{
    TArray<FDynamicAttribute> Attributes;
    const TArray<TSharedPtr<FJsonValue>>* AttributesArray;

    if (JsonObject->TryGetArrayField(FieldName, AttributesArray))
    {
        for (const auto& AttributeValue : *AttributesArray)
        {
            const TSharedPtr<FJsonObject> AttrObject = AttributeValue->AsObject();
            if (AttrObject.IsValid())
            {
                FDynamicAttribute Attribute;
                Attribute.Properties = JsonObjectToMap(AttrObject);
                Attributes.Add(Attribute);
            }
        }
    }

    return Attributes;
}




USTRUCT(BlueprintType)
struct FListings
{

    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
        FString id;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
        int32 price;

    FListings() {};

    FListings(FString _id, int32 _price) {

        id = _id;
        price = _price;

    }

};


USTRUCT(BlueprintType)
struct FProductItem
{

    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
        FString id;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
        FString name;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
        FString media_url;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
        FString token_id;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
        int32 price;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
        FString price_str;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
        bool owned;


    UPROPERTY(EditAnywhere, BlueprintReadWrite)
        TArray <FDynamicAttribute> attributes;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
        TArray<FListings> listings;

    FProductItem() {};

    FProductItem(
        FString _id,
        FString _name,
        FString _media_url,
        FString _token_id,
        int32 _price,
        FString _price_str,
        bool _owned,
        TArray<FDynamicAttribute> _attributes,
        TArray<FListings> _listings
    ) {

        id = _id;
        token_id = _token_id;
        name = _name;
        media_url = _media_url;
        token_id = _token_id;
        price = _price;
        price_str = _price_str;
        owned = _owned;
        attributes = _attributes;
        listings = _listings;

    }

};


USTRUCT(BlueprintType)
struct FProductsListResponse
{

    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
        bool success;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
        FString message;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
        TArray<FProductItem> data;

    FProductsListResponse() {};

    FProductsListResponse(bool _success, FString _message, TArray<FProductItem> _data) {
        success = _success;
        message = _message;
        data = _data;
    }

    FProductsListResponse(const FString& JsonString)
    {
        TSharedPtr<FJsonObject> JsonObject;
        TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(JsonString);

        if (FJsonSerializer::Deserialize(Reader, JsonObject) && JsonObject.IsValid())
        {
            // Use regular converter for basic fields
            FProductsListResponse TempResponse;
            FJsonObjectConverter::JsonObjectToUStruct(JsonObject.ToSharedRef(), &TempResponse);

            success = TempResponse.success;
            message = TempResponse.message;
            data = TempResponse.data;

            // Handle dynamic attributes using helper
            const TArray<TSharedPtr<FJsonValue>>* DataArray;
            if (JsonObject->TryGetArrayField(TEXT("data"), DataArray))
            {
                for (int32 i = 0; i < data.Num() && i < DataArray->Num(); i++)
                {
                    const TSharedPtr<FJsonObject> ProductObject = (*DataArray)[i]->AsObject();
                    if (ProductObject.IsValid())
                    {
                        data[i].attributes = ParseAttributes(ProductObject, TEXT("attributes"));
                    }
                }
            }
        }
    }

};


USTRUCT(BlueprintType)
struct FTxResult
{

    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
        bool success;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
        FString message;

    FTxResult() {};

    FTxResult(bool _success, FString _message) {

        success = _success;
        message = _message;

    }

    FTxResult(FString _json_) {
        FTxResult _tmpTransactionResult;

        FJsonObjectConverter::JsonObjectStringToUStruct<FTxResult>(
            _json_,
            &_tmpTransactionResult,
            0, 0);

        success = _tmpTransactionResult.success;
        message = _tmpTransactionResult.message;
    }

};


/**
 * 
 */
UCLASS()
class SUISDK_API UAPIDataTypes : public UObject
{
	GENERATED_BODY()
	
};
