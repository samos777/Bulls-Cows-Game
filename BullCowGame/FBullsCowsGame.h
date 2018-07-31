/*The game is a simple "Guess the word game" based on Mastermind */
/*In this game you need to find the pre-defined isogram (no double letter)*/
/*A bull means you got a letter in the right place */
/*A cow means you got a correct letter in the wrong place*/
/*enjoy the game*/

#pragma once
#include <string>
#include <array>
#define Tarray std::array

//To make syntax unreal friendly
using FString = std::string;
using int32 = int;

enum class EGuessStatus
{
	INVALID_STATUS,
	OK,
	NOT_ISOGRAM,
	WRONG_LENGTH,
	NOT_LOWERCASE
};


// all values initialized at zero
struct FBullCowCount
{
	int32 m_bulls = 0;
	int32 m_cows = 0;
};
typedef struct FBullCowCount BullCowCount;

class FBullsCowsGame {
public:
	FBullsCowsGame(); //CTOR

	int32 GetCurrentTry() const;
	int32 GetMaxTries() const;
	int32 GetHiddenWordLen() const;
	bool IsGameWon() const;
	EGuessStatus CheckGuessValidity(FString) const;
	void PrintInstruction();

	void Reset();

	FBullCowCount SubmitValidGuess(FString);

private:
	int32 myCurrentTry;
	FString myHiddenWord;
	bool bGameIsWon;
	const Tarray<FString, 10>isograms = {"air","no","yes","cake","magnet","beard","game","admin","organism","isogram" }; // MUST be isogram


	bool IsIsogram(FString _word) const;
	bool IsLowerCase(FString _word) const;
	FString ReturnRandomIsogram();
};
