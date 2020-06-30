/*
 * File: Portfolio-manager.cpp
 * Project: Portfolio-manager
 * File Created: 30/06/2020
 * Author: Chhaikheang Sok (chhaikheang.sok@gmail.com)
 * -----
 * Copyright © 2020
 */

#include <iostream>
using namespace std;

//structs declaration
struct User
{
    string name;
    string password;
};


//Function Declaration
bool login(); 

const string lines = "------------------------------------------------------------------------------\n"; 
int main()
{   
    //variable declaration
    bool log; 
    log = login(); 
    
    //login success
    if (log){
        cout << "Welcome to Portfolio Management System" << endl;
    }

    return 0; 

}

bool login(){

    //Variable declaration
    string username;
    string password;
    const int NUM_USER = 3; 

    //users list
    User user[NUM_USER]{
        {"ken", "007"},
        {"ben", "008"}, 
        {"gege", "009"}};

    //Login
    
    bool log = true;
    while (log)
    {
        cout << "Input username: ";
        cin >> username;
        cout << "Input password: ";
        cin >> password;
        for (int i = 0; i < NUM_USER; i++)
        {   
           
            if (user[i].name == username && user[i].password == password)
            {
                log = false;
                break;
            }
            
        }
        
        //wrong login input message 
        if (log){
            cout << "Username and/or password incorrect. Please try again below.\n"; 
            cout << lines;
        } 
        
    }

    
    return true; 

}