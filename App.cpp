#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
using namespace std;

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

int i = 0;        // Tracks the index of objects Os Customer Class
int j = 0, k = 0; // Tracks The Index Of Movie Object Day1 and Day2
int m = 0, n = 0; // Tracks The Index Of Character Of Seat Array Of Day1 And Day2 Object

void customerDashBoard();
void adminDashboard();
void accountValidation();
void loadData();
void loadMovieData();
void loadMovieSeats();

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
    string seats[10];
    int duration, screenNo;        // Movie Duration will be in total minutes
    float marvel, royal, recliner; // Ticket Pricing
    int showHr, showMins;          // Show That at what time show will start
    int showNo, dayNo;
    static int count;
    int showTrack;

public:
    void friend loadMovieSeats();
    void friend loadMovieData(); // Loads The Movie Infortmation At The Starting Of The Program
    void addMoive();
    void updateMovies();
    int printMovie();
    void printSeats(int val, int showNo);
    void printDay1Movies();
    void printDay2Movies();
    void loadSeats(int dayNo, int showNo);
    // void deleteMovies();
} day1[100], day2[100];

int Movie::count = 0;

void Movie::printSeats(int val, int showNo)
{
    Movie m;
    if (val == 1)
    {
        for (int k = 0; k < j; k++)
        {
            for (int i = 0; i < 10; i++)
            {
                for (int m = 0; m < 10; m++)
                {
                    cout << right << setw(5) << "X ";
                }
                cout << "\n";
            }
        }
        cout << "\n";
        cout << "\\________________________________________________/"
             << "\n             Screen This Side\n\n";
    }

    else
    {
        for (int j = 0; j < k; k++)
        {
            cout << "Show No : " << day2[j].showTrack << endl;
            for (int i = 0; i < 10; i++)
            {
                for (int m = 0; m < 10; m++)
                {
                    cout << day2[j].seats[i][m] << " ";
                }
                cout << "\n";
            }
        }
        cout << "\n";
    }
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

void Movie::updateMovies()
{
    int choice;
enterAgain:
    cout << "\n\n"
         << "        +----------------------------------------+\n"
         << "        |           UPDATE MOVIES                |\n"
         << "        +----------------------------------------+\n\n";
    cout << "        |  [1]  DAY 1                            |\n\n";
    cout << "        |  [2]  DAY 2                            |\n\n";
    cout << "        |  [3]  RETURN TO PREVIOUS MENU          |\n\n";
    cout << "        +----------------------------------------+\n"
         << leftSide << " Enter Your Choice => ";
    cin >> choice;
    if (choice > 3 || choice < 1)
    {
        system("clear");
        cout << leftSide << " Invalid Choice " << RightSide;
        goto enterAgain;
    }
}

int Movie::printMovie()
{
    int choice, choice1;
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
    }
    else if (choice1 == 2)
    {
        system("clear");
        m.printDay2Movies();
    }
    else if (choice1 == 3)
    {
        system("clear");
        m.printDay1Movies();
        m.printDay2Movies();
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
            m.updateMovies();
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
}

// Class Customer
class Customer
{
private:
    string name, movieSelected, MovieTime, password;
    int age, LastId;
    int customerId;
    long long int mobileNo;

public:
    void createAccount();

    friend void loadData();
    friend void accountValidation();

    void bookTickets();
    void bookForCurrentDayShows();
    void bookForNextDayShows();
    // void viewBookedTickets();
    // void updateInformation();
    // void cancelTickets();
} c1[10000];

void Customer::bookForCurrentDayShows()
{
    Movie m;
    int toalTickets, srNo;
    m.printDay1Movies();

enterAgain:
    cout << "Enter The Movie Sr No To Book Tickets =>";
    cin >> srNo;
    if (srNo >= j + 1 || srNo < 1)
    {
        cout << "\n\n";
        cout << leftSide << " Invalid Sr No , Enter Again " << RightSide;
        goto enterAgain;
    }

    cout << "\n\n";
    system("clear");
    m.printSeats(1, srNo - 1);
}

void Customer::bookTickets()
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
        bookForCurrentDayShows();
    }
    else if (choice == 2)
    {
        system("clear");
    }
    else if (choice == 3)
    {
        system("clear");
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
    loadData(); // Reloading Data After the new data get Enter
}

// Main Function
int main()
{
    system("clear");
    int choice;

    loadData();
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
void loadData()
{
    string line;
    ifstream inputFile("Customer_Account_Information.txt");
    if (!inputFile)
    {
        system("clear");
        cout << leftSide << "Unable To Open File / Or File Does Not Exist " << RightSide;
    }
    else
    {

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
}

void customerDashBoard()
{
    int choice;
    accountValidation();
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
            c.bookTickets();
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
}

void accountValidation()
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

        for (int k = 0; k < i; k++)
        {
            if (c1[k].mobileNo == inputMobileNo)
            {
            repeatPassword:
                cout << "\nEnter Your Password => ";
                cin >> password;
                if (c1[k].password == password)
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
}

void loadMovieData()
{
    string line;
    ifstream file1("Day1_Movie_Details.txt");
    if (!file1)
    {
        cout << leftSide << "Unable To Open File1 , Or File Does Not Exist" << RightSide << "\n"
             << lineSeperator;
    }

    else
    {
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
    }
    ifstream File2("Day2_Movie_Details.txt");
    if (!File2)
    {
        cout << leftSide << "Unable To Open File2 , Or File Does Not Exist" << RightSide << "\n"
             << lineSeperator;
    }

    else
    {
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
}

void loadMovieSeats()
{
    Movie m1;
    ifstream iFile;
    string line;
    iFile.open("Day1MovieSeats.txt");
    if (!iFile)
    {
        system("clear");
        cout << leftSide << "Unable to open the file  Day1MovieSeats/ or file does not exist" << RightSide << endl;
    }

    else
    {
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
            j++;
        }
        iFile.close();
    }

    iFile.open("Day2MovieSeats.txt");
    if (!iFile)
    {
        system("clear");
        cout << leftSide << "Unable to open the file Day2MovieSeats / or file does not exist" << RightSide << endl;
    }

    else
    {
        k = 0;
        while (getline(iFile, line))
        {
            day2[k].showTrack = stoi(line.substr(8));
            for (int i = 0; i < 10; i++)
            {
                getline(iFile, line);
                day2[k].seats[n++] = line;
            }
            getline(iFile, line);
            k++;
        }
        iFile.close();
    }
}
