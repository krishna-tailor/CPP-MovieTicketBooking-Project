#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
using namespace std;

void Enter_To_Continue()
{
    cout << endl
         << "Press Enter to Continue...";
    cin.ignore();
    cin.get();
}

const int WIDTH = 52;

ostream &mainHeading(ostream &out)
{
    out << string(WIDTH, '=');
    return out;
}

ostream &leftSide(ostream &out)
{
    out << "====>";
    return out;
}

ostream &RightSide(ostream &out)
{
    out << "<====";
    return out;
}

ostream &lineSeperator(ostream &out)
{
    out << '\n'
        << string(WIDTH, '-') << '\n';
    return out;
}

int i = 0;        // Tracks the index of objects Of Customer Class
int j = 0, k = 0; // Tracks The Index Of Movie Object Day1 and Day2
int m = 0, n = 0; // Tracks The Index Of Character Of Seat Array Of Day1 And Day2 Object
int l;            // Track The Index Of Current User Logged In

void customerDashBoard();
void adminDashboard();
void loadMovieData();
void loadMovieSeats();
void loadCustomerData();
void validateCustomerAcc();

/*
Read Data from The File As Soon As Program Starts
Make 2D array of the object where each column represents the show and row represents the
details of each unique movie
*/
// Movie Class
class Movie
{
private:
    string name;
    int duration, screenNo;        // Movie Duration will be in total minutes
    float marvel, royal, recliner; // Ticket Pricing
    int showHr, showMins;          // Show That at what time show will start
    int showNo, dayNo;
    static int count;
    int showTrack;

public:
    string seats[10];
    int availableTickets;
    int friend validateSeat(char row, int column, int showNo, int dayNo);
    void friend loadMovieSeats(); // Loads The Movie Seats At The Starting Of The Program
    void friend loadMovieData();  // Loads The Movie Infortmation At The Starting Of The Program

    void addMoive();
    // void updateMovies();
    int printMovie();
    void printSeatsAndInformation(int val, int showNo);
    void printDay1Movies();
    void printDay2Movies();
    void loadSeats(int dayNo, int showNo);
    // void deleteMovies();
} day1[100], day2[100];

int Movie::count = 0;

void Movie::printSeatsAndInformation(int dayNo, int showNo)
{
    char ch = 'A';
    system("clear");
    cout << "+------+------------------------------------------+----------+-----------+-------------------+--------------+\n";
    cout << "|Sr No | Movie Name                               | Duration | Screen No | Starting Time     | Show No      |\n";
    cout << "+-------------------------------------------------+----------+-----------+-------------------+--------------+\n";
    if (dayNo == 1)
    {
        cout << "| "
             << left << setw(4) << showNo + 1
             << " | "
             << left << setw(40) << day1[showNo].name
             << " | "
             << left << setw(8) << day1[showNo].duration
             << " | "
             << left << setw(9) << day1[showNo].screenNo
             << " | ";

        // Starting Time
        cout << right << setw(2) << setfill('0') << day1[showNo].showHr
             << ":"
             << setw(2) << day1[showNo].showMins
             << setfill(' ')
             << "             | ";

        // Show No
        cout << left << setw(13) << day1[showNo].showNo
             << "|\n";
    }

    else
    {
        cout << "| "
             << left << setw(4) << showNo + 1
             << " | "
             << left << setw(40) << day2[showNo].name
             << " | "
             << left << setw(8) << day2[showNo].duration
             << " | "
             << left << setw(9) << day2[showNo].screenNo
             << " | ";

        // Starting Time
        cout << right << setw(2) << setfill('0') << day2[showNo].showHr
             << ":"
             << setw(2) << day2[showNo].showMins
             << setfill(' ')
             << "             | ";

        // Show No
        cout << left << setw(13) << day2[showNo].showNo
             << "|\n";
    }
    cout << "+-------------------------------------------------+----------+-----------+-------------------+--------------+\n";
    cout << "\n";
    // Printing Seats Of The Show
    for (int i = 0; i < 10; i++)
    {
        if (i == 0 || i == 1)
        {
            if (dayNo == 1)
            {
                if (i == 0)
                    cout << right << setw(32) << "Recliner: Rs." << day1[showNo].recliner << "\n\n";
            }

            else
            {
                if (i == 0)
                    cout << right << setw(32) << "Recliner: Rs." << day2[showNo].recliner << "\n\n";
            }
            cout << ch++ << "       ";
        }

        if (i == 2 || i == 7)
            cout << "\n\n";

        if (i >= 2)
        {
            if (dayNo == 1)
            {
                if (i == 2)
                    cout << right << setw(30) << "Royal: Rs." << day1[showNo].royal << "\n\n";

                if (i == 7)
                    cout << right << setw(30) << "Marvel: Rs." << day1[showNo].marvel << "\n\n";
            }
            else
            {
                if (i == 2)
                    cout << right << setw(30) << "Royal: Rs." << day2[showNo].royal << "\n\n";

                if (i == 7)
                    cout << right << setw(30) << "Marvel: Rs." << day2[showNo].marvel << "\n\n";
            }
            if (i >= 7)
                cout << ch++ << "       ";
            else
                cout << ch++ << "    ";
        }

        for (int j = 0; j < 10; j++)
        {

            if (j != 9)
            {
                if (dayNo == 1)
                {

                    if (day1[showNo].seats[i][j] == 'O')
                    {
                        cout << "XX ";
                    }
                    else
                        cout << "0" << j + 1 << " ";
                }
                else if (dayNo == 2)
                {

                    if (day2[showNo].seats[i][j] == 'O')
                    {
                        cout << "XX ";
                    }
                    else
                        cout << "0" << j + 1 << " ";
                }
            }

            else
            {
                if (dayNo == 1)
                {

                    if (day1[showNo].seats[i][j] == 'O')
                    {
                        cout << "XX ";
                    }

                    else
                        cout << j + 1;
                }
                else if (dayNo == 2)
                {

                    if (day2[showNo].seats[i][j] == 'O')
                    {
                        cout << "XX ";
                    }
                    else
                        cout << j + 1;
                }
            }

            if (i >= 2 && i <= 6)
            {
                if (j == 1 || j == 7)
                    cout << "   ";
            }
        }
        cout << "\n";
    }

    cout << "\n\n  \\_________________________________________/\n"
         << "               Screen This Side\n";
}

