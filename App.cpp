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
int s = 0;        // Tracks The Index Of Booked Tickets Of Current User Logged In

void customerDashBoard();
void adminDashboard();
void loadMovieData();
void loadMovieSeats();
void loadCustomerData();
void loadBookedTickets();
void validateCustomerAcc();

// Class Customer
class Customer
{
private:
    string name, movieSelected, password, bookedSeats[20], showDuration, showTime;
    int age, LastId;
    int customerId, screenNo;
    long long int mobileNo;
    int showNo, dayNo;

public:
    float billAmount;
    void createAccount();

    friend void loadBookedTickets();
    friend void loadCustomerData();
    friend void validateCustomerAcc();

    void bookTicketsMenu();
    void bookTickets(int DayNo);
    void viewBookedTickets();
} c1[10000];

/*
Read Data from The File As Soon As Program Starts
Make 2D array of the object where each column represents the show and row represents the
details of each unique movie
*/
// Movie Class
class Movie
{
public:
    int duration, screenNo;        // Movie Duration will be in total minutes
    float marvel, royal, recliner; // Ticket Pricing
    int showHr, showMins;          // Show That at what time show will start
    int showNo, dayNo;
    static int count;

    string name;
    string seats[10];
    int availableTickets;
    int friend validateSeat(char row, int column, int showNo, int dayNo);
    void friend loadMovieSeats(); // Loads The Movie Seats At The Starting Of The Program
    void friend loadMovieData();  // Loads The Movie Infortmation At The Starting Of The Program

    void addMoive();
    void updateMovies();
    void deleteMovies();
    int printMovie();
    void printSeatsAndInformation(int val, int showNo);
    void printDay1Movies();
    void printDay2Movies();
    void loadSeats(int dayNo, int showNo, int flag);
} day1[100], day2[100];

int Movie::count = 0;

bool saveMovieDetails(int dayNo, int skippedIndex);
bool saveMovieSeats(int dayNo, int skippedIndex);

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
void Movie::loadSeats(int dayNo, int showNo, int flag = 0)
{
    ofstream oFile;
    if (flag == 0)
    {

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
        oFile << "\n\n";
        oFile.close();
    }

    else if (flag == 1)
    {
        if (dayNo == 1)
        {
            oFile.open("Day1MovieSeats.txt");
            cout << "Show No => " << showNo << endl;
            for (int k = 0; k < j; k++)
            {
                oFile << "Show No: " << day1[k].showNo << "\n";
                for (int i = 0; i < 10; i++)
                {
                    for (int p = 0; p < 10; p++)
                    {

                        if (day1[k].seats[i][p] == 'O')
                            oFile << 'O';
                        else
                            oFile << 'X';
                    }
                    oFile << "\n";
                }
                oFile << "Total Available Tickets => " << day1[k].availableTickets;

                oFile << "\n\n";
            }
            oFile.close();
        }
        else
        {

            oFile.open("Day2MovieSeats.txt");

            cout << "Show No => " << showNo << endl;
            for (int j = 0; j < k; j++)
            {
                oFile << "Show No: " << day2[j].showNo << "\n";
                for (int i = 0; i < 10; i++)
                {
                    for (int p = 0; p < 10; p++)
                    {

                        if (day2[j].seats[i][p] == 'O')
                            oFile << 'O';
                        else
                            oFile << 'X';
                    }
                    oFile << "\n";
                }
                oFile << "Total Available Tickets => " << day2[j].availableTickets;

                oFile << "\n\n";
            }
            oFile.close();
        }
    }
}

bool saveMovieDetails(int dayNo, int skippedIndex)
{
    ofstream outputFile;
    Movie *movies;
    int totalMovies;

    if (dayNo == 1)
    {
        outputFile.open("Day1_Movie_Details.txt");
        movies = day1;
        totalMovies = j;
    }
    else
    {
        outputFile.open("Day2_Movie_Details.txt");
        movies = day2;
        totalMovies = k;
    }

    if (!outputFile)
        return false;

    for (int movieNo = 0; movieNo < totalMovies; movieNo++)
    {
        if (movieNo == skippedIndex)
            continue;

        outputFile << "Name =>" << movies[movieNo].name
                   << "\nMovie Duration => " << movies[movieNo].duration
                   << "\nScreen No => " << movies[movieNo].screenNo
                   << "\nPrice Of Marvel Seat => " << movies[movieNo].marvel
                   << "\nPrice Of Royal Seat => " << movies[movieNo].royal
                   << "\nPrice Of Recliner Seat => " << movies[movieNo].recliner
                   << "\nShow Starting Time => " << movies[movieNo].showHr << " : " << movies[movieNo].showMins
                   << "\nShow No => " << movies[movieNo].showNo << "\n\n";
    }

    outputFile.close();
    return outputFile.good();
}

