// Copyright 2024 Dexter.Wan. All Rights Reserved. 
// EMail: 45141961@qq.com
// Website: https://dt.cq.cn/

using UnrealBuildTool;

public class DTGdalForUe : ModuleRules
{
	public DTGdalForUe(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
		
		PublicIncludePaths.AddRange( new string[] { } );
		PrivateIncludePaths.AddRange( new string[] { } );
		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
				"Projects",
				"DTGdalForUeLibrary",
			}
		);
		PrivateDependencyModuleNames.AddRange( new string[] { } );
		DynamicallyLoadedModuleNames.AddRange(new string[] { } );
	}
}