// Load Seats In the file when the new movie enters
void Movie::loadSeats(int dayNo, int showNo)
{
    ofstream oFile;
    if (dayNo == 1)
        oFile.open("Day1MovieSeats.txt", ios::app);
    else
        oFile.open("Day2MovieSeats.txt", ios::app);
    // Loading Temp Data
    oFile << "Show No: " << showNo << "\n";
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            oFile << "X";
        }
        oFile << "\n";
    }
    oFile << "Total Available Tickets => " << 20;
    oFile << "\n";
    oFile.close();
}

void Movie::addMoive()
{
    ofstream file;
    getchar();
    cout << "Enter The Name Of Movie => ";
    getline(cin, name);

duration:
    cout << "\nEnter Duration Of The Movie (Total Minutes) => ";
    cin >> duration;
    if (duration < 60)
    {
        system("clear");
        cout << leftSide << " Movie Duration Should Be Atleast 60 mins " << RightSide << endl;
        goto duration;
    }

screenNo:
    cout << "\nEnter Movie Screen No => ";
    cin >> screenNo;
    if (screenNo <= 0)
    {
        system("clear");
        cout << leftSide << " Screen No Should Be Greater Than 0 " << RightSide << endl;
        goto screenNo;
    }

marvel:
    cout << "\nEnter The Price Of Marvel Seat => ";
    cin >> marvel;
    if (marvel < 150)
    {
        system("clear");
        cout << leftSide << " Price Of Marvel Seat Must Be Atleast Rs.150 " << RightSide << endl;
        goto marvel;
    }

royal:
    cout << "\nEnter The Price Of Royal Seat => ";
    cin >> royal;
    if (royal <= marvel)
    {
        system("clear");
        cout << leftSide << " Price Of Royal Seat Must Be Greater Than Marvel Seat " << RightSide << endl;
        goto royal;
    }

Recliner:
    cout << "\nEnter The Price Of Recliner Seat => ";
    cin >> recliner;
    if (recliner <= marvel || recliner <= royal)
    {
        system("clear");
        cout << leftSide << " Price Of Recliner Seat Must Be Greater Than Marvel And Royal " << RightSide << endl;
        goto Recliner;
    }

showhr:
    cout << "\nEnter The Starting Hour Of Show => ";
    cin >> showHr;
    if (showHr > 24 || showHr < 0)
    {
        system("clear");
        cout << leftSide << " Starting Of Show Must Not Be Greater Than 24 And Less Than 0 " << RightSide << endl;
        goto showhr;
    }

showMin:
    cout << "\nEnter The Starting Minutes Of Show => ";
    cin >> showMins;
    if (showMins > 60 || showMins < 0)
    {
        system("clear");
        cout << leftSide << " Starting Of Show Must Not Be Greater Than 60 And Less Than 0" << RightSide << endl;
        goto showMin;
    }

dayNo:
    cout << "\nEnter Day No Of The Show => ";
    cin >> dayNo;
    if (dayNo > 2 || dayNo <= 0)
    {
        system("clear");
        cout << leftSide << " Day No Must Be 1 or 2 " << RightSide << endl;
        goto dayNo;
    }

    if (dayNo == 1)
    {
        file.open("Day1_Movie_Details.txt", ios::app);
        if (j > 0)
        {
            showNo = day1[j - 1].showNo;
            showNo++;
        }

        else
            showNo = 1;
    }

    else
    {
        file.open("Day2_Movie_Details.txt", ios::app);
        if (k > 0)
        {
            showNo = day2[k - 1].showNo;
            showNo++;
        }

        else
            showNo = 1;
    }

    file << "Name => " << name
         << "\nMovie Duration => " << duration
         << "\nScreen No => " << screenNo
         << "\nPrice Of Marvel Seat => " << marvel
         << "\nPrice Of Royal Seat => " << royal
         << "\nPrice Of Recliner Seat => " << recliner
         << "\nShow Starting Time => " << showHr << " : " << showMins
         << "\nShow No => " << showNo << "\n\n";
    file.close();
    loadSeats(dayNo, showNo); // ADDS ALL NEW SEATS FOR NEW MOVIE
    system("clear");
    cout << leftSide << " Movie Added Successfully " << RightSide << "\n\n";
    j = 0;
    k = 0;
    loadMovieData();
    Enter_To_Continue();
}

