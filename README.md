# snake-the-console-game
Snake run in cmd.exe on Windows. No guarantees for portability. Tested on one Windows 7 machine only.

This is a small project I bodged together over a short period of time because I friggin' could. It utilizes Windows specific APIs and a lot of horrible non-portable code written in a weird, spaghetti-like way. Don't ever tell anyone I told you it was okay to do coding like this. I make no guarantees that this program will work on any other computer, nor that it won't break other computers when it's run on them. I've previously made code that screwed up a friend's terminal input when he tried running it in Wine on Linux, so be warned.

The program itself is pretty simple. You control a snake which navigates the command prompt according to the input provided using the WASD keys as arrow keys. The standard settings utilize a cmd prompt with size 60x30 characters, and has a timeout of 50 milliseconds between each frame. However, it's possible to override these settings through command line arguments using the following  rules:

1 integer argument: Specify a different timeout length
2 integer arguments: Specify a different width and height. Argument 1 is the width (in character widths) and argument 2 is the height (in character heights).
3 integer arguments: Specify both a new timeout and a new width and height. Argument 1 is the timeout value, argument 2 is the width and argument 3 is the height.

Any other number of command line arguments results in the default settings. If you input non-integer values, the program will probably break somehow. You may try it, if you dare.

Known bugs and glitches:

- The program might occasionally hang around at a frame for longer than expected. This is because of the way the timeout is implemented. I've done it so that it should timeout pretty uniformely around the specified timeout, by measuring how much time it takes to go through the game loop and then subtracting that time from the timeout. However, if for some reason the elapsed time is greater than the timeout, the loop just keeps going with a delay. This shouldn't normally be noticeable, but you never know. Also, if for some reason the elapsed time is erroneously calculated to be sub-zero, the program will assume zero time has elapsed and sleep for a full timeout period, which may or may not cause a noticeable delay.

- There's a fun little glitch in the game when you move the snake into the bottom right corner of the cmd prompt, at which point it'll start spewing out graphics in ways that don't quite make sense at first glance. This is caused by the screen going to the next line when it has printed out a link in the snake's body, and thus scrolling and leaving the printed links there. Because fully erasing the screen's content through each iteration would be wasteful, I'm just erasing the graphical representation of the last link each iteration. Since these graphics will be in the wrong place, they won't be erased until the snake tracks over them again. Due to the scrolling and reblitting, dummy snake food items will also be created.

The amount of extra graphics created is dependent on how many links there are in the snake's body. If the snake is short, the game is still fully playable, but if it's long, we do have a bit of a problem. It effectively makes the game unplayable by removing the sense of where the snake is in the cmd prompt - everything is just a bunch of O-s. I've left the glitch there to horrify future players and/or spectators of this game who are unaware of this, but if you want to fix it, feel free to do so. It's simply a matter of detecting when the snake has a link in this bottom corner, then at those times clearing the screen using the clearScreen function I've provided in the "wndfuncs.h" header file. This should eliminate the glitch if done correctly.

I hope you enjoy playing this game for the 5 minutes you'll feel entertained by it. I certainly had fun making it. If it breaks your PC, lemme know, and I'll add a stronger warning in the readme file. If you're interested in porting this game to a Linux environment (or for that matter any other platform), feel free to fork this project and build upon it. I'm sorry for not commenting my code properly - I might revisit it later on and add some notes to make things clearer - but I'm assuming few people will come across it at all to begin with, and I probably won't build much upon it later on myself, either. So there's probably (hopefully) not much harm done. Do you have suggestions for improvements? Notify me! I promise I'll consider reading them before I ignore them and move on with my life.

Why did I make this, again? Well, mostly just for fun. I realized that since I could use these Windows APIs to muck around with the cmd cursor, I could as well see what I could do with it. And making the old classic, Snake, seemed like a reasonable choice. I feel like I've learned a few things while working on this project, and I might make other small and similar ones in the future, so stay tuned! (But don't expect too much.)

Thanks for reading this through. I appreciate that people put up with my rambling. And enjoy the game!
Sincerely,
Butterbeard Studios.
