#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <cstdio>
#include <string>
using namespace std;
void addStudent(){
    ofstream file("students.txt", ios::app);
    int id, age;
    string name, course;
    cout<<"Enter ID (numbers only): ";
    cin>>id;
    cin.ignore(1000, '\n');
    cout<<"Enter Name: ";
    getline(cin, name);
    cout<<"Enter Age: ";
    cin>>age;
    cin.ignore(1000, '\n');
    cout<<"Enter Course: ";
    getline(cin, course);
    file<<id<<"|"<<name<<"|"<<age<<"|"<<course<<endl;
    file.close();
    cout<<"Student Added Successfully\n";
}
void displayStudents(){
    ifstream file("students.txt");
    if (!file.is_open()) {
        cout<<"No records found!\n";
        return;
    }
    string line;
    cout<<"\n*** Student Records ***\n";
    while (getline(file,line)) {
        if (line.length()==0)
            continue;
        stringstream ss(line);
        string id,name,age,course;
        if (getline(ss,id,'|')&&getline(ss,name,'|')&&getline(ss,age,'|')&&getline(ss,course))
		 {
            cout<<"\nID: "<<id;
            cout<<"\nName: "<<name;
            cout<<"\nAge: "<<age;
            cout<<"\nCourse: "<<course;
            cout<<"\n------------------------";
        }
        else {
            continue;
        }
    }
    file.close();
}
void searchStudent(){
    ifstream file("students.txt");
    string line;
    int searchId;
    bool found=false;
    cout<<"Enter ID to search: ";
    cin>>searchId;
    while (getline(file, line)) {
        stringstream ss(line);
        string idStr,name,ageStr,course;
        getline(ss,idStr,'|');
        getline(ss,name,'|');
        getline(ss,ageStr,'|');
        getline(ss,course);
        if (atoi(idStr.c_str())==searchId) {
            cout<<"\nStudent Found:\n";
            cout<<"ID: "<<idStr<<"\nName: "<<name<<"\nAge: "<<ageStr<<"\nCourse: "<<course<<endl;
            found=true;
        }
    }
    if (!found)
        cout<<"Student not found\n";
    file.close();
}
void updateStudent(){
    ifstream file("students.txt");
    ofstream temp("temp.txt");
    string line;
    int searchId;
    bool found=false;
    cout<<"Enter ID to update: ";
    cin>>searchId;
    cin.ignore(1000,'\n');
    while (getline(file,line)) {
        stringstream ss(line);
        string idStr,name,ageStr,course;
        getline(ss,idStr,'|');
        getline(ss,name,'|');
        getline(ss,ageStr,'|');
        getline(ss,course);
        if (atoi(idStr.c_str())==searchId) {
            cout<<"Enter new details:\n";
            cout<<"New Name: ";
            getline(cin, name);
            cout<<"New Age: ";
            getline(cin, ageStr);
            cin.ignore(1000,'\n');
            cout<<"New Course: ";
            getline(cin, course);
            cin.ignore(1000,'\n');
            found=true;
        }
        temp<<idStr<<"|"<<name<<"|"<<ageStr<<"|"<<course<<endl;
    }
    file.close();
    temp.close();
    remove("students.txt");
    rename("temp.txt", "students.txt");
    if (found)
        cout<<"Updated Successfully\n";
    else
        cout<<"Student not found\n";
}
void deleteStudent() {
    ifstream file("students.txt");
    ofstream temp("temp.txt");
    string line;
    int deleteId;
    bool found=false;
    cout<<"Enter ID to delete: ";
    cin>>deleteId;
    cin.ignore(1000,'\n');
    while (getline(file, line)) {
        stringstream ss(line);
        string idStr, name, ageStr, course;
        getline(ss, idStr,'|');
        getline(ss, name,'|');
        getline(ss, ageStr,'|');
        getline(ss, course);
        if (atoi(idStr.c_str())==deleteId) {
            found=true;
            continue;
        }
        temp<<idStr<<"|"<<name<<"|"<<ageStr<<"|"<<course<<endl;
    }
    file.close();
    temp.close();
    remove("students.txt");
    rename("temp.txt", "students.txt");
    if (found)
        cout<<"Deleted Successfully\n";
    else
        cout<<"Student not found\n";
}
int main() {
    int choice;
    do {
        cout<<"\n***** Student Management System *****\n";
        cout<<"1. Add Student\n";
        cout<<"2. Display Students\n";
        cout<<"3. Search Student\n";
        cout<<"4. Update Student\n";
        cout<<"5. Delete Student\n";
        cout<<"6. Exit\n";
        cout<<"Enter choice: ";
        cin>>choice;

        switch (choice){
            case 1: addStudent(); break;
            case 2: displayStudents(); break;
            case 3: searchStudent(); break;
            case 4: updateStudent(); break;
            case 5: deleteStudent(); break;
            case 6: cout<<"Exiting...\n"; break;
            default: cout<<"Invalid choice!\n";
        }

    } while(choice!=6);
    return 0;
}