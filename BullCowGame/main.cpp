#pragma once
#include <iostream>
#include <string>
#include "FBullsCowsGame.h"

//To make syntax unreal friendly
using FText = std::string;
using int32 = int;

//declarations
void PrintIntro();
void PlayGame();
FText GetValidGuess();
bool AskToPlayAgain();
void SummarizeGame();

//global instance
FBullsCowsGame BCGame;

int main()
{
	PrintIntro();
	do
	{
		PlayGame();
	} 
	while (AskToPlayAgain());
	
	return 0;
}

void PrintIntro()
{
	std::cout << "\n\nWelcome to Bulls and Cows, a fun word game.\n";
	std::cout << std::endl;
	std::cout << "          }   {         ___ " << std::endl;
	std::cout << "          (o o)        (o o) " << std::endl;
	std::cout << "   /-------\\ /          \\ /-------\\ " << std::endl;
	std::cout << "  / | BULL |O            O| COW  | \\ " << std::endl;
	std::cout << " *  |-,--- |              |------|  * " << std::endl;
	std::cout << "    ^      ^              ^      ^ " << std::endl;
	

	return;
}

//Play one gmae to completion
void PlayGame()
{
	BCGame.Reset();
	BCGame.PrintInstruction();
	while (!BCGame.IsGameWon() && BCGame.GetCurrentTry() <= BCGame.GetMaxTries())
	{
		FText guess = GetValidGuess();

		FBullCowCount bullCowCount = BCGame.SubmitValidGuess(guess);

		std::cout << "Bulls = " << bullCowCount.m_bulls << " ";
		std::cout << "Cows = " << bullCowCount.m_cows << "\n\n";
	}

	SummarizeGame();

	return;
}


// loop continualy until the user put a valid guess
FText GetValidGuess() 
{
	EGuessStatus guessStatus = EGuessStatus::INVALID_STATUS;
	FText guess = "";
	do
	{
		int32 currentTry = BCGame.GetCurrentTry();
		std::cout << std::endl;
		std::cout << "This is try number " << currentTry << " of " << BCGame.GetMaxTries();
		std::cout << ". Enter your guess: ";
		std::getline(std::cin, guess);

		guessStatus = BCGame.CheckGuessValidity(guess);
		switch (guessStatus)
		{
		case EGuessStatus::WRONG_LENGTH:
			std::cout << "Please enter a " << BCGame.GetHiddenWordLen() << " letters isogram.\n\n";
			break;

		case EGuessStatus::NOT_ISOGRAM:
			std::cout << "Please enter a word without repeating letters.\n\n";
			break;
	
		case EGuessStatus::NOT_LOWERCASE:
			std::cout << "Please enter your guess in lowercase only.\n\n";
			break;

		default:
			break;
		}

	} while (guessStatus != EGuessStatus::OK);

	return guess;
}

bool AskToPlayAgain()
{
	std::cout << "Do you want to play again? (y/n)\n";
	FText response = "";
	std::getline(std::cin, response);

	return (response[0] == 'y' || response[0] == 'Y');
}

void SummarizeGame()
{
	if (BCGame.IsGameWon())
	{
		std::cout << "GAME IS WON. WELL DONE!\n";
	}
	else
	{
		std::cout << "Game is lost. Better luck next time.\n";
	}
	return;
}
