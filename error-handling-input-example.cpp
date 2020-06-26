//
// main.cpp
// w24
//
// Created by Virak Un on 6/24/20.
// Copyright © 2020 STEP. All rights reserved.
//

#include <iostream>
#include <sstream>
using namespace std;

bool validate_age(int);
int get_valid_age();

int main()
{
    // int age;
    //
    // age=get_valid_age();
    // cout << "You entered: " << age << '\n';
    //Option3
    int age;
    while (true)
    {
        string sAge;
        cout << "Enter Age ";
        cin >> sAge;
        bool valid = true;
        for (int i = 0; i < sAge.length(); i++)
        {
            if (!isdigit(sAge[i]))
            {
                valid = false;
                break;
            }
        }

        if (!valid)
        {
            continue;
        }
        stringstream strStream;
        strStream << sAge;
        strStream >> age;
        break;
    }

    cout << "Enter age " << age << endl;

    return 0;
}

int get_valid_age()
{
    int age;
    while (true)
    {
        cout << "Enter Age ";
        cin >> age;
        if (cin.fail()) // no extraction took place
        {
            cin.clear();             // reset the state bits back to goodbit so we can use ignore()
            cin.ignore(32767, '\n'); // clear out the bad input from the stream
            continue;                // try again
        }
        if (validate_age(age) == false)
        {
            continue;
        }
        break;
    }
    return age;
}

bool validate_age(int age)
{

    if (age <= 0)
    {
        return false;
    }
    else
    {
        return true;
    }
}