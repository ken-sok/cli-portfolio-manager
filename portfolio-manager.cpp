/*
 * File: Portfolio-manager.cpp
 * Project: Portfolio-manager to CREATE, READ, UPDATE, WRTIE, SORT, AND I/O TO FILE 
 * File Created: 30/06/2020
 * Author: Chhaikheang Sok (chhaikheang.sok@gmail.com)
 * -----
 * Copyright © 2020
 */


/**********************************************Libraries********************************************************************/
#include <iostream>
#include <fstream>
#include <sstream>
#include <cctype>
#include <string>
#include <ios> 
#include <limits> 
using namespace std;
/**********************************************Libraries********************************************************************/

/**********************************************structs declaration**********************************************************/

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
    double price; 
    int quantity; 
    Date date; 
};

enum asset_options { Add = 1, View_Search = 2, Delete = 3, Update = 4, Sort = 5, File_IO = 6, Exit = 7 };
enum msg_user {ASK_PRICE, ASK_QUANTITY, ASK_DAY, ASK_MONTH, ASK_YEAR, TRY_AGAIN_ASSET }; 
/**********************************************structs declaration**********************************************************/

/**********************************************functions declaration**********************************************************/

bool login(); 
int assets_manage(); 
void print_asset_manage_option(); 
double get_valid_input(short try_again); 
short get_valid_input(short try_again, short max_num); 
void search_asset(Asset* ptr_assets, int &count_asset); 
void view_search_controller(Asset* ptr_assets, int &count_asset); 
void insert_asset(Asset* ptr_assets, int &count_asset); 
void print_one_asset(Asset* ptr_assets, int found_index);  
void print_all_asset(Asset* ptr_assets, int &count_asset); 
int binarySearch(Asset* ptr_assets, int x, int low, int high); 
bool isNumeric(string str);  
bool delete_asset(Asset* ptr_assets, int &count_asset, int found_index); 
int delete_asset_controller(Asset* ptr_assets, int &count_asset); 
void update_asset_controller(Asset* ptr_assets, int &count_asset);
void update_asset(Asset* ptr_assets, int &count_asset, int found_index); 
void swap_asset_details(Asset* ptr_assets, int index); 
void sort_controller(Asset* ptr_assets, int &count_asset);  
void sort_prices_controller(Asset* ptr_assets, int &count_asset); 
void insertion_sort(Asset* ptr_assets, int &count_asset, int key); 
void save_asset_file(Asset* ptr_assets, int &count_asset); 
void load_asset_file(Asset* ptr_assets, int &count_asset); 
void file_controller(Asset* ptr_assets, int &count_asset); 
string ask_user_update(short info_asked); 
void ClearScreen(); 
/**********************************************functions declaration**********************************************************/

/**********************************************global constants***************************************************************/

const string LINES = "------------------------------------------------------------------------------\n"; 
const string INVALID_MSG = "Invalid Input. Please try again.\n"; 
const string ASSET_COL_NAMES = "ID\tName\t\t\tPrice\t\tQuantity\tDate"; 
const short MAX_YEAR_APP_USE = 2030; 

/**********************************************global constants***************************************************************/

/**********************************************MAIN FUNCTION**********************************************************/
int main()
{   

    //main function controlling flow of program

    //variable declaration
    bool log = false; 

    //login screen
    log = login(); 
    short asset_page_choice; 
    
    //login success
    if (log){    
        asset_page_choice = assets_manage(); 
    }

    return 0; 

}
/**********************************************MAIN FUNCTION**********************************************************/


