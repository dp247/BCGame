#pragma once
#include <string>

using FString = std::string;
using int32 = int;

struct FBullCowCount
{
    int32 Bulls = 0;
    int32 Cows = 0;
};

enum class EGuessStatus
{
    OK,
    Not_Isogram,
    Wrong_Length,
    Not_Lowercase,
    Invalid_Status
};

class FBullCowGame
{
private:
    int32 MyCurrentTry;
    int32 MyMaxTries;
    FString MyHiddenWord;
public:
    FBullCowGame(); //constructor

    int32 getMaxTries() const;
    int32 getHiddenWordLength() const;
    bool isGameWon() const;
    EGuessStatus checkGuessValidity(FString) const;

    int32 getCurrentTry();
    void reset();

    virtual FBullCowCount SubmitGuess(FString) final;
};
