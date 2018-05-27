#include "userinterface.h"

void UserInterface::welcome() const {
      cout << "\n\n=====================================================================\n"
       << "\t\t\tWelcome to Word Jumble!\n"
       << "=====================================================================\n\n"
       << "\t\t\t\tRULES\n"
       << "  (1) You have up to 3 guesses.\n"
       << "  (2) Type \"/lifeline\" for another word. You have up to 5 lifelines.\n"
       << "  (3) You may exit at any time. Type \"/exit\".\n"
       << "  (4) Type \"/stats\" to see # of guesses and lifelines left.\n"
       << "  (5) Type \"/help\" any time for list of commands.\n\n"
       << "\t\t\tPlease ENTER to begin." << endl;
}

void UserInterface::welcomeBack(int level, string word, int guess) const {
   cout << "\n\n=====================================================================\n"
       << "\t\t\tWelcome to Word Jumble!\n"
       << "=====================================================================\n\n"
       << "\t\t\t\tRULES\n"
       << "  (1) You have up to 3 guesses.\n"
       << "  (2) Type \"/lifeline\" for another word. You have up to 5 lifelines.\n"
       << "  (3) You may exit at any time. Type \"/exit\".\n"
       << "  (4) Type \"/stats\" to see # of guesses and lifelines left.\n"
       << "  (5) Type \"/help\" any time for list of commands.\n\n";
   cout << "  Statistics:\n"
        << "    Highest level reached: " << level << endl;
   cout << "    Longest word solved: " << word << endl;
   cout << "    Number of words guessed correctly: " << guess << endl;
   cout << "\n\t\t    Please type \"start\" to begin." << endl;

}

void UserInterface::helpDisplay() const {
   cout << " Help:\n"
        << "   /lifeline - Choose a different word to guess. You're subject to only 5 lifelines.\n"
        << "   /stats - View how may guesses and lifelines you have left.\n"
        << "   /exit - Exit the game. Can re-enter by typing \"./WordJumble\"\n"
        << "   /help - revisit help desk." << endl;
}

void UserInterface::displayStats(int level, int tries, int lives, string word) const {
   cout << " Current level: " << level << endl;
   cout << " Number of tries left: " << tries << endl;
   cout << " Number of lifelines left: " << lives << endl;
   cout << " Longest word guessed: " << word << endl;
}