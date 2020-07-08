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

    char fileName[] = "student.dat";
    ifstream inFile;
    ofstream outFile;

    //can use fstream file instead to avoid using two var
    int id = 100;
    char name[20] = "Samnang";
    int age = 20;
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
    inFile.open(fileName, ios::in);
    if (!inFile)
    {
        cerr << "Can't open file " << fileName << endl;
        return 1;
    }
    while (inFile >> id >> name >> age)
    {
        cout << id << " " << name << " " << age << endl;
    }
    inFile.close();

    return 0;
}

//alt
}

fstream file;
int id=104;
char name[20]="Chhaikheang";
int age=26;
//Step1
file.open(fileName, ios::out|ios::binary);
if(!file){
cerr<<"Can't open file "<<fileName<<endl;
return 1;
}
//Step2
file<<id<<" "<<name<<" "<<age<<endl;
//Step3
file.close();

//Read data from file
file.open(fileName,ios::in);
if(!file){
cerr<<"Can't open file "<<fileName<<endl;
return 1;
}
while(file>>id>>name>>age){
cout<<id<<" "<<name<<" "<<age<<endl;
}
file.close();

Send message to Public Chat

//Write struct student(id,name,age) into file
// Student students[2]={
// {100,"Dara",20},
// {200,"Lina",18}
// };
// fstream file;
// file.open("students.bin", ios::out|ios::binary);
// for(int i=0;i<2;i++){
// Student student=students[i];
// file.write((char *) &student,sizeof(student));
// }
//
// file.close();



//Read struct student from file
fstream file;
Student stu;

file.open("students.bin", ios::in|ios::binary);
while(file){
file.read((char *) &stu,sizeof(stu));
cout<<stu.id<<" "<<stu.name<<" "<<stu.age<<endl;
}

file.close()