bool saveMovieSeats(int dayNo, int skippedIndex)
{
    ofstream outputFile;
    Movie *movies;
    int totalMovies;
    string fileName;

    if (dayNo == 1)
    {
        fileName = "Day1MovieSeats.txt";
        movies = day1;
        totalMovies = j;
    }
    else
    {
        fileName = "Day2MovieSeats.txt";
        movies = day2;
        totalMovies = k;
    }

    outputFile.open(fileName.c_str());
    if (!outputFile)
        return false;

    for (int movieNo = 0; movieNo < totalMovies; movieNo++)
    {
        if (movieNo == skippedIndex)
            continue;

        outputFile << "Show No: " << movies[movieNo].showNo << "\n";
        for (int row = 0; row < 10; row++)
        {
            for (int column = 0; column < 10; column++)
            {
                if (movies[movieNo].seats[row][column] == 'O')
                    outputFile << 'O';
                else
                    outputFile << 'X';
            }
            outputFile << "\n";
        }
        outputFile << "Total Available Tickets => " << movies[movieNo].availableTickets << "\n\n";
    }

    outputFile.close();
    return outputFile.good();
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
    m = 0;
    loadMovieData();
    loadMovieSeats();
    Enter_To_Continue();
}

void Movie::updateMovies()
{
    int dayNo, showNo, totalMovies;
    Movie *movies;

    cout << "\n"
         << mainHeading << "\n"
         << setw(37) << right << "UPDATE MOVIE DETAILS\n"
         << mainHeading << "\n\n"
         << "        +--------------------------------------+\n"
         << "        |             SELECT SHOW DAY          |\n"
         << "        +--------------------------------------+\n"
         << "        |  [1]  Current Day                    |\n"
         << "        |  [2]  Next Day                       |\n"
         << "        +--------------------------------------+\n\n"
         << leftSide << " Select Day => ";
    cin >> dayNo;

    if (dayNo == 1)
    {
        movies = day1;
        totalMovies = j;
        printDay1Movies();
    }
    else if (dayNo == 2)
    {
        movies = day2;
        totalMovies = k;
        printDay2Movies();
    }
    else
    {
        cout << "\n" << leftSide << " Invalid Day Choice " << RightSide << endl;
        return;
    }

    if (totalMovies == 0)
    {
        cout << "\n" << leftSide << " No Movies Available For The Selected Day " << RightSide << endl;
        return;
    }

    cout << "\n" << leftSide << " Enter Movie Sr No To Update => ";
    cin >> showNo;
    if (showNo < 1 || showNo > totalMovies)
    {
        cout << "\n" << leftSide << " Invalid Movie Sr No " << RightSide << endl;
        return;
    }
    showNo--;

    Movie updatedMovie = movies[showNo];
    cout << "\n"
         << string(WIDTH, '-') << "\n"
         << setw(37) << right << "CURRENT MOVIE DETAILS\n"
         << string(WIDTH, '-') << "\n"
         << left << setw(23) << "Movie Name" << ": " << updatedMovie.name
         << "\n" << left << setw(23) << "Duration" << ": " << updatedMovie.duration << " minutes"
         << "\n" << left << setw(23) << "Screen No" << ": " << updatedMovie.screenNo
         << "\n" << left << setw(23) << "Marvel Seat Price" << ": Rs. " << updatedMovie.marvel
         << "\n" << left << setw(23) << "Royal Seat Price" << ": Rs. " << updatedMovie.royal
         << "\n" << left << setw(23) << "Recliner Seat Price" << ": Rs. " << updatedMovie.recliner
         << "\n" << left << setw(23) << "Show Time" << ": "
         << setw(2) << setfill('0') << updatedMovie.showHr << ":"
         << setw(2) << updatedMovie.showMins << setfill(' ') << "\n"
         << string(WIDTH, '-') << "\n\n";

    cin.ignore();
movieNameAgain:
    cout << leftSide << " Enter Movie Name => ";
    getline(cin, updatedMovie.name);
    if (updatedMovie.name.empty())
    {
        cout << leftSide << " Movie Name Cannot Be Empty " << RightSide << endl
             << endl;
        goto movieNameAgain;
    }
    updatedMovie.name = " " + updatedMovie.name;

durationAgain:
    cout << leftSide << " Enter Duration In Minutes (At Least 60) => ";
    cin >> updatedMovie.duration;
    if (updatedMovie.duration < 60)
    {
        cout << leftSide << " Movie Duration Should Be Atleast 60 Minutes " << RightSide << endl
             << endl;
        goto durationAgain;
    }

screenAgain:
    cout << leftSide << " Enter Screen No => ";
    cin >> updatedMovie.screenNo;
    if (updatedMovie.screenNo <= 0)
    {
        cout << leftSide << " Screen No Should Be Greater Than 0 " << RightSide << endl
             << endl;
        goto screenAgain;
    }

marvelAgain:
    cout << leftSide << " Enter Marvel Seat Price (Minimum Rs.150) => ";
    cin >> updatedMovie.marvel;
    if (updatedMovie.marvel < 150)
    {
        cout << leftSide << " Marvel Seat Price Must Be Atleast Rs.150 " << RightSide << endl
             << endl;
        goto marvelAgain;
    }

royalAgain:
    cout << leftSide << " Enter Royal Seat Price (Greater Than Marvel) => ";
    cin >> updatedMovie.royal;
    if (updatedMovie.royal <= updatedMovie.marvel)
    {
        cout << leftSide << " Royal Seat Price Must Be Greater Than Marvel Seat Price " << RightSide << endl
             << endl;
        goto royalAgain;
    }

reclinerAgain:
    cout << leftSide << " Enter Recliner Seat Price (Greater Than Royal) => ";
    cin >> updatedMovie.recliner;
    if (updatedMovie.recliner <= updatedMovie.royal)
    {
        cout << leftSide << " Recliner Seat Price Must Be Greater Than Royal Seat Price " << RightSide << endl
             << endl;
        goto reclinerAgain;
    }

showHourAgain:
    cout << leftSide << " Enter Show Starting Hour (0-24) => ";
    cin >> updatedMovie.showHr;
    if (updatedMovie.showHr > 24 || updatedMovie.showHr < 0)
    {
        cout << leftSide << " Starting Hour Must Be Between 0 And 24 " << RightSide << endl
             << endl;
        goto showHourAgain;
    }

showMinutesAgain:
    cout << leftSide << " Enter Show Starting Minutes (0-60) => ";
    cin >> updatedMovie.showMins;
    if (updatedMovie.showMins > 60 || updatedMovie.showMins < 0)
    {
        cout << leftSide << " Starting Minutes Must Be Between 0 And 60 " << RightSide << endl
             << endl;
        goto showMinutesAgain;
    }

    Movie previousMovie = movies[showNo];
    movies[showNo] = updatedMovie;
    if (!saveMovieDetails(dayNo, -1))
    {
        movies[showNo] = previousMovie;
        cout << "\n" << leftSide << " Unable To Save Movie Details " << RightSide << endl;
        return;
    }

    j = 0;
    k = 0;
    loadMovieData();
    loadMovieSeats();
    cout << "\n"
         << string(WIDTH, '-') << "\n"
         << leftSide << " Movie Details Updated Successfully " << RightSide << "\n"
         << string(WIDTH, '-') << endl;
    Enter_To_Continue();
}

