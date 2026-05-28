
#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h" // <-- Change this include
#include "Village/House/House.h"
#include "UKey_HouseArray.generated.h"

UCLASS(BlueprintType, Blueprintable)
class CAUWENBERGHYASMINZOMBIERUNTIME_API UUKey_HouseArray : public UObject
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AI Memory")
	TArray<AHouse*> VisitedHouses;
};