#include<iostream>

#include <iostream>
#include <cmath>
#include <string>
#include <cstdlib>
#include <fstream>
#include <conio.h>
#include <ctime>
#include <cstring>
#include <windows.h>

using namespace std;
const int MAX_WRONG = 500;

int wrongIndex[MAX_WRONG];        // question index r
int wrongType[MAX_WRONG];         // which subject+level
int wrongUserAns[MAX_WRONG];      // user answer
int wrongCorrectAns[MAX_WRONG];   // correct answer
int wrongCount = 0;
int replayAfterReview();        //replay questions

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

void setColor(int color);


void reviewWrongQuestions();
void loadQuestionsFromFile(const string filename, string Questions[10], string OptA[10], string OptB[10], string OptC[10], string OptD[10], int answer[10]);
//global variables
int correctAnswers = 0;
int wrongAnswers = 0;
bool replayHardDirect = false;
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

void setColor(int color)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
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

string getCurrentDateTime()
{
    time_t now = time(0);
    tm ltm;
    localtime_s(&ltm, &now);

    char buffer[40];
    sprintf_s(buffer, "%02d-%02d-%04d %02d:%02d",
        ltm.tm_mday,
        ltm.tm_mon + 1,
        1900 + ltm.tm_year,
        ltm.tm_hour,
        ltm.tm_min);

    return string(buffer);
}


// Save quiz session log to file with date
void saveQuizLog(const char* playerName, int score)
{

    ofstream logfile("quiz_logs.txt", ios::app);
    if (logfile.is_open())
    {
        logfile << "Name: " << playerName << " | DateTime: " << getCurrentDateTime() << " | Correct: " << correctAnswers
            << " | Wrong: " << wrongAnswers << " | Score: " << score << endl;
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

            setColor(12);
            cout << "-----------------" << endl;
            setColor(15);
            cout << "   Time is up!" << endl;
            setColor(12);
            cout << "-----------------" << endl;
            setColor(7);
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
                        setColor(4);
                        cout << "\nError: invalid option. Try again: " << flush;
                        setColor(7);
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
    setColor(11);
    cout << "====================================" << endl;
    setColor(15);
    cout << "      Welcome to Quiz game          " << endl;
    setColor(11);
    cout << "------------------------------------" << endl;
    setColor(7);

    while (true)
    {
        if (!replayHardDirect)
        {
            mainmenue();
            input = getValidatedInput(1, 4);
        }
        else
        {
            input = 1;          // Start Game
            input3 = 3;         // Hard
            replayHardDirect = false;
        } // Updated to include Top 5
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
                    setColor(11);
                    cout << "Select from the topic below" << endl;
                    setColor(7);
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
                    setColor(11);
                    cout << "Select from the topic below" << endl;
                    setColor(7);
                    do
                    {
                        submenue();
                        input1 = getValidatedInput(1, 6);
                        system("cls");
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
                    setColor(11);
                    cout << "Select from the topic below" << endl;
                    setColor(7);
                    do
                    {
                        submenue();
                        input1 = getValidatedInput(1, 6);
                        system("cls");
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
            if (wrongCount > 0)
            {
                char ch;
                cout << "Do you want to review wrong questions? (y/n): ";
                cin >> ch;

                if (ch == 'y' || ch == 'Y')
                {
                    reviewWrongQuestions();

                    int choice = replayAfterReview();

                    wrongCount = 0;   // reset after review

                    if (choice == 1)
                    {
                        replayHardDirect = true;
                        continue;
                    }
                    else
                    {
                        exit(0);
                    }
                }
                wrongCount = 0;
            }
            break;
        }
    }
    return 0;
}

int replayAfterReview()
{
    char ch;
    cout << "\nDo you want to replay questions? (y/n): ";
    cin >> ch;

    if (ch == 'y' || ch == 'Y')
        return 1;   // replay → difficulty menu
    else
        return -1;  // exit game
}


// ----------------------- MENU FUNCTIONS -----------------------
void mainmenue()
{
    setColor(14);
    cout << "   <<MAIN MENUE>>" << endl;
    setColor(7);
    cout << endl;
    cout << "Enter 1 ==>  Start Game" << endl;
    cout << "Enter 2 ==>  High Scores" << endl;
    cout << "Enter 3 ==>  Exit Game" << endl;
    cout << "Enter 4 ==>  Top 5 Players" << endl;
    setColor(11);
    cout << "------------------------------------" << endl;
    setColor(7);
}

void submenue()
{
    cout << endl;
    cout << "Enter 1 ==>  Science" << endl;
    cout << "Enter 2 ==>  Computer" << endl;
    cout << "Enter 3 ==>  Sports" << endl;
    cout << "Enter 4 ==>  History" << endl;
    cout << "Enter 5 ==>  IQ/Logic" << endl;
    setColor(14);
    cout << "Enter 6 ==>  GO TO DIFFICULTY MENU" << endl;
    setColor(7);
    cout << endl;
}

void diffcultymenue()
{
    cout << endl;
    setColor(13);
    cout << "  Difficulty Selection  " << endl;
    setColor(11);
    cout << "------------------------" << endl;
    setColor(10);
    cout << "Enter 1 ==>  Easy" << endl;
    setColor(3);
    cout << "Enter 2 ==>  Medium" << endl;
    setColor(12);
    cout << "Enter 3 ==>  Hard" << endl;
    setColor(14);
    cout << "Enter 4 ==>  GO TO MAIN MENU" << endl;
    setColor(7);
    cout << endl;
}

void liflines_system()
{
    setColor(11);
    cout << "\n========================================\n";
    setColor(14);
    cout << "           LIFELINES MENU\n";
    setColor(11);
    cout << "========================================\n";
    setColor(7);
    cout << " 1) 50/50          -> removes two wrong options\n";
    cout << " 2) Skip Question  -> skip without penalty\n";
    cout << " 3) Replace        -> get a completely new question\n";
    cout << " 4) Extra Time     -> +10 seconds for this question\n";
    cout << " 5) No Lifeline    -> answer without using any help\n";
    setColor(11);
    cout << "----------------------------------------\n";
    setColor(7);
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
    setColor(14);
    cout << "\n===== TOP 5 PLAYERS =====\n";
    setColor(11);
    cout << "Rank   Name        Score\n";
    cout << "------------------------\n";
    setColor(7);
    for (int i = 0; i < count && i < 5; i++)
    {
        cout << i + 1 << "      " << names[i] << "        " << scores[i] << endl;
    }
    setColor(11);
    cout << "=========================\n";
    setColor(10);
    cout << " enter any key to enter Main Menue = ";
    setColor(7);
    int a;
    cin >> a;
    system("cls");

}
void loadQuestionsFromFile(string filename, string Questions[10], string OptA[10], string OptB[10], string OptC[10], string OptD[10], int answer[10])
{
    ifstream file(filename);
    if (!file)
    {
        cout << "ERROR: File not found: " << filename << endl;
        return;
    }

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
    file.close();
}

void reviewWrongQuestions()
{
    if (wrongCount == 0)
    {
        setColor(10);
        cout << "No wrong answers to review.\n";
        setColor(7);
        return;
    }
    setColor(11);
    cout << "\n===== Review Wrong Questions =====\n";
    setColor(7);

    string Questions[10], OptA[10], OptB[10], OptC[10], OptD[10];
    int answer[10];

    for (int i = 0; i < wrongCount; ++i)
    {
        int idx = wrongIndex[i];  // r for that question
        int type = wrongType[i];

        string filename;

        if (type == 1)  filename = "science.txt";
        if (type == 2)  filename = "sciencemid.txt";
        if (type == 3)  filename = "sciencehard.txt";
        if (type == 4)  filename = "computer.txt";
        if (type == 5)  filename = "computermid.txt";
        if (type == 6)  filename = "computerhard.txt";
        if (type == 7)  filename = "sports.txt";
        if (type == 8)  filename = "sportsmid.txt";
        if (type == 9)  filename = "sportshard.txt";
        if (type == 10) filename = "history.txt";
        if (type == 11) filename = "historymid.txt";
        if (type == 12) filename = "historyhard.txt";
        if (type == 13) filename = "iq.txt";
        if (type == 14) filename = "iqmid.txt";
        if (type == 15) filename = "iqhard.txt";

        if (filename.empty())
            continue;

        loadQuestionsFromFile(filename, Questions, OptA, OptB, OptC, OptD, answer);

        if (idx < 0 || idx >= 10)
            continue;
        setColor(11);
        cout << "\nQuestion " << (i + 1) << ": " << Questions[idx] << "\n";
        setColor(7);
        cout << "1. " << OptA[idx] << "\n";
        cout << "2. " << OptB[idx] << "\n";
        cout << "3. " << OptC[idx] << "\n";
        cout << "4. " << OptD[idx] << "\n";
        setColor(12);
        cout << "Your answer: " << wrongUserAns[i] << "\n";
        setColor(10);
        cout << "Correct answer: " << wrongCorrectAns[i] << "\n";
        setColor(7);
    }

    cout << endl;
}




//questions for sciences
void Sciencequestions(int& highscore)   //easy level questions
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
        int r = rand() % 10;
        int userans = 0;
        int allowed[5] = { 0, 1, 1, 1, 1 }; // index 1..4 = allowed (1) or removed (0)
        int extraSeconds = 0; // extra seconds added by lifeline
        setColor(11);
        cout << "--------------------------------------" << endl;
        setColor(14);
        cout << Questions[r] << endl;
        setColor(7);
        cout << "1. " << OptA[r] << endl;
        cout << "2. " << OptB[r] << endl;
        cout << "3. " << OptC[r] << endl;
        cout << "4. " << OptD[r] << endl;
        cout << endl;
        setColor(10);
        cout << "==> Do you want to use your lifelines (y/n) =  ";
        setColor(7);
        char user_choice;

        cin >> user_choice;
        if (user_choice == 'y')
        {
            system("cls");
            liflines_system();
            int choice;
            cout << " " << endl;
            cout << "Enter your choice = ";
            cin >> choice;
            system("cls");
            if (choice == 1 && lifeline_5050 == false)
            {
                lifeline_5050 = true;
                cout << " " << endl;
                cout << "Two option removed " << endl;
                int correct = answer[r];
                int remove = 0;
                for (int i = 1; i <= 4; i++)
                {
                    allowed[i] = 1; // ensure default
                }
                for (int i = 1; i <= 4; i++)
                {
                    if (i == correct)
                        continue;
                    if (remove < 2)
                    {
                        allowed[i] = 0;
                        remove++;
                    }
                }
                for (int i = 1; i <= 4; i++)
                {
                    if (allowed[i] == 1)
                        continue;

                }
                setColor(14);
                cout << Questions[r] << endl;
                setColor(7);
                for (int j = 1; j <= 4; j++)
                {
                    if (allowed[j] == 0)
                        continue;
                    if (j == 1)
                        cout << "1. " << OptA[r] << endl;
                    if (j == 2)
                        cout << "2. " << OptB[r] << endl;
                    if (j == 3)
                        cout << "3. " << OptC[r] << endl;
                    if (j == 4)
                        cout << "4. " << OptD[r] << endl;
                }
            }
            else if (choice == 2 && lifeline_skip == false)
            {
                lifeline_skip = true;
                setColor(2);
                cout << "The question is skipped successfully " << endl;
                setColor(7);
                return;
            }
            else if (choice == 3 && lifeline_replace_question == false)
            {
                lifeline_replace_question = true;
                r = rand() % 10;
                setColor(11);
                cout << "--------------------------------------" << endl;
                setColor(14);
                cout << Questions[r] << endl;
                setColor(7);
                cout << "1. " << OptA[r] << endl;
                cout << "2. " << OptB[r] << endl;
                cout << "3. " << OptC[r] << endl;
                cout << "4. " << OptD[r] << endl;
            }
            else if (choice == 4 && lifeline_extratime == false)
            {
                lifeline_extratime = true;
                extraSeconds += 10;
                setColor(3);
                cout << "You got 10 extra seconds " << endl;
                setColor(11);
                cout << "--------------------------------------" << endl;
                setColor(14);
                cout << Questions[r] << endl;
                setColor(7);
                cout << "1. " << OptA[r] << endl;
                cout << "2. " << OptB[r] << endl;
                cout << "3. " << OptC[r] << endl;
                cout << "4. " << OptD[r] << endl;
                cout << endl;
            }
            else if (choice == 5)
            {
                setColor(3);
                cout << " you selected not to choose any lifeline ";
                cout << endl;
                setColor(11);
                cout << "--------------------------------------" << endl;
                setColor(14);
                cout << Questions[r] << endl;
                setColor(7);
                cout << "1. " << OptA[r] << endl;
                cout << "2. " << OptB[r] << endl;
                cout << "3. " << OptC[r] << endl;
                cout << "4. " << OptD[r] << endl;
                cout << endl;
            }
            else
            {
                setColor(3);
                cout << "You already used this lifeline " << endl;
                setColor(11);
                cout << "--------------------------------------" << endl;
                setColor(14);
                cout << Questions[r] << endl;
                setColor(7);
                cout << "1. " << OptA[r] << endl;
                cout << "2. " << OptB[r] << endl;
                cout << "3. " << OptC[r] << endl;
                cout << "4. " << OptD[r] << endl;
                cout << endl;
            }
            cout << "Enter your Answer = " << endl;
        }
        else
        {
            cout << " " << endl;
            cout << " You choose not to use any lifeline " << endl;
        }
        int timeForThis = 10 + extraSeconds;
        userans = getTimedAnswer(1, 4, timeForThis);
        if (userans == -1)
        {
            setColor(12);
            cout << " << You failed to answer in time. >>" << endl;
            setColor(7);
        }
        else
        {
            if (allowed[userans] == 0)
            {
                cout << endl;
                setColor(12);
                cout << "That option was removed by 50/50 lifeline. Incorrect." << endl;
                setColor(7);
            }
            else
            {
                cout << endl;
                cout << "" << endl;
            }
        }
        if (userans == answer[r])
        {
            cout << endl;
            setColor(2);
            cout << "Your Answer is Correct" << endl;
            setColor(7);
            highscore = highscore + 2;
            correctAnswers++;
            cout << highscore;
            system("pause");
            system("cls");
        }
        else
        {
            setColor(12);
            cout << " <<Your Answer is Incorrect.>>" << endl;
            setColor(14);
            setColor(2);
            cout << "correct answer is = " << answer[r] << endl;
            setColor(7);
            highscore = highscore - 2;
            wrongAnswers++;
            cout << endl;
            wrongIndex[wrongCount] = r;
            wrongType[wrongCount] = 1;
            wrongUserAns[wrongCount] = userans;
            wrongCorrectAns[wrongCount] = answer[r];
            wrongCount++;
            system("pause");
            system("cls");
        }

    }
}

