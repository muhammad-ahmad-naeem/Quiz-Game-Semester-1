#include <iostream>
#include <cmath>
#include <string>
#include <cstdlib>
#include <fstream>
#include <vector>
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
	cout << "====================================" << endl;
	cout << "      Welcome to Quiz game          " << endl;
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
	srand(time(0));

	ifstream file("science.txt");
	if (!file)
	{
		cout << "File not found!";
	}

	vector<string> questions;
	vector<string> optA;
	vector<string> optB;
	vector<string> optC;
	vector<string> optD;
	vector<int> answers;

	// Read 10 questions
	for (int i = 0; i < 10; i++)
	{
		string q, a, b, c, d;
		int ans;

		getline(file, q);
		getline(file, a);
		getline(file, b);
		getline(file, c);
		getline(file, d);
		file >> ans;
		file.ignore(); // skip newline

		questions.push_back(q);
		optA.push_back(a);
		optB.push_back(b);
		optC.push_back(c);
		optD.push_back(d);
		answers.push_back(ans);
	}

	// Pick random question
	int r = rand() % 10;
	int ans;
	cout << "\nRandom Question:\n";
	cout << questions[r] << "\n";
	cout << "1. " << optA[r] << "\n";
	cout << "2. " << optB[r] << "\n";
	cout << "3. " << optC[r] << "\n";
	cout << "4. " << optD[r] << "\n";
	cout << "\nEnter  answer = "<< endl;
	cin >> ans;
	if (ans == answers[r])
	{
		cout << "Correct answer" << endl;
	}
	else
	{
		cout << "Wrong answer" << endl;
	}
}
void Computerquestions()
{
	srand(time(0));

	ifstream file("computer.txt");
	if (!file)
	{
		cout << "File not found!";
	}

	vector<string> questions;
	vector<string> optA;
	vector<string> optB;
	vector<string> optC;
	vector<string> optD;
	vector<int> answers;

	// Read 10 questions
	for (int i = 0; i < 10; i++)
	{
		string q, a, b, c, d;
		int ans;

		getline(file, q);
		getline(file, a);
		getline(file, b);
		getline(file, c);
		getline(file, d);
		file >> ans;
		file.ignore(); // skip newline

		questions.push_back(q);
		optA.push_back(a);
		optB.push_back(b);
		optC.push_back(c);
		optD.push_back(d);
		answers.push_back(ans);
	}

	// Pick random question
	int r = rand() % 10;
	int ans;
	cout << "\nRandom Question:\n";
	cout << questions[r] << "\n";
	cout << "1. " << optA[r] << "\n";
	cout << "2. " << optB[r] << "\n";
	cout << "3. " << optC[r] << "\n";
	cout << "4. " << optD[r] << "\n";
	cout << "\nEnter  answer = " << endl;
	cin >> ans;
	if (ans == answers[r])
	{
		cout << "Correct answer" << endl;
	}
	else
	{
		cout << "Wrong answer" << endl;
	}
}
void Sportsquestions()
{
	srand(time(0));

	ifstream file("sports.txt");
	if (!file)
	{
		cout << "File not found!";
	}

	vector<string> questions;
	vector<string> optA;
	vector<string> optB;
	vector<string> optC;
	vector<string> optD;
	vector<int> answers;

	// Read 10 questions
	for (int i = 0; i < 10; i++)
	{
		string q, a, b, c, d;
		int ans;

		getline(file, q);
		getline(file, a);
		getline(file, b);
		getline(file, c);
		getline(file, d);
		file >> ans;
		file.ignore(); // skip newline

		questions.push_back(q);
		optA.push_back(a);
		optB.push_back(b);
		optC.push_back(c);
		optD.push_back(d);
		answers.push_back(ans);
	}

	// Pick random question
	int r = rand() % 10;
	int ans;
	cout << "\nRandom Question:\n";
	cout << questions[r] << "\n";
	cout << "1. " << optA[r] << "\n";
	cout << "2. " << optB[r] << "\n";
	cout << "3. " << optC[r] << "\n";
	cout << "4. " << optD[r] << "\n";
	cout << "\nEnter  answer = " << endl;
	cin >> ans;
	if (ans == answers[r])
	{
		cout << "Correct answer" << endl;
	}
	else
	{
		cout << "Wrong answer" << endl;
	}
}
void Historyquestions()
{
	srand(time(0));

	ifstream file("history.txt");
	if (!file)
	{
		cout << "File not found!";
	}

	vector<string> questions;
	vector<string> optA;
	vector<string> optB;
	vector<string> optC;
	vector<string> optD;
	vector<int> answers;

	// Read 10 questions
	for (int i = 0; i < 10; i++)
	{
		string q, a, b, c, d;
		int ans;

		getline(file, q);
		getline(file, a);
		getline(file, b);
		getline(file, c);
		getline(file, d);
		file >> ans;
		file.ignore(); // skip newline

		questions.push_back(q);
		optA.push_back(a);
		optB.push_back(b);
		optC.push_back(c);
		optD.push_back(d);
		answers.push_back(ans);
	}

	// Pick random question
	int r = rand() % 10;
	int ans;
	cout << "\nRandom Question:\n";
	cout << questions[r] << "\n";
	cout << "1. " << optA[r] << "\n";
	cout << "2. " << optB[r] << "\n";
	cout << "3. " << optC[r] << "\n";
	cout << "4. " << optD[r] << "\n";
	cout << "\nEnter  answer = " << endl;
	cin >> ans;
	if (ans == answers[r])
	{
		cout << "Correct answer" << endl;
	}
	else
	{
		cout << "Wrong answer" << endl;
	}
}
void Logicquestions()
{
	srand(time(0));

	ifstream file("iq.txt");
	if (!file)
	{
		cout << "File not found!";
	}

	vector<string> questions;
	vector<string> optA;
	vector<string> optB;
	vector<string> optC;
	vector<string> optD;
	vector<int> answers;

	// Read 10 questions
	for (int i = 0; i < 10; i++)
	{
		string q, a, b, c, d;
		int ans;

		getline(file, q);
		getline(file, a);
		getline(file, b);
		getline(file, c);
		getline(file, d);
		file >> ans;
		file.ignore(); // skip newline

		questions.push_back(q);
		optA.push_back(a);
		optB.push_back(b);
		optC.push_back(c);
		optD.push_back(d);
		answers.push_back(ans);
	}

	// Pick random question
	int r = rand() % 10;
	int ans;
	cout << "\nRandom Question:\n";
	cout << questions[r] << "\n";
	cout << "1. " << optA[r] << "\n";
	cout << "2. " << optB[r] << "\n";
	cout << "3. " << optC[r] << "\n";
	cout << "4. " << optD[r] << "\n";
	cout << "\nEnter  answer = " << endl;
	cin >> ans;
	if (ans == answers[r])
	{
		cout << "Correct answer" << endl;
	}
	else
	{
		cout << "Wrong answer" << endl;
	}
}
