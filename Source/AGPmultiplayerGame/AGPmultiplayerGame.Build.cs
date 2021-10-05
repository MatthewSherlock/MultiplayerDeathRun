// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class AGPmultiplayerGame : ModuleRules
{
	public AGPmultiplayerGame(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay" });
	}
}