void Sciencequestionsmid(int& highscore)   //meduim level questions
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
        int r = rand() % 10;
        int userans = 0;
        int allowed[5] = { 0, 1, 1, 1, 1 }; // index 1..4 = allowed (1) or removed (0)
        int extraSeconds = 0; // extra seconds added by lifeline
        setColor(11);
        cout << "--------------------------------------" << endl;
        setColor(14);
        cout << Questions[r] << endl;
        setColor(7);
        cout << "1. " << OptA[r] << endl;
        cout << "2. " << OptB[r] << endl;
        cout << "3. " << OptC[r] << endl;
        cout << "4. " << OptD[r] << endl;
        cout << endl;
        setColor(10);
        cout << "==> Do you want to use your lifelines (y/n) =  ";
        setColor(7);
        char user_choice;

        cin >> user_choice;
        if (user_choice == 'y')
        {
            system("cls");
            liflines_system();
            int choice;
            cout << " " << endl;
            cout << "Enter your choice = ";
            cin >> choice;
            system("cls");
            if (choice == 1 && lifeline_5050 == false)
            {
                lifeline_5050 = true;
                cout << " " << endl;
                cout << "Two option removed " << endl;
                int correct = answer[r];
                int remove = 0;
                for (int i = 1; i <= 4; i++)
                {
                    allowed[i] = 1; // ensure default
                }
                for (int i = 1; i <= 4; i++)
                {
                    if (i == correct)
                        continue;
                    if (remove < 2)
                    {
                        allowed[i] = 0;
                        remove++;
                    }
                }
                for (int i = 1; i <= 4; i++)
                {
                    if (allowed[i] == 1)
                        continue;

                }
                cout << Questions[r] << endl;
                for (int j = 1; j <= 4; j++)
                {
                    if (allowed[j] == 0)
                        continue;
                    if (j == 1)
                        cout << "1. " << OptA[r] << endl;
                    if (j == 2)
                        cout << "2. " << OptB[r] << endl;
                    if (j == 3)
                        cout << "3. " << OptC[r] << endl;
                    if (j == 4)
                        cout << "4. " << OptD[r] << endl;
                }
            }
            else if (choice == 2 && lifeline_skip == false)
            {
                lifeline_skip = true;
                cout << "The question is skipped successfully " << endl;
                return;
            }
            else if (choice == 3 && lifeline_replace_question == false)
            {
                lifeline_replace_question = true;
                r = rand() % 10;
                setColor(11);
                cout << "--------------------------------------" << endl;
                setColor(14);
                cout << Questions[r] << endl;
                setColor(7);
                cout << "1. " << OptA[r] << endl;
                cout << "2. " << OptB[r] << endl;
                cout << "3. " << OptC[r] << endl;
                cout << "4. " << OptD[r] << endl;
            }
            else if (choice == 4 && lifeline_extratime == false)
            {
                lifeline_extratime = true;
                extraSeconds += 10;
                cout << "You got 10 extra seconds " << endl;
                setColor(11);
                cout << "--------------------------------------" << endl;
                setColor(14);
                cout << Questions[r] << endl;
                setColor(7);
                cout << "1. " << OptA[r] << endl;
                cout << "2. " << OptB[r] << endl;
                cout << "3. " << OptC[r] << endl;
                cout << "4. " << OptD[r] << endl;
                cout << endl;
            }
            else if (choice == 5)
            {
                cout << " you selected not to choose any lifeline ";
                cout << endl;
                setColor(11);
                cout << "--------------------------------------" << endl;
                setColor(14);
                cout << Questions[r] << endl;
                setColor(7);
                cout << "1. " << OptA[r] << endl;
                cout << "2. " << OptB[r] << endl;
                cout << "3. " << OptC[r] << endl;
                cout << "4. " << OptD[r] << endl;
                cout << endl;
            }
            else
            {
                cout << "You already used this lifeline " << endl;
                setColor(11);
                cout << "--------------------------------------" << endl;
                setColor(14);
                cout << Questions[r] << endl;
                setColor(7);
                cout << "1. " << OptA[r] << endl;
                cout << "2. " << OptB[r] << endl;
                cout << "3. " << OptC[r] << endl;
                cout << "4. " << OptD[r] << endl;
                cout << endl;
            }
            cout << "Enter your Answer = " << endl;
        }
        else
        {
            cout << " " << endl;
            cout << " You choose not to use any lifeline " << endl;
        }
        int timeForThis = 10 + extraSeconds;
        userans = getTimedAnswer(1, 4, timeForThis);
        if (userans == -1)
        {
            cout << " << You failed to answer in time. >>" << endl;
        }
        else
        {
            if (allowed[userans] == 0)
            {
                cout << endl;
                cout << "That option was removed by 50/50 lifeline. Incorrect." << endl;
            }
            else
            {
                cout << endl;
                cout << "" << endl;
            }
        }
        if (userans == answer[r])
        {
            cout << endl;
            setColor(2);
            cout << "Your Answer is Correct" << endl;
            setColor(7);
            highscore = highscore + 3;
            correctAnswers++;
            cout << highscore;
            system("pause");
            system("cls");
        }
        else
        {
            setColor(12);
            cout << " <<Your Answer is Incorrect.>>" << endl;
            setColor(2);
            cout << "correct answer is = " << answer[r] << endl;
            setColor(7);
            highscore = highscore - 3;
            wrongAnswers++;
            cout << endl;
            wrongIndex[wrongCount] = r;
            wrongType[wrongCount] = 2;
            wrongUserAns[wrongCount] = userans;
            wrongCorrectAns[wrongCount] = answer[r];
            wrongCount++;
            system("pause");
            system("cls");
        }

    }
}


void Sciencequestionshard(int& highscore)   //Hard level questions
{
    srand(time(0));
    ifstream file("sciencehard.txt");
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
        int r = rand() % 10;
        int userans = 0;
        int allowed[5] = { 0, 1, 1, 1, 1 };       // index 1..4 = allowed (1) or removed (0)
        int extraSeconds = 0;                     // extra seconds added by lifeline
        setColor(11);
        cout << "--------------------------------------" << endl;
        setColor(14);
        cout << Questions[r] << endl;
        setColor(7);
        cout << "1. " << OptA[r] << endl;
        cout << "2. " << OptB[r] << endl;
        cout << "3. " << OptC[r] << endl;
        cout << "4. " << OptD[r] << endl;
        cout << endl;
        setColor(10);
        cout << "==> Do you want to use your lifelines (y/n) =  ";
        setColor(7);
        char user_choice;

        cin >> user_choice;
        if (user_choice == 'y')
        {
            system("cls");
            liflines_system();
            int choice;
            cout << " " << endl;
            cout << "Enter your choice = ";
            cin >> choice;
            system("cls");
            if (choice == 1 && lifeline_5050 == false)
            {
                lifeline_5050 = true;
                cout << " " << endl;
                cout << "Two option removed " << endl;
                int correct = answer[r];
                int remove = 0;
                for (int i = 1; i <= 4; i++)
                {
                    allowed[i] = 1; // ensure default
                }
                for (int i = 1; i <= 4; i++)
                {
                    if (i == correct)
                        continue;
                    if (remove < 2)
                    {
                        allowed[i] = 0;
                        remove++;
                    }
                }
                for (int i = 1; i <= 4; i++)
                {
                    if (allowed[i] == 1)
                        continue;

                }
                cout << Questions[r] << endl;
                for (int j = 1; j <= 4; j++)
                {
                    if (allowed[j] == 0)
                        continue;
                    if (j == 1)
                        cout << "1. " << OptA[r] << endl;
                    if (j == 2)
                        cout << "2. " << OptB[r] << endl;
                    if (j == 3)
                        cout << "3. " << OptC[r] << endl;
                    if (j == 4)
                        cout << "4. " << OptD[r] << endl;
                }
            }
            else if (choice == 2 && lifeline_skip == false)
            {
                lifeline_skip = true;
                cout << "The question is skipped successfully " << endl;
                return;
            }
            else if (choice == 3 && lifeline_replace_question == false)
            {
                lifeline_replace_question = true;
                r = rand() % 10;
                setColor(11);
                cout << "--------------------------------------" << endl;
                setColor(14);
                cout << Questions[r] << endl;
                setColor(7);
                cout << "1. " << OptA[r] << endl;
                cout << "2. " << OptB[r] << endl;
                cout << "3. " << OptC[r] << endl;
                cout << "4. " << OptD[r] << endl;
            }
            else if (choice == 4 && lifeline_extratime == false)
            {
                lifeline_extratime = true;
                extraSeconds += 10;
                cout << "You got 10 extra seconds " << endl;
                setColor(11);
                cout << "--------------------------------------" << endl;
                setColor(14);
                cout << Questions[r] << endl;
                setColor(7);
                cout << "1. " << OptA[r] << endl;
                cout << "2. " << OptB[r] << endl;
                cout << "3. " << OptC[r] << endl;
                cout << "4. " << OptD[r] << endl;
                cout << endl;
            }
            else if (choice == 5)
            {
                cout << " you selected not to choose any lifeline ";
                cout << endl;
                setColor(11);
                cout << "--------------------------------------" << endl;
                setColor(14);
                cout << Questions[r] << endl;
                setColor(7);
                cout << "1. " << OptA[r] << endl;
                cout << "2. " << OptB[r] << endl;
                cout << "3. " << OptC[r] << endl;
                cout << "4. " << OptD[r] << endl;
                cout << endl;
            }
            else
            {
                cout << "You already used this lifeline " << endl;
                setColor(11);
                cout << "--------------------------------------" << endl;
                setColor(14);
                cout << Questions[r] << endl;
                setColor(7);
                cout << "1. " << OptA[r] << endl;
                cout << "2. " << OptB[r] << endl;
                cout << "3. " << OptC[r] << endl;
                cout << "4. " << OptD[r] << endl;
                cout << endl;
            }
            cout << "Enter your Answer = " << endl;
        }
        else
        {
            cout << " " << endl;
            cout << " You choose not to use any lifeline " << endl;
        }
        int timeForThis = 10 + extraSeconds;
        userans = getTimedAnswer(1, 4, timeForThis);
        if (userans == -1)
        {
            cout << " << You failed to answer in time. >>" << endl;
        }
        else
        {
            if (allowed[userans] == 0)
            {
                cout << endl;
                cout << "That option was removed by 50/50 lifeline. Incorrect." << endl;
            }
            else
            {
                cout << endl;
                cout << "" << endl;
            }
        }
        if (userans == answer[r])
        {
            cout << endl;
            setColor(2);
            cout << "Your Answer is Correct" << endl;
            setColor(7);
            highscore = highscore + 5;
            correctAnswers++;
            cout << highscore;
            system("pause");
            system("cls");
        }
        else
        {
            setColor(12);
            cout << " <<Your Answer is Incorrect.>>" << endl;
            setColor(2);
            cout << "correct answer is = " << answer[r] << endl;
            setColor(7);
            highscore = highscore - 5;
            wrongAnswers++;
            cout << endl;
            wrongIndex[wrongCount] = r;
            wrongType[wrongCount] = 3;
            wrongUserAns[wrongCount] = userans;
            wrongCorrectAns[wrongCount] = answer[r];
            wrongCount++;
            system("pause");
            system("cls");
        }

    }
}




