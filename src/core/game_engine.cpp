#include <iostream>
#include <cmath>
#include <string>
#include <cstdlib>
#include <fstream>
using namespace std;
void mainmenue();
void submenue();
void Sciencequestions();
void Computerquestions();
void Sportsquestions();
void Historyquestions();
void Logicquestions();
int main()
{
	int input,input1;
	cout << "      Welcome to Quiz game" << endl;
	cout << "--------------------------------------" << endl;
	mainmenue();
	cin >> input;
	if (input != 1 && input != 2 && input != 3)
	{
		cout << "Error: Enter correct value" << endl;
		cout << " " << endl;
		mainmenue();
	}
	switch (input)
	{
	case 1:
		cout << "Select form the topic below" << endl;
		submenue();
		cin >> input1;
		if (input1 != 1 && input1 != 2 && input1 != 3 && input1 != 4 && input1 != 5)
		{
			cout << "Error: Enter correct value" << endl;
			cout << " " << endl;
			submenue();
		}
		switch (input1)
		{
		case 1:
			Sciencequestions();
			break;
		case 2:
			Computerquestions();
			break;
		case 3:
			Sportsquestions();
			break;
		case 4:
			Historyquestions();
			break;
		case 5:
			Logicquestions();
			break;
		}
		break;
	case 2:
		break;
	case 3:
		break;
		
	}
}
void mainmenue()
{
	cout << "Enter 1 ==>  Start Game" << endl;
	cout << "Enter 2 ==>  High Scores" << endl;
	cout << "Enter 3 ==>  Exit Game" << endl;
	cout << " " << endl;
	cout << "--------------------------------------" << endl;
}
void submenue()
{
	cout << " " << endl;
	cout << "Enter 1 ==>  Science" << endl;
	cout << "Enter 2 ==>  Computer" << endl;
	cout << "Enter 3 ==>  sports" << endl;
	cout << "Enter 4 ==>  History" << endl;
	cout << "Enter 5 ==>  Iq/Logic" << endl;
	cout << " " << endl;
	cout << "--------------------------------------" << endl;
}
void Sciencequestions()
{
	struct Question {
		string q;
		string options[4];
		int answer;
	};

	ifstream sq("science.txt");  
	if (!sq) {
		cout << "File not found!" << endl;
		return;
	}
	int totalQuestions = 0;
	string line;
	while (getline(sq, line))
		if (!line.empty()) totalQuestions++; // each line counts
	totalQuestions /= 6; // 6 lines per question

	sq.clear();            // reset EOF flag
	sq.seekg(0);           // go back to start of file
	srand(time(0));
	int qNum = rand() % totalQuestions; // 0 to totalQuestions-1
	Question q;
	for (int i = 0; i <= qNum; i++) {
		getline(sq, q.q);               // question text
		for (int j = 0; j < 4; j++)
			getline(sq, q.options[j]); // options
		sq >> q.answer;                  // correct answer
		sq.ignore();                     // skip leftover newline
	}
	cout << q.q << endl;
	for (int i = 0; i < 4; i++)
		cout << i + 1 << ") " << q.options[i] << endl;
	int userAns;
	cin >> userAns;

	if (userAns == q.answer)
		cout << "Correct!" << endl;
	else
		cout << "Wrong! Correct answer: " << q.answer
		<< ") " << q.options[q.answer - 1] << endl;

	sq.close();
}
void Computerquestions()
{

}
void Sportsquestions()
{

}
void Historyquestions()
{

}
void Logicquestions()
{

}
