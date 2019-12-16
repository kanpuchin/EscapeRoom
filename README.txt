Game name : escape room game

Function : Solo play, Multi play

1. Solo play : You can solve problems and enjoy escape room alone

2. Multi play : You can enjoy this game with another player
	- Wandering in the map, if you press 'c' you can send message to another player.

To test only solo play version of this game, just execute 'escape' file.
	ex)	./escape

To test multi play version of this game, please execute following format
	: ./escape (another player's hostname) (another player's port number) (your port number)
	ex) 	./escape hostname_a 15000 13000 //in your computer (host = hostname_b)
		./escape hostname_b 13000 15000 //in another computer (host = hostname_a)

Level1 : Quiz for [h] chest and hint for door both crossed.

Level2, Level3 : Only three hint for last door are crossed.
		Quiz for chests and other doors are same.
