

using UnrealBuildTool;
using System.Collections.Generic;

public class PlatformFighterStarterKitEditorTarget : TargetRules
{
	public PlatformFighterStarterKitEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.V5;

		ExtraModuleNames.AddRange( new string[] { "PlatformFighterStarterKit" } );
	}
}
