/*
 * File: Portfolio-manager.cpp
 * Project: Portfolio-manager
 * File Created: 30/06/2020
 * Author: Chhaikheang Sok (chhaikheang.sok@gmail.com)
 * -----
 * Copyright © 2020
 */

#include <iostream>
#include <sstream>
#include <cctype>
using namespace std;

//structs declaration
struct User
{
    string name;
    string password;
};
struct Date{
    int day; 
    int month; 
    int year; 
};
struct Asset
{
    int ID; 
    string name; 
    int price; 
    int quantity; 
    Date date; 
};


//Function Declaration
bool login(); 
int assets_manage(); 
void print_asset_manage_option(); 
short get_valid_input(string try_again); 
void view_search(short choice); 
void insert_asset(Asset *ptr_assets, int *count_asset); 
//global constants
const string LINES = "------------------------------------------------------------------------------\n"; 
const string INVALID_MSG = "Invalid Input. Please try again.\n"; 

int main()
{   
    //variable declaration
    bool log; 
    log = login(); 
    short asset_page_choice; 
    //login success
    if (log){
        //cout << "Welcome to Portfolio Management System" << endl;
        asset_page_choice = assets_manage(); 
        cout << "chose" << asset_page_choice; 
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
            cout << LINES;
        } 
        
    }

    
    return true; 

}


int assets_manage(){
    
    
    //insert Asset works, need valid input
    //var declaration 
    short option; 
    short sub_option; 
    const string TRY_AGAIN_ASSET = "Input Choice: "; 
    const int ASSET_QUANTITY_LIMIT = 50; 
    int *asset_count = 0;  
    Asset *ptr_assets, all_assets[ASSET_QUANTITY_LIMIT]; 
    ptr_assets = &all_assets; 

    do
    {
        
        print_asset_manage_option(); 
        
        //invalid input handling
        option = get_valid_input(TRY_AGAIN_ASSET); 

        switch (option)
        {
        case 1:
            cout << LINES; 
            cout << "Do you want to search ( type '1' ) or view all assets ( type '2') ?" << endl;
            
            while (true){
                //invalid input handling
                sub_option = get_valid_input(TRY_AGAIN_ASSET); 
                //search
                if (sub_option == 1){
                    view_search(1); 
                    break; 
                }
                //view 
                else if (sub_option == 2){
                    view_search(2); 
                    break; 
                } else {
                    cout << endl << INVALID_MSG << LINES; 
                    continue; 
                }

            }
        case 2: 
            insert_asset(ptr_assets, count_asset)
            
            

            
            break;
        
        default:
            cout << endl <<  INVALID_MSG << LINES; 
        }
    } while (option != 6);

    return option; 
}

void view_search(short choice){

    string query; 
    //search
    if (choice == 1){
        cout << "Please type in ID or Name of asset:"; 
        cin >> query; 
       
        //check 1st char
        if (isdigit(query[0])){
            //check ID before check names
            cout << "check ID and name"; 

        } else {
            //check only name
            cout << "check name"; 
        }
    }    
        

        


        //not found

    //view 
    else if (choice == 2){
        cout << "viewwww"; 
    }

}


short get_valid_input(string try_again)
{
    short choice;
    while (true)
    {
        cout << endl << try_again;  
        cin >> choice;
        if (cin.fail()) // no extraction took place
        {
            cin.clear();             // reset the state bits back to goodbit so we can use ignore()
            cin.ignore(32767, '\n'); // clear out the bad input from the stream
            cout << endl << INVALID_MSG << LINES; 
            continue;                // try again
        }
        break; 

    }
    return choice;
}

void print_asset_manage_option(){
    cout << LINES; 
    cout << "\nAssets Management\n\n";

    cout << "1. View all/ Search assets " << endl;
    cout << "2. Add new asset " << endl;
    cout << "3. Delete asset/portfolio " << endl;
    cout << "4. Edit asset " << endl;
    cout << "5. Sort assets " << endl;
    cout << "6. Return to Main Page " << endl;
    cout << "7. Read/ Write from file " << endl;

    cout << "Please type in number 1-7 according to your preferences. ";
}

void insert_asset(Asset *ptr_assets, int *count_asset){

    
    static int ID = 1; 
    *ptr_assets[*count_asset]).ID = ID; 

    cout << "Enter Asset name: "; 
    cin >> (ptr_assets[*count_asset]).name;
    cout << "Enter Asset price: "; 
    cin >> (ptr_assets[*count_asset]).price;
    cout << "Enter Asset purchase quantity: "; 
    cin >> (ptr_assets[*count_asset]).quantity; 
    cout << "Enter Asset purchase day: ";
    cin >> (ptr_assets[*count_asset]).date.day;
    cout << "Enter Asset purchase month: ";  
    cin >> (ptr_assets[*count_asset]).date.month;
    cout << "Enter Asset purchase year: "; 
    cin >> (*ptr_assets[*count_asset]).date.year;
    
    //output 
    cout << (ptr_assets[*count_asset]).ID;
    cout << (ptr_assets[*count_asset]).name;
    cout << (ptr_assets[*count_asset]).price;
    cout << (ptr_assets[*count_asset]).quantity; 
    cout << (ptr_assets[*count_asset]).date.day;
    cout << (ptr_assets[*count_asset]).date.month;
    cout << (ptr_assets[*count_asset]).date.year;
    
    //increase asset index by 1
    *count_asset +=1; 
    //auto increment ID
    ID++; 
}
