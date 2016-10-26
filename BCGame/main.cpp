//main.cpp

//Includes
#include <iostream>
#include <string>
#include "FBullCowGame.h"

//using setups based on Unreal Engine's coding standard
using FText = std::string;
using int32 = int;

//create an instance of the game
FBullCowGame BCGame;

//set currentGuess to zero
int32 currentGuess = 0;

//This function prints introductary lines when the game is first launched
void gameIntroduction()
{
    //Print introduction/rules of the game
    std::cout << "Welcome to Bulls & Cows, an original isogram game!\n";
    std::cout << "In this game, you must guess the " << BCGame.getHiddenWordLength() << " letter word.\n";
    std::cout << "The word is an isogram, meaning it has no repeating letters.\n";
}

//This function runs before playGame() and keeps track of how many games the user
//has played
int32 DisplayGameNumber(int32 gameCounter)
{
    ++gameCounter; //increment the counter
    std::cout << "\n\n--- GAME " << gameCounter << " ---" << std::endl; //display the count
    return gameCounter; //return the incremented value
}

//This function gets the user's guess, uses a switch statement to check if it
//is valid or not and then returns the guess. It does this using a do-while loop
//with a condition of there being an error.
FText GetValidGuess()
{
    //string that stores the guess
    FText Guess = "";

    //enum that stores the error
    EGuessStatus Status = EGuessStatus::Invalid_Status;
    do
    {
        //get the current try number
        currentGuess = BCGame.getCurrentTry();

        //get a guess from the player
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
            return Guess;
            break;
        }
    } while (Status != EGuessStatus::OK);
}

//This function handles the running of each game round
void playGame()
{
    //reset the game
    BCGame.reset();

    //get the number of tries
    int32 maxTries = BCGame.getMaxTries();

    //while the game is not won and there are still tries remaining
    while ((!BCGame.isGameWon()) && (BCGame.getCurrentTry() <= maxTries))
    {
        //put the return value of GetValidGuess into a new string
        FText Guess = GetValidGuess();

        //submit the new string as the guess and receive counts
        FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);

        //Display the number of bulls and cows
        std::cout << "Bulls = " << BullCowCount.Bulls << ".\n";
        std::cout << "Cows = " << BullCowCount.Cows << ".\n";

        //TODO Add a game summary
    }
}

//This function is called at the end of each game and asks the user if they
//want to play again using Y/N input. If they answer N (or n) or anything else,
//the game will exit. Otherwise, if they answer Y or y, the game will reset.
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

//Main function - this handles the set-up and running of the entire game,
//as well as exiting. It uses a do-while loop with a boolean condition that
//runs the game as long as it evaluates to true.
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
