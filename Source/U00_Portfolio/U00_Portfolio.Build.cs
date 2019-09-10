// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;

public class U00_Portfolio : ModuleRules
{
	public U00_Portfolio(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "UMG"});

        PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "NavigationSystem", "AIModule", "GameplayTasks" });

        PrivateDependencyModuleNames.AddRange(new string[] { "Slate","SlateCore" });

    }
}