//questions for computer
void Computerquestions(int& highscore)   //easy level questions
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
        int r = rand() % 10;
        int userans = 0;
        int allowed[5] = { 0, 1, 1, 1, 1 }; // index 1..4 = allowed (1) or removed (0)
        int extraSeconds = 0; // extra seconds added by lifeline
        setColor(11);
        cout << "--------------------------------------" << endl;
        setColor(14);
        cout << Questions[r] << endl;
        setColor(7);
        cout << "1. " << OptA[r] << endl;
        cout << "2. " << OptB[r] << endl;
        cout << "3. " << OptC[r] << endl;
        cout << "4. " << OptD[r] << endl;
        cout << endl;
        setColor(10);
        cout << "==> Do you want to use your lifelines (y/n) =  ";
        setColor(7);
        char user_choice;

        cin >> user_choice;
        if (user_choice == 'y')
        {
            system("cls");
            liflines_system();
            int choice;
            cout << " " << endl;
            cout << "Enter your choice = ";
            cin >> choice;
            system("cls");
            if (choice == 1 && lifeline_5050 == false)
            {
                lifeline_5050 = true;
                cout << " " << endl;
                cout << "Two option removed " << endl;
                int correct = answer[r];
                int remove = 0;
                for (int i = 1; i <= 4; i++)
                {
                    allowed[i] = 1; // ensure default
                }
                for (int i = 1; i <= 4; i++)
                {
                    if (i == correct)
                        continue;
                    if (remove < 2)
                    {
                        allowed[i] = 0;
                        remove++;
                    }
                }
                for (int i = 1; i <= 4; i++)
                {
                    if (allowed[i] == 1)
                        continue;

                }
                cout << Questions[r] << endl;
                for (int j = 1; j <= 4; j++)
                {
                    if (allowed[j] == 0)
                        continue;
                    if (j == 1)
                        cout << "1. " << OptA[r] << endl;
                    if (j == 2)
                        cout << "2. " << OptB[r] << endl;
                    if (j == 3)
                        cout << "3. " << OptC[r] << endl;
                    if (j == 4)
                        cout << "4. " << OptD[r] << endl;
                }
            }
            else if (choice == 2 && lifeline_skip == false)
            {
                lifeline_skip = true;
                cout << "The question is skipped successfully " << endl;
                return;
            }
            else if (choice == 3 && lifeline_replace_question == false)
            {
                lifeline_replace_question = true;
                r = rand() % 10;
                cout << "--------------------------------------" << endl;
                cout << Questions[r] << endl;
                cout << "1. " << OptA[r] << endl;
                cout << "2. " << OptB[r] << endl;
                cout << "3. " << OptC[r] << endl;
                cout << "4. " << OptD[r] << endl;
            }
            else if (choice == 4 && lifeline_extratime == false)
            {
                lifeline_extratime = true;
                extraSeconds += 10;
                cout << "You got 10 extra seconds " << endl;
                setColor(11);
                cout << "--------------------------------------" << endl;
                setColor(14);
                cout << Questions[r] << endl;
                setColor(7);
                cout << "1. " << OptA[r] << endl;
                cout << "2. " << OptB[r] << endl;
                cout << "3. " << OptC[r] << endl;
                cout << "4. " << OptD[r] << endl;
                cout << endl;
            }
            else if (choice == 5)
            {
                cout << " you selected not to choose any lifeline ";
                cout << endl;
                setColor(11);
                cout << "--------------------------------------" << endl;
                setColor(14);
                cout << Questions[r] << endl;
                setColor(7);
                cout << "1. " << OptA[r] << endl;
                cout << "2. " << OptB[r] << endl;
                cout << "3. " << OptC[r] << endl;
                cout << "4. " << OptD[r] << endl;
                cout << endl;
            }
            else
            {
                cout << "You already used this lifeline " << endl;
                setColor(11);
                cout << "--------------------------------------" << endl;
                setColor(14);
                cout << Questions[r] << endl;
                setColor(7);
                cout << "1. " << OptA[r] << endl;
                cout << "2. " << OptB[r] << endl;
                cout << "3. " << OptC[r] << endl;
                cout << "4. " << OptD[r] << endl;
                cout << endl;
            }
            cout << "Enter your Answer = " << endl;
        }
        else
        {
            cout << " " << endl;
            cout << " You choose not to use any lifeline " << endl;
        }
        int timeForThis = 10 + extraSeconds;
        userans = getTimedAnswer(1, 4, timeForThis);
        if (userans == -1)
        {
            cout << " << You failed to answer in time. >>" << endl;
        }
        else
        {
            if (allowed[userans] == 0)
            {
                cout << endl;
                cout << "That option was removed by 50/50 lifeline. Incorrect." << endl;
            }
            else
            {
                cout << endl;
                cout << "" << endl;
            }
        }
        if (userans == answer[r])
        {
            cout << endl;
            setColor(2);
            cout << "Your Answer is Correct" << endl;
            setColor(7);
            highscore = highscore + 2;
            correctAnswers++;
            cout << highscore;
            system("pause");
            system("cls");
        }
        else
        {
            setColor(12);
            cout << " <<Your Answer is Incorrect.>>" << endl;
            setColor(2);
            cout << "correct answer is = " << answer[r] << endl;
            setColor(7);
            highscore = highscore - 2;
            wrongAnswers++;
            cout << endl;
            wrongIndex[wrongCount] = r;
            wrongType[wrongCount] = 4;
            wrongUserAns[wrongCount] = userans;
            wrongCorrectAns[wrongCount] = answer[r];
            wrongCount++;
            system("pause");
            system("cls");
        }

    }
}

void Computerquestionsmid(int& highscore)   //medium level questions
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
        int r = rand() % 10;
        int userans = 0;
        int allowed[5] = { 0, 1, 1, 1, 1 }; // index 1..4 = allowed (1) or removed (0)
        int extraSeconds = 0; // extra seconds added by lifeline
        setColor(11);
        cout << "--------------------------------------" << endl;
        setColor(14);
        cout << Questions[r] << endl;
        setColor(7);
        cout << "1. " << OptA[r] << endl;
        cout << "2. " << OptB[r] << endl;
        cout << "3. " << OptC[r] << endl;
        cout << "4. " << OptD[r] << endl;
        cout << endl;
        setColor(10);
        cout << "==> Do you want to use your lifelines (y/n) =  ";
        setColor(7);
        char user_choice;

        cin >> user_choice;
        if (user_choice == 'y')
        {
            system("cls");
            liflines_system();
            int choice;
            cout << " " << endl;
            cout << "Enter your choice = ";
            cin >> choice;
            system("cls");
            if (choice == 1 && lifeline_5050 == false)
            {
                lifeline_5050 = true;
                cout << " " << endl;
                cout << "Two option removed " << endl;
                int correct = answer[r];
                int remove = 0;
                for (int i = 1; i <= 4; i++)
                {
                    allowed[i] = 1; // ensure default
                }
                for (int i = 1; i <= 4; i++)
                {
                    if (i == correct)
                        continue;
                    if (remove < 2)
                    {
                        allowed[i] = 0;
                        remove++;
                    }
                }
                for (int i = 1; i <= 4; i++)
                {
                    if (allowed[i] == 1)
                        continue;

                }
                cout << Questions[r] << endl;
                for (int j = 1; j <= 4; j++)
                {
                    if (allowed[j] == 0)
                        continue;
                    if (j == 1)
                        cout << "1. " << OptA[r] << endl;
                    if (j == 2)
                        cout << "2. " << OptB[r] << endl;
                    if (j == 3)
                        cout << "3. " << OptC[r] << endl;
                    if (j == 4)
                        cout << "4. " << OptD[r] << endl;
                }
            }
            else if (choice == 2 && lifeline_skip == false)
            {
                lifeline_skip = true;
                cout << "The question is skipped successfully " << endl;
                return;
            }
            else if (choice == 3 && lifeline_replace_question == false)
            {
                lifeline_replace_question = true;
                r = rand() % 10;
                setColor(11);
                cout << "--------------------------------------" << endl;
                setColor(14);
                cout << Questions[r] << endl;
                setColor(7);
                cout << "1. " << OptA[r] << endl;
                cout << "2. " << OptB[r] << endl;
                cout << "3. " << OptC[r] << endl;
                cout << "4. " << OptD[r] << endl;
            }
            else if (choice == 4 && lifeline_extratime == false)
            {
                lifeline_extratime = true;
                extraSeconds += 10;
                cout << "You got 10 extra seconds " << endl;
                setColor(11);
                cout << "--------------------------------------" << endl;
                setColor(14);
                cout << Questions[r] << endl;
                setColor(7);
                cout << "1. " << OptA[r] << endl;
                cout << "2. " << OptB[r] << endl;
                cout << "3. " << OptC[r] << endl;
                cout << "4. " << OptD[r] << endl;
                cout << endl;
            }
            else if (choice == 5)
            {
                cout << " you selected not to choose any lifeline ";
                cout << endl;
                setColor(11);
                cout << "--------------------------------------" << endl;
                setColor(14);
                cout << Questions[r] << endl;
                setColor(7);
                cout << "1. " << OptA[r] << endl;
                cout << "2. " << OptB[r] << endl;
                cout << "3. " << OptC[r] << endl;
                cout << "4. " << OptD[r] << endl;
                cout << endl;
            }
            else
            {
                cout << "You already used this lifeline " << endl;
                setColor(11);
                cout << "--------------------------------------" << endl;
                setColor(14);
                cout << Questions[r] << endl;
                setColor(7);
                cout << "1. " << OptA[r] << endl;
                cout << "2. " << OptB[r] << endl;
                cout << "3. " << OptC[r] << endl;
                cout << "4. " << OptD[r] << endl;
                cout << endl;
            }
            cout << "Enter your Answer = " << endl;
        }
        else
        {
            cout << " " << endl;
            cout << " You choose not to use any lifeline " << endl;
        }
        int timeForThis = 10 + extraSeconds;
        userans = getTimedAnswer(1, 4, timeForThis);
        if (userans == -1)
        {
            cout << " << You failed to answer in time. >>" << endl;
        }
        else
        {
            if (allowed[userans] == 0)
            {
                cout << endl;
                cout << "That option was removed by 50/50 lifeline. Incorrect." << endl;
            }
            else
            {
                cout << endl;
                cout << "" << endl;
            }
        }
        if (userans == answer[r])
        {
            cout << endl;
            setColor(2);
            cout << "Your Answer is Correct" << endl;
            setColor(7);
            highscore = highscore + 3;
            correctAnswers++;
            cout << highscore;
            system("pause");
            system("cls");
        }
        else
        {
            setColor(12);
            cout << " <<Your Answer is Incorrect.>>" << endl;
            setColor(2);
            cout << "correct answer is = " << answer[r] << endl;
            setColor(7);
            highscore = highscore - 3;
            wrongAnswers++;
            cout << endl;
            wrongIndex[wrongCount] = r;
            wrongType[wrongCount] = 5;
            wrongUserAns[wrongCount] = userans;
            wrongCorrectAns[wrongCount] = answer[r];
            wrongCount++;
            system("pause");
            system("cls");
        }

    }
}

