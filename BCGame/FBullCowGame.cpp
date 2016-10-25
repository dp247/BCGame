#include "FBullCowGame.h"

FBullCowGame::FBullCowGame()
{
    reset();
}

void FBullCowGame::reset()
{
    MyCurrentTry = 1;
    MyMaxTries = 8;

    const FString HIDDEN_WORD = "planet";
    MyHiddenWord = HIDDEN_WORD;
    return;
}

//recieves a valid guess, increments and returns count
FBullCowCount FBullCowGame::SubmitGuess(FString Guess)
{
    //Increment the try count
    MyCurrentTry++;

    //setup return variable
    FBullCowCount BullCowCount;
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

    //compare letters against hidden word

    return BullCowCount;
}

int32 FBullCowGame::getMaxTries() const { return MyMaxTries; }

int32 FBullCowGame::getHiddenWordLength() const { return MyHiddenWord.length(); }

int32 FBullCowGame::getCurrentTry()
{
    return MyCurrentTry;
}

bool FBullCowGame::isGameWon() const
{
    return false;
}

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
