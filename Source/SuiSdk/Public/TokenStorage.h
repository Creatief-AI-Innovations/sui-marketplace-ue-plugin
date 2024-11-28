#pragma once

#include "CoreMinimal.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/SaveGame.h"
#include "TokenStorage.generated.h"

UCLASS()
class SUISDK_API UTokenSaveGame : public USaveGame
{
    GENERATED_BODY()

public:
    UPROPERTY(BlueprintReadWrite, Category = "TokenStorage")
    FString Token;
};

UCLASS()
class SUISDK_API UTokenStorage : public UObject
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, Category = "TokenStorage")
    static void SaveToken(const FString& Token);

    UFUNCTION(BlueprintCallable, Category = "TokenStorage")
    static FString GetToken();

    UFUNCTION(BlueprintCallable, Category = "TokenStorage")
    static void RemoveToken();
};