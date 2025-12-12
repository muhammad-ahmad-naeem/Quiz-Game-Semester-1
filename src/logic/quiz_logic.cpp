#include <iostream>
#include <cmath>
#include <string>
#include <cstdlib>
#include <fstream>
#include <conio.h>
#include <ctime>
#include <cstring>
using namespace std;

// Lifelines
bool lifeline_5050 = false;
bool lifeline_skip = false;
bool lifeline_replace_question = false;
bool lifeline_extratime = false;

// Function declarations
void liflines_system();
void mainmenue();
void submenue();
void diffcultymenue();
void Sciencequestions(int& highscore);
void Sciencequestionsmid(int& highscore);
void Sciencequestionshard(int& highscore);
void Computerquestions(int& highscore);
void Computerquestionsmid(int& highscore);
void Computerquestionshard(int& highscore);
void Sportsquestions(int& highscore);
void Sportsquestionsmid(int& highscore);
void Sportsquestionshard(int& highscore);
void Historyquestions(int& highscore);
void Historyquestionsmid(int& highscore);
void Historyquestionshard(int& highscore);
void Logicquestions(int& highscore);
void Logicquestionsmid(int& highscore);
void Logicquestionshard(int& highscore);

// Player functions
void savePlayerScore(const char* name, int score);
void showTopPlayers();

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

// Get current date in DD-MM-YYYY format
string getCurrentDate() {
    time_t now = time(0);
    tm ltm;                       // create tm object (not pointer)
    localtime_s(&ltm, &now); 
    char buf[20];
    sprintf_s(buf, "%02d-%02d-%04d", ltm.tm_mday, ltm.tm_mon + 1, 1900 + ltm.tm_year);
    return string(buf);
}


// Save quiz session log to file with date
void saveQuizLog(const char* playerName, int score) {
    ofstream logfile("quiz_log.txt", ios::app);
    if (logfile.is_open()) {
        string date = getCurrentDate();
        logfile << "Name: " << playerName
            << " | Score: " << score
            << " | Date: " << date
            << endl;
        logfile.close();
    }
}

int getTimedAnswer(int minOption, int maxOption, int timeLimitSeconds)
{
    time_t start = time(0);
    string buffer;
    cout << " (You have " << timeLimitSeconds << " seconds) " << flush;
    cout << endl;
    while (true)
    {
        double elapsed = difftime(time(0), start);
        if (elapsed >= timeLimitSeconds)
        {
            cout << "-----------------" << endl;
            cout << "   Time is up!" << endl;
            cout << "-----------------" << endl;
            cout << endl;
            return -1;
        }
        if (_kbhit())
        {
            char ch = _getch();
            if (ch == '\r' || ch == '\n')
            {
                if (!buffer.empty())
                {
                    int value = stoi(buffer);
                    if (value >= minOption && value <= maxOption)
                    {
                        cout << endl;
                        return value;
                    }
                    else
                    {
                        cout << "\nError: invalid option. Try again: " << flush;
                        buffer.clear();
                    }
                }
            }
            else if (ch == '\b' || ch == 127)
            {
                if (!buffer.empty())
                {
                    buffer.pop_back();
                    cout << "\b \b" << flush;
                }
            }
            else if (ch >= '0' && ch <= '9')
            {
                buffer.push_back(ch);
                cout << ch << flush;
            }
        }
    }
}

