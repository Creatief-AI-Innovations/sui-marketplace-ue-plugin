#include "GetOwnedProductsAPI.h"

UGetOwnedProductsAPI* UGetOwnedProductsAPI::GetOwnedProducts(const FString& CollectionId)
{
    UGetOwnedProductsAPI* Node = NewObject<UGetOwnedProductsAPI>();
    Node->CollectionId = CollectionId;
    return Node;
}

void UGetOwnedProductsAPI::Activate()
{
    Super::Activate();
    APIClient->Get(FString::Printf(TEXT("/v1/user/product/owned?cid=%s"), *CollectionId), [this](FHttpResponsePtr Response, bool bWasSuccessful)
        {
            FProductsListResponse productsResponse;
            if (bWasSuccessful && Response->GetResponseCode() == 200)
            {
				FString Content = Response->GetContentAsString();
				//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, *Content);
				productsResponse = FProductsListResponse(Response->GetContentAsString());
				OnGetOwnedProducts.Broadcast(productsResponse.data, true);
            }
            else
            {
                OnGetOwnedProducts.Broadcast(TArray<FProductItem>(), false);
            }
        });
}