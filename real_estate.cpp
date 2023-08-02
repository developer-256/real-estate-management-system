// admin username: developer256
// admin password: qwerty
// p in data.txt --> plot to sell
// hr in data.txt --> house for rent
// hs in data.txt --> house to sell
// sr in data.txt --> shop for rent

#include <iostream>
#include <fstream>
using namespace std;

#define limit 100
string data[limit][7]; // Whole .txt file data will be stored in this when import_data() is called and this is global.
int rows = 0;          // rows are calculated and stored in this for later use in for loops in iterating 2D array
void import_data()
{
    data[limit][7]; // initializing array in which we will import data

    ifstream file;                   // it must be ifstream not fstream
    file.open("Data.txt", ios::app); // set file name and ios::app will not overwrite file while writing it again

    rows = 0;               // declaring rows (these are total rows in .txt file)
    while (file.eof() == 0) // reading file till end of file
    {
        string temp_row = "";
        getline(file, temp_row); // take line 1 of file as input in temp_row
        if (temp_row == "")      // if it is empty row you will skip to next row
        {
            rows++;
            continue;
        }
        int column = 0;
        string temp_col = "";
        for (int j = 0; j < temp_row.length(); j++) // breaking row that we input into different values
        {
            if (temp_row[j] != ',') // if , does not occur keep adding character in temp_row
            {
                temp_col += temp_row[j];
            }
            else // if , occur save temp_row into 2D array
            {
                data[rows][column] = temp_col;
                temp_col = ""; // empty temp_col
                column++;
            }
        }
        rows++;
        if (rows == limit) // if rows become equal to max limit, decrease row by one, show error message, break
        {
            rows--;
            cout << "%%%%% (Error) %%%%%%%%%%% (Maximum memory reached)%%%%%%%%%%%" << endl;
            break;
        }
    }
    file.close(); // closing file
}

string input(string x);
bool admin_auth();  // authentication of admin
void show_P_sold(); // show property sold
void show_P2S();    // show property selling
void add_P2S();     // add property to sell
void sell_prop();   // sell a property
void update_txt_file();

int main()
{

    while (admin_auth() == false)
    {
        system("cls");
        cout << "Invalid Username or Password\n";
    }

    int choice;
    do
    {
        cin.clear();
        fflush(stdin);
        // system("cls");
        cout << "________________________________\n";
        cout << "|--------( Admin Panel )-------|\n";
        cout << "| Choose one of the following: |\n";
        cout << "********************************\n";
        cout << "| 1: Property sold             |\n";
        cout << "| 2: Property to sell          |\n";
        cout << "| 3: Add property to sell      |\n";
        cout << "| 4: Sell property             |\n";
        cout << "| 5: Exit                      |\n";
        cout << "********************************\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            system("cls");
            import_data();
            show_P_sold(); // show property sold
            break;

        case 2:
            system("cls");
            import_data();
            show_P2S(); // show property selling
            break;

        case 3:
            system("cls");
            add_P2S(); // add property to sell
            break;

        case 4:
            system("cls");
            sell_prop();
            break;

        case 5:
            break;

        default:
            cout << "Invalid Input\n";
            break;
        }

    } while (choice != 5);
}

string input(string x)
{
    string y;
    cout << x;
    getline(cin >> ws, y);
    return y;
}
bool admin_auth()
{
    string user, pass;

    cout << "Enter your Username: ";
    cin >> user;

    cout << "Enter password: ";
    cin >> pass;

    return (user == "developer256" && pass == "qwerty");
}

void show_P_sold()
{
    for (int i = 0, j = 0; i < rows; i++)
    {
        if (data[i][j] == "sold")
        {
            cout << data[i][1] << endl;
            cout << "Covered area: " << data[i][2] << endl;
            cout << "Location: " << data[i][3] << endl;
            cout << "Sold to: " << data[i][4] << endl;
            cout << "Price recieved: Rs." << data[i][5] << endl
                 << endl;
        }
    }
}
void show_P2S() // show property selling
{
    for (int i = 0, j = 0; i < rows; i++)
    {
        if (data[i][j] == "2 sell")
        {
            cout << data[i][1] << endl;
            cout << "Property id: " << data[i][2] << endl;
            cout << "Covered area: " << data[i][3] << endl;
            cout << "Location: " << data[i][4] << endl;
            cout << "Owner: " << data[i][5] << endl;
            cout << "Price: Rs." << data[i][6] << endl
                 << endl;
        }
    }
}
void add_P2S() // add property to sell
{

    int ch;
    do
    {
        cin.clear();
        fflush(stdin);

        string type;
        // system("cls");
        cout << "________________________________\n";
        cout << "| Choose one of the following: |\n";
        cout << "********************************\n";
        cout << "| 1: Plot                      |\n"; // P4S
        cout << "| 2: House for rent            |\n"; // H4R
        cout << "| 3: House to sell             |\n"; // H2S
        cout << "| 4: Shop for rent             |\n"; // S4R
        cout << "| 5: Exit                      |\n";
        cout << "********************************\n";
        cout << "Enter your choice: ";
        cin >> ch;

        switch (ch)
        {
        case 1:
            type = "Plot";
            break;

        case 2:
            type = "House for rent";
            break;

        case 3:
            type = "House to sell";
            break;

        case 4:
            type = "Shop for rent";
            break;

        case 5:
            break;

        default:
            system("cls");
            cout << "Invalid Input\n";
            break;
        }
        if (ch == 1 || ch == 2 || ch == 3 || ch == 4)
        {
            string status = "2 sell"; // selling or sold
            string prop_id = input("Enter the property id: ");
            string name = input("Enter owners name: ");
            string size = input("Enter the covered area: ");
            string location = input("Enter the address: ");
            string price = input("Enter the price: Rs.");

            ofstream file;
            file.open("data.txt", ios::app);
            file << endl
                 << status << ',' << type << ',' << prop_id << ',' << size << ',' << location << ',' << name << ',' << price << ',';
            file.close();
            system("cls");
        }

    } while (ch != 5);
}
void sell_prop()
{
    import_data();
    show_P2S();
    string id;

    cout << "Enter the property id: ";
    cin >> id;
    int test = 0;
    for (int i = 0, j = 2; i < rows; i++)
    {
        if (data[i][j] == id)
        {
            string name = input("Enter name of new owner: ");
            data[i][5] = name;
            data[i][0] = "sold";
            test++;
        }
    }
    if (test == 1)
    {
        cout << "Property Sold\n";
        update_txt_file();
        return;
    }
    else
    {
        cout << "Property id not found\n";
        return;
    }
}

void update_txt_file()
{
    ofstream file;
    file.open("data.txt");
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < 7; j++)
        {
            file << data[i][j] << ',';
        }
        if (i < rows - 1) // if we dont do this after last row, an empty row will be added
        {
            file << endl;
        }
    }
    file.close();
}
