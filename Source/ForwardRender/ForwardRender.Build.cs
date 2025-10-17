// Copyright (c) Jared Taylor

using UnrealBuildTool;

public class ForwardRender : ModuleRules
{
	public ForwardRender(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
				"CoreUObject",
				"Engine",
				"UnrealEd",
			}
			);
	}
}
