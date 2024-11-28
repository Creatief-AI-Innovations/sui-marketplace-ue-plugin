#include "APIClient.h"
#include "HttpModule.h"
#include "TokenStorage.h"
#include "Interfaces/IHttpResponse.h"

void UAPIClient::Initialize()
{
    Headers.Add(TEXT("Content-Type"), TEXT("application/json"));
    Headers.Add(TEXT("x-api-key"), Settings->ApiKey);
    Headers.Add(TEXT("ngrok-skip-browser-warning"), TEXT("69420"));
}

void UAPIClient::Get(const FString& URL, const TFunction<void(FHttpResponsePtr, bool)>& Callback)
{
    TSharedRef<IHttpRequest, ESPMode::ThreadSafe> Request = FHttpModule::Get().CreateRequest();
    Request->OnProcessRequestComplete().BindLambda([Callback](FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
    {
        Callback(Response, bWasSuccessful);
    });

    Request->SetURL(Settings->Hostname + "/api" + URL);
    Request->SetVerb(TEXT("GET"));
    for (const auto& Header : Headers)
    {
        Request->SetHeader(Header.Key, Header.Value);
    }
	FString Token = UTokenStorage::GetToken();
    if (!Token.IsEmpty())
    {
        Request->SetHeader(TEXT("Authorization"), FString::Printf(TEXT("Bearer %s"), *Token));
    }
    Request->ProcessRequest();
}

void UAPIClient::Post(const FString& URL, const FString& Data, const TFunction<void(FHttpResponsePtr, bool)>& Callback)
{
    TSharedRef<IHttpRequest, ESPMode::ThreadSafe> Request = FHttpModule::Get().CreateRequest();
    Request->OnProcessRequestComplete().BindLambda([Callback](FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
    {
        Callback(Response, bWasSuccessful);
    });

    Request->SetURL(Settings->Hostname+ "/api" + URL);
    Request->SetVerb(TEXT("POST"));
    for (const auto& Header : Headers)
    {
        Request->SetHeader(Header.Key, Header.Value);
    }
    FString Token = UTokenStorage::GetToken();
    if (!Token.IsEmpty())
    {
        Request->SetHeader(TEXT("Authorization"), FString::Printf(TEXT("Bearer %s"), *Token));
    }
    Request->SetContentAsString(Data);
    Request->ProcessRequest();
}

void UAPIClient::Put(const FString& URL, const FString& Data, const TFunction<void(FHttpResponsePtr, bool)>& Callback)
{
    TSharedRef<IHttpRequest, ESPMode::ThreadSafe> Request = FHttpModule::Get().CreateRequest();
    Request->OnProcessRequestComplete().BindLambda([Callback](FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
    {
        Callback(Response, bWasSuccessful);
    });

    Request->SetURL(Settings->Hostname + "/api" + URL);
    Request->SetVerb(TEXT("PUT"));
    for (const auto& Header : Headers)
    {
        Request->SetHeader(Header.Key, Header.Value);
    }
    FString Token = UTokenStorage::GetToken();
    if (!Token.IsEmpty())
    {
        Request->SetHeader(TEXT("Authorization"), FString::Printf(TEXT("Bearer %s"), *Token));
    }
    Request->SetContentAsString(Data);
    Request->ProcessRequest();
}

void UAPIClient::Delete(const FString& URL, const TFunction<void(FHttpResponsePtr, bool)>& Callback)
{
    TSharedRef<IHttpRequest, ESPMode::ThreadSafe> Request = FHttpModule::Get().CreateRequest();
    Request->OnProcessRequestComplete().BindLambda([Callback](FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
    {
        Callback(Response, bWasSuccessful);
    });

    Request->SetURL(Settings->Hostname + "/api" + URL);
    Request->SetVerb(TEXT("DELETE"));
    for (const auto& Header : Headers)
    {
        Request->SetHeader(Header.Key, Header.Value);
    }
    FString Token = UTokenStorage::GetToken();
    if (!Token.IsEmpty())
    {
        Request->SetHeader(TEXT("Authorization"), FString::Printf(TEXT("Bearer %s"), *Token));
    }
    Request->ProcessRequest();
}