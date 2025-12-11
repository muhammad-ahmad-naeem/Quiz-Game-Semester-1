#include <iostream>
#include <cmath>
#include <string>
#include <cstdlib>
#include <fstream>
using namespace std;
bool lifeline_5050 = false;
bool lifeline_skip = false;
bool lifeline_replace_question = false;
bool lifeline_extratime = false;
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
                    break;                         //east tier questions end here

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
                    break;                            //MID Tier Question end here


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
                    break;                            //hard tier questions end here
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
        int r = rand() % 10, userans;
        cout << "--------------------------------------" << endl;
        cout << Questions[r] << endl;
        cout << "1. " << OptA[r] << endl;
        cout << "2. " << OptB[r] << endl;
        cout << "3. " << OptC[r] << endl;
        cout << "4. " << OptD[r] << endl;
        cout << "Enter your Answer = ";
        liflines_system();
        int choice;
        cout << "Enter your choice within the given options" << endl;
        cin >> choice;
        if (choice == 1 && lifeline_5050 == false)
        {
            lifeline_5050 = true;
            cout << "Two options will be removed " << endl;

            int correct = answer[r];
            int remove = 0;
            int allowed[5] = { 0, 1, 1, 1, 1 };

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
                if (i == 1) 
                    cout << OptA[r] << " Removed " << endl;
                if (i == 2) 
                    cout << OptB[r] << " Removed " << endl;
                if (i == 3) 
                    cout << OptC[r] << " Removed " << endl;
                if (i == 4) 
                    cout << OptD[r] << " Removed " << endl;
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
            cout << "You got 10 extra seconds " << endl;
        }
        else if (choice == 5)
        {
            cout << "  you selected not to choose any lifeline  ";
            cout << endl;
        }
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

void Computerquestionshard(int& highscore)   //hard level questions
{

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
        cout << "--------------------------------------" << endl;
        cout << Questions[r] << endl;
        cout << "1. " << OptA[r] << endl;
        cout << "2. " << OptB[r] << endl;
        cout << "3. " << OptC[r] << endl;
        cout << "4. " << OptD[r] << endl;
        cout << "Enter your Answer = ";
        int userans;
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
