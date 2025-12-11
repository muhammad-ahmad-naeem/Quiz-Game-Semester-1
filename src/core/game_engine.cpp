#include <iostream>
#include <cmath>
#include <string>
#include <cstdlib>
#include <fstream>
using namespace std;
void mainmenue();
void submenue();
void diffcultymenue();
void Sciencequestions(int& highscore);
void Sciencequestionsmid(int& highscore);

void Computerquestions(int& highscore);
void Computerquestionsmid(int& highscore);

void Sportsquestions(int& highscore);
void Sportsquestionsmid(int& highscore);

void Historyquestions(int& highscore);
void Historyquestionsmid(int& highscore);

void Logicquestions(int& highscore);
void Logicquestionsmid(int& highscore);

int getValidatedInput(int minOption, int maxOption)
{
    int input;
    while (true)
    {
        cin >> input;
        if (cin.fail() || input < minOption || input > maxOption)
        {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Error: Enter correct value" << endl;
        }
        else
            break;
    }
    return input;
}
int main()
{
    int input, input1, input3, highscore = 0;
    cout << "====================================" << endl;
    cout << "      Welcome to Quiz game          " << endl;
    cout << "------------------------------------" << endl;
    while (true)
    {
        mainmenue();
        input = getValidatedInput(1, 3);
        if (input == 3)
            break;
        if (input == 2)
        {
            cout << "High score = " << highscore << endl << endl;
            continue;
        }
        switch (input)
        {

        case 1:
            do
            {
                diffcultymenue();
                input3 = getValidatedInput(1, 4);

                switch (input3)
                {
                case 1:
                    cout << "Select from the topic below" << endl;
                    do
                    {
                        submenue();
                        input1 = getValidatedInput(1, 6);
                        switch (input1)
                        {
                        case 1:
                            Sciencequestions(highscore);
                            break;
                        case 2:
                            Computerquestions(highscore);
                            break;
                        case 3:
                            Sportsquestions(highscore);
                            break;
                        case 4:
                            Historyquestions(highscore);
                            break;
                        case 5:
                            Logicquestions(highscore);
                            break;
                        case 6:
                            break;
                        }
                    } while (input1 != 6);
                    break;

                case 2:
                    break;
                case 3:
                    break;
                case 4:
                    input = 0;
                    break;
                }

            } while (input3 != 4);
            break;

        case 2:
            break;

        case 3:
            break;
        }
    }
}

void mainmenue()
{
    cout << endl << "MAIN MENUE" << endl;
    cout << endl;
    cout << "Enter 1 ==>  Start Game" << endl;
    cout << "Enter 2 ==>  High Scores" << endl;
    cout << "Enter 3 ==>  Exit Game" << endl;
    cout << "--------------------------------------" << endl;
}

void submenue()
{
    cout << endl;
    cout << "Enter 1 ==>  Science" << endl;
    cout << "Enter 2 ==>  Computer" << endl;
    cout << "Enter 3 ==>  Sports" << endl;
    cout << "Enter 4 ==>  History" << endl;
    cout << "Enter 5 ==>  IQ/Logic" << endl;
    cout << "Enter 6 ==>  GO TO DIFFICULTY MENU" << endl;
    cout << endl;
}

void diffcultymenue()
{
    cout << endl;
    cout << "  Difficulty Selection  " << endl;
    cout << "------------------------" << endl;
    cout << "Enter 1 ==>  Easy" << endl;
    cout << "Enter 2 ==>  Medium" << endl;
    cout << "Enter 3 ==>  Hard" << endl;
    cout << "Enter 4 ==>  GO TO MAIN MENU" << endl;
    cout << endl;
}





void Sciencequestions(int& highscore)
{
    srand(time(0));
    ifstream file("science.txt");
    if (!file)
        cout << "ERROR: File Not found" << endl;
    else
    {
        string Questions[10], OptA[10], OptB[10], OptC[10], OptD[10];
        int answer[10];
        for (int i = 0; i < 10; i++)
        {
            getline(file, Questions[i]);
            getline(file, OptA[i]);
            getline(file, OptB[i]);
            getline(file, OptC[i]);
            getline(file, OptD[i]);
            file >> answer[i];
            file.ignore();
        }
        int r = rand() % 10, userans;
        cout << "--------------------------------------" << endl;
        cout << Questions[r] << endl;
        cout << "1. " << OptA[r] << endl;
        cout << "2. " << OptB[r] << endl;
        cout << "3. " << OptC[r] << endl;
        cout << "4. " << OptD[r] << endl;
        cout << "Enter your Answer = ";
        userans = getValidatedInput(1, 4);
        if (userans == answer[r])
        {
            cout << "Your Answer is Correct" << endl;
            highscore++;
        }
        else
            cout << "Your Answer is Incorrect" << endl;
    }
}