/**********************************************LOGIN*****************************************************************/
bool login(){

    //login function to ask user for username and password to use the application


    //Variable declaration
    string username;
    string password;
    const int NUM_USER = 3; 

    //all users list
    User user[NUM_USER]{
        {"ken", "007"},
        {"ben", "008"}, 
        {"gege", "009"}};

    
    
    cout << "\nLOGIN PAGE\n\n"; 

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
/**********************************************LOGIN*****************************************************************/

/**********************************************MANAGE ASSETS********************************************************/
int assets_manage(){
    
    //this function is controller for manage assets page

    
    //var declaration 
    short option;  
    const int ASSET_QUANTITY_LIMIT = 50; 
    int count = 0; 
    int &asset_count = count;  
    Asset *ptr_assets, all_assets[ASSET_QUANTITY_LIMIT]; 
    ptr_assets = all_assets; 
     
    
    do
    {
        ClearScreen();
        print_asset_manage_option(); 
        
        //get valid input for choice of function to use
        option = get_valid_input(TRY_AGAIN_ASSET); 
        

        
        switch (option)
        {

            //view or search
            case View_Search:
                { 
                    ClearScreen();
                    cout << LINES; 
                    view_search_controller(ptr_assets, asset_count);
                    break; 
                }

            //add new asset
            case Add: 
                {
                    ClearScreen();
                    cout << LINES; 
                    insert_asset(ptr_assets, asset_count); 
                    break;
                }
            
            //delete asset
            case Delete: 
                {
                    ClearScreen();
                    cout << LINES; 
                    delete_asset_controller(ptr_assets, asset_count);
                    break;
                }

            //update asset
            case Update: 
                {
                    ClearScreen();
                    cout << LINES; 
                    update_asset_controller(ptr_assets, asset_count);
                    break;
                }
            
            case Sort: 
                { 
                    ClearScreen();
                    cout << LINES; 
                    sort_controller(ptr_assets, asset_count); 
                    break;
                    
                }
            
            case File_IO: 
                {

                    ClearScreen();
                    cout << LINES; 
                    file_controller(ptr_assets, asset_count); 
                    break;
                    
                }


            default:
                { 
                    cout << endl <<  INVALID_MSG << LINES; 
                } 
        }
    } while (option != Exit);

    
    return option; 
}


void print_asset_manage_option(){
    
    //this function prints all options user can choose to complete tasks

    cout << LINES; 
    cout << "\n-----ASSETS MANAGEMENT-----\n\n";
    cout << "1. Add new asset" << endl;
    cout << "2. View all/ Search asset" << endl;
    cout << "3. Delete asset" << endl;
    cout << "4. Edit asset" << endl;
    cout << "5. Sort assets" << endl;
    cout << "6. Save/ Load from file" << endl;
    cout << "7. Exit application" << endl;

    cout << "Please type in number 1-7 according to your preferences. ";
}
/**********************************************MANAGE ASSETS********************************************************/

/**********************************************VIEW/SEARCH ASSETS***************************************************/



void view_search_controller(Asset* ptr_assets, int &count_asset){

    //this function controls the flow of view/search function of the program 

    //var declaration
    short sub_option; 
    cout << LINES; 
    cout << "Do you want to search (Type '1') or view all assets (Type '2') ?" << endl;
    
    
    while (true){

        
        sub_option = get_valid_input(TRY_AGAIN_ASSET); 
        
        //search an asset
        if (sub_option == 1){
            search_asset(ptr_assets, count_asset); 
            break; 
        }

        //view alll assets
        else if (sub_option == 2){
            print_all_asset(ptr_assets, count_asset);
            break; 
        } else {
            cout << endl << INVALID_MSG << LINES; 
            continue; 
        }
        break;

    }
}
void search_asset(Asset* ptr_assets, int &count_asset){

    //this function can search according to user input 

    string query; 
    short found_index = -1; 

    //search
    
    cout << "Please type in ID or Name of asset: "; 
    cin >> query; 
    
    //check asset IDs first if query is numeric
    if (isNumeric(query)){
        found_index = binarySearch(ptr_assets, stoi(query), 0, count_asset); 
        if (found_index != -1){
            cout << "Asset ID found!\n";
        }
            
    }
    
    //check asset names if alphanumeric or numeric query not found in IDs
    if (found_index == -1) {
        
        //do linear search of names
        for (int i = 0; i<count_asset; i++){
            if (ptr_assets[i].name == query){
                found_index = i; 
                cout << "Asset Name found!\n";
                break; 
            }
        }
    }

    //if asset found 
    if (found_index != -1){

        //print asset details    
        cout << "\nThis is the asset you looked for:\n";
        print_one_asset(ptr_assets, found_index);
        

    //if asset not found    
    } else {
        cout << "\nAsset not found.\n"; 
    }
}
/**********************************************VIEW/SEARCH ASSETS********************************************************/

/************************************************INSERT ASSET***********************************************************/

void insert_asset(Asset* ptr_assets, int &count_asset){

    //this function lets user insert one new asset 

    //var declaration
   
    static int ID = count_asset + 1;

    //get user input for asset details
    cout << "Please type in new asset details below." << endl;
    ptr_assets[count_asset].ID = ID;
    cout << "ID = " << ID << endl; 
    cout << "\nEnter Asset name: ";
    cin >> ptr_assets[count_asset].name;    
    ptr_assets[count_asset].price = get_valid_input(ASK_PRICE);
    ptr_assets[count_asset].quantity = get_valid_input(ASK_QUANTITY);  
    ptr_assets[count_asset].date.day = get_valid_input(ASK_DAY, 31);  
    ptr_assets[count_asset].date.month = get_valid_input(ASK_MONTH, 12);  
    ptr_assets[count_asset].date.year = get_valid_input(ASK_YEAR, MAX_YEAR_APP_USE);  
    
    
    //output to user for confirmation
    cout << "\n---NEW ASSET ADDDED---\n";
    print_one_asset(ptr_assets, count_asset); 

    
    //increase asset index by 1
    count_asset +=1; 

    //auto increment ID
    ID++; 
}


/************************************************INSERT ASSET*********************************************************/

/************************************************DELETE ASSET*********************************************************/

int delete_asset_controller(Asset* ptr_assets, int &count_asset){

    //this function controls the flow of program when user asks to delete an asset

    //var declaration
    string query;  
    int found_index = -1; 
    char check_ans = 'I'; 
    bool deleted = 0; 


    while (true)
    {
        cout << "\nPlease Enter ID of asset to delete: "; 
        cin >> query; 

        //check ID if query is numeric
        if (isNumeric(query)){
            
            found_index = binarySearch(ptr_assets, stoi(query), 0, count_asset); 

            //id is found
            if (found_index != -1){

                //ask for confirmation from user
                cout << "Are you sure? (Y/N)\n";
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); //clear buffer before taking new
                check_ans = getchar();
                check_ans = toupper(check_ans); 
                if (check_ans == 'Y'){
        
                    //print asset details
                    deleted = delete_asset(ptr_assets, count_asset, found_index); 

                    if (deleted){
                        cout << "---ASSET DELETED---.\n"; 
                    } else {
                        cout << "---Asset NOT deleted---.\n"; 
                    }
                    return 0; 
                            
                } else if (check_ans == 'N'){
                    return 0; 
                            
                } else {
                    cout << "Invalid input. Please try again. \n";
                      
                }

            //ID is not found after search    
            } else {
                cout << "ID not found. Please try again. \n"; 
                
            }

        //input handling when user input is not numeric; ID is numeric-only        
        } else {
            cout << "Invalid ID entered. Please try again. \n"; 
             
        }
    }
    

}