void Movie::printDay1Movies()
{
    cout << "\n\n";
    cout << "=============================== DAY 1 MOVIES ===============================\n\n";

    cout << "+------+------------------------------------------+----------+-----------+-------------------+--------------+\n";
    cout << "|Sr No | Movie Name                               | Duration | Screen No | Starting Time     | Show No      |\n";
    cout << "+-------------------------------------------------+----------+-----------+-------------------+--------------+\n";

    if (j == 0)
    {
        cout << right << setw(37) << "No Movies Present To Show\n";
    }
    for (int m = 0; m < j; m++)
    {
        cout << "| "
             << left << setw(4) << m + 1
             << " | "
             << left << setw(40) << day1[m].name
             << " | "
             << left << setw(8) << day1[m].duration
             << " | "
             << left << setw(9) << day1[m].screenNo
             << " | ";

        // Starting Time
        cout << right << setw(2) << setfill('0') << day1[m].showHr
             << ":"
             << setw(2) << day1[m].showMins
             << setfill(' ')
             << "             | ";

        // Show No
        cout << left << setw(13) << day1[m].showNo
             << "|\n";
    }

    cout << "+-------------------------------------------------+----------+-----------+-------------------+--------------+\n";
}

void Movie::printDay2Movies()
{
    cout << "\n\n";
    cout << "================================ NEXT DAY MOVIES ================================\n\n";

    cout << "+------+------------------------------------------+----------+-----------+-------------------+--------------+\n";
    cout << "|Sr No | Movie Name                               | Duration | Screen No | Starting Time     | Show No      |\n";
    cout << "+-------------------------------------------------+----------+-----------+-------------------+--------------+\n";
    if (k == 0)
    {
        cout << right << setw(37) << "No Movies Present To Show\n";
    }
    for (int m = 0; m < k; m++)
    {
        cout << "| "
             << left << setw(4) << m + 1
             << " | "
             << left << setw(40) << day2[m].name
             << " | "
             << left << setw(8) << day2[m].duration
             << " | "
             << left << setw(9) << day2[m].screenNo
             << " | ";

        // Starting Time
        cout << right << setw(2) << setfill('0') << day2[m].showHr
             << ":"
             << setw(2) << day2[m].showMins
             << setfill(' ')
             << "             | ";

        // Show No
        cout << left << setw(13) << day2[m].showNo
             << "|\n";
    }

    cout << "+-------------------------------------------------+----------+-----------+-------------------+--------------+\n";
}

int Movie::printMovie()
{
    int choice1;
    Movie m;
    cout << "\n";
    cout << "============================================================\n";
    cout << "                    MOVIE SHOWS\n";
    cout << "============================================================\n\n";
    cout << "        +------------------------------------------+\n";
    cout << "        |              MOVIE OPTIONS               |\n";
    cout << "        +------------------------------------------+\n\n";
    cout << "        |  [1]  Show Movies Of Current Day         |\n\n";
    cout << "        |  [2]  Show Movies Of Tomorrow            |\n\n";
    cout << "        |  [3]  Show Movies Of Both Days           |\n\n";
    cout << "        +------------------------------------------+\n\n";
    cout << "        Enter Your Choice => ";
    cin >> choice1;
    if (choice1 == 1)
    {
        system("clear");
        m.printDay1Movies();
        Enter_To_Continue();
    }
    else if (choice1 == 2)
    {
        system("clear");
        m.printDay2Movies();
        Enter_To_Continue();
    }
    else if (choice1 == 3)
    {
        system("clear");
        m.printDay1Movies();
        m.printDay2Movies();
        Enter_To_Continue();
    }
    else
    {
        system("clear");
        cout << "\nInvalid Choice! Please try again.\n";
    }
    return 0;
}

// Admin Class

class Admin
{
public:
    Movie m;
    int adminLogin();
    void movieOperatons(); // CRUD Operations
};

