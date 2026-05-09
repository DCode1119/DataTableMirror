// Copyright DCode. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "DataTableMirrorSettings.generated.h"

UCLASS(Config = DataTableMirror, DefaultConfig)
class UDataTableMirrorSettings : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY(Config, EditAnywhere, Category = "DataTable Mirror")
	FString OutputDirectory = TEXT("Data/JSON");

	UPROPERTY(Config, EditAnywhere, Category = "DataTable Mirror")
	bool bAutoExportOnSave = true;
};
