// - Mario Palmero [2017], zlib/libpng licensed.

using UnrealBuildTool;
using System.Collections.Generic;

public class BombermanLikeTarget : TargetRules
{
	public BombermanLikeTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;

		ExtraModuleNames.AddRange( new string[] { "BombermanLike" } );
	}
}
