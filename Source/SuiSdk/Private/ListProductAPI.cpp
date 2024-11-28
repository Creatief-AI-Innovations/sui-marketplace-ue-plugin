#include "ListProductAPI.h"

UListProductAPI* UListProductAPI::ListProduct(const FString& ProductId, float Price)
{
    UListProductAPI* Node = NewObject<UListProductAPI>();
    Node->ProductId = ProductId;
    Node->Price = Price;
    return Node;
}

void UListProductAPI::Activate()
{
    Super::Activate();
    FString Data;
    TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&Data);
    Writer->WriteObjectStart();
    Writer->WriteValue(TEXT("pid"), ProductId);
    Writer->WriteValue(TEXT("price"), Price);
    Writer->WriteObjectEnd();
    Writer->Close();

    APIClient->Post(TEXT("/v1/market/product/sell"), Data, [this](FHttpResponsePtr Response, bool bWasSuccessful)
        {
            FTxResult Result;
            if (bWasSuccessful && Response->GetResponseCode() == 200)
            {
				Result = FTxResult(Response->GetContentAsString());
				OnListProduct.Broadcast(Result, true);
            }
            else
            {
                OnListProduct.Broadcast(Result, false);
            }
        });
}