void Sciencequestionsmid(int& highscore)
{
    srand(time(0));
    ifstream file("sciencemid.txt");
    if (!file)
        cout << "ERROR: File Not found" << endl;
    else
    {
        string Questions[10], OptA[10], OptB[10], OptC[10], OptD[10];
        int answer[10];
        for (int i = 0; i < 10; i++)
        {
            getline(file, Questions[i]);
            getline(file, OptA[i]);
            getline(file, OptB[i]);
            getline(file, OptC[i]);
            getline(file, OptD[i]);
            file >> answer[i];
            file.ignore();
        }
        int r = rand() % 10, userans;
        cout << "--------------------------------------" << endl;
        cout << Questions[r] << endl;
        cout << "1. " << OptA[r] << endl;
        cout << "2. " << OptB[r] << endl;
        cout << "3. " << OptC[r] << endl;
        cout << "4. " << OptD[r] << endl;
        cout << "Enter your Answer = ";
        userans = getValidatedInput(1, 4);
        if (userans == answer[r])
        {
            cout << "Your Answer is Correct" << endl;
            highscore++;
        }
        else
            cout << "Your Answer is Incorrect" << endl;
    }
}





void Computerquestions(int& highscore)
{
    srand(time(0));
    ifstream file("computer.txt");
    if (!file)
        cout << "ERROR: File Not found" << endl;
    else
    {
        string Questions[10], OptA[10], OptB[10], OptC[10], OptD[10];
        int answer[10];
        for (int i = 0; i < 10; i++)
        {
            getline(file, Questions[i]);
            getline(file, OptA[i]);
            getline(file, OptB[i]);
            getline(file, OptC[i]);
            getline(file, OptD[i]);
            file >> answer[i];
            file.ignore();
        }
        int r = rand() % 10, userans;
        cout << "--------------------------------------" << endl;
        cout << Questions[r] << endl;
        cout << "1. " << OptA[r] << endl;
        cout << "2. " << OptB[r] << endl;
        cout << "3. " << OptC[r] << endl;
        cout << "4. " << OptD[r] << endl;
        cout << "Enter your Answer = ";
        userans = getValidatedInput(1, 4);
        if (userans == answer[r])
        {
            cout << "Your Answer is Correct" << endl;
            highscore++;
        }
        else
            cout << "Your Answer is Incorrect" << endl;
    }
}

void Computerquestionsmid(int& highscore)
{
    srand(time(0));
    ifstream file("computermid.txt");
    if (!file)
        cout << "ERROR: File Not found" << endl;
    else
    {
        string Questions[10], OptA[10], OptB[10], OptC[10], OptD[10];
        int answer[10];
        for (int i = 0; i < 10; i++)
        {
            getline(file, Questions[i]);
            getline(file, OptA[i]);
            getline(file, OptB[i]);
            getline(file, OptC[i]);
            getline(file, OptD[i]);
            file >> answer[i];
            file.ignore();
        }
        int r = rand() % 10, userans;
        cout << "--------------------------------------" << endl;
        cout << Questions[r] << endl;
        cout << "1. " << OptA[r] << endl;
        cout << "2. " << OptB[r] << endl;
        cout << "3. " << OptC[r] << endl;
        cout << "4. " << OptD[r] << endl;
        cout << "Enter your Answer = ";
        userans = getValidatedInput(1, 4);
        if (userans == answer[r])
        {
            cout << "Your Answer is Correct" << endl;
            highscore++;
        }
        else
            cout << "Your Answer is Incorrect" << endl;
    }
}





void Sportsquestions(int& highscore)
{
    srand(time(0));
    ifstream file("sports.txt");
    if (!file)
        cout << "ERROR: File Not found" << endl;
    else
    {
        string Questions[10], OptA[10], OptB[10], OptC[10], OptD[10];
        int answer[10];
        for (int i = 0; i < 10; i++)
        {
            getline(file, Questions[i]);
            getline(file, OptA[i]);
            getline(file, OptB[i]);
            getline(file, OptC[i]);
            getline(file, OptD[i]);
            file >> answer[i];
            file.ignore();
        }
        int r = rand() % 10, userans;
        cout << "--------------------------------------" << endl;
        cout << Questions[r] << endl;
        cout << "1. " << OptA[r] << endl;
        cout << "2. " << OptB[r] << endl;
        cout << "3. " << OptC[r] << endl;
        cout << "4. " << OptD[r] << endl;
        cout << "Enter your Answer = ";
        userans = getValidatedInput(1, 4);
        if (userans == answer[r])
        {
            cout << "Your Answer is Correct" << endl;
            highscore++;
        }
        else
            cout << "Your Answer is Incorrect" << endl;
    }
}

void Sportsquestionsmid(int& highscore)
{
    srand(time(0));
    ifstream file("sportsmid.txt");
    if (!file)
        cout << "ERROR: File Not found" << endl;
    else
    {
        string Questions[10], OptA[10], OptB[10], OptC[10], OptD[10];
        int answer[10];
        for (int i = 0; i < 10; i++)
        {
            getline(file, Questions[i]);
            getline(file, OptA[i]);
            getline(file, OptB[i]);
            getline(file, OptC[i]);
            getline(file, OptD[i]);
            file >> answer[i];
            file.ignore();
        }
        int r = rand() % 10, userans;
        cout << "--------------------------------------" << endl;
        cout << Questions[r] << endl;
        cout << "1. " << OptA[r] << endl;
        cout << "2. " << OptB[r] << endl;
        cout << "3. " << OptC[r] << endl;
        cout << "4. " << OptD[r] << endl;
        cout << "Enter your Answer = ";
        userans = getValidatedInput(1, 4);
        if (userans == answer[r])
        {
            cout << "Your Answer is Correct" << endl;
            highscore++;
        }
        else
            cout << "Your Answer is Incorrect" << endl;
    }
}





