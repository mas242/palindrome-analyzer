/*********************************************************************************
 * C++ Name Reversing Engine                                                     *
 * Author - mas242 (github)                                                      *
 * Date: 8/15/2022                                                               *
 ********************************************************************************/
#include <iostream>
#include <string>
#include <windows.h>
#include <vector>
#include <fstream>

using namespace std;

// declare functions
string spellBackwards(string, int &);
vector<string> findNameReverseFromFile(string);
bool doesReverse(string);

int main()
{
    int choice = 0;
    // ui

    while (choice != 3)
    {
        cout << "Enter the option you would like to do:" << endl
             << "1. Name Reverse \n"
             << "2. Find words that spell backwards the same: \n"
             << "3. Quit" << endl;
        cin >> choice;

        // if (cin.fail())
        // {
        //     cout << "Entry not an integer, please select an option again.";
        //     cin.ignore();
        // }

        if (choice == 1)
        {
            string userInput = "";    // user input
            int arrowAmount = 0;      // amount of arrows to display around reversed name
            string reversedName = ""; // captures returned name

            cout << "Enter name to reverse: ";
            cin.ignore();
            getline(cin, userInput);
            cout << "reversing..." << endl;
            Sleep(500);
            cout << "hold on..." << endl;
            Sleep(1000);
            reversedName = spellBackwards(userInput, arrowAmount);
            cout << "Here is your name spelled backwards:" << endl
                 << endl;

            for (int i = 0; i < arrowAmount; i++)
            {
                cout << "-";
            }
            cout << endl;

            cout << reversedName << endl;

            for (int i = 0; i < arrowAmount; i++)
            {
                cout << "-";
            }
            cout << endl;

            Sleep(500);
            cout << endl
                 << "Done, press 'enter' to return to menu. \n";
            cin.ignore();
        }

        else if (choice == 2)
        {
            string filename;
            vector<string> results;

            cout << "Enter text file name to read:\n";
            cin.ignore();
            cin >> filename;

            results = findNameReverseFromFile(filename);

            cout << "Results found "
                 << "(" << results.size() << ")" << endl;

            if (results.size() == 0)
            {
                cout << "no words found that spell the same forward and backward. \n";
                break;
            }

            for (int i = 0; i < results.size(); i++)
            {
                cout << "\t" << results[i] << endl;
            }

            cin.ignore();
            Sleep(500);
            cout << endl
                 << "Done, press 'enter' to return to menu. \n";
            cin.ignore();
        }

        else if (choice == 3)
        {
            cout << endl
                 << "Thank you!"
                 << endl
                 << "Quitting...\n";
            break;
        }

        else
        {
            cout << endl
                 << choice << " is not a valid option. Select a valid option." << endl
                 << endl;
        }
    }

    return 0;
}

/*********************************************************************************
 * SPELL BACKWARDS FUNCTION                                                      *
 * DESC - reverses character order of user input as a string using a char array. *
 ********************************************************************************/
string spellBackwards(string name, int &arrowAmount)
{
    string result = "";
    char *forwardChar;
    char *backwardChar;

    forwardChar = new char[name.length()];
    backwardChar = new char[name.length()];

    // copy string into char array
    strcpy(forwardChar, name.c_str());

    // reverse char array
    int j = name.length() - 1;
    for (int i = 0; i < name.length(); i++)
    {
        backwardChar[j] = forwardChar[i];
        j--;
    }

    // put char array back into string
    for (int i = 0; i < name.length(); i++)
    {
        result = result + backwardChar[i];
    }

    arrowAmount = result.size();

    return result;
}

/************************************************************************************************************
 * FIND SAME WORD REVERSALS                                                                                 *
 * DESC - Finds words from a .txt file that spell backwards the same they do forward, then returns results. *
 ***********************************************************************************************************/
vector<string> findNameReverseFromFile(string filename)
{
    vector<string> results;
    string word = "";
    ifstream inputFile;

    cout << "reading " << filename << " ...\n"
         << endl;

    inputFile.open(filename.c_str());
    //inputFile.open("C:/Users/Matt/repos/c++Fun/words.txt");
    if (inputFile.fail())
    {
        cout << "Could not open file: " << filename << endl;
    }
    while (inputFile >> word)
    {
        if (doesReverse(word))
        {
            results.push_back(word);
        }
    }
    inputFile.close();

    return results;
}

/******************************************************************************
 * FIND WORDS THAT REVERSE THE SAME AS FORWARD                                 *
 * DESC - Finds words that reverse the same as they are spelled forward.      *
 *****************************************************************************/
bool doesReverse(string word)
{
    string result = "";

    char *forwardChar;
    char *backwardChar;

    forwardChar = new char[word.length()];
    backwardChar = new char[word.length()];

    // copy string into char array
    strcpy(forwardChar, word.c_str());

    // reverse char array
    int j = word.length() - 1;
    for (int i = 0; i < word.length(); i++)
    {
        backwardChar[j] = forwardChar[i];
        j--;
    }

    // put char array back into string
    for (int i = 0; i < word.length(); i++)
    {
        result = result + backwardChar[i];
    }

    return (word == result && result.length() > 2);
}