// Copyright DCode. All Rights Reserved.

#include "DataTableMirrorCommandlet.h"
#include "DataTableMirrorStatics.h"

UDataTableMirrorCommandlet::UDataTableMirrorCommandlet()
{
	IsClient = false;
	IsEditor = true;
	IsServer = false;
	LogToConsole = true;
}

int32 UDataTableMirrorCommandlet::Main(const FString& Params)
{
	FDataTableMirrorStatics::GenerateMissingJsonFiles();

	UE_LOG(LogTemp, Display,
		TEXT("DataTable Mirror: JSON export complete."));

	return 0;
}
