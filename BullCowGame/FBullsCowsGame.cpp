#pragma once
#include <iostream>
#include "FBullsCowsGame.h"
#include <map>

#define Tmap std::map

using int32 = int;

FBullsCowsGame::FBullsCowsGame()
{
	Reset();
}

int32 FBullsCowsGame::GetCurrentTry() const
{
	return myCurrentTry;
}

int32 FBullsCowsGame::GetMaxTries() const
{
	Tmap <int32, int32> wordLenToMaxTries{ {2, 3}, {3, 4}, {4, 7}, {5, 10}, {6, 16}, {7, 20},{8, 24} };
	
	return wordLenToMaxTries[GetHiddenWordLen()];
}

int32 FBullsCowsGame::GetHiddenWordLen() const
{
	return myHiddenWord.length();
}

bool FBullsCowsGame::IsGameWon() const
{
	return bGameIsWon;
}

void FBullsCowsGame::Reset()
{
	const FString hiddenWord = ReturnRandomIsogram(); // MUST be an isogram
	
	myHiddenWord = hiddenWord;
	myCurrentTry = 1;
	bGameIsWon = false;
	
	return;
}

void FBullsCowsGame::PrintInstruction()
{
	std::cout << "Can you guess the " << GetHiddenWordLen();
	std::cout << " letter isogram i'm thinking of?" << std::endl;
}

FString FBullsCowsGame::ReturnRandomIsogram()  
{
	int32 isogramsSize = isograms.size();
	int32 randomIndex = rand() % isogramsSize;
	return isograms[randomIndex];
}


EGuessStatus FBullsCowsGame::CheckGuessValidity(FString _guess) const
{	
	if (!IsIsogram(_guess)) 
	{
		return EGuessStatus::NOT_ISOGRAM;
	}
	else if (!IsLowerCase(_guess))
	{
		return EGuessStatus::NOT_LOWERCASE;
	}
	else if (_guess.length() != GetHiddenWordLen()) 
	{
		return  EGuessStatus::WRONG_LENGTH;
	}
	else
	{
		return EGuessStatus::OK;
	}
}

// receive a valid guess and increments turn and return counts 
FBullCowCount FBullsCowsGame::SubmitValidGuess(FString _guess)
{
	++myCurrentTry;

	FBullCowCount bullCowCount; 
	int32 wordLen = myHiddenWord.length(); // assuming same word length

	for (int32 i = 0; i < wordLen; i++)
	{
		for (int32 j = 0; j < wordLen; j++)
		{
			if (_guess[j] == myHiddenWord[i])
			{
				if (i == j)
				{
					++bullCowCount.m_bulls;
				}
				else
				{
					++bullCowCount.m_cows;
				}
			}
		}
	}
	
	if (bullCowCount.m_bulls == wordLen)
	{
		bGameIsWon = true;
	}

	return bullCowCount;
}

bool FBullsCowsGame::IsIsogram(FString _word) const
{
	//treat 0 and 1 letter as isogram
	if (_word.length() <= 1)
	{
		return true;
	}

	Tmap < char, bool> letterSeen;
	for (auto letter : _word)
	{
		letter = tolower(letter);	//insensitive to uppercases. not needed if dependent on the IsLowerCase method
		
		if (letterSeen[letter])
		{
			return false;
		}
		else
		{
			letterSeen[letter] = true;
		}
	}
	
	return true;
}

bool FBullsCowsGame::IsLowerCase(FString _word) const
{
	for (auto letter : _word)
	{
		if (!islower(letter))
		{
			return false;
		}
	}
	return true;
}
