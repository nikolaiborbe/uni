#include "mastermind.h"

// BEGIN: 4
void playMastermind() {
    // 4a: Define constants
    constexpr int size = 4;        // Number of characters in the code
    constexpr int letters = 6;     // Number of different letters (A-F)
    constexpr int maxAttempts = 10; // 4i: Limited number of attempts

    bool playAgain = true;

    while (playAgain) {
        // 4b: Create strings for code and guess
        string code;
        string guess;

        // 4c: Generate random code
        code = randomizeString(size, 'A', 'A' + letters - 1);

        cout << "\n=== MASTERMIND ===\n";
        cout << "Guess the " << size << "-letter code (letters A-" << static_cast<char>('A' + letters - 1) << ")\n";
        cout << "You have " << maxAttempts << " attempts.\n\n";

        int attempts = 0;
        bool won = false;

        // 4g & 4h: Game loop
        while (attempts < maxAttempts) {
            attempts++;
            cout << "Attempt " << attempts << "/" << maxAttempts << ": ";

            // 4d: Get player input
            guess = readInputToString(size, 'A', 'A' + letters - 1);

            // Check the guess
            int correctPosition = checkCharactersAndPosition(code, guess);
            int correctChars = checkCharacters(code, guess);

            cout << "Correct letters: " << correctChars << ", Correct positions: " << correctPosition << "\n\n";

            // Check for win
            if (correctPosition == size) {
                won = true;
                break;
            }
        }

        // 4j: Victory or defeat message
        if (won) {
            cout << "Congratulations! You guessed the code " << code << " in " << attempts << " attempts!\n";
        } else {
            cout << "Sorry, you ran out of attempts. The code was: " << code << "\n";
        }

        // Ask to play again
        cout << "\nDo you want to play again? (y/n): ";
        char choice;
        cin >> choice;
        playAgain = (choice == 'y' || choice == 'Y');
    }

    cout << "Thanks for playing Mastermind!\n";
}
// END: 4

// BEGIN: 4e
int checkCharactersAndPosition(const string& code, const string& guess) {
    int correctPosition = 0;
    for (size_t i = 0; i < code.length(); i++) {
        if (code[i] == guess[i]) {
            correctPosition++;
        }
    }
    return correctPosition;
}
// END: 4e

// BEGIN: 4f
int checkCharacters(const string& code, const string& guess) {
    int correctChars = 0;
    // Iterate through all possible letters (A-F)
    for (char c = 'A'; c <= 'F'; c++) {
        int inCode = countChar(code, c);
        int inGuess = countChar(guess, c);
        // Take the minimum of the two counts
        correctChars += min(inCode, inGuess);
    }
    return correctChars;
}
// END: 4f
 