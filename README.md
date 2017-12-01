# BombermanLike

This game has been created under Unreal Engine 4.18.1, but does not use any fancy feature so it should be portable to older versions.

No other library or tool beside the named engine has been used.

Future Roadmap:

- Create a camera that follows players and zooms in and out depending on the distance between them. This should be pretty easy. Find the medium point and controll the Z value of the camera.
- Make use of the procedural map generation already present in the code. Right now the map is always created as a 11x11 grid but the function that is called accepts any dimension, so it should be just add a randomizer. Destructible blocks are already randomized.
- Clear the pickups. Right now the pickups that are left in the scenario aren't being earesed. Notice that pickups only are created when blocks are destroyed, so there is no info of pickups inside blocks. Just iterate through all of them. Pretty easy in BP, but not so trivial in C++ because they don't have an unique component or actor type accesible from C++ to iterate through. I suppose that I will create a new actor and make them inherit from that.
- Remote control pickup. I think there are two easy solutions for this. Possess the bomb as a pawn or use the input of the match controller to move the bomb instead. 
- AI. The Pawn has two hardcoded checks to PlayerController that should be removed, nothing very difficult or anything that should take long. With that, we could create our own AIController and create a BehaviourTree and a Blackboard for our AI agents. AI should be very straight forward at first, almost everything has been created thinking on the presence of more pawns. Behaviours: destroy blocks at first, avoid bombs, try to kill player. UE4 provides a lot of useful tools to do this simple.
- There is a minor bug (or feature) that should be fixed. The player doesn't collide with its own bombs. This is done through custom Object Channels. It was a quick solution but in the original games this only happens until the player steps out of its own bomb or a bomb created in the same tile the player is standing up. UE4 doesn't provides a quick solution, using it's movement component, to selectively choose wich player can step over or not. This should be fixed for the AI implementation because the 2 channel hack is not scalable to more pawns.
- Make it look pretty. At first I added some transition lapses to the interface thinking I would have time to animate the in and out of the screens. And so many other things that could be done to make it look decent enough. Most of the things have been thought or implemented to be easy to improve them visually.