bool delete_asset(Asset* ptr_assets, int &count_asset, int found_index){

    //this function deletes one asset according to the index specified in its controller function

    for (int j = found_index; j < count_asset; j++) {
                
        (ptr_assets[j]).ID = (ptr_assets[j + 1]).ID; 
        (ptr_assets[j]).name = (ptr_assets[j + 1]).name; 
        (ptr_assets[j]).price = (ptr_assets[j + 1]).price;
        (ptr_assets[j]).quantity = (ptr_assets[j + 1]).quantity; 
        (ptr_assets[j]).date.day = (ptr_assets[j + 1]).date.day;
        (ptr_assets[j]).date.month = (ptr_assets[j + 1]).date.month;
        (ptr_assets[j]).date.year = (ptr_assets[j + 1]).date.year;
    
    }

    (ptr_assets[count_asset]).ID = 0;   
    (ptr_assets[count_asset]).name = '0'; 
    (ptr_assets[count_asset]).price = 0; 
    (ptr_assets[count_asset]).quantity = 0;
    (ptr_assets[count_asset]).date.day = 0;
    (ptr_assets[count_asset]).date.month = 0;
    (ptr_assets[count_asset]).date.year = 0;
    count_asset -=1; 
    
    return true; 
}



/************************************************DELETE ASSET*********************************************************/