void Movie::deleteMovies()
{
    int dayNo, showNo, totalMovies;
    Movie *movies;
    char confirmation;

    cout << "\n"
         << mainHeading << "\n"
         << setw(37) << right << "DELETE MOVIE SHOW\n"
         << mainHeading << "\n\n"
         << "        +--------------------------------------+\n"
         << "        |             SELECT SHOW DAY          |\n"
         << "        +--------------------------------------+\n"
         << "        |  [1]  Current Day                    |\n"
         << "        |  [2]  Next Day                       |\n"
         << "        +--------------------------------------+\n\n"
         << leftSide << " Select Day => ";
    cin >> dayNo;

    if (dayNo == 1)
    {
        movies = day1;
        totalMovies = j;
        printDay1Movies();
    }
    else if (dayNo == 2)
    {
        movies = day2;
        totalMovies = k;
        printDay2Movies();
    }
    else
    {
        cout << "\n" << leftSide << " Invalid Day Choice " << RightSide << endl;
        return;
    }

    if (totalMovies == 0)
    {
        cout << "\n" << leftSide << " No Movies Available For The Selected Day " << RightSide << endl;
        return;
    }

    cout << "\n" << leftSide << " Enter Movie Sr No To Delete => ";
    cin >> showNo;
    if (showNo < 1 || showNo > totalMovies)
    {
        cout << "\n" << leftSide << " Invalid Movie Sr No " << RightSide << endl;
        return;
    }
    showNo--;

    if (movies[showNo].availableTickets != 20)
    {
        cout << "\n"
             << leftSide << " Cannot Delete This Show: Tickets Have Already Been Booked " << RightSide << endl
             << leftSide << " Booked Seats Must Be Preserved " << RightSide << endl;
        return;
    }

    cout << "\n"
         << string(WIDTH, '-') << "\n"
         << leftSide << " Delete \"" << movies[showNo].name << "\"? (Y/N) => ";
    cin >> confirmation;
    if (confirmation != 'Y' && confirmation != 'y')
    {
        cout << "\n" << leftSide << " Movie Deletion Cancelled " << RightSide << endl;
        return;
    }

    if (!saveMovieDetails(dayNo, showNo))
    {
        cout << "\n" << leftSide << " Unable To Save Movie Details " << RightSide << endl;
        return;
    }
    if (!saveMovieSeats(dayNo, showNo))
    {
        cout << "\n" << leftSide << " Unable To Save Movie Seat Data " << RightSide << endl;
        return;
    }

    for (int movieNo = showNo; movieNo < totalMovies - 1; movieNo++)
        movies[movieNo] = movies[movieNo + 1];

    if (dayNo == 1)
        j--;
    else
        k--;

    j = 0;
    k = 0;
    loadMovieData();
    loadMovieSeats();
    cout << "\n"
         << string(WIDTH, '-') << "\n"
         << leftSide << " Movie Show Deleted Successfully " << RightSide << "\n"
         << string(WIDTH, '-') << endl;
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
    void checkTotalRevenue();
    void dynamicTicketPricing();
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

        case 4:
            system("clear");
            m.deleteMovies();
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

void Admin::checkTotalRevenue()
{
    float totalRevenue = 0;
    int totalBookings = 0;
    int estimatedBookings = 0;
    string line, mobileLine, movieLine, screenLine, showLine;
    string dayLine, timeLine, durationLine, ticketsLine, amountLine;

    for (int fileNo = 1; fileNo <= 2; fileNo++)
    {
        ifstream inputFile;
        if (fileNo == 1)
            inputFile.open("Day1_Booked_Tickets.txt");
        else
            inputFile.open("Day2_Booked_Tickets.txt");

        if (!inputFile)
            continue;

        while (getline(inputFile, line))
        {
            if (line.substr(0, 16) != "Customer Name =>")
                continue;

            if (!getline(inputFile, mobileLine) ||
                !getline(inputFile, movieLine) ||
                !getline(inputFile, screenLine) ||
                !getline(inputFile, showLine) ||
                !getline(inputFile, dayLine) ||
                !getline(inputFile, timeLine) ||
                !getline(inputFile, durationLine) ||
                !getline(inputFile, ticketsLine))
                break;

            amountLine.clear();
            if (getline(inputFile, amountLine) && amountLine.substr(0, 16) == "Total Amount => ")
            {
                totalRevenue += stof(amountLine.substr(16));
            }
            else
            {
                int showNo = stoi(showLine.substr(11));
                int totalMovies;

                if (fileNo == 1)
                    totalMovies = j;
                else
                    totalMovies = k;

                for (int movieNo = 0; movieNo < totalMovies; movieNo++)
                {
                    if ((fileNo == 1 && day1[movieNo].showNo == showNo) ||
                        (fileNo == 2 && day2[movieNo].showNo == showNo))
                    {
                        string bookedSeats = ticketsLine.substr(17);
                        for (string::size_type seatNo = 0; seatNo < bookedSeats.length(); seatNo++)
                        {
                            if (bookedSeats[seatNo] == ' ' || (seatNo > 0 && bookedSeats[seatNo - 1] != ' '))
                                continue;

                            char row = bookedSeats[seatNo];
                            if (fileNo == 1)
                            {
                                if (row == 'A' || row == 'a' || row == 'B' || row == 'b')
                                    totalRevenue += day1[movieNo].recliner;
                                else if ((row >= 'C' && row <= 'G') || (row >= 'c' && row <= 'g'))
                                    totalRevenue += day1[movieNo].royal;
                                else if ((row >= 'H' && row <= 'J') || (row >= 'h' && row <= 'j'))
                                    totalRevenue += day1[movieNo].marvel;
                            }
                            else
                            {
                                if (row == 'A' || row == 'a' || row == 'B' || row == 'b')
                                    totalRevenue += day2[movieNo].recliner;
                                else if ((row >= 'C' && row <= 'G') || (row >= 'c' && row <= 'g'))
                                    totalRevenue += day2[movieNo].royal;
                                else if ((row >= 'H' && row <= 'J') || (row >= 'h' && row <= 'j'))
                                    totalRevenue += day2[movieNo].marvel;
                            }
                        }
                        estimatedBookings++;
                        break;
                    }
                }
            }
            totalBookings++;
        }
    }

    cout << "\n"
         << mainHeading << "\n"
         << setw(36) << right << "TOTAL REVENUE REPORT\n"
         << mainHeading << "\n\n"
         << left << setw(24) << "Total Bookings" << ": " << totalBookings << "\n"
         << left << setw(24) << "Total Revenue" << ": Rs. "
         << fixed << setprecision(2) << totalRevenue << "\n";
    if (estimatedBookings > 0)
        cout << "\n" << leftSide << " " << estimatedBookings
             << " Older Booking(s) Estimated Using Current Ticket Prices " << RightSide << "\n";
    if (totalBookings == 0)
        cout << "\n" << leftSide << " No Booking Records Found " << RightSide << "\n";
    cout << endl;
    Enter_To_Continue();
}

void Admin::dynamicTicketPricing()
{
    int dayNo, showNo;
    float marvelPrice, royalPrice, reclinerPrice;
    int totalMovies;
    string fileName;
    ofstream outputFile;

    cout << "\n"
         << mainHeading << "\n"
         << setw(39) << right << "DYNAMIC TICKET PRICING\n"
         << mainHeading << "\n\n"
         << "        +--------------------------------------+\n"
         << "        |             SELECT SHOW DAY          |\n"
         << "        +--------------------------------------+\n"
         << "        |  [1]  Current Day                    |\n"
         << "        |  [2]  Next Day                       |\n"
         << "        +--------------------------------------+\n\n"
         << leftSide << " Select Day => ";
    cin >> dayNo;

    if (dayNo == 1)
    {
        totalMovies = j;
        fileName = "Day1_Movie_Details.txt";
        m.printDay1Movies();
    }
    else if (dayNo == 2)
    {
        totalMovies = k;
        fileName = "Day2_Movie_Details.txt";
        m.printDay2Movies();
    }
    else
    {
        cout << "\n" << leftSide << " Invalid Day Choice " << RightSide << endl;
        return;
    }

    if (totalMovies == 0)
    {
        cout << "\n" << leftSide << " No Movies Available For The Selected Day " << RightSide << endl;
        return;
    }

    cout << "\n" << leftSide << " Enter Movie Sr No To Update => ";
    cin >> showNo;
    if (showNo < 1 || showNo > totalMovies)
    {
        cout << "\n" << leftSide << " Invalid Movie Sr No " << RightSide << endl;
        return;
    }
    showNo--;

    cout << "\n"
         << string(WIDTH, '-') << "\n"
         << setw(39) << right << "CURRENT TICKET PRICES\n"
         << string(WIDTH, '-') << "\n";
    if (dayNo == 1)
    {
        cout << left << setw(23) << "Marvel Seat" << right << "Rs. " << day1[showNo].marvel
             << "\n" << left << setw(23) << "Royal Seat" << right << "Rs. " << day1[showNo].royal
             << "\n" << left << setw(23) << "Recliner Seat" << right << "Rs. " << day1[showNo].recliner << endl;
    }
    else
    {
        cout << left << setw(23) << "Marvel Seat" << right << "Rs. " << day2[showNo].marvel
             << "\n" << left << setw(23) << "Royal Seat" << right << "Rs. " << day2[showNo].royal
             << "\n" << left << setw(23) << "Recliner Seat" << right << "Rs. " << day2[showNo].recliner << endl;
    }
    cout << string(WIDTH, '-') << "\n\n"
         << setw(35) << right << "ENTER NEW TICKET PRICES\n\n";

marvelPriceAgain:
    cout << leftSide << " Marvel Seat (Minimum Rs.150) => ";
    cin >> marvelPrice;
    if (marvelPrice < 150)
    {
        cout << leftSide << " Marvel Seat Price Must Be Atleast Rs.150 " << RightSide << endl
             << endl;
        goto marvelPriceAgain;
    }

royalPriceAgain:
    cout << leftSide << " Royal Seat (Greater Than Marvel) => ";
    cin >> royalPrice;
    if (royalPrice <= marvelPrice)
    {
        cout << leftSide << " Royal Seat Price Must Be Greater Than Marvel Seat Price " << RightSide << endl
             << endl;
        goto royalPriceAgain;
    }

reclinerPriceAgain:
    cout << leftSide << " Recliner Seat (Greater Than Royal) => ";
    cin >> reclinerPrice;
    if (reclinerPrice <= royalPrice)
    {
        cout << leftSide << " Recliner Seat Price Must Be Greater Than Royal Seat Price " << RightSide << endl
             << endl;
        goto reclinerPriceAgain;
    }

    outputFile.open(fileName.c_str());
    if (!outputFile)
    {
        cout << "\n" << leftSide << " Unable To Update Movie Details File " << RightSide << endl;
        return;
    }

    if (dayNo == 1)
    {
        day1[showNo].marvel = marvelPrice;
        day1[showNo].royal = royalPrice;
        day1[showNo].recliner = reclinerPrice;
        for (int movieNo = 0; movieNo < j; movieNo++)
        {
            outputFile << "Name =>" << day1[movieNo].name
                       << "\nMovie Duration => " << day1[movieNo].duration
                       << "\nScreen No => " << day1[movieNo].screenNo
                       << "\nPrice Of Marvel Seat => " << day1[movieNo].marvel
                       << "\nPrice Of Royal Seat => " << day1[movieNo].royal
                       << "\nPrice Of Recliner Seat => " << day1[movieNo].recliner
                       << "\nShow Starting Time => " << day1[movieNo].showHr << " : " << day1[movieNo].showMins
                       << "\nShow No => " << day1[movieNo].showNo << "\n\n";
        }
    }
    else
    {
        day2[showNo].marvel = marvelPrice;
        day2[showNo].royal = royalPrice;
        day2[showNo].recliner = reclinerPrice;
        for (int movieNo = 0; movieNo < k; movieNo++)
        {
            outputFile << "Name =>" << day2[movieNo].name
                       << "\nMovie Duration => " << day2[movieNo].duration
                       << "\nScreen No => " << day2[movieNo].screenNo
                       << "\nPrice Of Marvel Seat => " << day2[movieNo].marvel
                       << "\nPrice Of Royal Seat => " << day2[movieNo].royal
                       << "\nPrice Of Recliner Seat => " << day2[movieNo].recliner
                       << "\nShow Starting Time => " << day2[movieNo].showHr << " : " << day2[movieNo].showMins
                       << "\nShow No => " << day2[movieNo].showNo << "\n\n";
        }
    }

    outputFile.close();
    if (!outputFile)
    {
        cout << "\n" << leftSide << " Error While Saving Ticket Prices " << RightSide << endl;
        return;
    }
    j = 0;
    k = 0;
    loadMovieData();
    cout << "\n"
         << string(WIDTH, '-') << "\n"
         << leftSide << " Ticket Prices Updated And Saved Successfully " << RightSide << "\n"
         << string(WIDTH, '-') << endl;
}

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

    // Resting Bill Amount To 0 When A Customer Book New Tickets
    c1[l].billAmount = 0;
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
        if (totalTickets > day1[srNo - 1].availableTickets || totalTickets <= 0)
        {
            cout << leftSide << "The Number Of Tickets Your Want Are More Than The Total Tickets Available " << RightSide << endl;
            goto reEnterTotalTickets;
        }
    }

    else
    {
        if (totalTickets > day2[srNo - 1].availableTickets || totalTickets <= 0)
        {
            cout << leftSide << "The Number Of Tickets Your Want Are More Than The Total Tickets Available " << RightSide << endl;
            goto reEnterTotalTickets;
        }
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
                    day2[srNo - 1].seats[9][column - 1] = 'O';
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

        // Calculating Bill
        if (dayNo == 1)
        {

            c1[l].bookedSeats[a++] = row + to_string(column);
            if (row == 'A' || row == 'a' || row == 'B' || row == 'b')
                c1[l].billAmount += day1[srNo - 1].recliner;

            else if ((row >= 'C' && row <= 'G') || (row >= 'c' && row <= 'g'))
            {
                c1[l].billAmount += day1[srNo - 1].royal;
            }

            else if (row >= 'H' && row <= 'J' || row >= 'h' && row <= 'j')
                c1[l].billAmount += day1[srNo - 1].marvel;

            day1[srNo - 1].availableTickets--;
        }

        else
        {
            c1[l].bookedSeats[a++] = row + to_string(column);
            if (row == 'A' || row == 'a' || row == 'B' || row == 'b')
                c1[l].billAmount += day2[srNo - 1].recliner;

            else if (row >= 'C' && row <= 'G' || row >= 'c' && row <= 'g')
            {
                c1[l].billAmount += day2[srNo - 1].royal;
            }

            else
                c1[l].billAmount += day2[srNo - 1].marvel;
            day2[srNo - 1].availableTickets--;
        }
    }

    cout << "\n\n";
    cout << "================================================\n";
    cout << "              MOVIE TICKET BILL                 \n";
    cout << "================================================\n\n";
    if (dayNo == 1)
    {

        cout << "  Movie Name       : " << day1[srNo - 1].name << endl;
        cout << "  Screen No        : " << day1[srNo - 1].screenNo << endl;
        cout << "  Show No          : " << day1[srNo - 1].showNo << endl;
        cout << "  Day No           : " << dayNo << endl;
        cout << "  Show Duration    : " << day1[srNo - 1].duration << endl;
        cout << "  Show Time        : "
             << day1[srNo - 1].showHr << ":"
             << setw(2) << setfill('0') << day1[srNo - 1].showMins
             << setfill(' ') << endl;
        cout << "------------------------------------------------\n";
        cout << "  Total Tickets    : ";
        for (int i = 0; i < a; i++)
            cout << c1[l].bookedSeats[i] << " ";
        cout << endl;
        cout << "------------------------------------------------\n";
        cout << "  TOTAL AMOUNT     : Rs. " << c1[l].billAmount << endl;
    }

    else
    {
        cout << "  Movie Name       : " << day2[srNo - 1].name << endl;
        cout << "  Screen No        : " << day2[srNo - 1].screenNo << endl;
        cout << "  Show No          : " << day2[srNo - 1].showNo << endl;
        cout << "  Day No           : " << day2[srNo - 1].dayNo << endl;
        cout << "  Show Duration    : " << day2[srNo - 1].duration << endl;
        cout << "  Show Time        : "
             << day2[srNo - 1].showHr << ":"
             << setw(2) << setfill('0') << day2[srNo - 1].showMins
             << setfill(' ') << endl;
        cout << "------------------------------------------------\n";
        cout << "  Total Tickets    : ";
        for (int i = 0; i < a; i++)
            cout << c1[l].bookedSeats[i] << " ";
        cout << endl;
        cout << "------------------------------------------------\n";
        cout << "  TOTAL AMOUNT     : Rs. " << c1[l].billAmount << endl;
    }
    cout << "================================================\n";
    cout << "          THANK YOU! ENJOY YOUR MOVIE            \n";
    cout << "================================================\n";

    if (dayNo == 1)
    {
        ofstream oFile("Day1_Booked_Tickets.txt", ios::app);

        oFile << "Customer Name => " << c1[l].name << endl;
        oFile << "Mobile No: " << c1[l].mobileNo << endl;
        oFile << "Movie Name => " << day1[srNo - 1].name << endl;
        oFile << "Screen No => " << day1[srNo - 1].screenNo << endl;
        oFile << "Show No => " << day1[srNo - 1].showNo << endl;
        oFile << "Day No => " << dayNo << endl;
        oFile << "Show Time => " << day1[srNo - 1].showHr << ":" << day1[srNo - 1].showMins;
        oFile << "\nShow Duration => " << day1[srNo - 1].duration;
        oFile << "\nTotal Tickets => ";
        for (int i = 0; i < a; i++)
            oFile << c1[l].bookedSeats[i] << " ";
        oFile << "\nTotal Amount => " << fixed << setprecision(2) << c1[l].billAmount << "\n\n";
        oFile.close();

        m.loadSeats(dayNo, srNo - 1, 1); // Last Parameter is flag
    }

    else
    {
        ofstream oFile("Day2_Booked_Tickets.txt", ios::app);

        oFile << "Customer Name => " << c1[l].name << endl;
        oFile << "Mobile No: " << c1[l].mobileNo << endl;
        oFile << "Movie Name => " << day2[srNo - 1].name << endl;
        oFile << "Screen No => " << day2[srNo - 1].screenNo << endl;
        oFile << "Show No => " << day2[srNo - 1].showNo << endl;
        oFile << "Day No => " << dayNo << endl;
        oFile << "Show Time => " << day2[srNo - 1].showHr << ":" << day2[srNo - 1].showMins;
        oFile << "\nShow Duration => " << day2[srNo - 1].duration;
        oFile << "\nTotal Tickets => ";
        for (int i = 0; i < a; i++)
            oFile << c1[l].bookedSeats[i] << " ";
        oFile << "\nTotal Amount => " << fixed << setprecision(2) << c1[l].billAmount << "\n\n";
        oFile.close();

        m.loadSeats(dayNo, srNo - 1, 1); // Last Parameter is flag
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
        bookTickets(2);
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

void Customer::viewBookedTickets()
{
    ifstream inputFile;
    string line, mobileLine, movieLine, screenLine, showLine;
    string dayLine, timeLine, durationLine, ticketsLine, ticketSeats;
    int bookingNo = 0;

    cout << "\n"
         << mainHeading << "\n"
         << setw(39) << right << "MY BOOKED TICKETS\n"
         << mainHeading << "\n";

    for (int fileNo = 1; fileNo <= 2; fileNo++)
    {
        inputFile.clear();
        if (fileNo == 1)
            inputFile.open("Day1_Booked_Tickets.txt");
        else
            inputFile.open("Day2_Booked_Tickets.txt");

        if (!inputFile)
        {
            if (fileNo == 1)
                cout << "\n" << leftSide << " Unable To Open Day 1 Booking File " << RightSide << endl;
            continue;
        }

        while (getline(inputFile, line))
        {
            if (line.substr(0, 16) != "Customer Name =>")
                continue;

            if (!getline(inputFile, mobileLine) ||
                !getline(inputFile, movieLine) ||
                !getline(inputFile, screenLine) ||
                !getline(inputFile, showLine) ||
                !getline(inputFile, dayLine) ||
                !getline(inputFile, timeLine) ||
                !getline(inputFile, durationLine) ||
                !getline(inputFile, ticketsLine))
                break;

            if (stoll(mobileLine.substr(11)) != c1[l].mobileNo)
                continue;

            bookingNo++;
            int ticketCount = 0;
            ticketSeats = ticketsLine.substr(17);
            for (string::size_type seatNo = 0; seatNo < ticketSeats.length(); seatNo++)
            {
                if (ticketSeats[seatNo] != ' ' && (seatNo == 0 || ticketSeats[seatNo - 1] == ' '))
                    ticketCount++;
            }

            cout << "\n"
                 << string(WIDTH, '=') << "\n"
                 << setw(35) << right << "BOOKING " << bookingNo << "\n"
                 << string(WIDTH, '-') << "\n"
                 << left << setw(18) << "Customer" << ": " << line.substr(17) << "\n"
                 << left << setw(18) << "Movie" << ": " << movieLine.substr(14) << "\n"
                 << left << setw(18) << "Screen" << ": " << screenLine.substr(13) << "\n"
                 << left << setw(18) << "Show No" << ": " << showLine.substr(11) << "\n"
                 << left << setw(18) << "Day" << ": " << dayLine.substr(10) << "\n"
                 << left << setw(18) << "Show Time" << ": " << timeLine.substr(13) << "\n"
                 << left << setw(18) << "Duration" << ": " << durationLine.substr(17) << " minutes\n"
                 << left << setw(18) << "Tickets" << ": " << ticketCount << "\n"
                 << left << setw(18) << "Seat Numbers" << ": " << ticketSeats << "\n"
                 << string(WIDTH, '=') << "\n";
        }
        inputFile.close();
    }

    if (bookingNo == 0)
        cout << "\n" << leftSide << " No Booked Tickets Found " << RightSide << endl;

    Enter_To_Continue();
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
        cout << "|  [4]  Back To Previous Menu              |\n";
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

        case 3:
            system("clear");
            c.viewBookedTickets();
            break;
        case 5:
            system("clear");
            break;

        default:
            system("clear");
            cout << leftSide << " Invalid Choice " << RightSide;
            cout << lineSeperator;
            break;
        }
    } while (choice != 4);
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
        cout << "        |  [2]  Check Total Revenue                |\n";
        cout << "        |  [3]  Dynamic Ticket Pricing             |\n"
             << "        |       Update Ticket Prices               |\n\n";
        cout << "        |  [4]  Exit                               |\n"
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

        case 2:
            system("clear");
            a.checkTotalRevenue();
            break;

        case 3:
            system("clear");
            a.dynamicTicketPricing();
            break;

        case 4:
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
    } while (choice != 4);
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
    m = 0;
    while (getline(iFile, line))
    {
        for (int i = 0; i <= 9; i++)
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
        for (int i = 0; i < 10; i++)
        {
            getline(iFile1, line);
            day2[k].seats[n++] = line;
        }
        getline(iFile1, line);
        day2[k].availableTickets = stoi(line.substr(26));
        getline(iFile1, line);
        k++;
        n = 0;
    }
    iFile1.close();
}

