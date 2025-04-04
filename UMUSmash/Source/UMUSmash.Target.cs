

using UnrealBuildTool;
using System.Collections.Generic;

public class UMUSmashTarget : TargetRules
{
	public UMUSmashTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		DefaultBuildSettings = BuildSettingsVersion.V5;

		ExtraModuleNames.AddRange( new string[] { "UMUSmash" } );
	}
}
