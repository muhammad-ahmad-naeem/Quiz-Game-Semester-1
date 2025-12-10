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
	struct Question
	{
		string q;
		string options[4];
		int answer;
	};

	ifstream sq("science.txt");
	if (!sq)
	{
		cout << "File not found!" << endl;
		return;
	}
	int totalQuestions = 0;
	string line;
	while (getline(sq, line))
	{
		if (!line.empty())
		{
			totalQuestions++; // each line counts
		}

	}
	totalQuestions /= 6; // 6 lines per question

	sq.clear();            // reset EOF flag
	sq.seekg(0);           // go back to start of file
	srand(time(0));
	int qNum = rand() % totalQuestions; // 0 to totalQuestions-1
	Question q;
	for (int i = 0; i <= qNum; i++)
	{
		getline(sq, q.q);               // question text
		for (int j = 0; j < 4; j++)
		{
			getline(sq, q.options[j]); // options
		}
		sq >> q.answer;                  // correct answer
		sq.ignore();                     // skip leftover newline
	}
	cout << q.q << endl;
	for (int i = 0; i < 4; i++)
	{
		cout << i + 1 << ") " << q.options[i] << endl;
	}
	int userAns;
	cin >> userAns;
	if (userAns == q.answer)
	{
		cout << "Correct!" << endl;
	}
	else
	{
		cout << "Wrong! Correct answer: " << q.answer << ") " << q.options[q.answer - 1] << endl;
	}


	sq.close();
}
void Computerquestions()
{
	struct Question
	{
		string q;
		string options[4];
		int answer;
	};

	ifstream cq("computer.txt");
	if (!cq)
	{
		cout << "File not found!" << endl;
		return;
	}
	int totalQuestions = 0;
	string line;
	while (getline(cq, line))
	{
		if (!line.empty())
		{
			totalQuestions++; // each line counts
		}

	}
	totalQuestions /= 6; // 6 lines per question

	cq.clear();            // reset EOF flag
	cq.seekg(0);           // go back to start of file
	srand(time(0));
	int qNum = rand() % totalQuestions; // 0 to totalQuestions-1
	Question q;
	for (int i = 0; i <= qNum; i++)
	{
		getline(cq, q.q);               // question text
		for (int j = 0; j < 4; j++)
		{
			getline(cq, q.options[j]); // options
		}
		cq >> q.answer;                  // correct answer
		cq.ignore();                     // skip leftover newline
	}
	cout << q.q << endl;
	for (int i = 0; i < 4; i++)
	{
		cout << i + 1 << ") " << q.options[i] << endl;
	}
	int userAns;
	cin >> userAns;
	if (userAns == q.answer)
	{
		cout << "Correct!" << endl;
	}
	else
	{
		cout << "Wrong! Correct answer: " << q.answer << ") " << q.options[q.answer - 1] << endl;
	}


	cq.close();
}
void Sportsquestions()
{
	struct Question 
	{
		string q;
		string options[4];
		int answer;
	};
	ifstream soq("sports.txt");
	if (!soq) 
	{
		cout << "File not found!" << endl;
		return;
	}
	int totalQuestions = 0;
	string line;
	while (getline(soq, line))
	{
		if (!line.empty())
		{
			totalQuestions++; // each line counts
		}
	} 
	totalQuestions /= 6; // 6 lines per question
	soq.clear();            // reset EOF flag
	soq.seekg(0);           // go back to start of file
	srand(time(0));
	int qNum = rand() % totalQuestions; // 0 to totalQuestions-1
	Question q;
	for (int i = 0; i <= qNum; i++) 
	{
		getline(soq, q.q);               // question text
		for (int j = 0; j < 4; j++)
		{
			getline(soq, q.options[j]); // options
		}
		soq >> q.answer;                  // correct answer
		soq.ignore();                     // skip leftover newline
	}
	cout << q.q << endl;
	for (int i = 0; i < 4; i++)
	{
		cout << i + 1 << ") " << q.options[i] << endl;
	}
	int userAns;
	cin >> userAns;
	if (userAns == q.answer)
	{
		cout << "Correct!" << endl;
	}
	else
	{
		cout << "Wrong! Correct answer: " << q.answer<< ") " << q.options[q.answer - 1] << endl;
	}
	soq.close();
}
void Historyquestions()
{
	struct Question 
	{
		string q;
		string options[4];
		int answer;
	};

	ifstream hq("history.txt");
	if (!hq) 
	{
		cout << "File not found!" << endl;
		return;
	}
	int totalQuestions = 0;
	string line;
	while (getline(hq, line))
	{
		if (!line.empty())
		{
			totalQuestions++; // each line counts
		}
		
	}
	totalQuestions /= 6; // 6 lines per question

	hq.clear();            // reset EOF flag
	hq.seekg(0);           // go back to start of file
	srand(time(0));
	int qNum = rand() % totalQuestions; // 0 to totalQuestions-1
	Question q;
	for (int i = 0; i <= qNum; i++) 
	{
		getline(hq, q.q);               // question text
		for (int j = 0; j < 4; j++)
		{
			getline(hq, q.options[j]); // options
		}
		hq >> q.answer;                  // correct answer
		hq.ignore();                     // skip leftover newline
	}
	cout << q.q << endl;
	for (int i = 0; i < 4; i++)
	{
		cout << i + 1 << ") " << q.options[i] << endl;
	}	
	int userAns;
	cin >> userAns;
	if (userAns == q.answer)
	{
		cout << "Correct!" << endl;
	}
	else
	{
		cout << "Wrong! Correct answer: " << q.answer << ") " << q.options[q.answer - 1] << endl;
	}
		

	hq.close();
}
void Logicquestions()
{
	struct Question
	{
		string q;
		string options[4];
		int answer;
	};

	ifstream lq("iq.txt");
	if (!lq)
	{
		cout << "File not found!" << endl;
		return;
	}
	int totalQuestions = 0;
	string line;
	while (getline(lq, line))
	{
		if (!line.empty())
		{
			totalQuestions++; // each line counts
		}

	}
	totalQuestions /= 6; // 6 lines per question

	lq.clear();            // reset EOF flag
	lq.seekg(0);           // go back to start of file
	srand(time(0));
	int qNum = rand() % totalQuestions; // 0 to totalQuestions-1
	Question q;
	for (int i = 0; i <= qNum; i++)
	{
		getline(lq, q.q);               // question text
		for (int j = 0; j < 4; j++)
		{
			getline(lq, q.options[j]); // options
		}
		lq >> q.answer;                  // correct answer
		lq.ignore();                     // skip leftover newline
	}
	cout << q.q << endl;
	for (int i = 0; i < 4; i++)
	{
		cout << i + 1 << ") " << q.options[i] << endl;
	}
	int userAns;
	cin >> userAns;
	if (userAns == q.answer)
	{
		cout << "Correct!" << endl;
	}
	else
	{
		cout << "Wrong! Correct answer: " << q.answer << ") " << q.options[q.answer - 1] << endl;
	}


	lq.close();
}
