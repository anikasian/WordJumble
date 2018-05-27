/********************************************************************************
Title:      userinterface.h
Created on: March 8th, 2018
Purpose:    Displays welcome signs and game stats on the terminal.
Usage:      main.cpp
Build with: use makefile
********************************************************************************/

#ifndef USERINTERFACE_H_
#define USERINTERFACE_H_

#include "wordjumble.h"

class UserInterface {
public:
   /** Displays the welcome sign.
     @Pre:  none.
     @Post: displays the welcome sign in terminal.
   */
   void welcome() const;

   /** Displays the help section.
     @Pre:  none.
     @Post: displays the list of commands in terminal.
   */
   void helpDisplay() const;

   /** Displays the user stats.
     @Pre:  user must have guessed or attempted to guess one word.
     @Post: displays stats on the terminal.
   */
   void displayStats(int level, int tries, int lives, string word) const;

   /** Displays the welcome sign from returning guest on the same input file.
     @Pre:  user must have inputted the inputfile and played on it at least once.
     @Post: displays the welcome sign along with the game stats.
   */
   void welcomeBack(int level, string word, int guess) const;
};


#endif // USERINTERFACE_H_