// Admin Class Functions
int Admin::adminLogin()
{
    string userName, password;
    int count = 0;
tryAgain:
    cout << "Enter Admin User Name: ";
    cin >> userName;

    cout << "Enter Admin Password: ";
    cin >> password;

    if (userName != "Admin" || password != "Admin@123")
    {
        system("clear");
        count++;
        cout << leftSide << " Invalid Admin Credentials , You Have " << 3 - count << " Attempts left " << RightSide << endl;
        if (count == 3)
        {
            cout << endl
                 << leftSide << " Now You Have Logged Out " << RightSide;
            return 1;
        }
        goto tryAgain;
    }

    else
    {
        system("clear");
        cout << leftSide << " Logged In Successfully " << RightSide << "\n";
        cout << lineSeperator;
        return 0;
    }
}

void Admin::movieOperatons()
{
    int choice, choice1;
    do
    {

        cout << "\n";
        cout << mainHeading;
        cout << "\n        MOVIE MANAGEMENT MENU\n";
        cout << mainHeading;

        cout << "\n\n"
             << "        +--------------------------------------+\n"
             << "        |           MOVIE OPERATIONS           |\n"
             << "        +--------------------------------------+\n\n";
        cout << "        |  [1]  Add Movie                      |\n\n";
        cout << "        |  [2]  View Movies                    |\n\n";
        cout << "        |  [3]  Update Movie Details           |\n\n";
        cout << "        |  [4]  Delete Movie                   |\n\n";
        cout << "        |  [5]  Back To Admin Dashboard        |\n";
        cout << "        +--------------------------------------+\n"
             << leftSide << " Enter Your Choice => ";

        cin >> choice;

        switch (choice)
        {

        case 1:
            system("clear");
            m.addMoive();
            break;

        case 2:
            system("clear");
            m.printMovie();
            break;

        case 3:
            system("clear");
            // m.updateMovies();
            break;

        case 5:
            system("clear");
            cout << leftSide << "Returning to Admin Dashboard..." << RightSide << endl
                 << lineSeperator;
            break;

        default:
            system("clear");
            cout << leftSide << " Invalid Choice " << RightSide << endl;
            break;
        }
    } while (choice != 5);
    Enter_To_Continue();
}

// Class Customer
class Customer
{
private:
    string name, movieSelected, MovieTime, password, bookedSeats[20];
    int age, LastId;
    int customerId;
    long long int mobileNo;

public:
    void createAccount();

    friend void loadCustomerData();
    friend void validateCustomerAcc();

    void bookTicketsMenu();
    void bookTickets(int DayNo);
    // void viewBookedTickets();
    // void updateInformation();
    // void cancelTickets();
} c1[10000];

int validateSeat(char row, int column, int showNo, int dayNo)
{
    // Day 1 Seat Validation
    if (dayNo == 1)
    {
        switch (row)
        {
        case 'A':
        case 'a':
            if (day1[showNo].seats[0][column - 1] == 'O')
                return 1;
            break;
        case 'B':
        case 'b':
            if (day1[showNo].seats[1][column - 1] == 'O')
                return 1;
            break;
        case 'C':
        case 'c':
            if (day1[showNo].seats[2][column - 1] == 'O')
                return 1;
            break;
        case 'D':
        case 'd':
            if (day1[showNo].seats[3][column - 1] == 'O')
                return 1;
            break;
        case 'E':
        case 'e':
            if (day1[showNo].seats[4][column - 1] == 'O')
                return 1;
            break;
        case 'F':
        case 'f':
            if (day1[showNo].seats[5][column - 1] == 'O')
                return 1;
            break;
        case 'G':
        case 'g':
            if (day1[showNo].seats[6][column - 1] == 'O')
                return 1;
            break;
        case 'H':
        case 'h':
            if (day1[showNo].seats[7][column - 1] == 'O')
                return 1;
            break;
        case 'I':
        case 'i':
            if (day1[showNo].seats[8][column - 1] == 'O')
                return 1;
            break;
        case 'J':
        case 'j':
            if (day1[showNo].seats[9][column - 1] == 'O')
                return 1;
            break;
        }
    }

    // Day 2 Seat Validation
    else
    {
        switch (row)
        {
        case 'A':
        case 'a':
            if (day2[showNo].seats[0][column - 1] == 'O')
                return 1;
            break;
        case 'B':
        case 'b':
            if (day2[showNo].seats[1][column - 1] == 'O')
                return 1;
            break;
        case 'C':
        case 'c':
            if (day2[showNo].seats[2][column - 1] == 'O')
                return 1;
            break;
        case 'D':
        case 'd':
            if (day2[showNo].seats[3][column - 1] == 'O')
                return 1;
            break;
        case 'E':
        case 'e':
            if (day2[showNo].seats[4][column - 1] == 'O')
                return 1;
            break;
        case 'F':
        case 'f':
            if (day2[showNo].seats[5][column - 1] == 'O')
                return 1;
            break;
        case 'G':
        case 'g':
            if (day2[showNo].seats[6][column - 1] == 'O')
                return 1;
            break;
        case 'H':
        case 'h':
            if (day2[showNo].seats[7][column - 1] == 'O')
                return 1;
            break;
        case 'I':
        case 'i':
            if (day2[showNo].seats[8][column - 1] == 'O')
                return 1;
            break;
        case 'J':
        case 'j':
            if (day2[showNo].seats[9][column - 1] == 'O')
                return 1;
            break;
        }
    }
    return 0;
}