void loadBookedTickets()
{
    long long int mobileNo;
    string line;
    ifstream iFile, iFile1;
    iFile.open("Day1_Booked_Tickets.txt");
    while (getline(iFile, line))
    {
        getline(iFile, line);
        mobileNo = stoll(line.substr(15));
        for (int i = 0; i < l; i++)
        {
            if (c1[i].mobileNo == mobileNo)
            {
                getline(iFile, line);
                c1[i].movieSelected = line.substr(16);

                getline(iFile, line);
                c1[i].screenNo = stoi(line.substr(12));

                getline(iFile, line);
                getline(iFile, line);

                getline(iFile, line);
                c1[i].showTime = line.substr(13);

                getline(iFile, line);
                c1[i].showDuration = stoi(line.substr(17));

                getline(iFile, line);
                c1[i].bookedSeats[s++] = line.substr(16);

                getline(iFile, line);
            }
        }
    }
    iFile.close();
    iFile1.open("Day2_Booked_Tickets.txt");
    while (getline(iFile1, line))
    {
        getline(iFile1, line);
        mobileNo = stoll(line.substr(15));
        for (int i = 0; i < l; i++)
        {
            if (c1[i].mobileNo == mobileNo)
            {
                getline(iFile1, line);
                c1[i].movieSelected = line.substr(16);

                getline(iFile1, line);
                c1[i].screenNo = stoi(line.substr(12));

                getline(iFile1, line);
                getline(iFile1, line);

                getline(iFile1, line);
                c1[i].showTime = line.substr(13);

                getline(iFile1, line);
                c1[i].showDuration = stoi(line.substr(17));

                getline(iFile1, line);
                c1[i].bookedSeats[s++] = line.substr(16);

                getline(iFile1, line);
            }
        }
    }
    iFile1.close();
}