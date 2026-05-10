// Copyright DCode. All Rights Reserved.

#include "CoreMinimal.h"
#include "Misc/AutomationTest.h"
#include "Misc/FileHelper.h"
#include "Misc/Paths.h"
#include "HAL/FileManager.h"
#include "Serialization/JsonReader.h"
#include "Serialization/JsonSerializer.h"
#include "Engine/DataTable.h"

#include "DataTableMirrorStatics.h"
#include "DataTableMirrorTestTypes.h"

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FDataTableMirrorExportValidRows,
	"DataTableMirror.Export.ExportsValidRows",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool FDataTableMirrorExportValidRows::RunTest(const FString& Parameters)
{
	UDataTable* DataTable = NewObject<UDataTable>(
		GetTransientPackage(), FName("DTMirror_Test_ValidRows"));
	if (!DataTable)
	{
		AddError(TEXT("Failed to create test DataTable"));
		return false;
	}

	DataTable->RowStruct = FDataTableMirrorTest_SimpleRow::StaticStruct();

	FDataTableMirrorTest_SimpleRow Row1;
	Row1.Label = TEXT("Alpha");
	Row1.Value = 1.5f;
	Row1.Count = 10;

	FDataTableMirrorTest_SimpleRow Row2;
	Row2.Label = TEXT("Beta");
	Row2.Value = 2.5f;
	Row2.Count = 20;

	DataTable->AddRow("RowAlpha", Row1);
	DataTable->AddRow("RowBeta", Row2);

	FDataTableMirrorStatics::ExportDataTableToJson(DataTable);

	const FString JsonDir = FPaths::ProjectDir() / TEXT("Data/JSON");
	const FString JsonPath = JsonDir / TEXT("DTMirror_Test_ValidRows.json");

	TestTrue(TEXT("JSON file should exist"), FPaths::FileExists(JsonPath));

	FString JsonContent;
	TestTrue(TEXT("Should read JSON file"),
		FFileHelper::LoadFileToString(JsonContent, *JsonPath));

	TArray<TSharedPtr<FJsonValue>> JsonArray;
	TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(JsonContent);
	TestTrue(TEXT("JSON should be valid array"),
		FJsonSerializer::Deserialize(Reader, JsonArray));

	TestEqual(TEXT("Should have 2 rows"), JsonArray.Num(), 2);

	if (JsonArray.Num() >= 2)
	{
		const TSharedPtr<FJsonObject>* Obj1 = nullptr;
		TestTrue(TEXT("First row should be object"),
			JsonArray[0]->TryGetObject(Obj1));
		if (Obj1)
		{
			TestEqual(TEXT("First row Name"),
				(*Obj1)->GetStringField(TEXT("Name")), TEXT("RowAlpha"));
			TestEqual(TEXT("First row Label"),
				(*Obj1)->GetStringField(TEXT("Label")), TEXT("Alpha"));
			TestEqual(TEXT("First row Count"),
				(*Obj1)->GetIntegerField(TEXT("Count")), 10);
		}

		const TSharedPtr<FJsonObject>* Obj2 = nullptr;
		TestTrue(TEXT("Second row should be object"),
			JsonArray[1]->TryGetObject(Obj2));
		if (Obj2)
		{
			TestEqual(TEXT("Second row Name"),
				(*Obj2)->GetStringField(TEXT("Name")), TEXT("RowBeta"));
			TestEqual(TEXT("Second row Count"),
				(*Obj2)->GetIntegerField(TEXT("Count")), 20);
		}
	}

	IFileManager::Get().Delete(*JsonPath);
	return !HasAnyErrors();
}


IMPLEMENT_SIMPLE_AUTOMATION_TEST(FDataTableMirrorExportEmptyTable,
	"DataTableMirror.Export.ExportsEmptyTable",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool FDataTableMirrorExportEmptyTable::RunTest(const FString& Parameters)
{
	UDataTable* DataTable = NewObject<UDataTable>(
		GetTransientPackage(), FName("DTMirror_Test_Empty"));
	DataTable->RowStruct = FDataTableMirrorTest_SimpleRow::StaticStruct();

	FDataTableMirrorStatics::ExportDataTableToJson(DataTable);

	const FString JsonPath =
		FPaths::ProjectDir() / TEXT("Data/JSON/DTMirror_Test_Empty.json");

	TestTrue(TEXT("JSON file should exist"), FPaths::FileExists(JsonPath));

	FString JsonContent;
	FFileHelper::LoadFileToString(JsonContent, *JsonPath);

	TArray<TSharedPtr<FJsonValue>> JsonArray;
	TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(JsonContent);
	TestTrue(TEXT("JSON should be valid array"),
		FJsonSerializer::Deserialize(Reader, JsonArray));

	TestEqual(TEXT("Empty table should produce empty array"),
		JsonArray.Num(), 0);

	IFileManager::Get().Delete(*JsonPath);
	return !HasAnyErrors();
}


IMPLEMENT_SIMPLE_AUTOMATION_TEST(FDataTableMirrorExportNullRowStruct,
	"DataTableMirror.Export.HandlesNullRowStruct",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool FDataTableMirrorExportNullRowStruct::RunTest(const FString& Parameters)
{
	UDataTable* DataTable = NewObject<UDataTable>(
		GetTransientPackage(), FName("DTMirror_Test_NullStruct"));

	FDataTableMirrorStatics::ExportDataTableToJson(DataTable);

	const FString JsonPath =
		FPaths::ProjectDir() / TEXT("Data/JSON/DTMirror_Test_NullStruct.json");

	TestFalse(TEXT("JSON file should NOT be created for null RowStruct"),
		FPaths::FileExists(JsonPath));

	return !HasAnyErrors();
}
