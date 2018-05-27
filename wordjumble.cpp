#include "wordjumble.h"

WordJumble::WordJumble(istream & wordfile) {
   string word;
   while (getline(wordfile, word)) {
      //Using erase() from string to erase any characters that are not letters.
      word.erase(remove_if(word.begin(), word.end(), [](char c) { 
         return !isalpha(c); }
         ), word.end());
      listOfWords.insert(pair<int,string*>(word.size(), new string(word)));
   }

   /*
      posOfGame is pointing to the beginning of the listOfWords.
      Purpose of posOfGame is to keep track of which word the user is up on
   */
   posOfGame = listOfWords.begin();

}

WordJumble::WordJumble(vector<string> & vecOfWords) {
   /*
      adding words from vector into the multimap.
      No need to handle characters that are not from a-z because 
      this vector retrieved words from gamedata.txt and the words in that file
      have had all other characters eliminated.
   */
   for (int i = 1; i < vecOfWords.size(); i++)
      listOfWords.insert(pair<int, string*>((vecOfWords.at(i)).size(), new string(vecOfWords.at(i))));
      
      // Erasing any empty strings/whitespaces.
      listOfWords.erase(0);
   /*
      posOfGame is pointing to the beginning of the listOfWords.
      Purpose of posOfGame is to keep track of which word the user is up on
   */
   posOfGame = listOfWords.begin();

}

string WordJumble::scrambleWord(string word) {
   srand(time(0)); // get random number

   istringstream ss(word);
   string token;
   ss >> token;

   // shuffling the characters in the string token
   for (int i = 0; i < token.size(); i++) {
      int index = (rand()%token.size());
      swap(token[i], token[index]);
   }

   // preventing the randomizer from returning the actual word.
   if (token != word)
      return token;
   else
      return scrambleWord(token);
}


void WordJumble::goToNextDifficultyLevel(int currentLevel) {
   posOfGame = listOfWords.upper_bound(currentLevel);
}

void WordJumble::useLifeline() {
   int wordsize = posOfGame->first;
   nextWord();
   /*
      Checking if the next word is still in the same level.
      If the next word is a new level, posOfGame will point to the 
      first word in the level.
   */
   if (getWordSize() == wordsize)
      return;
   else
      posOfGame = listOfWords.lower_bound(wordsize);
      
}

void WordJumble::outputToFile(ostream & outFile, int currentLevel, string lastWordSolved, int highestGuesses) {
   // Outputting the game stats on the first line
   outFile << currentLevel << " " << lastWordSolved << " " << highestGuesses << endl;
   
   // After the first line will be the list of words. Iterating through the position of the current word to the end.
   for(multimap<int, string*>::iterator it = posOfGame; it != listOfWords.end(); ++it) {
      outFile << getCurrentWord() << endl;
      nextWord();
   }
}