void Customer::bookTickets(int dayNo)
{
    Movie m;
    char row;
    int column;
    int srNo, totalTickets;
    int a = 0; // Track The Index Of No Of Booked Tickets

    if (dayNo == 1)
        m.printDay1Movies();
    else
        m.printDay2Movies();

enterSrNoAgain:
    cout << "Enter The Movie Sr No To Book Tickets =>";
    cin >> srNo;
    if (dayNo == 1)
    {
        if (srNo >= j + 1 || srNo < 1) // This Condition Is To Check If The
        {
            cout << "\n\n";
            cout << leftSide << " Invalid Sr No , Please Enter Again " << RightSide << "\n";
            goto enterSrNoAgain;
        }
        cout << "\n\n";
        system("clear");
        m.printSeatsAndInformation(1, srNo - 1);
    }

    else
    {
        if (srNo >= k + 1 || srNo < 1)
        {
            cout << "\n\n";
            cout << leftSide << " Invalid Sr No , Enter Again " << RightSide << "\n";
            goto enterSrNoAgain;
        }
        cout << "\n\n";
        system("clear");
        m.printSeatsAndInformation(2, srNo - 1);
    }

reEnterTotalTickets:
    cout << "\nEnter How Many Tickets Your Want To Book At A Time: ";
    cin >> totalTickets;
    if (dayNo == 1)
    {
        if (totalTickets > day1[srNo - 1].availableTickets)
        {
            cout << leftSide << "The Number Of Tickets Your Want Are More Than The Total Tickets Available " << RightSide << endl;
            goto reEnterTotalTickets;
        }

        else
            day1[srNo - 1].availableTickets -= totalTickets;
    }

    else
    {
        if (totalTickets > day2[srNo - 1].availableTickets)
        {
            cout << leftSide << "The Number Of Tickets Your Want Are More Than The Total Tickets Available " << RightSide << endl;
            goto reEnterTotalTickets;
        }

        else
            day2[srNo - 1].availableTickets -= totalTickets;
    }

    for (int i = 0; i < totalTickets; i++)
    {
        cout << endl
             << leftSide << "Enter The Details Of Ticket " << i + 1 << RightSide;
        cout << "\n";

    reEnterRow:
        cout << "\nEnter Row Character: ";
        cin >> row;

        if (row > 'j' && row > 'J' || row < 'A' && row < 'a')
        {
            cout << leftSide << " Invalid Row Character , Please Enter Again " << RightSide << endl;
            goto reEnterRow;
        }

    reEnterColumnNo:
        cout << "\nEnter Column No => ";
        cin >> column;

        if (column > 10 || column < 1)
        {
            cout << leftSide << " Invalid Column No , Please Enter Again " << RightSide << endl;
            goto reEnterColumnNo;
        }

        if (validateSeat(row, column, srNo - 1, dayNo) == 1)
        {
            cout << leftSide << " Seat Already Occupied , Please Enter Seat Again " << RightSide;
            cout << "\n";
            goto reEnterRow;
        }

        else
        {
            switch (row)
            {
            case 'A':
            case 'a':
                if (dayNo == 1)
                    day1[srNo - 1].seats[0][column - 1] = 'O';
                else
                    day2[srNo - 1].seats[0][column - 1] = 'O';
                break;
            case 'B':
            case 'b':
                if (dayNo == 1)
                    day1[srNo - 1].seats[1][column - 1] = 'O';
                else
                    day2[srNo - 1].seats[1][column - 1] = 'O';
                break;
            case 'C':
            case 'c':
                if (dayNo == 1)
                    day1[srNo - 1].seats[2][column - 1] = 'O';
                else
                    day2[srNo - 1].seats[2][column - 1] = 'O';
                break;
            case 'D':
            case 'd':
                if (dayNo == 1)
                    day1[srNo - 1].seats[3][column - 1] = 'O';
                else
                    day2[srNo - 1].seats[3][column - 1] = 'O';
                break;
            case 'E':
            case 'e':
                if (dayNo == 1)
                    day1[srNo - 1].seats[4][column - 1] = 'O';
                else
                    day2[srNo - 1].seats[4][column - 1] = 'O';
                break;
            case 'F':
            case 'f':
                if (dayNo == 1)
                    day1[srNo - 1].seats[5][column - 1] = 'O';
                else
                    day2[srNo - 1].seats[5][column - 1] = 'O';
                break;
            case 'G':
            case 'g':
                if (dayNo == 1)
                    day1[srNo - 1].seats[6][column - 1] = 'O';
                else
                    day2[srNo - 1].seats[6][column - 1] = 'O';
                break;
            case 'H':
            case 'h':
                if (dayNo == 1)
                    day1[srNo - 1].seats[7][column - 1] = 'O';
                else
                    day2[srNo - 1].seats[7][column - 1] = 'O';
                break;
            case 'I':
            case 'i':
                if (dayNo == 1)
                    day1[srNo - 1].seats[8][column - 1] = 'O';
                else
                    day2[srNo - 1].seats[8][column - 1] = 'O';
                break;
            case 'J':
            case 'j':
                if (dayNo == 1)
                    day1[srNo - 1].seats[9][column - 1] = 'O';
                else
                    day2[srNo - 1].seats[0][column - 1] = 'O';
                break;
            }

            if (dayNo == 1)
            {
                system("clear");
                m.printSeatsAndInformation(1, srNo - 1);
            }

            else
            {
                system("clear");
                m.printSeatsAndInformation(2, srNo - 1);
            }
        }
        c1[l].bookedSeats[a++] = row + to_string(column);
    }
    
}

