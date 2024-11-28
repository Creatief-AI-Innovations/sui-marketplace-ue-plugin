#pragma once

#include "CoreMinimal.h"
#include "Http.h"
#include "SdkSettings.h"
#include "APIClient.generated.h"


UCLASS()
class SUISDK_API UAPIClient : public UObject
{
    GENERATED_BODY()

private:
    TMap<FString, FString> Headers;

public:

    UAPIClient() {
        Settings = GetMutableDefault<USdkSettings>();
    }

    void Initialize();

    void Get(const FString& URL, const TFunction<void(FHttpResponsePtr, bool)>& Callback);

    void Post(const FString& URL, const FString& Data, const TFunction<void(FHttpResponsePtr, bool)>& Callback);

    void Put(const FString& URL, const FString& Data, const TFunction<void(FHttpResponsePtr, bool)>& Callback);

    void Delete(const FString& URL, const TFunction<void(FHttpResponsePtr, bool)>& Callback);

    const USdkSettings* Settings;
};