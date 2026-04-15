#include "masterVisual.h"
#include "mastermind.h"

// i denne løses 5 a, d, g og litt av f
// BEGIN: 5

void playMastermindVisual() {
    constexpr int size = 4;
    constexpr int letters = 6;
    constexpr int maxAttempts = 6;

    bool playAgain = true;

    while (playAgain) {
        // Create the graphics window
        MastermindWindow mwin{900, 20, winW, winH, size, "Mastermind"};

        string code = randomizeString(size, 'A', 'A' + letters - 1);
        string guess;

        // Add the code to display (hidden by default)
        addGuess(mwin, code, 'A');
        mwin.setCodeHidden(true);

        int attempts = 0;
        bool won = false;

        while (attempts < maxAttempts && !mwin.should_close()) {
            attempts++;

            // 5d: Get player input using mwin.getInput()
            guess = mwin.getInput(size, 'A', 'A' + letters - 1);

            if (mwin.should_close()) break;

            // Add the guess to the display
            addGuess(mwin, guess, 'A');

            // Check the guess
            int correctPosition = checkCharactersAndPosition(code, guess);
            int correctChars = checkCharacters(code, guess);

            // Add feedback
            addFeedback(mwin, correctPosition, correctChars - correctPosition);

            // Check for win
            if (correctPosition == size) {
                won = true;
                break;
            }
        }

        // 5g: Show the hidden code at game end
        if (!mwin.should_close()) {
            if (won) {
                cout << "Congratulations! You won!\n";
            } else {
                cout << "Game over! The code was: " << code << "\n";
            }

            mwin.drawGuessesAndFeedbacks();
            mwin.setCodeHidden(false);
            mwin.wait_for_close();
        }

        cout << "Play again? (y/n): ";
        char choice;
        cin >> choice;
        playAgain = (choice == 'y' || choice == 'Y');
    }
}

// END: 5


void addGuess(MastermindWindow &mwin, const string code, const char startLetter)
{
	// BEGIN: 5b
	Guess newGuess{code, startLetter};
	mwin.guesses.push_back(newGuess);
	// END: 5b
}

void addFeedback(MastermindWindow &mwin, const int correctPosition, const int correctCharacter)
{
	// BEGIN: 5e
	Feedback newFeedback{correctPosition, correctCharacter};
	mwin.feedbacks.push_back(newFeedback);
	// END: 5e
}

void MastermindWindow::drawCodeHider()
{
	if (code_hidden) {
		draw_rectangle(Point{padX, 3 * padY}, winW - size * padX, padY, Color::black);
	}
}

MastermindWindow::MastermindWindow(int x, int y, int w, int h, int size, const string &title) 
: AnimationWindow(x, y, w, h, title),
guessBtn{{upperLeftCornerBtn.x, upperLeftCornerBtn.y}, btnW, btnH, "Add"},
guess{{upperLeftCornerInBox.x, upperLeftCornerInBox.y}, inBoxW, inBoxH, ""},
size(size)
{
	add(guess);
	add(guessBtn);
	guessBtn.setCallback(std::bind(&MastermindWindow::cb_guess, this));
};

void MastermindWindow::drawGuessesAndFeedbacks()
{
	std::map<int, Color> colorConverter{
		{1, Color::red},
		{2, Color::green},
		{3, Color::yellow},
		{4, Color::blue},
		{5, Color::blue_violet},
		{6, Color::dark_cyan}};

	for (int guessIndex = 0; guessIndex < static_cast<int>(guesses.size()); guessIndex++)
	{
		/*********************************************************************/

		// BEGIN: 5c

		// Implementer funksjonalitet slik at det vises fargede rektangler i grafikkvinduet
		// Legg merke til at vi er i et for-løkke som går gjennom alle gjettene som er gjort.
		// Tegn gjettet som ligger på plassen guessIndex i vektoren guesses.

		// Calculate y position: first row is code (index 0), guesses start at row 1
		// yPos depends on the guess index (row number)
		int yPos = 3 * padY + guessIndex * 2 * padY;

		for (int i = 0; i < size; i++)
		{
			// Denna for-løkken går gjennom alle firkantene som skal tegnes i et gjett.
			// Tegn rektangler ved bruk av draw_rectangle(). Bruk: colorConverter.at() for å få riktig farge

			// Calculate x position for this rectangle
			int xPos = padX + i * 2 * padX;

			// Get the character at position i and convert to color index
			char c = guesses[guessIndex].code[i];
			int colorIndex = toupper(c) - guesses[guessIndex].startLetter + 1;

			// Draw the rectangle
			Color fillColor = colorConverter.at(colorIndex);
			draw_rectangle(Point{xPos, yPos}, padX, padY, fillColor, Color::black);
		}
		// END: 5c
	}

	for (int feedbackIndex = 0; feedbackIndex < static_cast<int>(feedbacks.size()); feedbackIndex++)
	{
		/*********************************************************************/

		// BEGIN: 5f

		// Implementer feedback
		// Her skal mye likt gjøres som i 5c

		// y position: feedbacks correspond to guesses (feedbackIndex 0 is for guess 1, etc.)
		// So we add 1 to skip the code row
		int yPosFeedback = 3 * padY + (feedbackIndex + 1) * 2 * padY + padY / 2;

		// x position for circles (after the 4 rectangles)
		int xPosCircles = padX + size * 2 * padX;

		for (int i = 0; i < size; i++)
		{
			// Tegn sirkler ved hjelp av draw_circle().

			// Calculate x position for this circle
			int xCircle = xPosCircles + i * 2 * radCircle + radCircle;

			// Determine color: black for correct position, white for correct char, gray for nothing
			Color indicatorColor;
			if (i < feedbacks[feedbackIndex].correctPosition) {
				indicatorColor = Color::black;  // Correct position
			} else if (i < feedbacks[feedbackIndex].correctPosition + feedbacks[feedbackIndex].correctCharacter) {
				indicatorColor = Color::white;  // Correct character, wrong position
			} else {
				indicatorColor = Color::gray;   // Neither
			}

			draw_circle(Point{xCircle, yPosFeedback}, radCircle, indicatorColor);
		}
		// END: 5f
	}
}

string MastermindWindow::wait_for_guess()
{

	while (!button_pressed && !should_close())
	{
		drawGuessesAndFeedbacks();
		// Burde tegnes sist siden den skal ligge på toppen
		drawCodeHider();

		next_frame();
	}
	button_pressed = false;

	string newGuess = guess.getText();
	guess.setText("");

	return newGuess;
}

string MastermindWindow::getInput(unsigned int n, char lower, char upper)
{
	bool validInput = false;
	string guess;
	while (!validInput && !should_close())
	{
		guess.clear();
		string input = wait_for_guess();
		if (input.size() == n)
		{
			for (unsigned int i = 0; i < n; i++)
			{
				char ch = input.at(i);
				if (isalpha(ch) && toupper(ch) <= upper && lower <= toupper(ch))
				{
					guess += toupper(ch);
				}
				else
					break;
			}
		}
		if (guess.size() == n)
		{
			validInput = true;
		}
		else
		{
			cout << "Invalid input guess again" << endl;
		}
	}
	return guess;
}

void MastermindWindow::setCodeHidden(bool hidden) {
	code_hidden = hidden;
}

 