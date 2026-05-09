// Copyright DCode. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

class UDataTable;

struct FDataTableMirrorStatics
{
	static void ExportDataTableToJson(UDataTable* DataTable);
	static bool GenerateMissingJsonFiles();
};