void Computerquestionshard(int& highscore)   //hard level questions
{
    srand(time(0));
    ifstream file("computershard.txt");
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
        int r = rand() % 10;
        int userans = 0;
        int allowed[5] = { 0, 1, 1, 1, 1 }; // index 1..4 = allowed (1) or removed (0)
        int extraSeconds = 0; // extra seconds added by lifeline
        setColor(11);
        cout << "--------------------------------------" << endl;
        setColor(14);
        cout << Questions[r] << endl;
        setColor(7);
        cout << "1. " << OptA[r] << endl;
        cout << "2. " << OptB[r] << endl;
        cout << "3. " << OptC[r] << endl;
        cout << "4. " << OptD[r] << endl;
        cout << endl;
        setColor(10);
        cout << "==> Do you want to use your lifelines (y/n) =  ";
        setColor(7);
        char user_choice;

        cin >> user_choice;
        if (user_choice == 'y')
        {
            system("cls");
            liflines_system();
            int choice;
            cout << " " << endl;
            cout << "Enter your choice = ";
            cin >> choice;
            system("cls");
            if (choice == 1 && lifeline_5050 == false)
            {
                lifeline_5050 = true;
                cout << " " << endl;
                cout << "Two option removed " << endl;
                int correct = answer[r];
                int remove = 0;
                for (int i = 1; i <= 4; i++)
                {
                    allowed[i] = 1; // ensure default
                }
                for (int i = 1; i <= 4; i++)
                {
                    if (i == correct)
                        continue;
                    if (remove < 2)
                    {
                        allowed[i] = 0;
                        remove++;
                    }
                }
                for (int i = 1; i <= 4; i++)
                {
                    if (allowed[i] == 1)
                        continue;

                }
                cout << Questions[r] << endl;
                for (int j = 1; j <= 4; j++)
                {
                    if (allowed[j] == 0)
                        continue;
                    if (j == 1)
                        cout << "1. " << OptA[r] << endl;
                    if (j == 2)
                        cout << "2. " << OptB[r] << endl;
                    if (j == 3)
                        cout << "3. " << OptC[r] << endl;
                    if (j == 4)
                        cout << "4. " << OptD[r] << endl;
                }
            }
            else if (choice == 2 && lifeline_skip == false)
            {
                lifeline_skip = true;
                cout << "The question is skipped successfully " << endl;
                return;
            }
            else if (choice == 3 && lifeline_replace_question == false)
            {
                lifeline_replace_question = true;
                r = rand() % 10;
                setColor(11);
                cout << "--------------------------------------" << endl;
                setColor(14);
                cout << Questions[r] << endl;
                setColor(7);
                cout << "1. " << OptA[r] << endl;
                cout << "2. " << OptB[r] << endl;
                cout << "3. " << OptC[r] << endl;
                cout << "4. " << OptD[r] << endl;
            }
            else if (choice == 4 && lifeline_extratime == false)
            {
                lifeline_extratime = true;
                extraSeconds += 10;
                cout << "You got 10 extra seconds " << endl;
                setColor(11);
                cout << "--------------------------------------" << endl;
                setColor(14);
                cout << Questions[r] << endl;
                setColor(7);
                cout << "1. " << OptA[r] << endl;
                cout << "2. " << OptB[r] << endl;
                cout << "3. " << OptC[r] << endl;
                cout << "4. " << OptD[r] << endl;
                cout << endl;
            }
            else if (choice == 5)
            {
                cout << " you selected not to choose any lifeline ";
                cout << endl;
                setColor(11);
                cout << "--------------------------------------" << endl;
                setColor(14);
                cout << Questions[r] << endl;
                setColor(7);
                cout << "1. " << OptA[r] << endl;
                cout << "2. " << OptB[r] << endl;
                cout << "3. " << OptC[r] << endl;
                cout << "4. " << OptD[r] << endl;
                cout << endl;
            }
            else
            {
                cout << "You already used this lifeline " << endl;
                setColor(11);
                cout << "--------------------------------------" << endl;
                setColor(14);
                cout << Questions[r] << endl;
                setColor(7);
                cout << "1. " << OptA[r] << endl;
                cout << "2. " << OptB[r] << endl;
                cout << "3. " << OptC[r] << endl;
                cout << "4. " << OptD[r] << endl;
                cout << endl;
            }
            cout << "Enter your Answer = " << endl;
        }
        else
        {
            cout << " " << endl;
            cout << " You choose not to use any lifeline " << endl;
        }
        int timeForThis = 10 + extraSeconds;
        userans = getTimedAnswer(1, 4, timeForThis);
        if (userans == -1)
        {
            cout << " << You failed to answer in time. >>" << endl;
        }
        else
        {
            if (allowed[userans] == 0)
            {
                cout << endl;
                cout << "That option was removed by 50/50 lifeline. Incorrect." << endl;
            }
            else
            {
                cout << endl;
                cout << "" << endl;
            }
        }
        if (userans == answer[r])
        {
            cout << endl;
            setColor(2);
            cout << "Your Answer is Correct" << endl;
            setColor(7);
            highscore = highscore + 5;
            correctAnswers++;
            cout << highscore;
            system("pause");
            system("cls");
        }
        else
        {
            setColor(12);
            cout << " <<Your Answer is Incorrect.>>" << endl;
            setColor(2);
            cout << "correct answer is = " << answer[r] << endl;
            setColor(7);
            highscore = highscore - 5;
            wrongAnswers++;
            cout << endl;
            wrongIndex[wrongCount] = r;
            wrongType[wrongCount] = 6;
            wrongUserAns[wrongCount] = userans;
            wrongCorrectAns[wrongCount] = answer[r];
            wrongCount++;
            system("pause");
            system("cls");
        }

    }
}





//questions for sports
void Sportsquestions(int& highscore)   //easy level questions
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
        int r = rand() % 10;
        int userans = 0;
        int allowed[5] = { 0, 1, 1, 1, 1 }; // index 1..4 = allowed (1) or removed (0)
        int extraSeconds = 0; // extra seconds added by lifeline
        setColor(11);
        cout << "--------------------------------------" << endl;
        setColor(14);
        cout << Questions[r] << endl;
        setColor(7);
        cout << "1. " << OptA[r] << endl;
        cout << "2. " << OptB[r] << endl;
        cout << "3. " << OptC[r] << endl;
        cout << "4. " << OptD[r] << endl;
        cout << endl;
        setColor(10);
        cout << "==> Do you want to use your lifelines (y/n) =  ";
        setColor(7);
        char user_choice;

        cin >> user_choice;
        if (user_choice == 'y')
        {
            system("cls");
            liflines_system();
            int choice;
            cout << " " << endl;
            cout << "Enter your choice = ";
            cin >> choice;
            system("cls");
            if (choice == 1 && lifeline_5050 == false)
            {
                lifeline_5050 = true;
                cout << " " << endl;
                cout << "Two option removed " << endl;
                int correct = answer[r];
                int remove = 0;
                for (int i = 1; i <= 4; i++)
                {
                    allowed[i] = 1; // ensure default
                }
                for (int i = 1; i <= 4; i++)
                {
                    if (i == correct)
                        continue;
                    if (remove < 2)
                    {
                        allowed[i] = 0;
                        remove++;
                    }
                }
                for (int i = 1; i <= 4; i++)
                {
                    if (allowed[i] == 1)
                        continue;

                }
                cout << Questions[r] << endl;
                for (int j = 1; j <= 4; j++)
                {
                    if (allowed[j] == 0)
                        continue;
                    if (j == 1)
                        cout << "1. " << OptA[r] << endl;
                    if (j == 2)
                        cout << "2. " << OptB[r] << endl;
                    if (j == 3)
                        cout << "3. " << OptC[r] << endl;
                    if (j == 4)
                        cout << "4. " << OptD[r] << endl;
                }
            }
            else if (choice == 2 && lifeline_skip == false)
            {
                lifeline_skip = true;
                cout << "The question is skipped successfully " << endl;
                return;
            }
            else if (choice == 3 && lifeline_replace_question == false)
            {
                lifeline_replace_question = true;
                r = rand() % 10;
                setColor(11);
                cout << "--------------------------------------" << endl;
                setColor(14);
                cout << Questions[r] << endl;
                setColor(7);
                cout << "1. " << OptA[r] << endl;
                cout << "2. " << OptB[r] << endl;
                cout << "3. " << OptC[r] << endl;
                cout << "4. " << OptD[r] << endl;
            }
            else if (choice == 4 && lifeline_extratime == false)
            {
                lifeline_extratime = true;
                extraSeconds += 10;
                cout << "You got 10 extra seconds " << endl;
                setColor(11);
                cout << "--------------------------------------" << endl;
                setColor(14);
                cout << Questions[r] << endl;
                setColor(7);
                cout << "1. " << OptA[r] << endl;
                cout << "2. " << OptB[r] << endl;
                cout << "3. " << OptC[r] << endl;
                cout << "4. " << OptD[r] << endl;
                cout << endl;
            }
            else if (choice == 5)
            {
                cout << " you selected not to choose any lifeline ";
                cout << endl;
                setColor(11);
                cout << "--------------------------------------" << endl;
                setColor(14);
                cout << Questions[r] << endl;
                setColor(7);
                cout << "1. " << OptA[r] << endl;
                cout << "2. " << OptB[r] << endl;
                cout << "3. " << OptC[r] << endl;
                cout << "4. " << OptD[r] << endl;
                cout << endl;
            }
            else
            {
                cout << "You already used this lifeline " << endl;
                setColor(11);
                cout << "--------------------------------------" << endl;
                setColor(14);
                cout << Questions[r] << endl;
                setColor(7);
                cout << "1. " << OptA[r] << endl;
                cout << "2. " << OptB[r] << endl;
                cout << "3. " << OptC[r] << endl;
                cout << "4. " << OptD[r] << endl;
                cout << endl;
            }
            cout << "Enter your Answer = " << endl;
        }
        else
        {
            cout << " " << endl;
            cout << " You choose not to use any lifeline " << endl;
        }
        int timeForThis = 10 + extraSeconds;
        userans = getTimedAnswer(1, 4, timeForThis);
        if (userans == -1)
        {
            cout << " << You failed to answer in time. >>" << endl;
        }
        else
        {
            if (allowed[userans] == 0)
            {
                cout << endl;
                cout << "That option was removed by 50/50 lifeline. Incorrect." << endl;
            }
            else
            {
                cout << endl;
                cout << "" << endl;
            }
        }
        if (userans == answer[r])
        {
            cout << endl;
            setColor(2);
            cout << "Your Answer is Correct" << endl;
            setColor(7);
            highscore = highscore + 2;
            correctAnswers++;
            cout << highscore;
            system("pause");
            system("cls");
        }
        else
        {
            setColor(12);
            cout << " <<Your Answer is Incorrect.>>" << endl;
            setColor(2);
            cout << "correct answer is = " << answer[r] << endl;
            setColor(7);
            highscore = highscore - 2;
            wrongAnswers++;
            cout << endl;
            wrongIndex[wrongCount] = r;
            wrongType[wrongCount] = 7;
            wrongUserAns[wrongCount] = userans;
            wrongCorrectAns[wrongCount] = answer[r];
            wrongCount++;
            system("pause");
            system("cls");
        }

    }
}