int main()
{
    char playerName[50];
    cout << "Enter your name: ";
    cin.getline(playerName, 50);

    int input, input1, input3, highscore = 0;
    system("cls");
    cout << "====================================" << endl;
    cout << "      Welcome to Quiz game          " << endl;
    cout << "------------------------------------" << endl;

    while (true)
    {
        mainmenue();
        input = getValidatedInput(1, 4); // Updated to include Top 5
        system("cls");
        if (input == 3)
        {
            savePlayerScore(playerName, highscore); // Save score on exit
            saveQuizLog(playerName, highscore);
            break;
        }
        if (input == 2)
        {
            cout << "High score = " << highscore << endl;
            cout << "Your score = " << highscore << endl;
            continue;
        }
        if (input == 4)
        {
            showTopPlayers();
            continue;
        }
        switch (input)
        {
        case 1:
            do
            {
                diffcultymenue();
                input3 = getValidatedInput(1, 4);
                system("cls");
                switch (input3)
                {
                case 1:
                    cout << "Select from the topic below" << endl;
                    do
                    {
                        submenue();
                        input1 = getValidatedInput(1, 6);
                        system("cls");
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
                    cout << "Select from the topic below" << endl;
                    do
                    {
                        submenue();
                        input1 = getValidatedInput(1, 6);
                        switch (input1)
                        {
                        case 1:
                            Sciencequestionsmid(highscore);
                            break;
                        case 2:
                            Computerquestionsmid(highscore);
                            break;
                        case 3:
                            Sportsquestionsmid(highscore);
                            break;
                        case 4:
                            Historyquestionsmid(highscore);
                            break;
                        case 5:
                            Logicquestionsmid(highscore);
                            break;
                        case 6:
                            break;
                        }
                    } while (input1 != 6);
                    break;

                case 3:
                    cout << "Select from the topic below" << endl;
                    do
                    {
                        submenue();
                        input1 = getValidatedInput(1, 6);
                        switch (input1)
                        {
                        case 1:
                            Sciencequestionshard(highscore);
                            break;
                        case 2:
                            Computerquestionshard(highscore);
                            break;
                        case 3:
                            Sportsquestionshard(highscore);
                            break;
                        case 4:
                            Historyquestionshard(highscore);
                            break;
                        case 5:
                            Logicquestionshard(highscore);
                            break;
                        case 6:
                            break;
                        }
                    } while (input1 != 6);
                    break;

                case 4:
                    input = 0;
                    break;
                }

            } while (input3 != 4);
            break;
        }
    }
    return 0;
}

// ----------------------- MENU FUNCTIONS -----------------------
void mainmenue()
{
    
    cout << "   MAIN MENUE" << endl;
    cout << endl;
    cout << "Enter 1 ==>  Start Game" << endl;
    cout << "Enter 2 ==>  High Scores" << endl;
    cout << "Enter 3 ==>  Exit Game" << endl;
    cout << "Enter 4 ==>  Top 5 Players" << endl; // New
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

void liflines_system()
{
    cout << "\n========================================\n";
    cout << "           LIFELINES MENU\n";
    cout << "========================================\n";
    cout << " 1) 50/50          -> removes two wrong options\n";
    cout << " 2) Skip Question  -> skip without penalty\n";
    cout << " 3) Replace        -> get a completely new question\n";
    cout << " 4) Extra Time     -> +10 seconds for this question\n";
    cout << " 5) No Lifeline    -> answer without using any help\n";
    cout << "----------------------------------------\n";
    cout << " Choose your lifeline (1-5): ";
}

// ----------------------- PLAYER FUNCTIONS -----------------------
void savePlayerScore(const char* name, int score)
{
    ofstream file("players_scores.txt", ios::app);
    if (file.is_open())
    {
        file << name << " " << score << endl;
        file.close();
    }
}

void showTopPlayers()
{
    const int MAX_PLAYERS = 100;
    char names[MAX_PLAYERS][50];
    int scores[MAX_PLAYERS];
    int count = 0;
    ifstream file("players_scores.txt");
    if (!file)
    {
        cout << "No scores found!" << endl;
        return;
    }
    while (file >> names[count] >> scores[count])
    {
        count++;
        if (count >= MAX_PLAYERS) break;
    }
    file.close();

    // Bubble sort for top scores
    for (int i = 0; i < count - 1; i++)
    {
        for (int j = i + 1; j < count; j++)
        {
            if (scores[i] < scores[j])
            {
                int tempScore = scores[i];
                scores[i] = scores[j];
                scores[j] = tempScore;

                char tempName[50];
                strcpy_s(tempName, names[i]);
                strcpy_s(names[i], names[j]);
                strcpy_s(names[j], tempName);
            }
        }
    }
    cout << "\n===== TOP 5 PLAYERS =====\n";
    cout << "Rank   Name        Score\n";
    cout << "------------------------\n";
    for (int i = 0; i < count && i < 5; i++)
    {
        cout << i + 1 << "      " << names[i] << "        " << scores[i] << endl;
    }
    cout << "=========================\n";
    cout <<" enter any key to enter Main Menue = ";
    int a;
    cin >> a;
    system("cls");
    
}
