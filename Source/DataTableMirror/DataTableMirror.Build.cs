using UnrealBuildTool;

public class DataTableMirror : ModuleRules
{
	public DataTableMirror(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PrivateDependencyModuleNames.AddRange(new[]
		{
			"Core",
			"CoreUObject",
			"Engine",
			"Json",
			"JsonUtilities",
			"AssetRegistry",
			"UnrealEd"
		});
	}
}
