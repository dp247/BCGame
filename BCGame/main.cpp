#include <iostream>
#include <string>
#include "FBullCowGame.h"
using FText = std::string;
using int32 = int;

FBullCowGame BCGame;					//create an instance of the game
int32 currentGuess = 0;

void gameIntroduction()
{
    //Print introduction/rules of the game
    //qawdawd
    std::cout << "Welcome to Bulls & Cows, an original isogram game!\n";
    std::cout << "In this game, you must guess the " << BCGame.getHiddenWordLength() << " letter word.\n";
    std::cout << "The word is an isogram, meaning it has no repeating letters.\n";
}

FText GetValidGuess()
{
    //Enum variable declaration
    EGuessStatus Status = EGuessStatus::Invalid_Status;
    do
    {
        //Variable declarations
        FText Guess = "";									//string that stores the guess
        currentGuess = BCGame.getCurrentTry();		        //int32 that is the current guess

        //Get a guess from the player
        std::cout << "\nEnter guess #" << currentGuess << ": ";
        std::getline(std::cin, Guess);

        //check the guess validity and return a status
        Status = BCGame.checkGuessValidity(Guess);

        //check the status
        switch (Status)
        {
            //If the status returned specifies wrong length
        case EGuessStatus::Wrong_Length:
            std::cout << "Please enter a " << BCGame.getHiddenWordLength() << " letter word.\n ";
            break;

            //If the status returned specifies it is not an isogram
        case EGuessStatus::Not_Isogram:
            std::cout << "Please enter a valid isogram.\n ";
            break;

            //If the status returned specifies that the guess is not lowercase
        case EGuessStatus::Not_Lowercase:
            std::cout << "Not lowercase.\n ";
            break;

        default:

            //currentGuess++;
            return Guess;
        }
    } while (Status != EGuessStatus::OK);
}

int32 DisplayGameNumber(int32 gameCounter)
{
    ++gameCounter; //increment the counter
    std::cout << "\n\n--- GAME " << gameCounter << " ---" << std::endl; //display the count
    return gameCounter; //return the incremented value
}

void playGame()
{
    BCGame.reset();
    int32 maxTries = BCGame.getMaxTries();

    for (int32 i = 0; i < maxTries; ++i)
    {
        //put the return value of GetValidGuess into a new string
        FText Guess = GetValidGuess();

        //submit the new string as the guess and receive counts
        FBullCowCount BullCowCount = BCGame.SubmitGuess(Guess);

        //Display the number of bulls and cows
        std::cout << "Bulls = " << BullCowCount.Bulls << ".\n";
        std::cout << "Cows = " << BullCowCount.Cows << ".\n";

        //TODO Add a game summary
    }
}

bool askToPlayAgain()
{
    //Ask the user if they want to play again
    std::cout << "\n\nDo you want to play again? \nAnswer (Y/N): ";

    //New string for a response
    FText Response = "";

    //Get the user's response
    std::getline(std::cin, Response);

    //If the first letter is a y or Y
    if (Response[0] == 'y' || Response[0] == 'Y')
    {
        //return the letter
        return (Response[0] == 'y') || (Response[0] == 'Y');
    }

    //If the first letter is a n or N
    else if (Response[0] == 'n' || Response[0] == 'N')
    {
        //Display a thank you message and send an exit success
        std::cout << "\n\n\nThanks for playing!\n\n" << std::endl;
        exit(0);
    }

    //Else if the user types in anything else
    else
    {
        //Display a thank you message and send an exit success
        std::cout << "\n\n\nThanks for playing!\n\n" << std::endl;
        exit(0);
    }
}

int main()
{
    //while true, the user will play again
    bool bPlayAgain = true;

    //Integer that stores the number of games played
    int32 gameCounter = 0;

    //call to gameIntroduction() to print instructions at the top of the screen
    gameIntroduction();

    //do this while bPlayAgain is true
    do
    {
        //call DisplayGameNumber and pass the game count to it. Then, when
        //done, set the incremented value to be the new value (as it has
        //been returned)
        gameCounter = DisplayGameNumber(gameCounter);

        //call to playGame() to play the game
        playGame();

        //ask the user if they would like to play again and set the bool
        //to the returned value. This is kind of obsolete since the exits
        //are handled in askToPlayAgain()
        bPlayAgain = askToPlayAgain();
    }

    while (bPlayAgain);

    //return 0 to exit
    return 0;
}
