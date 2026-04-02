// new rock,paper,scissor.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <cstdlib>
#include <windows.h>

using namespace std;
enum enGameChoice{paper=1,rock=2,scissor=3};
enum enWinner{Player=1,computer=2,draw=3};
struct strRoundInfo {
	int Round;
	enGameChoice PlayerChoice;
	enGameChoice ComputerChoice;
	enWinner winner;
};
struct strGameResults {
	int NumberOfRounds;
	int computerWins;
	int DrawTimes;
	int playerWins;
	enWinner winner;
};

int HowManyRounds() {
	int NumberOfRounds;
	do {
		cout << "enter how many rounds You want to play: ";
		cin >> NumberOfRounds;
	} while (NumberOfRounds > 10 || NumberOfRounds < 1);
	return NumberOfRounds;
}
int RandomNumber(int from, int to) {
	return rand() % (to - from + 1) + from;
}
enGameChoice ReadPlayerChoice() {
	int choice;
	do {
		cout << "Please enter your choice: paper(1) rock(2) scissor(3): \n";
		cin >> choice;
	} while (choice > 3 || choice < 1);
	return enGameChoice(choice);
}
enGameChoice getComputerChoice() {
	int choice = RandomNumber(1, 3);
	return enGameChoice(choice);
}
string GetChoiceName(enGameChoice choice) {
	string choices[3] = {"paper","rock","scissor"};
	return choices[choice - 1];
}
string GetWinnerName(enWinner winner) {
	string choices[3] = { "player","compouter","No Winner" };
	return choices[winner - 1];
}
strGameResults ReadGameResults(int &NumberOfRounds, int &PlayerWins, int &computerWins, int &Draw) {
	strGameResults GameResults;
	GameResults.NumberOfRounds = NumberOfRounds;
	GameResults.computerWins = computerWins;
	GameResults.playerWins = PlayerWins;
	GameResults.DrawTimes = Draw;
	return GameResults;
}
void ShowGameOverScreen() {
	cout << "--------------------------------------------------------------\n";
	cout << "                   ++GAME OVER++                               \n";
	cout << "-----------------------------------------------------------------";
}
enWinner getWinner(strGameResults GameResults) {
	if (GameResults.computerWins == GameResults.playerWins) {
		return enWinner::draw;
	}
	else if (GameResults.computerWins > GameResults.playerWins) {
		return enWinner::computer;
	}
	else {
		return enWinner::Player;
	}
}
void printfinalResults(strGameResults GameResults){
	cout << "\nNumber of Rounds: " << GameResults.NumberOfRounds << endl;
	cout<<"Computer winning times: "<<GameResults.computerWins << endl;
	cout<<"Player winning times: "<<GameResults.playerWins << endl;
	cout << "Draw  times: " << GameResults.DrawTimes << endl;
	enWinner winner = getWinner(GameResults);
	cout << "Winner in the game is" << GetWinnerName(winner);
}
void printRoundResults(strRoundInfo RoundInfo) {
	cout << "\n---------[" << RoundInfo.Round << "]--------\n";
	cout << "computer choice: " << GetChoiceName(RoundInfo.ComputerChoice)<<"\n";
	cout << "player choice: " << GetChoiceName(RoundInfo.PlayerChoice) << "\n";
	cout << "Winner is: " << GetWinnerName(RoundInfo.winner)<<"\n";
	cout << "------------------------------------------\n";
}

void ResetScreen() {
	system("color 0F");
}
strGameResults PlayGame(int NumberOfRounds) {
	strRoundInfo RoundInfo;
	int PlayerWins=0, computerWins=0, DrawTimes=0;
	enWinner winner;




	for (int i = 1; i <= NumberOfRounds; i++) {
		enGameChoice playerChoice = ReadPlayerChoice();
		enGameChoice computerChoice = getComputerChoice();
		strGameResults GameResluts;
		RoundInfo.ComputerChoice = computerChoice;
		RoundInfo.PlayerChoice = playerChoice;
		RoundInfo.Round = i;
		if (playerChoice == computerChoice) {
			RoundInfo.winner = enWinner::draw;
			DrawTimes++;
			system("color 6F");
		}
		else if (playerChoice == enGameChoice::paper && computerChoice == enGameChoice::rock) {
			RoundInfo.winner = enWinner::Player;
			PlayerWins++;
			system("color 2F");
		}
		else if (playerChoice == enGameChoice::rock && computerChoice == enGameChoice::scissor) {
			RoundInfo.winner = enWinner::Player;
			PlayerWins++;
			system("color 2F");
		}
		else if (playerChoice == enGameChoice::scissor && computerChoice == enGameChoice::paper) {
			RoundInfo.winner = enWinner::Player;
			PlayerWins++;
			system("color 2F");
		}
		else {
			computerWins++;
			RoundInfo.winner = enWinner::computer;
			system("color 4F");
			cout << "\a";
		}
		printRoundResults(RoundInfo);
	}
	strGameResults GameResults = ReadGameResults(NumberOfRounds, PlayerWins, computerWins, DrawTimes);
	return GameResults;

}
void StartGame() {
	char playMore;
	do {
		ResetScreen();
		strGameResults GameResults=PlayGame(HowManyRounds());
		ShowGameOverScreen();
		printfinalResults(GameResults);

		cout << "\nDo You want to play again: Yes[Y] No[N] ";
		cin >> playMore;
	} while (playMore == 'y' || playMore == 'Y');

}
int main()
{
	//call random function once
	srand(time(NULL));
	StartGame();
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
