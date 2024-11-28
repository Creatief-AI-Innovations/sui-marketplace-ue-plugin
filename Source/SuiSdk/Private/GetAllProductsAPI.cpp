#include "GetAllProductsAPI.h"

UGetAllProductsAPI* UGetAllProductsAPI::GetAllProducts(const FString& CollectionId)
{
    UGetAllProductsAPI* Node = NewObject<UGetAllProductsAPI>();
    Node->CollectionId = CollectionId;
    return Node;
}

void UGetAllProductsAPI::Activate()
{
    Super::Activate();
    APIClient->Get(FString::Printf(TEXT("/v1/market/products?cid=%s"), *CollectionId), [this](FHttpResponsePtr Response, bool bWasSuccessful)
        {
            FProductsListResponse ProductsResponse;
            if (bWasSuccessful && Response->GetResponseCode() == 200)
            {
				FString Content = Response->GetContentAsString();
                //GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, *Content);
				ProductsResponse = FProductsListResponse(Response->GetContentAsString());
				OnGetAllProducts.Broadcast(ProductsResponse.data, true);
            }
            else
            {
                OnGetAllProducts.Broadcast(TArray<FProductItem>(), false);
            }
        });
}