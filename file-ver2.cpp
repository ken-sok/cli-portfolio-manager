//
// main.cpp
// File
//
// Created by Virak Un on 7/1/20.
// Copyright © 2020 Limkokwing. All rights reserved.
//

#include <iostream>
#include <fstream>

using namespace std;
int add();

int main()
{
    // //File Input/Output Concept
    //
    // //Save or Write Data into File
    // //Step1: Open Data File
    // //Overide data file
    // //ofstream outf("Sample.dat", ios::out);
    // //Appending data file
    // ofstream outf("Sample.dat", ios::app);
    // //Step2: Manupulate Data File (Read/Retrieve and Write/Save data)
    // if(!outf){
    // cerr<<"Sample.dat could not found be opened for writing";
    // return 1;
    // }
    // outf<<"This is line 1"<<"\n";
    // outf<<"This is line 2"<<"\n";
    // outf<<"This is line 5"<<"\n";
    // outf<<"This is line 6"<<"\n";
    //
    // //Step3: Close Data File
    // outf.close();
    //
    // //Retrieve or Read Data from File
    // //Step1: Open Data File
    // ifstream inf("Sample.dat", ios::in);
    // //Step2: Manupulate Data File
    // if(!inf){
    // cerr<<"Sample.dat could not found be opened for reading";
    // return 1;
    // }
    // while(inf){
    // string strInput;
    // getline(inf,strInput);
    // cout<<strInput<<"\n";
    // }
    // //Step3: Close Data File
    // inf.close();

    //Another option
    //Student Data(id,name,age) into student.dat file

    // char fileName[]="student.dat";
    // ifstream inFile;
    // ofstream outFile;
    // int id=100;
    // char name[20]="Samnang";
    // int age=20;
    // //Step1
    // outFile.open(fileName, ios::out);
    // if(!outFile){
    // cerr<<"Can't open file "<<fileName<<endl;
    // return 1;
    // }
    // //Step2
    // outFile<<id<<" "<<name<<" "<<age<<endl;
    // //Step3
    // outFile.close();

    //Read data from file
    // inFile.open(fileName,ios::in);
    // if(!inFile){
    // cerr<<"Can't open file "<<fileName<<endl;
    // return 1;
    // }
    // while(inFile>>id>>name>>age){
    // cout<<id<<" "<<name<<" "<<age<<endl;
    // }
    // inFile.close();

    int arr[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int num;
    bool flag = false;
    do
    {
        cout << "Enter a number ";
        cin >> num;
        for (int i = 0; i < 10; i++)
        {
            if (num == arr[i])
            {
                flag = true;
                break;
            }
        }
    } while (flag == false);

    cout << add() << endl;

    return 0;
}

int add()
{
    return 10 + 20;
