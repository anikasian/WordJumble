/********************************************************************************
Title:      wordjumble.h
Created on: March 8th, 2018
Purpose:    Stores words into a multimap, scramble words, levels up,
            keeps track of current word, current levels and outputs
            data onto a textfile.
Usage:      main.cpp
Build with: use makefile
********************************************************************************/

#ifndef WORDJUMBLE_H_
#define WORDJUMBLE_H_

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <map>
using namespace std;


class WordJumble {
private:
   multimap<int, string*> listOfWords;
   multimap<int, string*>::iterator posOfGame;

public: 
   /** Creating a WordJumble object and adding words into my multimap.
     @Pre:  input-file was able to open. User has never played this game yet.
     @Post: multimap has all of the words from the file.
     @Param wordfile: inputfile.
   */
   WordJumble(istream & wordfile);

   /** Creating a WordJumble object and adding words into my multimap.
     @Pre:  user has played this game before and has exited from it.
            The words are from the gamedata.txt and all of those words
            are letters from a-z (no other characters).
     @Post: multimap has all of the words from the file.
     @Param vecOfWords: vector of all the words the user was playing with.
   */
   WordJumble(vector<string> & vecOfWords);

   /** Deleting all of the contents in the multimap.
     @Pre:  none
     @Post: multimap is empty.
   */
   ~WordJumble() { listOfWords.clear(); }

   /** Scrambles a word.
     @Pre:  none.
     @Post: returns scrambled words.
     @Param word: word string to be scrambled.
   */
   string scrambleWord(string word);

   /** Retrieves the user's current game difficulty.
     @Pre:  none.
     @Post: returns user's current difficulty level (int).
   */
   int getCurrentLevel() const { return posOfGame->first - 2; }
   
   /** Retrieves the size of a word.
     @Pre:  none.
     @Post: returns the current size of the word (int).
   */
   int getWordSize() const { return getCurrentLevel() + 2; }

   /** Retrieves the current word the user is on.
     @Pre:  none.
     @Post: returns a string of the word the user is on.
   */
   string getCurrentWord() const { return *(posOfGame->second); }

   /** Retrieves the number of words to guess in the game.
     @Pre:  none.
     @Post: returns an int of size of multimap.
   */
   int getNumOfWords() const { return listOfWords.size(); }

   /** Moves the iterator posOfGame to the next word in the multimap.
     @Pre:  user has either guessed the previous word or used a lifeline.
     @Post: iterator is now pointing to the next word in the multimap.
   */
   void nextWord() { ++posOfGame; }

   /** Moves the iterator posOfGame to the previous word in the multimap.
     @Pre:  user has used a lifeline and there are no new words in the map of
            that same difficulty level.
     @Post: iterator is now pointing to the previous word in the multimap.
   */
   void prevWord() { --posOfGame; }

   /** Moves iterator posOfGame to the start of the list of words.
     @Pre:  none.
     @Post: iterator is now pointing to the start of the list of words.
   */
   void startWord() { posOfGame = listOfWords.begin(); }

   /** Skips all of the words at current level and iterator is pointing at
       the next level of the multimap.
     @Pre:  user was able to answer three words of current level correctly.
     @Post: user it at the next level of words.
     @Param currentLevel: current level the user is on before advancing.
   */
   void goToNextDifficultyLevel(int currentLevel);

   /** Either goes to the next word in the level or the first word in the level.
     @Pre:  user still has lifelines.
     @Post: user is still in the current level. Either the next word or the first word.
   */
   void useLifeline();

   /** Output the user's current game stats and the remaining words that were unsolved in
       an output file.
     @Pre:  user must have solved at least one word.
     @Post: first line of the file will have game stats and following that will be the words.
     @Param outFile: the output file declaired in main.
     @Param currentLevel: the current/last level the user was on before he/she exited the game.
     @Param lastWordSolved: last word the user solved
     @Param highestGuesses: the highest streak of guesses from all games of that input file.
   */
   void outputToFile(ostream & outFile, int currentLevel, string lastWordSolved, int highestGuesses);

   /** Prints all of multimap contents: word size and word.
     @Pre:  multimap must not be empty.
     @Post: list of all of the words in multimap.
   */

};

#endif // WORDJUMBLE_H_