void Historyquestions(int& highscore)
{
    srand(time(0));
    ifstream file("history.txt");
    if (!file)
        cout << "ERROR: File Not found" << endl;
    else
    {
        string Questions[10], OptA[10], OptB[10], OptC[10], OptD[10];
        int answer[10];
        for (int i = 0; i < 10; i++)
        {
            getline(file, Questions[i]);
            getline(file, OptA[i]);
            getline(file, OptB[i]);
            getline(file, OptC[i]);
            getline(file, OptD[i]);
            file >> answer[i];
            file.ignore();
        }
        int r = rand() % 10, userans;
        cout << "--------------------------------------" << endl;
        cout << Questions[r] << endl;
        cout << "1. " << OptA[r] << endl;
        cout << "2. " << OptB[r] << endl;
        cout << "3. " << OptC[r] << endl;
        cout << "4. " << OptD[r] << endl;
        cout << "Enter your Answer = ";
        userans = getValidatedInput(1, 4);
        if (userans == answer[r])
        {
            cout << "Your Answer is Correct" << endl;
            highscore++;
        }
        else
            cout << "Your Answer is Incorrect" << endl;
    }
}

void Historyquestionsmid(int& highscore)
{
    srand(time(0));
    ifstream file("historymid.txt");
    if (!file)
        cout << "ERROR: File Not found" << endl;
    else
    {
        string Questions[10], OptA[10], OptB[10], OptC[10], OptD[10];
        int answer[10];
        for (int i = 0; i < 10; i++)
        {
            getline(file, Questions[i]);
            getline(file, OptA[i]);
            getline(file, OptB[i]);
            getline(file, OptC[i]);
            getline(file, OptD[i]);
            file >> answer[i];
            file.ignore();
        }
        int r = rand() % 10, userans;
        cout << "--------------------------------------" << endl;
        cout << Questions[r] << endl;
        cout << "1. " << OptA[r] << endl;
        cout << "2. " << OptB[r] << endl;
        cout << "3. " << OptC[r] << endl;
        cout << "4. " << OptD[r] << endl;
        cout << "Enter your Answer = ";
        userans = getValidatedInput(1, 4);
        if (userans == answer[r])
        {
            cout << "Your Answer is Correct" << endl;
            highscore++;
        }
        else
            cout << "Your Answer is Incorrect" << endl;
    }
}





void Logicquestions(int& highscore)
{
    srand(time(0));
    ifstream file("iq.txt");
    if (!file)
        cout << "ERROR: File Not found" << endl;
    else
    {
        string Questions[10], OptA[10], OptB[10], OptC[10], OptD[10];
        int answer[10];
        for (int i = 0; i < 10; i++)
        {
            getline(file, Questions[i]);
            getline(file, OptA[i]);
            getline(file, OptB[i]);
            getline(file, OptC[i]);
            getline(file, OptD[i]);
            file >> answer[i];
            file.ignore();
        }
        int r = rand() % 10, userans;
        cout << "--------------------------------------" << endl;
        cout << Questions[r] << endl;
        cout << "1. " << OptA[r] << endl;
        cout << "2. " << OptB[r] << endl;
        cout << "3. " << OptC[r] << endl;
        cout << "4. " << OptD[r] << endl;
        cout << "Enter your Answer = ";
        userans = getValidatedInput(1, 4);
        if (userans == answer[r])
        {
            cout << "Your Answer is Correct" << endl;
            highscore++;
        }
        else
            cout << "Your Answer is Incorrect" << endl;
    }
}
void Logicquestionsmid(int& highscore)
{
    srand(time(0));
    ifstream file("iqmid.txt");
    if (!file)
        cout << "ERROR: File Not found" << endl;
    else
    {
        string Questions[10], OptA[10], OptB[10], OptC[10], OptD[10];
        int answer[10];
        for (int i = 0; i < 10; i++)
        {
            getline(file, Questions[i]);
            getline(file, OptA[i]);
            getline(file, OptB[i]);
            getline(file, OptC[i]);
            getline(file, OptD[i]);
            file >> answer[i];
            file.ignore();
        }
        int r = rand() % 10, userans;
        cout << "--------------------------------------" << endl;
        cout << Questions[r] << endl;
        cout << "1. " << OptA[r] << endl;
        cout << "2. " << OptB[r] << endl;
        cout << "3. " << OptC[r] << endl;
        cout << "4. " << OptD[r] << endl;
        cout << "Enter your Answer = ";
        userans = getValidatedInput(1, 4);
        if (userans == answer[r])
        {
            cout << "Your Answer is Correct" << endl;
            highscore++;
        }
        else
            cout << "Your Answer is Incorrect" << endl;
    }
}
