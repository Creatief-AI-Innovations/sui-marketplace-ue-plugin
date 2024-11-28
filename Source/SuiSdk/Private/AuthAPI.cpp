#include "AuthAPI.h"
#include "TokenStorage.h"


UAuthAPI* UAuthAPI::LoginWithSuiSDK(const FString& Username, const FString& Password)
{
    UAuthAPI* Node = NewObject<UAuthAPI>();
    Node->Username = Username;
    Node->Password = Password;
    return Node;
}

void UAuthAPI::Activate()
{
    Super::Activate();
    FString Data;
    TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&Data);
    Writer->WriteObjectStart();
    Writer->WriteValue(TEXT("username"), Username);
    Writer->WriteValue(TEXT("password"), Password);
    Writer->WriteObjectEnd();
    Writer->Close();
    APIClient->Post(TEXT("/v1/login"), Data, [this](FHttpResponsePtr Response, bool bWasSuccessful)
        {
            FAuthResponse AuthResponse;
            if (bWasSuccessful && Response->GetResponseCode() == 200)
            {
                AuthResponse = FAuthResponse(Response->GetContentAsString());
                UTokenStorage::SaveToken(AuthResponse.token);
                OnLogin.Broadcast(AuthResponse, true);
            }
            else
            {
                OnLogin.Broadcast(FAuthResponse(), false);
            }
        });
}