# WordJumble
Very simple spelling game where you can save your game and return to it.

## Compiling
Using a makefile. Type: `make` <br><br>
OS Compiled in:
- macOS Sierra 10.12
- Ubuntu 16.04

## Running the game
Starting a new game: `./WordJumble inputfile.txt` <br>
Returning to a game: `./WordJumble` <br>
   ###### NOTE: You cannot return to a game you haven't started or quit from.
   
## How it works
- Each difficulty level corresponds to the length of the word. <br>
- Solving 3 consecutive words in one level will advance you to the next level. <br>
- If you've mispelled 3 consecutive words, you lose the game and all data will be wiped. <br>
- You are given up to 5 lifelines where you can try a different word in the same level. <br>
- You may exit the game at any time. Type `/exit`. Return by running the program with no input file. <br>
- First level of difficulty will be 3 letter words. <br>
- To view the number of lives, guesses and the longest word you've spelled correctly, you can type: `/stats`. <br>
- All commands have are prompted with a forward-slash. Typing `exit` instead of `/exit` is considered an actual word in the game.

****

I have provided `inputfile.txt` with the highest difficulty being 12 letters. You may edit or create or your list of words as long as it follows these conditions:
- Distinction between each adjacent level is one letter. You cannot advance from a level of 5 letters to a level of 7.<br>
- First level must be a minimum of 3 letters. Program will not work if there is a level with 2 letters.<br>
- This program does not know if the words in the textfile are dictionary words or not. It will read a word and erase any characters that are not from a-z. It will remove capital letters, numbers, and nother notations. <br>
    - For instance: <br>
		    - flOweRs will be taken as flwes <br>
		    - 45Newbaby will be taken as ewbaby <br>
		    - http://google.com will be taken as httpgooglecom <br>
        
## Bugs
Program does not handle whitespace. If you type a space right after your guess, it will result in a segfault. If there is a segfault just run the test again by typing any one of the two commands above.
