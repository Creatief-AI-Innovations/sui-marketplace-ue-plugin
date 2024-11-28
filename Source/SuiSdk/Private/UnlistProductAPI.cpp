#include "UnlistProductAPI.h"

UUnlistProductAPI* UUnlistProductAPI::UnlistProduct(const FString& ProductId)
{
    UUnlistProductAPI* Node = NewObject<UUnlistProductAPI>();
    Node->ProductId = ProductId;
    return Node;
}

void UUnlistProductAPI::Activate()
{
	Super::Activate();
    FString Data;
    TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&Data);
    Writer->WriteObjectStart();
    Writer->WriteValue(TEXT("pid"), ProductId);
    Writer->WriteObjectEnd();
    Writer->Close();

    APIClient->Post(TEXT("/v1/market/product/unlist"), Data, [this](FHttpResponsePtr Response, bool bWasSuccessful)
        {
            FTxResult Result;
            if (bWasSuccessful && Response->GetResponseCode() == 200)
            {
				Result = FTxResult(Response->GetContentAsString());
				OnUnlistProduct.Broadcast(Result, true);
            }
            else
            {
                OnUnlistProduct.Broadcast(Result, false);
            }
        });
}