void Sportsquestionsmid(int& highscore)   //hard level questions
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
        int r = rand() % 10;
        int userans = 0;
        int allowed[5] = { 0, 1, 1, 1, 1 }; // index 1..4 = allowed (1) or removed (0)
        int extraSeconds = 0; // extra seconds added by lifeline
        setColor(11);
        cout << "--------------------------------------" << endl;
        setColor(14);
        cout << Questions[r] << endl;
        setColor(7);
        cout << "1. " << OptA[r] << endl;
        cout << "2. " << OptB[r] << endl;
        cout << "3. " << OptC[r] << endl;
        cout << "4. " << OptD[r] << endl;
        cout << endl;
        setColor(10);
        cout << "==> Do you want to use your lifelines (y/n) =  ";
        setColor(7);
        char user_choice;

        cin >> user_choice;
        if (user_choice == 'y')
        {
            system("cls");
            liflines_system();
            int choice;
            cout << " " << endl;
            cout << "Enter your choice = ";
            cin >> choice;
            system("cls");
            if (choice == 1 && lifeline_5050 == false)
            {
                lifeline_5050 = true;
                cout << " " << endl;
                cout << "Two option removed " << endl;
                int correct = answer[r];
                int remove = 0;
                for (int i = 1; i <= 4; i++)
                {
                    allowed[i] = 1; // ensure default
                }
                for (int i = 1; i <= 4; i++)
                {
                    if (i == correct)
                        continue;
                    if (remove < 2)
                    {
                        allowed[i] = 0;
                        remove++;
                    }
                }
                for (int i = 1; i <= 4; i++)
                {
                    if (allowed[i] == 1)
                        continue;

                }
                cout << Questions[r] << endl;
                for (int j = 1; j <= 4; j++)
                {
                    if (allowed[j] == 0)
                        continue;
                    if (j == 1)
                        cout << "1. " << OptA[r] << endl;
                    if (j == 2)
                        cout << "2. " << OptB[r] << endl;
                    if (j == 3)
                        cout << "3. " << OptC[r] << endl;
                    if (j == 4)
                        cout << "4. " << OptD[r] << endl;
                }
            }
            else if (choice == 2 && lifeline_skip == false)
            {
                lifeline_skip = true;
                cout << "The question is skipped successfully " << endl;
                return;
            }
            else if (choice == 3 && lifeline_replace_question == false)
            {
                lifeline_replace_question = true;
                r = rand() % 10;
                setColor(11);
                cout << "--------------------------------------" << endl;
                setColor(14);
                cout << Questions[r] << endl;
                setColor(7);
                cout << "1. " << OptA[r] << endl;
                cout << "2. " << OptB[r] << endl;
                cout << "3. " << OptC[r] << endl;
                cout << "4. " << OptD[r] << endl;
            }
            else if (choice == 4 && lifeline_extratime == false)
            {
                lifeline_extratime = true;
                extraSeconds += 10;
                cout << "You got 10 extra seconds " << endl;
                setColor(11);
                cout << "--------------------------------------" << endl;
                setColor(14);
                cout << Questions[r] << endl;
                setColor(7);
                cout << "1. " << OptA[r] << endl;
                cout << "2. " << OptB[r] << endl;
                cout << "3. " << OptC[r] << endl;
                cout << "4. " << OptD[r] << endl;
                cout << endl;
            }
            else if (choice == 5)
            {
                cout << " you selected not to choose any lifeline ";
                cout << endl;
                setColor(11);
                cout << "--------------------------------------" << endl;
                setColor(14);
                cout << Questions[r] << endl;
                setColor(7);
                cout << "1. " << OptA[r] << endl;
                cout << "2. " << OptB[r] << endl;
                cout << "3. " << OptC[r] << endl;
                cout << "4. " << OptD[r] << endl;
                cout << endl;
            }
            else
            {
                cout << "You already used this lifeline " << endl;
                setColor(11);
                cout << "--------------------------------------" << endl;
                setColor(14);
                cout << Questions[r] << endl;
                setColor(7);
                cout << "1. " << OptA[r] << endl;
                cout << "2. " << OptB[r] << endl;
                cout << "3. " << OptC[r] << endl;
                cout << "4. " << OptD[r] << endl;
                cout << endl;
            }
            cout << "Enter your Answer = " << endl;
        }
        else
        {
            cout << " " << endl;
            cout << " You choose not to use any lifeline " << endl;
        }
        int timeForThis = 10 + extraSeconds;
        userans = getTimedAnswer(1, 4, timeForThis);
        if (userans == -1)
        {
            cout << " << You failed to answer in time. >>" << endl;
        }
        else
        {
            if (allowed[userans] == 0)
            {
                cout << endl;
                cout << "That option was removed by 50/50 lifeline. Incorrect." << endl;
            }
            else
            {
                cout << endl;
                cout << "" << endl;
            }
        }
        if (userans == answer[r])
        {
            cout << endl;
            setColor(2);
            cout << "Your Answer is Correct" << endl;
            setColor(7);
            highscore = highscore + 3;
            correctAnswers++;
            cout << highscore;
            system("pause");
            system("cls");
        }
        else
        {
            setColor(12);
            cout << " <<Your Answer is Incorrect.>>" << endl;
            setColor(2);
            cout << "correct answer is = " << answer[r] << endl;
            setColor(7);
            highscore = highscore - 3;
            wrongAnswers++;
            cout << endl;
            wrongIndex[wrongCount] = r;
            wrongType[wrongCount] = 8;
            wrongUserAns[wrongCount] = userans;
            wrongCorrectAns[wrongCount] = answer[r];
            wrongCount++;
            system("pause");
            system("cls");
        }

    }
}

void Sportsquestionshard(int& highscore)   //hard level questions
{
    srand(time(0));
    ifstream file("sportshard.txt");
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
        int r = rand() % 10;
        int userans = 0;
        int allowed[5] = { 0, 1, 1, 1, 1 }; // index 1..4 = allowed (1) or removed (0)
        int extraSeconds = 0; // extra seconds added by lifeline
        setColor(11);
        cout << "--------------------------------------" << endl;
        setColor(14);
        cout << Questions[r] << endl;
        setColor(7);
        cout << "1. " << OptA[r] << endl;
        cout << "2. " << OptB[r] << endl;
        cout << "3. " << OptC[r] << endl;
        cout << "4. " << OptD[r] << endl;
        cout << endl;
        setColor(10);
        cout << "==> Do you want to use your lifelines (y/n) =  ";
        setColor(7);
        char user_choice;

        cin >> user_choice;
        if (user_choice == 'y')
        {
            system("cls");
            liflines_system();
            int choice;
            cout << " " << endl;
            cout << "Enter your choice = ";
            cin >> choice;
            system("cls");
            if (choice == 1 && lifeline_5050 == false)
            {
                lifeline_5050 = true;
                cout << " " << endl;
                cout << "Two option removed " << endl;
                int correct = answer[r];
                int remove = 0;
                for (int i = 1; i <= 4; i++)
                {
                    allowed[i] = 1; // ensure default
                }
                for (int i = 1; i <= 4; i++)
                {
                    if (i == correct)
                        continue;
                    if (remove < 2)
                    {
                        allowed[i] = 0;
                        remove++;
                    }
                }
                for (int i = 1; i <= 4; i++)
                {
                    if (allowed[i] == 1)
                        continue;

                }
                cout << Questions[r] << endl;
                for (int j = 1; j <= 4; j++)
                {
                    if (allowed[j] == 0)
                        continue;
                    if (j == 1)
                        cout << "1. " << OptA[r] << endl;
                    if (j == 2)
                        cout << "2. " << OptB[r] << endl;
                    if (j == 3)
                        cout << "3. " << OptC[r] << endl;
                    if (j == 4)
                        cout << "4. " << OptD[r] << endl;
                }
            }
            else if (choice == 2 && lifeline_skip == false)
            {
                lifeline_skip = true;
                cout << "The question is skipped successfully " << endl;
                return;
            }
            else if (choice == 3 && lifeline_replace_question == false)
            {
                lifeline_replace_question = true;
                r = rand() % 10;
                setColor(11);
                cout << "--------------------------------------" << endl;
                setColor(14);
                cout << Questions[r] << endl;
                setColor(7);
                cout << "1. " << OptA[r] << endl;
                cout << "2. " << OptB[r] << endl;
                cout << "3. " << OptC[r] << endl;
                cout << "4. " << OptD[r] << endl;
            }
            else if (choice == 4 && lifeline_extratime == false)
            {
                lifeline_extratime = true;
                extraSeconds += 10;
                cout << "You got 10 extra seconds " << endl;
                setColor(11);
                cout << "--------------------------------------" << endl;
                setColor(14);
                cout << Questions[r] << endl;
                setColor(7);
                cout << "1. " << OptA[r] << endl;
                cout << "2. " << OptB[r] << endl;
                cout << "3. " << OptC[r] << endl;
                cout << "4. " << OptD[r] << endl;
                cout << endl;
            }
            else if (choice == 5)
            {
                cout << " you selected not to choose any lifeline ";
                cout << endl;
                setColor(11);
                cout << "--------------------------------------" << endl;
                setColor(14);
                cout << Questions[r] << endl;
                setColor(7);
                cout << "1. " << OptA[r] << endl;
                cout << "2. " << OptB[r] << endl;
                cout << "3. " << OptC[r] << endl;
                cout << "4. " << OptD[r] << endl;
                cout << endl;
            }
            else
            {
                cout << "You already used this lifeline " << endl;
                setColor(11);
                cout << "--------------------------------------" << endl;
                setColor(14);
                cout << Questions[r] << endl;
                setColor(7);
                cout << "1. " << OptA[r] << endl;
                cout << "2. " << OptB[r] << endl;
                cout << "3. " << OptC[r] << endl;
                cout << "4. " << OptD[r] << endl;
                cout << endl;
            }
            cout << "Enter your Answer = " << endl;
        }
        else
        {
            cout << " " << endl;
            cout << " You choose not to use any lifeline " << endl;
        }
        int timeForThis = 10 + extraSeconds;
        userans = getTimedAnswer(1, 4, timeForThis);
        if (userans == -1)
        {
            cout << " << You failed to answer in time. >>" << endl;
        }
        else
        {
            if (allowed[userans] == 0)
            {
                cout << endl;
                cout << "That option was removed by 50/50 lifeline. Incorrect." << endl;
            }
            else
            {
                cout << endl;
                cout << "" << endl;
            }
        }
        if (userans == answer[r])
        {
            cout << endl;
            setColor(2);
            cout << "Your Answer is Correct" << endl;
            setColor(7);
            highscore = highscore + 5;
            correctAnswers++;
            cout << highscore;
            system("pause");
            system("cls");
        }
        else
        {
            setColor(12);
            cout << " <<Your Answer is Incorrect.>>" << endl;
            setColor(2);
            cout << "correct answer is = " << answer[r] << endl;
            setColor(7);
            highscore = highscore - 5;
            wrongAnswers++;
            cout << endl;
            wrongIndex[wrongCount] = r;
            wrongType[wrongCount] = 9;
            wrongUserAns[wrongCount] = userans;
            wrongCorrectAns[wrongCount] = answer[r];
            wrongCount++;
            system("pause");
            system("cls");
        }

    }
}





