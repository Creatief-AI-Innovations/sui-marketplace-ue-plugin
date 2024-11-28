#pragma once

#include "CoreMinimal.h"
#include "APIClient.h"
#include "APIBase.h"
#include "HttpManager.h"
#include "HttpModule.h"
#include "TokenStorage.h"
#include "Runtime/Online/HTTP/Public/Http.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "Runtime/JsonUtilities/Public/JsonUtilities.h"
#include <string>
#include "Kismet/BlueprintAsyncActionBase.h"
#include "Runtime/JsonUtilities/Public/JsonObjectConverter.h"
#include "Kismet/GameplayStatics.h"
#include "AuthAPI.generated.h"

USTRUCT(BlueprintType)
struct FLoginCredentials
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AuthAPI")
    FString Username;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AuthAPI")
    FString Password;
};

USTRUCT(BlueprintType)
struct FAuthData
{

    GENERATED_BODY()

        UPROPERTY(EditAnywhere, BlueprintReadWrite)
        FString username;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
        FString wallet;

    FAuthData() {};

    FAuthData(FString _username, FString _wallet) {

        username = _username;
        wallet = _wallet;

    }

};

USTRUCT(BlueprintType)
struct FAuthResponse
{

    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
        bool success;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
        FString token;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
        FString message;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
        FAuthData data;

    FAuthResponse() {};

    FAuthResponse(bool _success, FString _token, FString _message, FAuthData _data) {

        success = _success;
        token = _token;
        message = _message;
        data = _data;

    }

    /* Don't Forget to setup your project
    Add #include "Runtime/JsonUtilities/Public/JsonObjectConverter.h" in
    file with this structs.
    Also you need add "Json", "JsonUtilities" in Build.cs */

    FAuthResponse(FString _json_) {
        FAuthResponse _tmpAuthResponse;

        FJsonObjectConverter::JsonObjectStringToUStruct<FAuthResponse>(
            _json_,
            &_tmpAuthResponse,
            0, 0);

        success = _tmpAuthResponse.success;
        token = _tmpAuthResponse.token;
        message = _tmpAuthResponse.message;
        data = _tmpAuthResponse.data;
    }

};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FAuthResponseDelegate, const FAuthResponse&, AuthResponse, bool, bWasSuccessful);

UCLASS()
class SUISDK_API UAuthAPI : public UAPIBase
{
    GENERATED_BODY()

public:
    virtual void Activate() override;

public:
    UPROPERTY(BlueprintAssignable, Category = "AuthAPI")
        FAuthResponseDelegate OnLogin;

    UFUNCTION(BlueprintCallable, Category = "SuiMarketAuthAPI", meta = (BlueprintInternalUseOnly = "true"))
        static UAuthAPI* LoginWithSuiSDK(const FString& Username, const FString& Password);

    UPROPERTY() 
        FString Username;

    UPROPERTY()
        FString Password;

};