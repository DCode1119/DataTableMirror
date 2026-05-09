// Copyright DCode. All Rights Reserved.

#include "DataTableMirrorStatics.h"
#include "DataTableMirrorSettings.h"

#include "AssetRegistry/AssetRegistryModule.h"
#include "Engine/DataTable.h"
#include "HAL/FileManager.h"
#include "Misc/FileHelper.h"
#include "Misc/Paths.h"
#include "Serialization/JsonWriter.h"
#include "Serialization/JsonSerializer.h"
#include "JsonObjectConverter.h"

void FDataTableMirrorStatics::ExportDataTableToJson(UDataTable* DataTable)
{
	if (!DataTable || !DataTable->RowStruct)
	{
		return;
	}

	const FString OutputDirSetting =
		GetDefault<UDataTableMirrorSettings>()->OutputDirectory;

	const FString JsonDir = FPaths::ProjectDir() / OutputDirSetting;
	const FString JsonPath = JsonDir / (DataTable->GetName() + TEXT(".json"));

	IFileManager::Get().MakeDirectory(*JsonDir, true);

	TArray<TSharedPtr<FJsonValue>> JsonRows;

	for (const TPair<FName, uint8*>& Pair : DataTable->GetRowMap())
	{
		const FName RowName = Pair.Key;
		const uint8* RowData = Pair.Value;

		if (!RowData)
		{
			continue;
		}

		TSharedRef<FJsonObject> RowJson = MakeShared<FJsonObject>();
		RowJson->SetStringField(TEXT("Name"), RowName.ToString());

		TSharedPtr<FJsonObject> StructJson = MakeShared<FJsonObject>();

		FJsonObjectConverter::UStructToJsonObject(
			DataTable->RowStruct,
			RowData,
			StructJson.ToSharedRef(),
			0,
			0
		);

		for (const TPair<FString, TSharedPtr<FJsonValue>>& Field :
			StructJson->Values)
		{
			RowJson->SetField(Field.Key, Field.Value);
		}

		JsonRows.Add(MakeShared<FJsonValueObject>(RowJson));
	}

	FString JsonString;

	const TSharedRef<TJsonWriter<>> Writer =
		TJsonWriterFactory<>::Create(&JsonString);

	FJsonSerializer::Serialize(JsonRows, Writer);

	if (!FFileHelper::SaveStringToFile(JsonString, *JsonPath))
	{
		UE_LOG(LogTemp, Warning,
			TEXT("DataTableMirror: Failed to export JSON: %s"), *JsonPath);
	}
}

bool FDataTableMirrorStatics::GenerateMissingJsonFiles()
{
	bool bSuccess = true;

	FAssetRegistryModule& AssetRegistryModule =
		FModuleManager::LoadModuleChecked<FAssetRegistryModule>(
			TEXT("AssetRegistry"));

	FARFilter Filter;
	Filter.ClassPaths.Add(UDataTable::StaticClass()->GetClassPathName());
	Filter.bRecursiveClasses = true;

	TArray<FAssetData> DataTableAssets;
	AssetRegistryModule.Get().GetAssets(Filter, DataTableAssets);

	const FString OutputDirSetting =
		GetDefault<UDataTableMirrorSettings>()->OutputDirectory;

	const FString JsonDir = FPaths::ProjectDir() / OutputDirSetting;

	for (const FAssetData& AssetData : DataTableAssets)
	{
		UDataTable* DataTable = Cast<UDataTable>(AssetData.GetAsset());
		if (!DataTable)
		{
			bSuccess = false;
			continue;
		}

		const FString JsonPath =
			JsonDir / (DataTable->GetName() + TEXT(".json"));

		if (!FPaths::FileExists(JsonPath))
		{
			ExportDataTableToJson(DataTable);
		}
	}

	return bSuccess;
}