/************************************************UPDATE ASSET*********************************************************/

void update_asset_controller(Asset* ptr_assets, int &count_asset){

    //this function controls the flow for updating one asset
    
    //var declaration
    string query; 
    int found_index = -1; 

    
    while (true)
    {
        //get ID 
        cout << "\nPlease Enter ID of asset to update: "; 
        cin >> query; 

        //check ID if query is numeric
        if (isNumeric(query)){
            found_index = binarySearch(ptr_assets, stoi(query), 0, count_asset); 
            if (found_index != -1){

                //found ID to update
                update_asset(ptr_assets, count_asset, found_index);
                break; 

            } else {
                cout << "ID not found. Please try again. \n"; 
                
            }

        } else {
            cout << "Invalid ID entered. Please try again. \n"; 
        }
    }
   
    
}

void update_asset(Asset* ptr_assets, int &count_asset, int found_index){

    //this function allows user to update one asset according to the index specified in its controller function

    
    //get user input
    cout << "Please type in new asset details below." << endl;
    cout << "ID = " << ptr_assets[found_index].ID << endl; 
    cout << "\nEnter NEW Asset name: ";
    cin >> ptr_assets[found_index].name;
    ptr_assets[found_index].price = get_valid_input(ASK_PRICE);
    ptr_assets[found_index].quantity = get_valid_input(ASK_QUANTITY);  
    ptr_assets[found_index].date.day = get_valid_input(ASK_DAY, 31);  
    ptr_assets[found_index].date.month = get_valid_input(ASK_MONTH, 12);  
    ptr_assets[found_index].date.year = get_valid_input(ASK_YEAR, MAX_YEAR_APP_USE);  
    
    
    //output to user for confirmation
    cout << "\n---ASSET UPDATED---\n";
    print_one_asset(ptr_assets, found_index); 

    
}



/************************************************UPDATE ASSET*********************************************************/

/**********************************************SORT ASSETS***********************************************************/
void sort_controller(Asset* ptr_assets, int &count_asset){

    //this function is the controller for sort asset function of app

    //var declaration
    
    short sub_option; 
    cout << LINES; 
    cout << "Do you want to sort by Name (Type '1') or Price (Type '2') ? " << endl;
    
    
    while (true){
        
        sub_option = get_valid_input(TRY_AGAIN_ASSET); 
        
        //sort names
        if (sub_option == 1){
            
            insertion_sort(ptr_assets, count_asset, 0); 
            cout << "\n---NAMES SORTED ALPHABETICALLY!---\n";  
            
            break; 
        }

        //sort prices
        else if (sub_option == 2){
            
            sort_prices_controller(ptr_assets, count_asset); 

            break; 
        } else {
            cout << endl << INVALID_MSG << LINES; 
            continue; 
        }
        break;

    }

    print_all_asset(ptr_assets, count_asset); 

}


