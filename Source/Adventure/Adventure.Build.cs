// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.IO;

public class Adventure : ModuleRules
{
	public Adventure(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;


		/*
		PublicIncludePaths.AddRange(
			new string[] {
				Path.Combine(ModuleDirectory, "../../ThirdParty/pocketsphinx-master/include"),
				Path.Combine(ModuleDirectory, "path/to/generated/sphinx_config.h_directory")
			}
		);
		*/

		PublicIncludePaths.AddRange(
			new string[] {
				Path.Combine(ModuleDirectory, "../../ThirdParty/aquila-master")
			}
		);


		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay", "NavigationSystem", "AIModule", "Niagara", "EnhancedInput", "UMG", "ProceduralMeshComponent",  "Chaos", "Slate", "SlateCore", "Json", "JsonUtilities"});
		PublicIncludePaths.AddRange(new string[] { "Public" });

		// PrivateDependencyModuleNames.AddRange(new string[] {  });




		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
