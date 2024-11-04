#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

class Word {
private:
    std::vector<char> word;
    std::vector<char> guessedWord;

public:
    // Constructor to initialize the word and guessedWord with underscores
    Word(const std::string& str) {
        for (char c : str) {
            word.push_back(c);
            guessedWord.push_back('_');
        }
    }

    // Returns the current state of the guessed word
    std::vector<char> getWord() const {
        return guessedWord;
    }

    // Replaces underscores with the correct guessed letter in the word
    bool addLetter(char ch) {
        bool found = false;
        for (size_t i = 0; i < word.size(); ++i) {
            if (word[i] == ch) {
                guessedWord[i] = ch;
                found = true;
            }
        }
        return found;
    }

    // Checks if the guessed letter is in the word
    bool findLetter(char ch) const {
        return std::find(word.begin(), word.end(), ch) != word.end();
    }

    // Returns true if the word has been completely guessed
    bool solved() const {
        return word == guessedWord;
    }
};

class GameState {
private:
    std::vector<std::string> states;
    int currentState;

public:
    // Constructor initializes the game states
    GameState() : currentState(0) {
        states = { "PLATFORM", "HEAD", "BODY", "LEFT_ARM", "RIGHT_ARM", "LEFT_LEG", "RIGHT_LEG" };
    }

    // Returns the current hangman state
    std::string getState() const {
        if (currentState < states.size()) {
            return states[currentState];
        }
        return "GAME_OVER";
    }

    // Adds the next state, simulating incorrect guess
    void addState() {
        if (currentState < states.size()) {
            ++currentState;
        }
    }

    // Returns true if the game is over
    bool gameOver() const {
        return currentState >= states.size();
    }
};

class GuessedLetters {
private:
    std::vector<char> letters;

public:
    // Returns the list of guessed letters
    std::vector<char> getLetters() const {
        return letters;
    }

    // Adds a guessed letter to the list
    void addLetter(char ch) {
        if (std::find(letters.begin(), letters.end(), ch) == letters.end()) {
            letters.push_back(ch);
        }
    }
};

int main() {
    std::string secretWord;
    std::cout << "Enter the word to guess: ";
    std::cin >> secretWord;

    Word word(secretWord);
    GameState gameState;
    GuessedLetters guessedLetters;

    while (!gameState.gameOver() && !word.solved()) {
        std::cout << "\nCurrent word: ";
        for (char ch : word.getWord()) {
            std::cout << ch << ' ';
        }

        std::cout << "\nGuessed letters: ";
        for (char ch : guessedLetters.getLetters()) {
            std::cout << ch << ' ';
        }

        std::cout << "\nCurrent hangman state: " << gameState.getState() << std::endl;

        char guess;
        std::cout << "Enter your guess: ";
        std::cin >> guess;

        guessedLetters.addLetter(guess);

        if (word.findLetter(guess)) {
            word.addLetter(guess);
        } else {
            gameState.addState();
        }
    }

    if (word.solved()) {
        std::cout << "Congratulations! You've guessed the word: ";
        for (char ch : word.getWord()) {
            std::cout << ch;
        }
        std::cout << std::endl;
    } else {
        std::cout << "Game Over! The word was: " << secretWord << std::endl;
    }

    return 0;
}
