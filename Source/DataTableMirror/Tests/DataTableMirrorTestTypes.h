// Copyright DCode. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "DataTableMirrorTestTypes.generated.h"

USTRUCT()
struct FDataTableMirrorTest_SimpleRow : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY()
	FString Label;

	UPROPERTY()
	float Value = 0.0f;

	UPROPERTY()
	int32 Count = 0;
};