void sort_prices_controller(Asset* ptr_assets, int &count_asset){

    //this function sorts assets according to their prices

    //var declaration
    
    short sub_option; 
    cout << LINES; 
    cout << "Do you want to sort prices ascending (Type '1') or descending (Type '2') ?: " << endl;
    
    
    while (true){
        
        sub_option = get_valid_input(TRY_AGAIN_ASSET); 
        
        //ascending 
        if (sub_option == 1){
            insertion_sort(ptr_assets, count_asset, 1); 
            cout << "\n---PRICES SORTED ASCENDING---\n"; 
            break; 
        }

        //descending
        else if (sub_option == 2){
            insertion_sort(ptr_assets, count_asset, 2); 
            cout << "\n---PRICE SORTED DESCENDING---\n";   
            break; 
        } else {
            cout << endl << INVALID_MSG << LINES; 
            continue; 
        }
        break;

    }

}

 

/**********************************************SORT ASSETS***********************************************************/

/**********************************************FILE I/O***********************************************************/

void file_controller(Asset* ptr_assets, int &count_asset){

    //this function is controller for writing data to file/reading data from file 

    //var declaration
   
    short sub_option; 
    cout << LINES; 
    cout << "Do you want to save to file (Type '1') or load from file ('Type 2')? : " << endl;
    
    
    while (true){
        
        sub_option = get_valid_input(TRY_AGAIN_ASSET); 
        
        
        if (sub_option == 1){
            
            cout << "\nSaving to file...\n"; 
            save_asset_file(ptr_assets, count_asset); 
            break; 
        }

     
        else if (sub_option == 2){
           
            cout << "\nLoading from file...\n"; 
            load_asset_file(ptr_assets, count_asset); 
            break; 
        } else {
            cout << endl << INVALID_MSG << LINES; 
            continue; 
        }
        break;

    }


    
}
void save_asset_file(Asset* ptr_assets, int &count_asset) {

    //this function saves all assets data to file 

    fstream file;
    file.open("AssetsData.bin", ios::out | ios::binary );  
    if (file.good()) {      
        for (int i = 0; i < count_asset; i++) {

            Asset asset = ptr_assets[i]; 
            file.write((char*)&asset, sizeof(asset)); 

        }
        
        cout << "---Saved to file Successfully---" << endl;
        file.close();
    }
    else {
        
        cout << "---FAILED saving to file---" << endl;
    }

}


void load_asset_file(Asset* ptr_assets, int &count_asset) {

    //this function loads all assets data from file 

    fstream file;
    Asset asset;
    file.open("AssetsData.bin", ios::in | ios::binary);
    if (file.good()) {
        count_asset = 0;
        file.read((char*)&asset, sizeof(asset));
        while (!file.eof()) {
            ptr_assets[count_asset] = asset;
            file.read((char*)&asset, sizeof(asset));
            count_asset++;
        }
        cout << "---Loaded from file successfully!---" << endl;
        file.close();
    }
    else {
        cout << "---FAILED loading from file---" << endl;
    }
}


/**********************************************FILE I/O***********************************************************/



