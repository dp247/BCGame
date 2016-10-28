//FBullCowGame.cpp

//Includes
#include "FBullCowGame.h"

#include <map>
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <time.h>

//replace std::map with TMap
#define TMap std::map

//Constructor - calls reset to reset game variables
FBullCowGame::FBullCowGame()
{
    reset();
}

//This function returns a randomly generated integer
unsigned int FBullCowGame::randomInt(unsigned int min, unsigned int max)
{
    return (rand() % ((max + 1) - min) + min);
}

//This function loads in words from a text file into a vector, picks a random one
//then returns it.
FString FBullCowGame::getWord()
{
    //Declare the word file name and location
    std::string wordFile = "./isograms.txt";

    //Open the file
    std::ifstream fileIn(wordFile.c_str());

    //Throw an error if file cannot be loaded
    if (!fileIn)
    {
        std::cout << "err: Failed To Load (" << wordFile << ")\n";
    }

    //create a new vector of strings to hold each word
    std::vector<std::string> words;

    //create a new string variable to read a line
    std::string line;

    //get each line of the file
    while (getline(fileIn, line))
    {
        //put each line into the words vector
        words.push_back(line);

        //clear the line variable ready for the next take
        line.clear();
    }

    //Stop reading the file
    fileIn.close();

    //Check if the words list was populated
    if (words.empty())
    {
        std::cout << "err: No Words Found!\n";
    }

    //Seed the random number generator
    srand(static_cast<unsigned int>(time(NULL)));

    //Generate random number
    unsigned int randomNumber = randomInt(0, words.size() - 1);

    //Using the random number, set the word
    FString word = words[randomNumber];

    //return the word
    return word;
}

//This function resets game variables to their default states.
void FBullCowGame::reset()
{
    //Reset the try count and game win status
    MyCurrentTry = 1;
    bGameWon = false;

    //Get a new word and set it to a variable
    const FString HIDDEN_WORD = getWord();
    MyHiddenWord = HIDDEN_WORD;

    //Debug code to print the hidden word
    //std::cout << "\n\nThe hidden word is: " << MyHiddenWord << "\n\n";

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

//Function that checks if the parameter is an isogram or not
bool FBullCowGame::isIsogram(FString Guess) const
{
    //If the guess is 0 or 1 letters long, it is an isogram, so return true
    if (Guess.length() <= 1)
    {
        return true;
    }

    //Setup the map
    TMap <char, bool> LetterSeen;

    //for all letters of the guess
    for (auto Letter : Guess)
    {
        //Handle mixed case by converting all letters to lowercase
        Letter = tolower(Letter);

        //If the letter is in the map, the guess is not an isogram
        if (LetterSeen[Letter])
        {
            return false;
        }

        //Else, add the letter to the map
        else
        {
            LetterSeen[Letter] = true;
        }
    }

    return true;
}

//Function that checks if the parameter is all lowercase
bool FBullCowGame::isLowercase(FString Guess) const
{
    //for the letters in the guess
    for (auto Letter : Guess)
    {
        if (!islower(Letter))
        {
            return false;
        }
    }

    return true;
}

//Getter function for max tries
int32 FBullCowGame::getMaxTries() const
{
    //This map stores the word length to max tries. For example: a word that is 3
    //letters long would give the user 4 tries to solve it
    TMap<int32, int32> WordLengthToMaxTries{ {3,4}, {4,7}, {5,10}, {6,16}, {7,21}, {8,28} };

    //return the number of tries based on the word length
    return WordLengthToMaxTries[MyHiddenWord.length()];
}

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
    //if the guess is not an isogram
    if (!isIsogram(Guess))
    {
        return EGuessStatus::Not_Isogram;
    }

    //if not all lowercase
    else if (!isLowercase(Guess))
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
