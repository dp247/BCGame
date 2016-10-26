//FBullCowGame.cpp

//Includes
#include "FBullCowGame.h"

//Constructor - calls reset to reset game variables
FBullCowGame::FBullCowGame()
{
    reset();
}

//This function resets game variables to their default states.
//TODO - add a function to load in words from a file, select one and set it here
void FBullCowGame::reset()
{
    MyCurrentTry = 1;
    MyMaxTries = 10;

    bGameWon = false;

    const FString HIDDEN_WORD = "planet";
    MyHiddenWord = HIDDEN_WORD;
    return;
}

//This function takes in a guess and checks it for bulls and cows.
FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess)
{
    //Increment the try count
    MyCurrentTry++;

    //setup return variable
    FBullCowCount BullCowCount;

    //set hidden word length to zero
    int32 HiddenWordLength = 0;

    //Get the word's length
    HiddenWordLength = MyHiddenWord.length();

    //loop through all letters in guess
    for (int32 i = 0; i < HiddenWordLength; i++)
    {
        //compare the letters against the hidden word
        for (int32 j = 0; j < HiddenWordLength; j++)
        {
            //if the letters match
            if (Guess[i] == MyHiddenWord[j])
            {
                //if they're in the same place
                if (i == j)
                {
                    //increment the bull count
                    ++BullCowCount.Bulls;
                }

                //if they match but are in a different place
                else
                {
                    //increment the cow count
                    ++BullCowCount.Cows;
                }
            }
        }
    }

    //If the number of bulls (letters in the right places) is equivalent to
    //the length of the word, the word is correct, so set the bGameWon boolean
    //to true. If not, it is false.
    if (BullCowCount.Bulls == HiddenWordLength)
    {
        bGameWon = true;
    }
    else
    {
        bGameWon = false;
    }

    return BullCowCount;
}

//Getter function for max tries
int32 FBullCowGame::getMaxTries() const { return MyMaxTries; }

//Getter function for hidden word length
int32 FBullCowGame::getHiddenWordLength() const { return MyHiddenWord.length(); }

//Getter function for the game won boolean
bool FBullCowGame::isGameWon() const { return bGameWon; }

//Getter function for the current try number
int32 FBullCowGame::getCurrentTry() { return MyCurrentTry; }

//This functions checks a guess' validity by setting an appropriate
//status
EGuessStatus FBullCowGame::checkGuessValidity(FString Guess) const
{
    //if guess is not isogram
    if (false)
    {
        return EGuessStatus::Not_Isogram;
    }

    //if not all lowercase
    else if (false)
    {
        return EGuessStatus::Not_Lowercase;
    }

    //if guess length is wrong
    else if (Guess.length() != getHiddenWordLength())
    {
        return EGuessStatus::Wrong_Length;
    }

    //otherwise return OK
    else
    {
        return EGuessStatus::OK;
    }
}