/************************************************HELPER FUNCTIONS****************************************************/ 
void insertion_sort(Asset* ptr_assets, int &count_asset, int key){

    //this functions utilises insertion sort algorithm to sort names, and prices of asset

    short swapped = 0; 
    for(int i=1; i<count_asset; i++)
        {   
            swapped = 0; 

            for(int j=1; j<count_asset; j++)
            {   
                //sort name alphabetically
                if (key == 0){
                //check if the name of the last name is alphabetically after the next name
                    if ((((ptr_assets[j-1]).name).compare((ptr_assets[j]).name))>0)
                    {   
                        //if true, swap between the two assets

                        
                        //other details
                        swap_asset_details(ptr_assets, j); 
                        swapped = 1; 
                    }
                
                //sort price ascending
                } else if (key == 1){

                      //check if the last price is bigger than the current one 
                    if ((ptr_assets[j-1]).price > (ptr_assets[j]).price) 
                    {   
                        //if true, swap between the two assets
                        swap_asset_details(ptr_assets, j); 
                        swapped = 1; 
                    }
                } 

                //sort price descending

                else if (key == 2){
                    
                      //check if the last price is bigger than the current one 
                    if ((ptr_assets[j-1]).price < (ptr_assets[j]).price) 
                    {   
                        //if true, swap between the two assets
                        swap_asset_details(ptr_assets, j); 
                        swapped = 1; 
                    }
                } 


            
            }

            //stop comparing when there are no swaps in the thing at any round.
            if (swapped == 0){
                break; 
            }
        }
}
void swap_asset_details(Asset* ptr_assets, int index){
    
    //this function acts as helper function to insertion sort to swap two assets' places 
    //within all assets array

    //var declaration
    double temp; 
    string temp_str; 



    //name
    temp_str = (ptr_assets[index-1]).name; 
    (ptr_assets[index-1]).name = (ptr_assets[index]).name; 
    (ptr_assets[index]).name = temp_str; 

    temp = (ptr_assets[index - 1]).ID;
    (ptr_assets[index - 1]).ID = (ptr_assets[index]).ID; 
    (ptr_assets[index]).ID = temp; 

    temp = (ptr_assets[index - 1]).price;
    (ptr_assets[index - 1]).price = (ptr_assets[index]).price; 
    (ptr_assets[index]).price = temp; 

    temp = (ptr_assets[index - 1]).quantity;
    (ptr_assets[index - 1]).quantity = (ptr_assets[index]).quantity; 
    (ptr_assets[index]).quantity = temp; 

    temp = (ptr_assets[index - 1]).date.day;
    (ptr_assets[index - 1]).date.day = (ptr_assets[index]).date.day; 
    (ptr_assets[index]).date.day = temp; 

    temp = (ptr_assets[index - 1]).date.month;
    (ptr_assets[index - 1]).date.month = (ptr_assets[index]).date.month; 
    (ptr_assets[index]).date.month = temp; 

    temp = (ptr_assets[index - 1]).date.day;
    (ptr_assets[index - 1]).date.day = (ptr_assets[index]).date.day; 
    (ptr_assets[index]).date.day = temp; 

}


double get_valid_input(short try_again){   
    
    //this function handles wrong input type(besides numbers), letters before numbers, numbers over 32767 and show user feedback
    //caveat: numbers before letters will take the numbers in front 
    //it returns a double to cover cases for floating point such as price

    double choice;

    string msg = ask_user_update(try_again); 
    while (true)
    {
        cout << endl << msg;  
        cin >> choice;
        if (cin.fail()) 
        {
            cin.clear();             
            cin.ignore(32767, '\n'); 
            cout << endl << INVALID_MSG << LINES; 
            continue;                
        }

        if (choice <= 0) {
            cout << endl << INVALID_MSG << LINES; 
            continue; 
        }

        break; 

    }
    return choice;
}

short get_valid_input(short try_again, short max_num){

    //this function handles wrong input type(besides numbers), letters before numbers, numbers over 32767 and show user feedback
    //it also handles numbers specified in max_num to get a valid date input from user
    //caveat: numbers before letters will take the numbers in front 
    
    short choice;
    string msg = ask_user_update(try_again); 
    while (true)
    {
        cout << endl << msg;  
        cin >> choice;
        if (cin.fail()) 
        {
            cin.clear();             
            cin.ignore(32767, '\n'); 
            cout << endl << INVALID_MSG << LINES; 
            continue;                
        }

        if ((choice > max_num) || (choice <= 0)) {
            cout << endl << INVALID_MSG << LINES; 
            continue; 
        }
        break; 
        


    }

    
    return choice;
}

