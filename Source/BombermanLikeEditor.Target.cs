// - Mario Palmero [2017], zlib/libpng licensed.

using UnrealBuildTool;
using System.Collections.Generic;

public class BombermanLikeEditorTarget : TargetRules
{
	public BombermanLikeEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;

		ExtraModuleNames.AddRange( new string[] { "BombermanLike" } );
	}
}
