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
	int input,input1;a
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
	struct Question
	{
		string q;
		string options[4];
		int answer;
	};
	ifstream sq("science.txt");  //sq = science questions
	if (!sq)
	{
		cout << "File not found" << endl;
		return;
	}
	Question q;
	getline(sq, q.q);  //Reading Questions
	for (int i = 0; i < 4; i++)
	{
		getline(sq, q.options[i]);  // read option of questions
	}
	sq >> q.answer;
	sq.ignore(); //it will ignore remaining lines.

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