//questions for History
void Historyquestions(int& highscore)   //easy level questions
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
        int r = rand() % 10;
        int userans = 0;
        int allowed[5] = { 0, 1, 1, 1, 1 }; // index 1..4 = allowed (1) or removed (0)
        int extraSeconds = 0; // extra seconds added by lifeline
        setColor(11);
        cout << "--------------------------------------" << endl;
        setColor(14);
        cout << Questions[r] << endl;
        setColor(7);
        cout << "1. " << OptA[r] << endl;
        cout << "2. " << OptB[r] << endl;
        cout << "3. " << OptC[r] << endl;
        cout << "4. " << OptD[r] << endl;
        cout << endl;
        setColor(10);
        cout << "==> Do you want to use your lifelines (y/n) =  ";
        setColor(7);
        char user_choice;

        cin >> user_choice;
        if (user_choice == 'y')
        {
            system("cls");
            liflines_system();
            int choice;
            cout << " " << endl;
            cout << "Enter your choice = ";
            cin >> choice;
            system("cls");
            if (choice == 1 && lifeline_5050 == false)
            {
                lifeline_5050 = true;
                cout << " " << endl;
                cout << "Two option removed " << endl;
                int correct = answer[r];
                int remove = 0;
                for (int i = 1; i <= 4; i++)
                {
                    allowed[i] = 1; // ensure default
                }
                for (int i = 1; i <= 4; i++)
                {
                    if (i == correct)
                        continue;
                    if (remove < 2)
                    {
                        allowed[i] = 0;
                        remove++;
                    }
                }
                for (int i = 1; i <= 4; i++)
                {
                    if (allowed[i] == 1)
                        continue;

                }
                cout << Questions[r] << endl;
                for (int j = 1; j <= 4; j++)
                {
                    if (allowed[j] == 0)
                        continue;
                    if (j == 1)
                        cout << "1. " << OptA[r] << endl;
                    if (j == 2)
                        cout << "2. " << OptB[r] << endl;
                    if (j == 3)
                        cout << "3. " << OptC[r] << endl;
                    if (j == 4)
                        cout << "4. " << OptD[r] << endl;
                }
            }
            else if (choice == 2 && lifeline_skip == false)
            {
                lifeline_skip = true;
                cout << "The question is skipped successfully " << endl;
                return;
            }
            else if (choice == 3 && lifeline_replace_question == false)
            {
                lifeline_replace_question = true;
                r = rand() % 10;
                setColor(11);
                cout << "--------------------------------------" << endl;
                setColor(14);
                cout << Questions[r] << endl;
                setColor(7);
                cout << "1. " << OptA[r] << endl;
                cout << "2. " << OptB[r] << endl;
                cout << "3. " << OptC[r] << endl;
                cout << "4. " << OptD[r] << endl;
            }
            else if (choice == 4 && lifeline_extratime == false)
            {
                lifeline_extratime = true;
                extraSeconds += 10;
                cout << "You got 10 extra seconds " << endl;
                setColor(11);
                cout << "--------------------------------------" << endl;
                setColor(14);
                cout << Questions[r] << endl;
                setColor(7);
                cout << "1. " << OptA[r] << endl;
                cout << "2. " << OptB[r] << endl;
                cout << "3. " << OptC[r] << endl;
                cout << "4. " << OptD[r] << endl;
                cout << endl;
            }
            else if (choice == 5)
            {
                cout << " you selected not to choose any lifeline ";
                cout << endl;
                setColor(11);
                cout << "--------------------------------------" << endl;
                setColor(14);
                cout << Questions[r] << endl;
                setColor(7);
                cout << "1. " << OptA[r] << endl;
                cout << "2. " << OptB[r] << endl;
                cout << "3. " << OptC[r] << endl;
                cout << "4. " << OptD[r] << endl;
                cout << endl;
            }
            else
            {
                cout << "You already used this lifeline " << endl;
                setColor(11);
                cout << "--------------------------------------" << endl;
                setColor(14);
                cout << Questions[r] << endl;
                setColor(7);
                cout << "1. " << OptA[r] << endl;
                cout << "2. " << OptB[r] << endl;
                cout << "3. " << OptC[r] << endl;
                cout << "4. " << OptD[r] << endl;
                cout << endl;
            }
            cout << "Enter your Answer = " << endl;
        }
        else
        {
            cout << " " << endl;
            cout << " You choose not to use any lifeline " << endl;
        }
        int timeForThis = 10 + extraSeconds;
        userans = getTimedAnswer(1, 4, timeForThis);
        if (userans == -1)
        {
            cout << " << You failed to answer in time. >>" << endl;
        }
        else
        {
            if (allowed[userans] == 0)
            {
                cout << endl;
                cout << "That option was removed by 50/50 lifeline. Incorrect." << endl;
            }
            else
            {
                cout << endl;
                cout << "" << endl;
            }
        }
        if (userans == answer[r])
        {
            cout << endl;
            setColor(2);
            cout << "Your Answer is Correct" << endl;
            setColor(7);
            highscore = highscore + 2;
            correctAnswers++;
            cout << highscore;
            system("pause");
            system("cls");
        }
        else
        {
            setColor(12);
            cout << " <<Your Answer is Incorrect.>>" << endl;
            setColor(2);
            cout << "correct answer is = " << answer[r] << endl;
            setColor(7);
            highscore = highscore - 2;
            wrongAnswers++;
            cout << endl;
            wrongIndex[wrongCount] = r;
            wrongType[wrongCount] = 10;
            wrongUserAns[wrongCount] = userans;
            wrongCorrectAns[wrongCount] = answer[r];
            wrongCount++;
            system("pause");
            system("cls");
        }

    }
}

void Historyquestionsmid(int& highscore)   ///meduim level questions
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
        int r = rand() % 10;
        int userans = 0;
        int allowed[5] = { 0, 1, 1, 1, 1 }; // index 1..4 = allowed (1) or removed (0)
        int extraSeconds = 0; // extra seconds added by lifeline
        setColor(11);
        cout << "--------------------------------------" << endl;
        setColor(14);
        cout << Questions[r] << endl;
        setColor(7);
        cout << "1. " << OptA[r] << endl;
        cout << "2. " << OptB[r] << endl;
        cout << "3. " << OptC[r] << endl;
        cout << "4. " << OptD[r] << endl;
        cout << endl;
        setColor(10);
        cout << "==> Do you want to use your lifelines (y/n) =  ";
        setColor(7);
        char user_choice;

        cin >> user_choice;
        if (user_choice == 'y')
        {
            system("cls");
            liflines_system();
            int choice;
            cout << " " << endl;
            cout << "Enter your choice = ";
            cin >> choice;
            system("cls");
            if (choice == 1 && lifeline_5050 == false)
            {
                lifeline_5050 = true;
                cout << " " << endl;
                cout << "Two option removed " << endl;
                int correct = answer[r];
                int remove = 0;
                for (int i = 1; i <= 4; i++)
                {
                    allowed[i] = 1; // ensure default
                }
                for (int i = 1; i <= 4; i++)
                {
                    if (i == correct)
                        continue;
                    if (remove < 2)
                    {
                        allowed[i] = 0;
                        remove++;
                    }
                }
                for (int i = 1; i <= 4; i++)
                {
                    if (allowed[i] == 1)
                        continue;

                }
                cout << Questions[r] << endl;
                for (int j = 1; j <= 4; j++)
                {
                    if (allowed[j] == 0)
                        continue;
                    if (j == 1)
                        cout << "1. " << OptA[r] << endl;
                    if (j == 2)
                        cout << "2. " << OptB[r] << endl;
                    if (j == 3)
                        cout << "3. " << OptC[r] << endl;
                    if (j == 4)
                        cout << "4. " << OptD[r] << endl;
                }
            }
            else if (choice == 2 && lifeline_skip == false)
            {
                lifeline_skip = true;
                cout << "The question is skipped successfully " << endl;
                return;
            }
            else if (choice == 3 && lifeline_replace_question == false)
            {
                lifeline_replace_question = true;
                r = rand() % 10;
                setColor(11);
                cout << "--------------------------------------" << endl;
                setColor(14);
                cout << Questions[r] << endl;
                setColor(7);
                cout << "1. " << OptA[r] << endl;
                cout << "2. " << OptB[r] << endl;
                cout << "3. " << OptC[r] << endl;
                cout << "4. " << OptD[r] << endl;
            }
            else if (choice == 4 && lifeline_extratime == false)
            {
                lifeline_extratime = true;
                extraSeconds += 10;
                cout << "You got 10 extra seconds " << endl;
                setColor(11);
                cout << "--------------------------------------" << endl;
                setColor(14);
                cout << Questions[r] << endl;
                setColor(7);
                cout << "1. " << OptA[r] << endl;
                cout << "2. " << OptB[r] << endl;
                cout << "3. " << OptC[r] << endl;
                cout << "4. " << OptD[r] << endl;
                cout << endl;
            }
            else if (choice == 5)
            {
                cout << " you selected not to choose any lifeline ";
                cout << endl;
                setColor(11);
                cout << "--------------------------------------" << endl;
                setColor(14);
                cout << Questions[r] << endl;
                setColor(7);
                cout << "1. " << OptA[r] << endl;
                cout << "2. " << OptB[r] << endl;
                cout << "3. " << OptC[r] << endl;
                cout << "4. " << OptD[r] << endl;
                cout << endl;
            }
            else
            {
                cout << "You already used this lifeline " << endl;
                setColor(11);
                cout << "--------------------------------------" << endl;
                setColor(14);
                cout << Questions[r] << endl;
                setColor(7);
                cout << "1. " << OptA[r] << endl;
                cout << "2. " << OptB[r] << endl;
                cout << "3. " << OptC[r] << endl;
                cout << "4. " << OptD[r] << endl;
                cout << endl;
            }
            cout << "Enter your Answer = " << endl;
        }
        else
        {
            cout << " " << endl;
            cout << " You choose not to use any lifeline " << endl;
        }
        int timeForThis = 10 + extraSeconds;
        userans = getTimedAnswer(1, 4, timeForThis);
        if (userans == -1)
        {
            cout << " << You failed to answer in time. >>" << endl;
        }
        else
        {
            if (allowed[userans] == 0)
            {
                cout << endl;
                cout << "That option was removed by 50/50 lifeline. Incorrect." << endl;
            }
            else
            {
                cout << endl;
                cout << "" << endl;
            }
        }
        if (userans == answer[r])
        {
            cout << endl;
            setColor(2);
            cout << "Your Answer is Correct" << endl;
            setColor(7);
            highscore = highscore + 3;
            correctAnswers++;
            cout << highscore;
            system("pause");
            system("cls");
        }
        else
        {
            setColor(12);
            cout << " <<Your Answer is Incorrect.>>" << endl;
            setColor(2);
            cout << "correct answer is = " << answer[r] << endl;
            setColor(7);
            highscore = highscore - 3;
            wrongAnswers++;
            cout << endl;
            wrongIndex[wrongCount] = r;
            wrongType[wrongCount] = 11;
            wrongUserAns[wrongCount] = userans;
            wrongCorrectAns[wrongCount] = answer[r];
            wrongCount++;
            system("pause");
            system("cls");
        }

    }
}