void print_one_asset(Asset* ptr_assets, int found_index){
    
    //this function prints one asset's detail 
    
    int ID = (ptr_assets[found_index]).ID;
    string name = (ptr_assets[found_index]).name;
    double price = (ptr_assets[found_index]).price;
    int quantity = (ptr_assets[found_index]).quantity; 
    int day = (ptr_assets[found_index]).date.day;
    int month = (ptr_assets[found_index]).date.month;
    int year = (ptr_assets[found_index]).date.year;
    
    cout << LINES; 
    cout << ASSET_COL_NAMES; 
    cout << endl; 
    cout << ID << "\t" << name << "\t\t\t" << price << "\t\t" << quantity << "\t\t" << day << "/" << month << "/"<< year ; 
    cout << endl;
    cout << LINES; 

}



void print_all_asset(Asset* ptr_assets, int &count_asset){

    //this function prints all assets by taking pointer to assets and total number of assets
    
    //print headings
    cout << "\n---ALL ASSETS LIST---\n"; 
    cout << LINES; 
    cout << ASSET_COL_NAMES; 

    //print assets
    for (int i = 0; i < count_asset; i++){
        
        //output each asset 
        int new_ID = (ptr_assets[i]).ID;
        string name = (ptr_assets[i]).name;
        double price = (ptr_assets[i]).price;
        int quantity = (ptr_assets[i]).quantity; 
        int day = (ptr_assets[i]).date.day;
        int month = (ptr_assets[i]).date.month;
        int year = (ptr_assets[i]).date.year;
        cout << endl; 
        cout << new_ID << "\t" << name << "\t\t\t" << price << "\t\t" << quantity << "\t\t" << day << "/" << month << "/"<< year;

    }

    //ending lines
    cout << endl;
    cout << LINES;
     
}
//////////////////////////////////////////////////////////////////////////////////////////////////
/////MODIFIED FROM https://www.programiz.com/dsa/binary-search///////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////


int binarySearch(Asset* ptr_assets, int x, int low, int high) {

    //this is the binary search algorithm to search for ID of asset

    while (low <= high)
    {
        int mid = low + (high - low) / 2;

        if ((ptr_assets[mid]).ID == x)
            return mid;

        if ((ptr_assets[mid]).ID < x)
            low = mid + 1;

        else
            high = mid - 1;
    }

    return -1;
}


//////////////////////////////////////////////////////////////////////////////////////////////////
/////MODIFIED FROM https://www.programiz.com/dsa/binary-search///////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////////
/////COPIED FROM https://www.tutorialspoint.com/how-to-check-if-input-is-numeric-in-cplusplus///
////////////////////////////////////////////////////////////////////////////////////////////////
bool isNumeric(string str) {

    //this function checks if a string is numeric

    for (int i = 0; i < str.length(); i++)
        if (isdigit(str[i]) == false)
            return false; //when one non numeric value is found, return false
    return true;
}
/////////////////////////////////////////////////////////////////////////////////////////////////
/////COPIED FROM https://www.tutorialspoint.com/how-to-check-if-input-is-numeric-in-cplusplus///
////////////////////////////////////////////////////////////////////////////////////////////////

string ask_user_update(short info_asked){

    //this function returns a feedback message for users according to
    //input needed by program to execute tasks

    if (info_asked == ASK_PRICE) {
        return "Enter NEW Asset price: "; 
    } else if (info_asked == ASK_QUANTITY) {
        return "Enter NEW Asset purchase quantity: "; 
    } else if (info_asked == ASK_DAY) {
        return "Enter NEW Asset purchase day: "; 
    } else if (info_asked == ASK_MONTH) {
        return "Enter NEW Asset purchase month: "; 
    } else if (info_asked == ASK_YEAR) {
        return "Enter NEW Asset purchase year: "; 
    } else if (info_asked == TRY_AGAIN_ASSET){
        return "\nInput Choice: "; 
    }
 
    return "Error."; 
}


void ClearScreen()
{
    //this function clears the screen after 'Enter' is pressed by user

    cout << "Press Enter key to continue..."; 
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
    cin.get();  // or getchar()
    cout << string( 100, '\n' );
}


 
/************************************************HELPER FUNCTIONS****************************************************/