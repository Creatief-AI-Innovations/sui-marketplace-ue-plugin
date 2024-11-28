#include "TokenStorage.h"
#include "Misc/ConfigCacheIni.h"

const FString TokenSlotName = TEXT("MarketplaceTokenSlot");

void UTokenStorage::SaveToken(const FString& Token)
{
    UTokenSaveGame* SaveGameInstance = Cast<UTokenSaveGame>(UGameplayStatics::CreateSaveGameObject(UTokenSaveGame::StaticClass()));
    SaveGameInstance->Token = Token;
    UGameplayStatics::SaveGameToSlot(SaveGameInstance, TokenSlotName, 0);
}

FString UTokenStorage::GetToken()
{
    UTokenSaveGame* LoadGameInstance = Cast<UTokenSaveGame>(UGameplayStatics::LoadGameFromSlot(TokenSlotName, 0));
    return LoadGameInstance ? LoadGameInstance->Token : FString();
}

void UTokenStorage::RemoveToken()
{
    UGameplayStatics::DeleteGameInSlot(TokenSlotName, 0);
}