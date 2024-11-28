#include "BuyProductAPI.h"

UBuyProductAPI* UBuyProductAPI::BuyProduct(const FString& ProductId)
{
    UBuyProductAPI* Node = NewObject<UBuyProductAPI>();
    Node->ProductId = ProductId;
    return Node;
}

void UBuyProductAPI::Activate()
{
	Super::Activate();
    FString Data;
    TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&Data);
    Writer->WriteObjectStart();
    Writer->WriteValue(TEXT("pid"), ProductId);
    Writer->WriteObjectEnd();
    Writer->Close();

    APIClient->Post(TEXT("/v1/market/product/buy"), Data, [this](FHttpResponsePtr Response, bool bWasSuccessful)
        {
            FTxResult Result;
            if (bWasSuccessful && Response->GetResponseCode() == 200)
            {
				Result = FTxResult(Response->GetContentAsString());
				OnBuyProduct.Broadcast(Result, true);
            }
            else
            {
                OnBuyProduct.Broadcast(Result, false);
            }
        });
}