void Historyquestionshard(int& highscore)   //hard level questions
{
    srand(time(0));
    ifstream file("historyhard.txt");
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
        int r = rand() % 10;
        int userans = 0;
        int allowed[5] = { 0, 1, 1, 1, 1 }; // index 1..4 = allowed (1) or removed (0)
        int extraSeconds = 0; // extra seconds added by lifeline
        setColor(11);
        cout << "--------------------------------------" << endl;
        setColor(14);
        cout << Questions[r] << endl;
        setColor(7);
        cout << "1. " << OptA[r] << endl;
        cout << "2. " << OptB[r] << endl;
        cout << "3. " << OptC[r] << endl;
        cout << "4. " << OptD[r] << endl;
        cout << endl;
        setColor(10);
        cout << "==> Do you want to use your lifelines (y/n) =  ";
        setColor(7);
        char user_choice;

        cin >> user_choice;
        if (user_choice == 'y')
        {
            system("cls");
            liflines_system();
            int choice;
            cout << " " << endl;
            cout << "Enter your choice = ";
            cin >> choice;
            system("cls");
            if (choice == 1 && lifeline_5050 == false)
            {
                lifeline_5050 = true;
                cout << " " << endl;
                cout << "Two option removed " << endl;
                int correct = answer[r];
                int remove = 0;
                for (int i = 1; i <= 4; i++)
                {
                    allowed[i] = 1; // ensure default
                }
                for (int i = 1; i <= 4; i++)
                {
                    if (i == correct)
                        continue;
                    if (remove < 2)
                    {
                        allowed[i] = 0;
                        remove++;
                    }
                }
                for (int i = 1; i <= 4; i++)
                {
                    if (allowed[i] == 1)
                        continue;

                }
                cout << Questions[r] << endl;
                for (int j = 1; j <= 4; j++)
                {
                    if (allowed[j] == 0)
                        continue;
                    if (j == 1)
                        cout << "1. " << OptA[r] << endl;
                    if (j == 2)
                        cout << "2. " << OptB[r] << endl;
                    if (j == 3)
                        cout << "3. " << OptC[r] << endl;
                    if (j == 4)
                        cout << "4. " << OptD[r] << endl;
                }
            }
            else if (choice == 2 && lifeline_skip == false)
            {
                lifeline_skip = true;
                cout << "The question is skipped successfully " << endl;
                return;
            }
            else if (choice == 3 && lifeline_replace_question == false)
            {
                lifeline_replace_question = true;
                r = rand() % 10;
                setColor(11);
                cout << "--------------------------------------" << endl;
                setColor(14);
                cout << Questions[r] << endl;
                setColor(7);
                cout << "1. " << OptA[r] << endl;
                cout << "2. " << OptB[r] << endl;
                cout << "3. " << OptC[r] << endl;
                cout << "4. " << OptD[r] << endl;
            }
            else if (choice == 4 && lifeline_extratime == false)
            {
                lifeline_extratime = true;
                extraSeconds += 10;
                cout << "You got 10 extra seconds " << endl;
                setColor(11);
                cout << "--------------------------------------" << endl;
                setColor(14);
                cout << Questions[r] << endl;
                setColor(7);
                cout << "1. " << OptA[r] << endl;
                cout << "2. " << OptB[r] << endl;
                cout << "3. " << OptC[r] << endl;
                cout << "4. " << OptD[r] << endl;
                cout << endl;
            }
            else if (choice == 5)
            {
                cout << " you selected not to choose any lifeline ";
                cout << endl;
                setColor(11);
                cout << "--------------------------------------" << endl;
                setColor(14);
                cout << Questions[r] << endl;
                setColor(7);
                cout << "1. " << OptA[r] << endl;
                cout << "2. " << OptB[r] << endl;
                cout << "3. " << OptC[r] << endl;
                cout << "4. " << OptD[r] << endl;
                cout << endl;
            }
            else
            {
                cout << "You already used this lifeline " << endl;
                setColor(11);
                cout << "--------------------------------------" << endl;
                setColor(14);
                cout << Questions[r] << endl;
                setColor(7);
                cout << "1. " << OptA[r] << endl;
                cout << "2. " << OptB[r] << endl;
                cout << "3. " << OptC[r] << endl;
                cout << "4. " << OptD[r] << endl;
                cout << endl;
            }
            cout << "Enter your Answer = " << endl;
        }
        else
        {
            cout << " " << endl;
            cout << " You choose not to use any lifeline " << endl;
        }
        int timeForThis = 10 + extraSeconds;
        userans = getTimedAnswer(1, 4, timeForThis);
        if (userans == -1)
        {
            cout << " << You failed to answer in time. >>" << endl;
        }
        else
        {
            if (allowed[userans] == 0)
            {
                cout << endl;
                cout << "That option was removed by 50/50 lifeline. Incorrect." << endl;
            }
            else
            {
                cout << endl;
                cout << "" << endl;
            }
        }
        if (userans == answer[r])
        {
            cout << endl;
            setColor(2);
            cout << "Your Answer is Correct" << endl;
            setColor(7);
            highscore = highscore + 5;
            correctAnswers++;
            cout << highscore;
            system("pause");
            system("cls");
        }
        else
        {
            setColor(12);
            cout << " <<Your Answer is Incorrect.>>" << endl;
            setColor(2);
            cout << "correct answer is = " << answer[r] << endl;
            setColor(7);
            highscore = highscore - 5;
            wrongAnswers++;
            cout << endl;
            wrongIndex[wrongCount] = r;
            wrongType[wrongCount] = 12;
            wrongUserAns[wrongCount] = userans;
            wrongCorrectAns[wrongCount] = answer[r];
            wrongCount++;
            system("pause");
            system("cls");
        }

    }
}





//questions for logic and iq
void Logicquestions(int& highscore)   //easy level questions
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
        int r = rand() % 10;
        int userans = 0;
        int allowed[5] = { 0, 1, 1, 1, 1 }; // index 1..4 = allowed (1) or removed (0)
        int extraSeconds = 0; // extra seconds added by lifeline
        setColor(11);
        cout << "--------------------------------------" << endl;
        setColor(14);
        cout << Questions[r] << endl;
        setColor(7);
        cout << "1. " << OptA[r] << endl;
        cout << "2. " << OptB[r] << endl;
        cout << "3. " << OptC[r] << endl;
        cout << "4. " << OptD[r] << endl;
        cout << endl;
        setColor(10);
        cout << "==> Do you want to use your lifelines (y/n) =  ";
        setColor(7);
        char user_choice;

        cin >> user_choice;
        if (user_choice == 'y')
        {
            system("cls");
            liflines_system();
            int choice;
            cout << " " << endl;
            cout << "Enter your choice = ";
            cin >> choice;
            system("cls");
            if (choice == 1 && lifeline_5050 == false)
            {
                lifeline_5050 = true;
                cout << " " << endl;
                cout << "Two option removed " << endl;
                int correct = answer[r];
                int remove = 0;
                for (int i = 1; i <= 4; i++)
                {
                    allowed[i] = 1; // ensure default
                }
                for (int i = 1; i <= 4; i++)
                {
                    if (i == correct)
                        continue;
                    if (remove < 2)
                    {
                        allowed[i] = 0;
                        remove++;
                    }
                }
                for (int i = 1; i <= 4; i++)
                {
                    if (allowed[i] == 1)
                        continue;

                }
                cout << Questions[r] << endl;
                for (int j = 1; j <= 4; j++)
                {
                    if (allowed[j] == 0)
                        continue;
                    if (j == 1)
                        cout << "1. " << OptA[r] << endl;
                    if (j == 2)
                        cout << "2. " << OptB[r] << endl;
                    if (j == 3)
                        cout << "3. " << OptC[r] << endl;
                    if (j == 4)
                        cout << "4. " << OptD[r] << endl;
                }
            }
            else if (choice == 2 && lifeline_skip == false)
            {
                lifeline_skip = true;
                cout << "The question is skipped successfully " << endl;
                return;
            }
            else if (choice == 3 && lifeline_replace_question == false)
            {
                lifeline_replace_question = true;
                r = rand() % 10;
                setColor(11);
                cout << "--------------------------------------" << endl;
                setColor(14);
                cout << Questions[r] << endl;
                setColor(7);
                cout << "1. " << OptA[r] << endl;
                cout << "2. " << OptB[r] << endl;
                cout << "3. " << OptC[r] << endl;
                cout << "4. " << OptD[r] << endl;
            }
            else if (choice == 4 && lifeline_extratime == false)
            {
                lifeline_extratime = true;
                extraSeconds += 10;
                cout << "You got 10 extra seconds " << endl;
                setColor(11);
                cout << "--------------------------------------" << endl;
                setColor(14);
                cout << Questions[r] << endl;
                setColor(7);
                cout << "1. " << OptA[r] << endl;
                cout << "2. " << OptB[r] << endl;
                cout << "3. " << OptC[r] << endl;
                cout << "4. " << OptD[r] << endl;
                cout << endl;
            }
            else if (choice == 5)
            {
                cout << " you selected not to choose any lifeline ";
                cout << endl;
                setColor(11);
                cout << "--------------------------------------" << endl;
                setColor(14);
                cout << Questions[r] << endl;
                setColor(7);
                cout << "1. " << OptA[r] << endl;
                cout << "2. " << OptB[r] << endl;
                cout << "3. " << OptC[r] << endl;
                cout << "4. " << OptD[r] << endl;
                cout << endl;
            }
            else
            {
                cout << "You already used this lifeline " << endl;
                setColor(11);
                cout << "--------------------------------------" << endl;
                setColor(14);
                cout << Questions[r] << endl;
                setColor(7);
                cout << "1. " << OptA[r] << endl;
                cout << "2. " << OptB[r] << endl;
                cout << "3. " << OptC[r] << endl;
                cout << "4. " << OptD[r] << endl;
                cout << endl;
            }
            cout << "Enter your Answer = " << endl;
        }
        else
        {
            cout << " " << endl;
            cout << " You choose not to use any lifeline " << endl;
        }
        int timeForThis = 10 + extraSeconds;
        userans = getTimedAnswer(1, 4, timeForThis);
        if (userans == -1)
        {
            cout << " << You failed to answer in time. >>" << endl;
        }
        else
        {
            if (allowed[userans] == 0)
            {
                cout << endl;
                cout << "That option was removed by 50/50 lifeline. Incorrect." << endl;
            }
            else
            {
                cout << endl;
                cout << "" << endl;
            }
        }
        if (userans == answer[r])
        {
            cout << endl;
            setColor(2);
            cout << "Your Answer is Correct" << endl;
            setColor(7);
            highscore = highscore + 2;
            correctAnswers++;
            cout << highscore;
            system("pause");
            system("cls");
        }
        else
        {
            setColor(12);
            cout << " <<Your Answer is Incorrect.>>" << endl;
            setColor(2);
            cout << "correct answer is = " << answer[r] << endl;
            setColor(7);
            highscore = highscore - 2;
            wrongAnswers++;
            cout << endl;
            wrongIndex[wrongCount] = r;
            wrongType[wrongCount] = 13;
            wrongUserAns[wrongCount] = userans;
            wrongCorrectAns[wrongCount] = answer[r];
            wrongCount++;
            system("pause");
            system("cls");
        }

    }
}