void Customer::bookTicketsMenu()
{
    int choice;
    cout << "\n";
    cout << "============================================================\n";
    cout << "                      BOOK TICKET OPTIONS\n";
    cout << "============================================================\n\n";
    cout << "        +------------------------------------------+\n";
    cout << "        |              MOVIE OPTIONS               |\n";
    cout << "        +------------------------------------------+\n\n";
    cout << "        |  [1]  BOOK TICKET FOR CURRENT DAY SHOWS  |\n\n";
    cout << "        |  [2]  BOOK TICKET FOR NEXT DAY SHOWS     |\n\n";
    cout << "        |  [3]  BACK TO THE PREVIOUS MENU          |\n\n";
    cout << "        +------------------------------------------+\n\n";
    cout << "        Enter Your Choice => ";
    cin >> choice;
    if (choice == 1)
    {
        system("clear");
        bookTickets(1);
        Enter_To_Continue();
    }
    else if (choice == 2)
    {
        system("clear");
        Enter_To_Continue();
    }
    else if (choice == 3)
    {
        system("clear");
        cout << leftSide << " REDIRECTED TO PREVIOUS MENU" << RightSide << endl;
        cout << lineSeperator << endl;
    }
    else
    {
        system("clear");
        cout << "\nInvalid Choice! Please try again.\n";
    }
}

void Customer::createAccount()
{
    ofstream outputFile;
    system("clear");

    // Taking The Last Customer ID From File
    if (i > 0)
    {
        customerId = c1[i - 1].customerId;
        customerId++;
    }

    else if (i == 0)
    {
        customerId = 100;
    }

    getchar();
    cout << "Enter Your Name => ";
    getline(cin, name);

    do
    {
        cout << "Enter Your Age => ";
        cin >> age;
        if (age < 18)
        {
            system("clear");
            cout << left << " Your Age Must be Greater Than 18 " << right << endl;
        }
    } while (age < 18);

    do
    {
    inputMobileNo:
        cout << "Enter Your Mobile No => ";
        cin >> mobileNo;

        if (mobileNo > 9999999999 || mobileNo <= 999999999)
        {
            system("clear");
            cout << left << " Invalid Mobile Number , Please Try Again " << right << endl;
        }

        else
        {
            /*
                Logic Of If Condition
            If file Will Not Open / does not exist / is empty
            So The Index Value Will Be 0 , no data will be stored And No valdation will be done
            */

            if (i > 0)
            {

                for (int j = 0; j < i; j++)
                {
                    if (mobileNo == c1[j].mobileNo)
                    {
                        system("clear");
                        cout << left << " Duplicate Mobile Number , Please Try Again " << right << endl;
                        goto inputMobileNo;
                    }
                }
            }
        }
    } while (mobileNo > 9999999999 || mobileNo <= 999999999);

    do
    {
        cout << "Enter Your Password => ";
        cin >> password;
        if (password.length() < 8)
        {
            system("clear");
            cout << left << " Password Must Be At Least Of 8 Characters , Please Try Again " << right << endl;
        }
    } while (password.length() < 8);

    outputFile.open("Customer_Account_Information.txt", ios::app);
    outputFile << "Name => " << name
               << "\nAge => " << age
               << "\nMobile No => " << mobileNo
               << "\nPassword => " << password
               << "\nCustomer Id => " << customerId << "\n\n";
    outputFile.close();

    i = 0;
    loadCustomerData(); // Reloading Data After the new data get Enter
}

