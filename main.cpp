#include "userinterface.h"

int main(int argc, char *argv[]) {
   // Starting game simulation
   UserInterface newGame;

   /********************** COMMAND LINE HAS INPUT FILE **********************
      This if-statement will always create a new game. Whatever data was 
      saved in the gamedata.txt file from the previous game will be wiped out.
   */
   if (argc == 2) {
      string inputFile = argv[1];
      ifstream inFile(inputFile.c_str(), ios::in);
      ofstream outFile("gamedata.txt", ios::out | ios::trunc);

      // Checking if file is good.
      if (!inFile.is_open())
         cerr << "Error: Could not open file." << endl;
      else {  
         WordJumble obj(inFile);

         // File has already been parsed. No need for it anymore.
         inFile.close();

         newGame.welcome();

         unsigned int NUM_OF_CORRECT = 0, NUM_OF_TRIES = 3, NUM_OF_LIVES = 5, TOTAL_CORRECT = 0;
         string lastSolved = "";

         string guess;
         getline(cin, guess);

         while(true) {
            cout << obj.scrambleWord(obj.getCurrentWord()) << endl;
            cout << "> ";
            getline(cin, guess);

            if (guess == "/help")
               newGame.helpDisplay();
            else if(guess == "/lifeline") {
               if (NUM_OF_LIVES == 1)
                  cout << "Out of lifelines." << endl;
               else {
                  obj.useLifeline();
                  NUM_OF_LIVES--;
               }
            }
            else if(guess == "/stats")
               newGame.displayStats(obj.getCurrentLevel(), NUM_OF_TRIES, NUM_OF_LIVES, lastSolved);
            else if(guess == "/exit")
               break;
            else {
               if (guess == obj.getCurrentWord()) {
                  lastSolved = obj.getCurrentWord();
                  if (NUM_OF_CORRECT == 2) {
                     // reset number of correct guesses back to 0 in new level.
                     NUM_OF_CORRECT = 0;

                     obj.goToNextDifficultyLevel(obj.getWordSize());

                     cout << "Correct! You've skipped to level " << obj.getCurrentLevel() << "!" << endl;
                     cout << "Next word: " << endl;
                  }
                  else {
                     cout << "Correct! Next word: " << endl;
                     obj.nextWord();
                     NUM_OF_CORRECT++;
                  }
                  TOTAL_CORRECT++;
               }
               else {
                  if (NUM_OF_TRIES == 1) {
                     cout << "Incorrect. Out of tries. Game over." << endl;
                     exit(1);
                  }
                  else {
                     cout << "Incorrect. Try again: " << endl;
                     NUM_OF_TRIES--;
                  }
               }
            }
         }

         /*
            I've only reached this point if user has exited the program.
            The user's highest level, longest word guessed and the remaining 
            unsolved list of words will be outputted to gamedata.txt which is a 
            textfile that the program creates.
         */

         // Function to output the remaining words to gamedata.txt
         obj.outputToFile(outFile, obj.getCurrentLevel(), obj.getCurrentWord(), TOTAL_CORRECT);

         // Ending program
         exit(1);

      }
   }

   /********************** COMMAND LINE HAS NO INPUT FILES ****************
      This else statement will continue on with the game on the same input file
      that was parsed.
   */
   else if (argc == 1) {
      ifstream inFile("gamedata.txt");
      /*
         Checking whether gamedata.txt exists or if gamedata.txt is empty.
         If gamedata.txt doesn't exist then user hasn't played any game yet.
         If gamedata.txt is empty, user ended the previous game.
      */
      if(!inFile.is_open() ||  inFile.peek() == ifstream::traits_type::eof())
         cout << "Error: No existing game to return to." << endl;
      else {
         /*
            gamedata.txt has the user's highest level so far, the longest string that
            was solved, the number of correct guesses and the list of remaining words
            the user hasn't guessed yet from the same input file.
         */

         // Simulate the game
         UserInterface newGame;

         int highestLevel, numOfWordsGuessed;
         string longestSolvedWord, words;
         vector<string> vecOfRemainingWords;

         // Gathering the first 3 info and then pushing all remaining words into a vector.
          inFile >> highestLevel >> longestSolvedWord >> numOfWordsGuessed;
         while ( inFile.good()) {
            getline(inFile, words);
            vecOfRemainingWords.push_back(words);
         }

          inFile.close();

         // Inputting my words into a multimap.
         WordJumble obj(vecOfRemainingWords);

         newGame.welcomeBack(highestLevel, longestSolvedWord, numOfWordsGuessed);

         unsigned int NUM_OF_CORRECT = 0, NUM_OF_TRIES = 3, NUM_OF_LIVES = 5, TOTAL_CORRECT = 0;
         string lastSolved = "";

         string guess;
         cout << ">  ";
         getline(cin, guess);

         while(true) {
            cout << obj.scrambleWord(obj.getCurrentWord()) << endl;
            cout << "> ";
            getline(cin, guess);

            if (guess == "/help")
               newGame.helpDisplay();
            else if(guess == "/lifeline") {
               if (NUM_OF_LIVES == 1)
                  cout << "Out of lifelines." << endl;
               else {
                  obj.useLifeline();
                  NUM_OF_LIVES--;
               }
            }
            else if(guess == "/stats")
               newGame.displayStats(obj.getCurrentLevel(), NUM_OF_TRIES, NUM_OF_LIVES, lastSolved);
            else if(guess == "/exit")
               break;
            else {
               if (guess == obj.getCurrentWord()) {
                  lastSolved = obj.getCurrentWord();
                  if (NUM_OF_CORRECT == 2) {
                     // reset number of correct guesses back to 0 in new level.
                     NUM_OF_CORRECT = 0;

                     obj.goToNextDifficultyLevel(obj.getWordSize());

                     cout << "Correct! You've skipped to level " << obj.getCurrentLevel() << "!" << endl;
                     cout << "Next word: " << endl;
                  }
                  else {
                     cout << "Correct! Next word: " << endl;
                     obj.nextWord();
                     NUM_OF_CORRECT++;
                  }
                  TOTAL_CORRECT++;
               }
               else {
                  if (NUM_OF_TRIES == 1) {
                     cout << "Incorrect. Out of tries. Game over." << endl;
                     exit(1);
                  }
                  else {
                     cout << "Incorrect. Try again: " << endl;
                     NUM_OF_TRIES--;
                  }
               }
            }
         }

         /*
            I've only reached this point if user has exited the program.
            The old gamedata.txt will be wiped and the user's highest level, 
            longest word guessed and the remaining unsolved list of words 
            will be outputted to gamedata.txt.
         */

         if (TOTAL_CORRECT > numOfWordsGuessed)
            numOfWordsGuessed = TOTAL_CORRECT;

         // declaring ofstream will wipe the contents in the file.
         ofstream outFile("gamedata.txt", ios::out | ios::trunc);

         // Function to output the remaining words to gamedata.txt
         obj.outputToFile(outFile, obj.getCurrentLevel(), lastSolved, numOfWordsGuessed);

         // Ending program
         exit(1);
      }
   }

   return 0;
}

   