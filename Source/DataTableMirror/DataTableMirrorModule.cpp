// Copyright DCode. All Rights Reserved.

#include "DataTableMirrorModule.h"
#include "DataTableMirrorStatics.h"
#include "DataTableMirrorSettings.h"

#include "Engine/DataTable.h"
#include "HAL/IConsoleManager.h"
#include "UObject/ObjectSaveContext.h"

void FDataTableMirrorModule::StartupModule()
{
#if WITH_EDITOR
	const bool bAutoExport =
		GetDefault<UDataTableMirrorSettings>()->bAutoExportOnSave;

	if (bAutoExport)
	{
		FCoreUObjectDelegates::OnObjectPreSave.AddRaw(
			this,
			&FDataTableMirrorModule::HandleObjectPreSave
		);
	}

	GenerateJsonCommandHandle =
		IConsoleManager::Get().RegisterConsoleCommand(
			TEXT("DataTableMirror.GenerateMissingJson"),
			TEXT("Generates JSON files for DataTables"
				" that are missing them in the output directory."),
			FConsoleCommandDelegate::CreateRaw(
				this,
				&FDataTableMirrorModule::GenerateMissingJsonCommand),
			ECVF_Default
		);
#endif
}

void FDataTableMirrorModule::ShutdownModule()
{
#if WITH_EDITOR
	FCoreUObjectDelegates::OnObjectPreSave.RemoveAll(this);

	if (GenerateJsonCommandHandle)
	{
		IConsoleManager::Get().UnregisterConsoleObject(
			GenerateJsonCommandHandle);
		GenerateJsonCommandHandle = nullptr;
	}
#endif
}

void FDataTableMirrorModule::HandleObjectPreSave(
	UObject* Object, FObjectPreSaveContext SaveContext)
{
#if WITH_EDITOR
	UDataTable* DataTable = Cast<UDataTable>(Object);
	if (!DataTable || !DataTable->RowStruct)
	{
		return;
	}

	if (DataTable->HasAnyFlags(RF_ClassDefaultObject | RF_Transient))
	{
		return;
	}

	FDataTableMirrorStatics::ExportDataTableToJson(DataTable);
#endif
}

void FDataTableMirrorModule::GenerateMissingJsonCommand()
{
	FDataTableMirrorStatics::GenerateMissingJsonFiles();
}

IMPLEMENT_MODULE(FDataTableMirrorModule, DataTableMirror)