// Main Function
int main()
{
    system("clear");
    int choice;

    loadCustomerData();
    loadMovieData();
    loadMovieSeats();
    do
    {
        // Uer Interface Part Starts
        cout << '\n';
        cout << mainHeading;
        cout << "\n"
             << setw(35) << right << "MOVIE TICKET BOOKING SYSTEM\n";
        cout << mainHeading;

        cout << "\n\n"
             << setw(34) << right << "USER DASHBOARD\n";

        cout << lineSeperator;

        cout << "\n"
             << "       1.  Login As Admin\n\n"
             << "       2.  Login As Customer\n\n"
             << "       3.  Exit\n";

        cout << lineSeperator;

        cout << "\n       Enter Your Choice => ";
        cin >> choice;

        cout << '\n';
        // Uer Interface Part Ends

        switch (choice)
        {
        case 1:
            system("clear");
            adminDashboard();
            break;

        case 2:
            system("clear");
            customerDashBoard();
            break;

        case 3:
            system("clear");
            cout << leftSide << " Thank You Please Visit Again " << RightSide << endl;
            cout << lineSeperator;
            break;

        default:
            system("clear");
            cout << leftSide << " Invalid Choice " << RightSide;
            cout << lineSeperator;
            break;
        }
    } while (choice != 3);
}

// External Functions
void loadCustomerData()
{
    string line;
    ifstream inputFile("Customer_Account_Information.txt");

    while (getline(inputFile, line))
    {
        c1[i].name = line.substr(7);
        getline(inputFile, line);
        c1[i].age = stoi(line.substr(6));
        getline(inputFile, line);
        c1[i].mobileNo = stoll(line.substr(13));
        getline(inputFile, line);
        c1[i].password = line.substr(12);
        getline(inputFile, line);
        c1[i].customerId = stoi(line.substr(15));
        getline(inputFile, line);

        i++;
    }

    // for (int k = 0; k < i; k++)
    // {
    //     cout << c1[k].name << endl;
    //     cout << c1[k].age << endl;
    //     cout << c1[k].mobileNo << endl;
    //     cout << c1[k].password << endl;
    //     cout << c1[k].customerId << endl
    //          << endl;
    // }
}

void customerDashBoard()
{
    int choice;
    validateCustomerAcc();
    Movie m;
    Customer c;
    system("clear");

    // User Interface starts

    do
    {
        cout << "\n";
        cout << mainHeading << mainHeading << "\n";
        cout << "||" << setw(58) << right << "CUSTOMER DASHBOARD" << "                                          ||\n";
        cout << mainHeading << mainHeading;

        cout << "\n\n";

        cout << "+------------------------------------------+\n";
        cout << "|              WHAT WOULD YOU LIKE         |\n";
        cout << "|                  TO DO?                  |\n";
        cout << "+------------------------------------------+\n\n";
        cout << "|  [1]  Check Movies                       |\n";
        cout << "|       Browse movies & show timings       |\n\n";
        cout << "|  [2]  Book Tickets                       |\n";
        cout << "|       Select seats & make payment        |\n\n";
        cout << "|  [3]  My Booked Tickets                  |\n";
        cout << "|       View your booking details          |\n\n";
        cout << "|  [4]  Update Information                 |\n";
        cout << "|       Manage your account details        |\n\n";
        cout << "|  [5]  Cancel Tickets                     |\n";
        cout << "|       Cancel booking & view charges      |\n\n";
        cout << "|  [6]  Back To Previous Menu              |\n";
        cout << "+------------------------------------------+\n";
        cout << "\n  " << leftSide
             << " Enter Your Choice => ";
        cin >> choice;
        // User Interface Ends

        switch (choice)
        {
        case 1:
            system("clear");
            m.printMovie();
            break;

        case 2:
            system("clear");
            c.bookTicketsMenu();
            break;

        case 6:
            system("clear");
            break;

        default:
            system("clear");
            cout << leftSide << " Invalid Choice " << RightSide;
            cout << lineSeperator;
            break;
        }
    } while (choice != 6);
    Enter_To_Continue();
}

void validateCustomerAcc()
{
    Customer c;
    int flag = 1;
    int response;
    long long int inputMobileNo;
    string password;

again:
    // User Interface Part Starts
    cout << '\n';
    cout << mainHeading;
    cout << "\n"
         << setw(38) << right << "CUSTOMER ACCOUNT\n";
    cout << mainHeading;

    cout << "\n\n"
         << RightSide << " Have You Signed In? " << leftSide;

    cout << "\n\n"
         << "       1.  Yes, I have an account\n\n"
         << "       2.  No, Create a new account\n";

    cout << lineSeperator;

    cout << "\n       Enter Your Choice => ";
    cin >> response;
    // User Interface Part Ends

    if (response == 1)
    {
        system("clear");

    reEnterMobileNo:
        cout << "Enter Your Mobile No => ";
        cin >> inputMobileNo;

        for (l = 0; l < i; l++)
        {
            if (c1[l].mobileNo == inputMobileNo)
            {
            repeatPassword:
                cout << "\nEnter Your Password => ";
                cin >> password;
                if (c1[l].password == password)
                {
                    return;
                }
                else
                {
                    system("clear");
                    cout << leftSide << " Invalid Password " << RightSide;
                    goto repeatPassword;
                }
            }
        }

        system("clear");
        cout << leftSide << " MOBILE NUMBER DOES NOT EXIST , PLEASE ENTER AGAIN " << RightSide << "\n\n";
        goto reEnterMobileNo;
    }

    else if (response == 2)
    {
        c.createAccount();
        system("clear");
        cout << left << "Account Created Successfully " << right
             << lineSeperator;
    }

    else
    {
        system("clear");
        cout << left << "Invalid Option Number " << right << endl;
        goto again;
    }
}

