// Copyright DCode. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

class IConsoleObject;

class FDataTableMirrorModule final : public IModuleInterface
{
public:
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

private:
	void HandleObjectPreSave(UObject* Object,
		FObjectPreSaveContext SaveContext);
	void GenerateMissingJsonCommand();

	IConsoleObject* GenerateJsonCommandHandle = nullptr;
};
