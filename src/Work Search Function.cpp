#include <iostream>
#include <string>
#include <math.h>
#include <fstream>
#include <vector>
#include <sstream>
#include <shlobj.h>
#include <shlwapi.h>
#include <objbase.h>
#include <Windows.h>
#include <shellapi.h>
#include <stdlib.h>

#pragma comment(lib,"shell32.lib")

using namespace std;

//store location
//char notepad[] = "notepad.exe";

// Search function
string searchfunc(string unitcheck, string filecheck) 
{

    //var's
    ifstream rpdatabase("test.txt");
    string line, unit, file, location;
    wstring path;
    bool finished = false;
    int counter = 0, menuoption = 0;

    //output
    cout << "Searching..." << endl;

    //while loop which compares the inputs to a line in your database
    while (getline(rpdatabase, line) && finished == false)
    {
            stringstream ss(line);
            getline(ss, unit, ',');
            getline(ss, file, ',');
            getline(ss, location, ',');

            //check if the file exists
                if (unitcheck == unit && filecheck == file)
                {
                    path.assign(location.begin(), location.end());
                    ShellExecute(NULL, L"open", path.c_str(), NULL, NULL, SW_SHOWDEFAULT);
                    //working link -> C:\\Users\\Angel\\Documents\\Contracts (double slashes)
                    //system(path.c_str());
                    cout << "File found!" << endl << endl;
                    finished = true;
                    rpdatabase.close();
                }

                //display if file does not exist
                else if (counter >= 1000)
                {
                    cout << "File not found..." << endl;
                }
                counter += 1;
    }
    return "";

    //close file
    rpdatabase.close();
}
//main function
int main()
{
    //vars
    bool program = true, searching = true;
    int searchnum = 0;
    string search, searchfile;

    while (program == true)
    {

        //main prompt
        system("CLS");
        cout << "To search, type in the three letters that make up your unit ";
        cout << "Example: LK-G-3000 can be serached by typing LKG\n Use 'q' in order to kill program.\n\n" << endl;
        cout << "Which unit are you looking for?" << endl;
        cin >> search;

        //second prompt
        cout << "Which file are you looking for?" << endl;
        cout << "1. Checksheet" << endl;
        cout << "2. Keyword List" << endl;

        //menu check, used switch case at first but was having issues, this was more smooth
        cin >> searchnum;
        if (searchnum == 1)
        {
            searchfile = "checksheet";
        }
        else if (searchnum == 2)
        {
            searchfile = "keywordlist";
        }
        else
        {
            searchfile = "";
        }
        if (search == "q")
            {
                program = false;
                break;
            }
            else
            {
                searching = true;
            }
                while (searching == true)
                {
                    searchfunc(search, searchfile);
                    system("pause");
                    searching = false;
                }
    }
   /*rpdatabase.close();*/
}