void adminDashboard()
{
    Admin a;
    Movie m;
    if (a.adminLogin() == 1)
        return;

    int choice;

    do
    {
        cout << "\n";
        cout << mainHeading;
        cout << "\n"
             << setw(42) << right
             << "ADMIN DASHBOARD\n";
        cout << mainHeading;

        cout << "\n\n"
             << "        +------------------------------------------+\n"
             << "        |               ADMIN MENU                 |\n"
             << "        +------------------------------------------+\n\n";
        cout << "        |  [1]  Movie Management                   |\n"
             << "        |       Add / View / Update / Delete       |\n\n";
        cout << "        |  [2]  Sales Analysis                     |\n"
             << "        |       Revenue / Tickets Sold / Top Movies|\n\n";
        cout << "        |  [3]  Booking And Seat Statistics        |\n"
             << "        |       Bookings / Occupied / Available    |\n\n";
        cout << "        |  [4]  Dynamic Ticket Pricing             |\n"
             << "        |       Set / Update Ticket Prices         |\n\n";
        cout << "        |  [5]  Exit                               |\n"
             << "        |       Return To Main Menu                |\n";
        cout << "        +------------------------------------------+\n";
        cout << "\n\n"
             << leftSide << " Enter Your Choice => ";

        cin >> choice;

        switch (choice)
        {
        case 1:
            system("clear");
            a.movieOperatons();
            break;

        case 5:
            system("clear");
            cout << leftSide << " Returning To Main Menu "
                 << RightSide << "\n";
            break;

        default:
            cout << "\n"
                 << leftSide << " Invalid Choice! Try Again "
                 << RightSide << "\n";
            break;
        }
    } while (choice != 5);
    Enter_To_Continue();
}

void loadMovieData()
{
    string line;
    ifstream file1("Day1_Movie_Details.txt");

    while (getline(file1, line))
    {
        day1[j].name = line.substr(7);
        getline(file1, line);
        day1[j].duration = stoi(line.substr(17));
        getline(file1, line);
        day1[j].screenNo = stoi(line.substr(12));
        getline(file1, line);
        day1[j].marvel = stof(line.substr(23));
        getline(file1, line);
        day1[j].royal = stof(line.substr(22));
        getline(file1, line);
        day1[j].recliner = stof(line.substr(25));
        getline(file1, line);
        day1[j].showHr = stoi(line.substr(21));

        if (day1[j].showHr >= 10)
            day1[j].showMins = stoi(line.substr(26));
        else
            day1[j].showMins = stoi(line.substr(25));
        getline(file1, line);
        day1[j].showNo = stoi(line.substr(11));

        getline(file1, line);
        j++;
    }
    file1.close();

    ifstream File2("Day2_Movie_Details.txt");

    while (getline(File2, line))
    {
        day2[k].name = line.substr(7);
        getline(File2, line);
        day2[k].duration = stoi(line.substr(17));
        getline(File2, line);
        day2[k].screenNo = stoi(line.substr(12));
        getline(File2, line);
        day2[k].marvel = stof(line.substr(23));
        getline(File2, line);
        day2[k].royal = stof(line.substr(22));
        getline(File2, line);
        day2[k].recliner = stof(line.substr(25));
        getline(File2, line);
        day2[k].showHr = stoi(line.substr(21));

        if (day2[k].showHr >= 10)
            day2[k].showMins = stoi(line.substr(26));
        else
            day2[k].showMins = stoi(line.substr(25));
        getline(File2, line);
        day2[k].showNo = stoi(line.substr(11));
        getline(File2, line);
        k++;
    }
    File2.close();
}

void loadMovieSeats()
{
    Movie m1;
    ifstream iFile, iFile1;
    string line;
    iFile.open("Day1MovieSeats.txt");
    j = 0;
    while (getline(iFile, line))
    {
        day1[j].showTrack = stoi(line.substr(8));
        for (int i = 0; i < 10; i++)
        {
            getline(iFile, line);
            day1[j].seats[m++] = line;
        }
        getline(iFile, line);
        day1[j].availableTickets = stoi(line.substr(26));
        getline(iFile, line);
        j++;
        m = 0;
    }
    iFile.close();

    iFile1.open("Day2MovieSeats.txt");

    k = 0;
    while (getline(iFile1, line))
    {
        day2[k].showTrack = stoi(line.substr(8));
        for (int i = 0; i < 10; i++)
        {
            getline(iFile1, line);
            day2[k].seats[n++] = line;
        }
        getline(iFile1, line);
        k++;
        n = 0;
    }
    iFile1.close();
}
