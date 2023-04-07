void cls(HANDLE hStdOut)
{
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    COORD coordScreen = {0, 0};
    DWORD cCharsWritten;
    DWORD dwConSize;

    GetConsoleScreenBufferInfo(hStdOut, &csbi);
    dwConSize = csbi.dwSize.X * csbi.dwSize.Y;
    FillConsoleOutputCharacter(hStdOut, (TCHAR)' ', dwConSize, coordScreen, &cCharsWritten);
    GetConsoleScreenBufferInfo(hStdOut, &csbi);
    FillConsoleOutputAttribute(hStdOut, csbi.wAttributes, dwConSize, coordScreen, &cCharsWritten);
    SetConsoleCursorPosition(hStdOut, coordScreen);

    return;
}

void gotoxy(int x, int y)
{
    COORD coord = {0, 0};
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void chan(int x)
{
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(console, x);
}

void styleOfPages(int mode)
{
    int i = 1;
    int x = 60, pos = i + 6;

    for (i; i <= buttonOfpageHmuch; i++)
    {
        gotoxy(x, pos);
        char ch = 205;
        cout << (char)201 << setfill(ch) << setw(22) << (char)187;

        gotoxy(x, ++pos);
        cout << (char)186;
        pos == ((mode * 4) + 4) ? chan(240) : chan(15);
        cout << setfill(' ') << setw(21) << left << menuText[modeOfAllPages - 1][i - 1];
        chan(15);
        cout << (char)186;

        gotoxy(x, ++pos);
        cout << (char)200 << setfill(ch) << setw(22) << right << (char)188;

        pos += 2;
    }
}

void styleOfPrinting(vector <EmployeeS> v) {
    cout << setfill(' ') << setw(10) << left << "SSN";
    cout << setfill(' ') << setw(15) << left << "First Name";
    cout << setfill(' ') << setw(15) << left << "Last Name";
    if (typeOfEmployee == 3){
        cout << setfill(' ') << setw(15) << left << "grossSales";
        cout << setfill(' ') << setw(15) << left << "CommissionRate";
    }else if (typeOfEmployee == 2){
        cout << setfill(' ') << setw(15) << left << "Hours";
        cout << setfill(' ') << setw(15) << left << "Wage";
    }else
        cout << setfill(' ') << setw(15) << left << "Salary"; 
    cout << endl;
    cout << setfill('-') << setw(60) << " ";
    cout << endl;

    for (auto &a: v)
    {
        cout << setfill(' ') << setw(10) << left << a.SSN;
        cout << setfill(' ') << setw(15) << left << a.FirstName;
        cout << setfill(' ') << setw(15) << left << a.LastName;
        if(typeOfEmployee == 2 || typeOfEmployee == 3){
            cout << setfill(' ') << setw(15) << left << a.salary1;
            cout << setfill(' ') << setw(15) << left << a.salary2;
        }else
            if(TOP == 1)
                cout << setfill(' ') << setw(15) << left << a.salary1 * a.salary2;
            else
                cout << setfill(' ') << setw(15) << left << a.salary1;
        cout << endl;
    }
}

void showAllEmployee()
{
    fstream Employee;
    EmployeeS s;
    vector<EmployeeS> v;

    Employee.open("EmployeeInfo.txt", ios::in);

    while (Employee >> s.typeOE >> s.SSN >> s.FirstName >> s.LastName >> s.salary1 >> s.salary2)
    {
        if (s.typeOE == typeOfEmployee)
            v.push_back(s);
    }

    Employee.close();

   // v.pop_back();
    styleOfPrinting(v);
}

void addNewEmployee()
{
    fstream addEmployee;
    string FirstName, LastName;
    int SSN, type;
    int Salary, Hours, Wages, grossSales;
    float CommissionRate;

    gotoxy(0, 0);
    cout << setfill(' ') << setw(17) << left << "First name : ";
    cin >> ws;
    cin >> FirstName;

    cout << endl << setfill(' ') << setw(17) << left << "Last name : ";
    cin >> ws;
    cin >> LastName;

    if(editStute == 1)
        SSN = SSN_G;
    else{
        do{
            cout << endl << setfill(' ') << setw(17) << left << "SSN : ";
            cin >> SSN;
        } while (SSN < 1 || SSN > 8000000);
    }
    switch (typeOfEmployee){
    case 1:
        do {
            cout << endl << setfill(' ') << setw(17) << left << "Salary : ";
            cin >> Salary;
        } while (Salary < 1);
        break;

    case 2:
        do {
            cout << endl << setfill(' ') << setw(17) << left << "Hours : ";
            cin >> Hours;
        } while (Hours < 1);

        do {
            cout << endl << setfill(' ') << setw(17) << left << "Wages : ";
            cin >> Wages;
        } while (Wages < 1);
        break;

    case 3:
        do {
            cout << endl << setfill(' ') << setw(17) << left << "grossSales : ";
            cin >> grossSales;
        } while (grossSales < 1);

        do {
            cout << endl << setfill(' ') << setw(17) << left << "CommissionRate : ";
            cin >> CommissionRate;
        } while (CommissionRate < 0);
        break;

    default:
        cout << "Wrong: Error input" << endl;
        break;
    }
    // open the file 
    addEmployee.open("EmployeeInfo.txt", ios::out | ios::app );

    // check the type of employee
    if(typeOfEmployee == 3)
        addEmployee << typeOfEmployee << " " << SSN << " " << FirstName << " " << LastName << " " << grossSales << " " << setprecision(2) << CommissionRate << endl;
    else if(typeOfEmployee == 2)
        addEmployee << typeOfEmployee << " " << SSN << " " << FirstName << " " << LastName << " " << Hours << " " << Wages << endl;
    else
        addEmployee << typeOfEmployee << " " << SSN << " " << FirstName << " " << LastName << " " << Salary << " " << 1 << endl;
    addEmployee.close();
}

void EditDelete() {

    fstream Employee;
    EmployeeS s;
    vector<EmployeeS> v;
    int ssn;

    cout << "Enter the SSN number of Employee: ";
    cin >> ws;
    cin >> ssn;

    Employee.open("EmployeeInfo.txt", ios::in);

    while (Employee >> s.typeOE >> s.SSN >> s.FirstName >> s.LastName >> s.salary1 >> s.salary2)
    {
        if (s.SSN != ssn && s.typeOE == typeOfEmployee || s.typeOE != typeOfEmployee)
            v.push_back(s);  
    }
    Employee.close();

    if(v.size() > 1){
        Employee.open("EmployeeInfo.txt", ios::out);
        for(auto &a: v){
            if(typeOfEmployee == 1)
                Employee << a.typeOE << " " << a.SSN << " " << a.FirstName << " " << a.LastName << " " << a.salary1  << " " << 1 << endl;
            else
                Employee << a.typeOE << " " << a.SSN << " " << a.FirstName << " " << a.LastName << " " << a.salary1  << " " << a.salary2 << endl;
        }
        Employee.close();

        if(editStute == 1){
            SSN_G = ssn; 
            cls(hStdOutput);
            addNewEmployee();
        }
    }
    cout << endl << "Done" << endl;
}

void searchOfEmployee()
{
    int ssn;
    string firstName, lastName;
    if (stuteSearch == 1){
        cout << "Enter the SSN number: ";
        cin >> ws;
        cin >> ssn;
    }else if (stuteSearch == 2){
        cout << "Enter the first name: ";
        cin >> ws;
        cin >> firstName;
    }else if (stuteSearch == 3){
        cout << "Enter the last name: ";
        cin >> ws;
        cin >> lastName;
    }

    fstream Employee;
    EmployeeS s;
    vector <EmployeeS> v;

    Employee.open("EmployeeInfo.txt", ios::in);

    while (Employee >> s.typeOE >> s.SSN >> s.FirstName >> s.LastName >> s.salary1 >> s.salary2)
    {
        if (s.SSN == ssn || s.FirstName == firstName || s.LastName == lastName)
            v.push_back(s);
    }

    Employee.close();
    styleOfPrinting(v);
}

void topFive()
{
    fstream Employee;
    EmployeeS s;
    vector<EmployeeS> v;

    Employee.open("EmployeeInfo.txt", ios::in);

    while (Employee >> s.typeOE >> s.SSN >> s.FirstName >> s.LastName >> s.salary1 >> s.salary2)
    {
        v.push_back(s);
    }

    Employee.close();

    for(int i{0}; i < v.size(); ++i)
        for(int j{i + 1}; j < v.size(); ++j)
            if((v[j].salary1*v[j].salary2) > (v[i].salary1*v[i].salary2))
                swap(v[i], v[j]);

    if(v.size() > 5)
        v.erase (v.begin()+5, v.end());
    styleOfPrinting(v);
}

void projectMode(int selection)
{
    switch (modeOfAllPages)
    {
    case 1:
        // the main menu
        switch (selection)
        {
        case 1:
            modeOfAllPages = 2;
            buttonOfpageHmuch = 3;
            styleOfPages(1);
            break;

        case 2:
            modeOfAllPages = 5;
            buttonOfpageHmuch = 3;
            styleOfPages(1);
            break;

        case 3:
            topFive();
            modeOfAllPages = 4;
            buttonOfpageHmuch = 1;
            styleOfPages(1);
            break;

        case 4:
            exit(0);
            break;

        default:
            cerr << "Wrong : Error in menu part > style.h >  project mode " << endl;
            break;
        }
        break;

    case 2:
        // Employee choosing
        switch (selection)
        {
        case 1:
            modeOfAllPages = 3;
            buttonOfpageHmuch = 5;
            typeOfEmployee = 1;
            styleOfPages(1);
            break;

        case 2:
            modeOfAllPages = 3;
            buttonOfpageHmuch = 5;
            typeOfEmployee = 2;
            styleOfPages(1);
            break;

        case 3:
            modeOfAllPages = 3;
            buttonOfpageHmuch = 5;
            typeOfEmployee = 3;
            styleOfPages(1);
            break;

        default:
            cerr << "Wrong : Error in employee type > style.h >  project mode " << endl;
            break;
        }
        break;

    case 3:
        // setting of employee pages
        switch (selection)
        {
        case 1:
            editStute = 0;
            showAllEmployee();
            modeOfAllPages = 4;
            buttonOfpageHmuch = 1;
            styleOfPages(1);
            break;

        case 2:
            modeOfAllPages = 4;
            buttonOfpageHmuch = 1;
            addNewEmployee();
            styleOfPages(1);
            break;

        case 3:
            EditDelete();
            modeOfAllPages = 4;
            buttonOfpageHmuch = 1;
            styleOfPages(1);
            break;

        case 4:
            editStute = 1;
            EditDelete();
            modeOfAllPages = 4;
            buttonOfpageHmuch = 1;
            styleOfPages(1);
            editStute = 0;
            break;

        case 5:
            modeOfAllPages = 1;
            buttonOfpageHmuch = 4;
            typeOfEmployee = 0;
            styleOfPages(1);
            break;

        default:
            cerr << "Wrong : Error in employee type > style.h >  setting of employee pages " << endl;
            break;
        }
        break;

    case 4:
        // input Employee data in the add part
        switch (selection)
        {
        case 1:
            modeOfAllPages = 1;
            buttonOfpageHmuch = 4;
            typeOfEmployee = 0;
            styleOfPages(1);
            break;

        case 2:
            modeOfAllPages = 1;
            buttonOfpageHmuch = 4;
            typeOfEmployee = 0;
            styleOfPages(1);
            break;
        }
        break;

    case 5:
        stuteSearch = selection;
        searchOfEmployee();
        modeOfAllPages = 4;
        buttonOfpageHmuch = 1;
        styleOfPages(1);
        break;

    default:
        cerr << "Wrong: Error in project mode part..." << endl;
        break;
    }
}