void Logicquestionsmid(int& highscore)   //meduim level questions
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
        int r = rand() % 10;
        int userans = 0;
        int allowed[5] = { 0, 1, 1, 1, 1 }; // index 1..4 = allowed (1) or removed (0)
        int extraSeconds = 0; // extra seconds added by lifeline
        setColor(11);
        cout << "--------------------------------------" << endl;
        setColor(14);
        cout << Questions[r] << endl;
        setColor(7);
        cout << "1. " << OptA[r] << endl;
        cout << "2. " << OptB[r] << endl;
        cout << "3. " << OptC[r] << endl;
        cout << "4. " << OptD[r] << endl;
        cout << endl;
        setColor(10);
        cout << "==> Do you want to use your lifelines (y/n) =  ";
        setColor(7);
        char user_choice;

        cin >> user_choice;
        if (user_choice == 'y')
        {
            system("cls");
            liflines_system();
            int choice;
            cout << " " << endl;
            cout << "Enter your choice = ";
            cin >> choice;
            system("cls");
            if (choice == 1 && lifeline_5050 == false)
            {
                lifeline_5050 = true;
                cout << " " << endl;
                cout << "Two option removed " << endl;
                int correct = answer[r];
                int remove = 0;
                for (int i = 1; i <= 4; i++)
                {
                    allowed[i] = 1; // ensure default
                }
                for (int i = 1; i <= 4; i++)
                {
                    if (i == correct)
                        continue;
                    if (remove < 2)
                    {
                        allowed[i] = 0;
                        remove++;
                    }
                }
                for (int i = 1; i <= 4; i++)
                {
                    if (allowed[i] == 1)
                        continue;

                }
                cout << Questions[r] << endl;
                for (int j = 1; j <= 4; j++)
                {
                    if (allowed[j] == 0)
                        continue;
                    if (j == 1)
                        cout << "1. " << OptA[r] << endl;
                    if (j == 2)
                        cout << "2. " << OptB[r] << endl;
                    if (j == 3)
                        cout << "3. " << OptC[r] << endl;
                    if (j == 4)
                        cout << "4. " << OptD[r] << endl;
                }
            }
            else if (choice == 2 && lifeline_skip == false)
            {
                lifeline_skip = true;
                cout << "The question is skipped successfully " << endl;
                return;
            }
            else if (choice == 3 && lifeline_replace_question == false)
            {
                lifeline_replace_question = true;
                r = rand() % 10;
                setColor(11);
                cout << "--------------------------------------" << endl;
                setColor(14);
                cout << Questions[r] << endl;
                setColor(7);
                cout << "1. " << OptA[r] << endl;
                cout << "2. " << OptB[r] << endl;
                cout << "3. " << OptC[r] << endl;
                cout << "4. " << OptD[r] << endl;
            }
            else if (choice == 4 && lifeline_extratime == false)
            {
                lifeline_extratime = true;
                extraSeconds += 10;
                cout << "You got 10 extra seconds " << endl;
                cout << "--------------------------------------" << endl;
                cout << Questions[r] << endl;
                cout << "1. " << OptA[r] << endl;
                cout << "2. " << OptB[r] << endl;
                cout << "3. " << OptC[r] << endl;
                cout << "4. " << OptD[r] << endl;
                cout << endl;
            }
            else if (choice == 5)
            {
                cout << " you selected not to choose any lifeline ";
                cout << endl;
                setColor(11);
                cout << "--------------------------------------" << endl;
                setColor(14);
                cout << Questions[r] << endl;
                setColor(7);
                cout << "1. " << OptA[r] << endl;
                cout << "2. " << OptB[r] << endl;
                cout << "3. " << OptC[r] << endl;
                cout << "4. " << OptD[r] << endl;
                cout << endl;
            }
            else
            {
                cout << "You already used this lifeline " << endl;
                setColor(11);
                cout << "--------------------------------------" << endl;
                setColor(14);
                cout << Questions[r] << endl;
                setColor(7);
                cout << "1. " << OptA[r] << endl;
                cout << "2. " << OptB[r] << endl;
                cout << "3. " << OptC[r] << endl;
                cout << "4. " << OptD[r] << endl;
                cout << endl;
            }
            cout << "Enter your Answer = " << endl;
        }
        else
        {
            cout << " " << endl;
            cout << " You choose not to use any lifeline " << endl;
        }
        int timeForThis = 10 + extraSeconds;
        userans = getTimedAnswer(1, 4, timeForThis);
        if (userans == -1)
        {
            cout << " << You failed to answer in time. >>" << endl;
        }
        else
        {
            if (allowed[userans] == 0)
            {
                cout << endl;
                cout << "That option was removed by 50/50 lifeline. Incorrect." << endl;
            }
            else
            {
                cout << endl;
                cout << "" << endl;
            }
        }
        if (userans == answer[r])
        {
            cout << endl;
            setColor(2);
            cout << "Your Answer is Correct" << endl;
            setColor(7);
            highscore = highscore + 3;
            correctAnswers++;
            cout << highscore;
            system("pause");
            system("cls");
        }
        else
        {
            setColor(12);
            cout << " <<Your Answer is Incorrect.>>" << endl;
            setColor(2);
            cout << "correct answer is = " << answer[r] << endl;
            setColor(7);
            highscore = highscore - 3;
            wrongAnswers++;
            cout << endl;
            wrongIndex[wrongCount] = r;
            wrongType[wrongCount] = 4;
            wrongUserAns[wrongCount] = userans;
            wrongCorrectAns[wrongCount] = answer[r];
            wrongCount++;
            system("pause");
            system("cls");
        }

    }
}

void Logicquestionshard(int& highscore)   //hard level question
{
    srand(time(0));
    ifstream file("iqhard.txt");
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
        int r = rand() % 10;
        int userans = 0;
        int allowed[5] = { 0, 1, 1, 1, 1 }; // index 1..4 = allowed (1) or removed (0)
        int extraSeconds = 0; // extra seconds added by lifeline
        setColor(11);
        cout << "--------------------------------------" << endl;
        setColor(14);
        cout << Questions[r] << endl;
        setColor(7);
        cout << "1. " << OptA[r] << endl;
        cout << "2. " << OptB[r] << endl;
        cout << "3. " << OptC[r] << endl;
        cout << "4. " << OptD[r] << endl;
        cout << endl;
        setColor(10);
        cout << "==> Do you want to use your lifelines (y/n) =  ";
        setColor(7);
        char user_choice;

        cin >> user_choice;
        if (user_choice == 'y')
        {
            system("cls");
            liflines_system();
            int choice;
            cout << " " << endl;
            cout << "Enter your choice = ";
            cin >> choice;
            system("cls");
            if (choice == 1 && lifeline_5050 == false)
            {
                lifeline_5050 = true;
                cout << " " << endl;
                cout << "Two option removed " << endl;
                int correct = answer[r];
                int remove = 0;
                for (int i = 1; i <= 4; i++)
                {
                    allowed[i] = 1; // ensure default
                }
                for (int i = 1; i <= 4; i++)
                {
                    if (i == correct)
                        continue;
                    if (remove < 2)
                    {
                        allowed[i] = 0;
                        remove++;
                    }
                }
                for (int i = 1; i <= 4; i++)
                {
                    if (allowed[i] == 1)
                        continue;

                }
                cout << Questions[r] << endl;
                for (int j = 1; j <= 4; j++)
                {
                    if (allowed[j] == 0)
                        continue;
                    if (j == 1)
                        cout << "1. " << OptA[r] << endl;
                    if (j == 2)
                        cout << "2. " << OptB[r] << endl;
                    if (j == 3)
                        cout << "3. " << OptC[r] << endl;
                    if (j == 4)
                        cout << "4. " << OptD[r] << endl;
                }
            }
            else if (choice == 2 && lifeline_skip == false)
            {
                lifeline_skip = true;
                cout << "The question is skipped successfully " << endl;
                return;
            }
            else if (choice == 3 && lifeline_replace_question == false)
            {
                lifeline_replace_question = true;
                r = rand() % 10;
                setColor(11);
                cout << "--------------------------------------" << endl;
                setColor(14);
                cout << Questions[r] << endl;
                setColor(7);
                cout << "1. " << OptA[r] << endl;
                cout << "2. " << OptB[r] << endl;
                cout << "3. " << OptC[r] << endl;
                cout << "4. " << OptD[r] << endl;
            }
            else if (choice == 4 && lifeline_extratime == false)
            {
                lifeline_extratime = true;
                extraSeconds += 10;
                cout << "You got 10 extra seconds " << endl;
                cout << "--------------------------------------" << endl;
                cout << Questions[r] << endl;
                cout << "1. " << OptA[r] << endl;
                cout << "2. " << OptB[r] << endl;
                cout << "3. " << OptC[r] << endl;
                cout << "4. " << OptD[r] << endl;
                cout << endl;
            }
            else if (choice == 5)
            {
                cout << " you selected not to choose any lifeline ";
                cout << endl;
                setColor(11);
                cout << "--------------------------------------" << endl;
                setColor(14);
                cout << Questions[r] << endl;
                setColor(7);
                cout << "1. " << OptA[r] << endl;
                cout << "2. " << OptB[r] << endl;
                cout << "3. " << OptC[r] << endl;
                cout << "4. " << OptD[r] << endl;
                cout << endl;
            }
            else
            {
                cout << "You already used this lifeline " << endl;
                setColor(11);
                cout << "--------------------------------------" << endl;
                setColor(14);
                cout << Questions[r] << endl;
                setColor(7);
                cout << "1. " << OptA[r] << endl;
                cout << "2. " << OptB[r] << endl;
                cout << "3. " << OptC[r] << endl;
                cout << "4. " << OptD[r] << endl;
                cout << endl;
            }
            cout << "Enter your Answer = " << endl;
        }
        else
        {
            cout << " " << endl;
            cout << " You choose not to use any lifeline " << endl;
        }
        int timeForThis = 10 + extraSeconds;
        userans = getTimedAnswer(1, 4, timeForThis);
        if (userans == -1)
        {
            cout << " << You failed to answer in time. >>" << endl;
        }
        else
        {
            if (allowed[userans] == 0)
            {
                cout << endl;
                cout << "That option was removed by 50/50 lifeline. Incorrect." << endl;
            }
            else
            {
                cout << endl;
                cout << "" << endl;
            }
        }
        if (userans == answer[r])
        {
            cout << endl;
            setColor(2);
            cout << "Your Answer is Correct" << endl;
            setColor(7);
            highscore = highscore + 5;
            correctAnswers++;
            cout << highscore;
            system("pause");
            system("cls");
        }
        else
        {
            setColor(12);
            cout << " <<Your Answer is Incorrect.>>" << endl;
            setColor(2);
            cout << "correct answer is = " << answer[r] << endl;
            setColor(7);
            highscore = highscore - 5;
            wrongAnswers++;
            cout << endl;
            wrongIndex[wrongCount] = r;
            wrongType[wrongCount] = 15;
            wrongUserAns[wrongCount] = userans;
            wrongCorrectAns[wrongCount] = answer[r];
            wrongCount++;
            system("pause");
            system("cls");
        }

    }
}
