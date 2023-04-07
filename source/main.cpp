#include <iostream>
#include <windows.h>
#include <conio.h>
#include <iomanip>
#include <vector>
#include <fstream>
#include <string>

using namespace std;
/*
 *   Globale variables
 *   more details in notes.txt file
 *   v0.0.1
 */
struct EmployeeS
{
    string FirstName, LastName;
    int SSN, typeOE;
    float salary1 , salary2;
};

HANDLE hStdOutput = NULL;
int modeOfAllPages = 1;
int buttonOfpageHmuch = 4;
int typeOfEmployee;
int stuteSearch;
int TOP;
int editStute, SSN_G;
vector<vector<string>> menuText = {{"Employee", "Search", "Viwe top5", "Exit"},
                                   {"Salary Employee", "Hourly Employee", "commission Employee"},
                                   {"Show all Employee", "Add new Employee", "Delete Employee", "Edit Employee info", "Back"},
                                   {"Back"},
                                   {"SSN", "First Name", "Last Name"}};
#include "header/style.h"

int main(void)
{    
    INPUT_RECORD ir[128];
    HANDLE hStdInput = NULL;
    HANDLE hEvent = NULL;
    DWORD nRead;
    COORD xy;
    char ch, ch2;
    int keyCounter = 1;

    hStdInput = GetStdHandle(STD_INPUT_HANDLE);
    hStdOutput = GetStdHandle(STD_OUTPUT_HANDLE);
    cls(hStdOutput);

    styleOfPages(1);
    SetConsoleMode(hStdInput, ENABLE_ECHO_INPUT | ENABLE_LINE_INPUT | ENABLE_MOUSE_INPUT | ENABLE_EXTENDED_FLAGS);
    FlushConsoleInputBuffer(hStdInput);
    hEvent = CreateEvent(NULL, FALSE, FALSE, NULL);         
    HANDLE handles[2] = {hEvent, hStdInput};                 
    while (WaitForMultipleObjects(2, handles, FALSE, INFINITE)) 
    {
        ShowCursor(FALSE);
        ReadConsoleInput(hStdInput, ir, 128, &nRead);
        for (size_t i = 0; i < nRead; i++)            
        {                                             
            switch (ir[i].EventType)                 
            {                                         
            case MOUSE_EVENT:                         
                xy.X = 0, xy.Y = 1;
                SetConsoleCursorPosition(hStdOutput, xy);

                if (ir[i].Event.MouseEvent.dwMousePosition.X >= 45 &&
                    ir[i].Event.MouseEvent.dwMousePosition.X <= 66)
                {
                    switch (ir[i].Event.MouseEvent.dwMousePosition.Y)
                    {
                    case 8:
                        keyCounter = 1;
                        styleOfPages(keyCounter);
                        if ((int)ir[i].Event.MouseEvent.dwButtonState == 1)
                        {
                            cls(hStdOutput);
                            projectMode(keyCounter);
                        }
                        break;
                    case 12:
                        keyCounter = 2;
                        styleOfPages(keyCounter);
                        if ((int)ir[i].Event.MouseEvent.dwButtonState == 1)
                        {
                            cls(hStdOutput);
                            projectMode(keyCounter);
                        }
                        break;
                    case 16:
                        keyCounter = 3;
                        styleOfPages(keyCounter);
                        if ((int)ir[i].Event.MouseEvent.dwButtonState == 1)
                        {
                            cls(hStdOutput);
                            projectMode(keyCounter);
                        }
                        break;
                    case 20:
                        keyCounter = 4;
                        styleOfPages(keyCounter);
                        if ((int)ir[i].Event.MouseEvent.dwButtonState == 1)
                        {
                            cls(hStdOutput);
                            projectMode(keyCounter);
                        }
                        break;
                    case 24:
                        keyCounter = 5;
                        styleOfPages(keyCounter);
                        if ((int)ir[i].Event.MouseEvent.dwButtonState == 1)
                        {
                            cls(hStdOutput);
                            projectMode(keyCounter);
                        }
                        break;
                    }
                }
                break;
            }
        }
    };

    return 0;
}
