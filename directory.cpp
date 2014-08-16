//Date: 03/27/2014
//Author: Marco Araujo
//About: Program that creates a text document and with a menu gives the ability to create a contact, modify or show data.
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <locale>
#include <sstream>
#include <string>

using namespace std;
// arrays and variables definitions
struct content
{
  int SS_number;
  string last_names;
  string names;
  int cell_number;
};

int menu_options ;
char menu_selection;
std::string result;
ofstream myfile;
content contact;
int social_security_number;


 void show_data () // function that gets inside the text document and outputs all the document content to the console
{

  string line;
  ifstream myfile ("data.txt");
  if (myfile.is_open())
  {
    while ( getline (myfile,line) )
    {
      cout << line << '\n';
    }
    myfile.close();
  }

  else cout << "Unable to open file"; 
}

bool search_data () // function that searches line by line by the social_security_number security number provided.
{
  do // loop that keeps asking for the SS number until 4 digits has been entered
  {
    cout << "Enter the last 4 digits of the SS number \n";
    cin >> contact.SS_number;
    social_security_number = contact.SS_number;
    ostringstream convert;
    convert << social_security_number;
    result = convert.str();
  }while (result.length() != 4);

  string line;
  int found;
  ifstream myfile ("data.txt");
  if (myfile.is_open())
  {
    while ( getline (myfile,line) )
    {

      found=line.find(result);
      if (found == 0)
      {
        cout << "Already Exist \n";
        return true;
      }
    }
  }

  else cout << "Unable to open file"; 
  return false;
}

void modify() // function that eliminates a found registry by removing the file and opening a new one
{
  string line;
  string line2;
  int found;

  if (search_data() == true) // calls the function search to get a line of registry by the SS_number
  {
    ifstream myfile ("data.txt");
    if (myfile.is_open())
    {
      while ( getline (myfile,line) )
      {

        found=line.find(result);
        if (found == 0)
        {
          ofstream out("outfile.txt");
          while( getline(myfile,line2) )
          {
            if(line2 != line)
            out << line2 << "\n";
          }
          myfile.close();
          out.close();    
          remove("data.txt");
          rename("outfile.txt","data.txt");

        }
      }
      ofstream myfile;
      myfile.open("data.txt", fstream::app);
        cout << "Enter the last names \n";
        cin >> contact.last_names;
        cout << "Enter the names \n";
        cin >> contact.names;
        cout << "Enter the phone number \n";
        cin >> contact.cell_number;
        myfile << result;
        myfile << "     ";
        myfile << contact.last_names;
        myfile << "     ";
        myfile << contact.names;
        myfile << "     ";
        myfile << contact.cell_number;
        myfile << "\n";
      myfile.close();
    }
  }
}

void write() // a function that writes the structure to the text document.
{
  if (search_data() == false)
  {
  cout << "Enter the last names \n";
  cin >> contact.last_names;
  cout << "Enter the names \n";
  cin >> contact.names;
  cout << "Enter the phone number \n";
  cin >> contact.cell_number;
    myfile << result;
    myfile << "     ";
    myfile << contact.last_names;
    myfile << "     ";
    myfile << contact.names;
    myfile << "     ";
    myfile << contact.cell_number;
    myfile << "\n";
  }  
}

int main () 
{
  do // loop that controls the main menu.
  {
    myfile.open("data.txt", fstream::app);
      cout << "Contacts database\n" ;
      cout << "1) To enter a new contact \n";
      cout << "2) To modify a contact \n";
      cout << "3) To show all contacts \n";
      cout << "4) Exit the menu \n";
      // Series of outputs and inputs that allows the user select the desired action to be taken.
      cin >> menu_options ;
      // Switch case that takes the value of menu_options and performs certain actions based on the input provided.
      switch ( menu_options ) 
      {
        case 1 : // calls write function.
          write();
          break;
        case 2 : // calls the modidy function.
          modify();
          break;
        case 3 : // case 3 shows all data stored in the document by calling show_data function.
          show_data();
          break;
        case 4 : // gets out of the menu
          break;
        default : 
            cout << "You must choose a operator between 1 and 4 \n" ;
        break;
      }
      cout << "Exit the programme? Y/N \n";
      cin >> menu_selection; // variable that decides to get out the loop
      cout << "\n";
    myfile.close();

  }while ((menu_selection == 'N') || (menu_selection == 'n'));
  cout << "\n";
  return 0;
}