//FBullCowGame.h

#pragma once

//Includes
#include <string>

//using setups based on Unreal Engine's coding standard
using FString = std::string;
using int32 = int;

//struct definition that holds the bull and cow count
struct FBullCowCount
{
    int32 Bulls = 0;
    int32 Cows = 0;
};

//enum definition for the guess' statuses
enum class EGuessStatus
{
    OK,                 //returned if guess is acceptable
    Not_Isogram,        //returned if letters are repeating in the guess
    Wrong_Length,       //returned if guess is not the same length as the word
    Not_Lowercase,      //returned if the guess is not lowercase
    Invalid_Status      //returned at start only, as no other status is valid
};

//class definition for FBullCowGame
class FBullCowGame
{
private:
    int32 MyCurrentTry;                 //current try number
    FString MyHiddenWord;               //string that stores hidden word
    bool bGameWon;                      //boolean that evaluates if game is won

    bool isIsogram(FString) const;      //returns true if the passed parameter is an

                                        //isogram
    bool isLowercase(FString) const;
    FString getWord();
    unsigned int randomInt(unsigned int min, unsigned int max);

public:
    FBullCowGame();                     //constructor

    int32 getCurrentTry();              //getter for current try
    int32 getMaxTries() const;          //getter for max tries number
    int32 getHiddenWordLength() const;  //getter for hidden word's length
    bool isGameWon() const;             //getter for game won boolean

    EGuessStatus checkGuessValidity(FString) const; //function to check guess validity
    void reset();                                   //function to reset the game
    virtual FBullCowCount SubmitValidGuess(FString) final;  //function to submit guesses
};
