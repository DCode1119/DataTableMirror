// Copyright DCode. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Commandlets/Commandlet.h"
#include "DataTableMirrorCommandlet.generated.h"

UCLASS()
class UDataTableMirrorCommandlet : public UCommandlet
{
	GENERATED_BODY()

public:
	UDataTableMirrorCommandlet();

	virtual int32 Main(const FString& Params) override;
};
