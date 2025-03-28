

using UnrealBuildTool;
using System.Collections.Generic;

public class PlatformFighterStarterKitTarget : TargetRules
{
	public PlatformFighterStarterKitTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		DefaultBuildSettings = BuildSettingsVersion.V5;

		ExtraModuleNames.AddRange( new string[] { "PlatformFighterStarterKit" } );
	}
}
