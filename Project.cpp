#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <time.h>

#define MAXLIMIT 3

using namespace std;

void delay(int s)
{
    int milli = 1000*s;
    int cu = clock();
    while(clock() < cu + milli);
}

class Person
{
public:
    string name;
    int age;
    int type;
    void showPerson()
    {
        cout<<"Enter name: ";
        cin>>name;
        cout<<"Enter age: ";
        cin>>age;
    }
    virtual void display() = 0;
    virtual int getId() = 0;
};

// ------------------------------------------------------------------------------------

class Student : public Person
{
public:
    static int rollCount;
    int rollNo;
    Student()
    {
        cout<<"\nStudent details: \n";
        type = 2;
        showPerson();
        rollNo = rollCount++;
    }
    int getId()
    {
        return rollNo;
    }
    void display()
    {
        
        cout<<name<<"\t "<<age<<"\t "<<rollNo<<"\n";
    }
};
int Student::rollCount = 301;

// ------------------------------------------------------------------------------------

class Professor : public Person
{
public:
    static int idCount;
    int id;
    string courseTaught;
    Professor()
    {
        cout<<"\nProfessor details: \n";
        type = 1;
        showPerson();

        id = idCount++;
    }
    int getId()
    {
        return id; 
    }
    void display()
    {
        cout<<name<<"\t "<<age<<"\t "<<id<<"\n";
    }
};
int Professor::idCount = 10;

// ------------------------------------------------------------------------------------

class CourseRoom
{
public:
    string courseName;
    string courseCode;
    map<string , string> Assignments;

    void setCourseRoom()
    {
        cout<<"\nCourse details: \n";
        cout<<"Course name: ";
        cin>>courseName;
        cout<<"Course code: ";
        cin>>courseCode;
    }

    void display()
    {
        cout<<courseName<<" \t\t"<<courseCode<<"\n";
    }

    void displayAssignments()
    {
        cout<<"Course name: "<<courseName;
        cout<<"\nCourse code: "<<courseCode;

        if(Assignments.empty())
        {
            cout<<"\nNo Assignments !!";
            return ;
        }
        cout<<"\n\nAssignment \t Due date\n";
        auto it = Assignments.begin();
        for( ; it!=Assignments.end() ; it++)
        {
            cout<<(it->first)<<"\t "<<(it->second)<<endl;
        }
    }
};

// ------------------------------------------------------------------------------------

class Authentication
{
    map<int , string> id_pass; 
public:
    void getData(int userId)
    {
        string password;
        cout<<"Your User Id: "<<userId<<"\n";
        cout<<"Enter password: ";
        cin>>password;
        id_pass.insert({userId , password});
    }
    bool checkAuthentication(int userId , string password)
    {
        if(id_pass[userId] == password)
            return true;
        return false;
    }
};

// ------------------------------------------------------------------------------------

class ClassRoom
{
public:
    vector<Person*> person;
    vector<CourseRoom> courseRoom;
    Authentication authorize;
    int noOfCourse;
    int noOfStudents;
    ClassRoom()
    {
        cout<<"Enter no. of courses: ";
        cin>>noOfCourse;
        for(int i=0 ; i<noOfCourse ; i++)
        {
            CourseRoom temp;
            temp.setCourseRoom();
            courseRoom.push_back(temp);
            
            Person *tempProf = new Professor();
            person.push_back(tempProf);

            authorize.getData(tempProf->getId());

        }
        cout<<"\n\nEnter no. of students to be added to the class room: ";
        cin>>noOfStudents;
        for(int i=0 ; i<noOfStudents ; i++)
        {
            Person *tempStud = new Student();
            person.push_back(tempStud);
            authorize.getData(tempStud->getId());
        }
    }

    void attendence()
    {
        cout<<"Name \t Age \t Unique Id\n";
        for(int i=0 ; i<person.size() ; i++)
        {
            if(person[i]->type == 2)
                person[i]->display();
        }
    }

    void displayClassRoom()
    {
        cout<<"Course name \t Course code\n";
        for(int i=0 ; i<noOfCourse ; i++)
            courseRoom[i].display();
        cout<<"\n";
        cout<<"Name \t Age \t Unique Id\n";
        for(int i=0 ; i<person.size() ; i++)
            person[i]->display();
    }

    void assignAssignment(int userId)
    {
        system("cls");
        cout<<"Your are assigning an assignment\n\n";
        string docName , dueDate;
        cout<<"Enter Document name: ";
        cin>>docName;
        cout<<"Enter Due Date: ";
        cin>>dueDate;
        for(int i=0 ; i<noOfCourse ; i++)
        {
            if(person[i]->getId()==userId)
            {
                courseRoom[i].Assignments.insert({docName , dueDate});
                cout<<"Assignment assigned successfully\n";
                delay(2);
                return;
            }
        }
    }

    void assignedAssignment()
    {
        for(int i=0 ; i<noOfCourse ; i++)
        {
            cout<<"\n";
            courseRoom[i].displayAssignments();
        }
    }

    void coursesEnrolled()
    {
        cout<<"\nCourse Name \t Course Code\n";
        for(int i=0 ; i<noOfCourse ; i++)
        {
            courseRoom[i].display();
        }
    }

    bool checkValidUser(int userId , string password )
    {
        return authorize.checkAuthentication(userId , password);
    }
};

// ------------------------------------------------------------------------------------

int main()
{
    system("cls");
    
    ClassRoom c;
    
    int choice , userId , count=0;
    string password;
    bool validUser=false , logout=false;
    while (true)
    {
        system("cls");
        cout<<"\tWelcome to ABC class room\n\n";
        cout<<"1. Login as Professor\n";
        cout<<"2. Login as Student\n";
        cout<<"3. Close the app\n";
        cout<<"Enter your choice: ";
        cin>>choice;
        switch (choice)
        {
        case 1:
                count = 0;
                do
                {
                    system("cls");
                    cout<<"\tWelcome to ABC class room\n\n";
                    cout<<"Enter User Id: ";
                    cin>>userId;
                    cout<<"Enter Password: ";
                    cin>>password;
                    if(userId <= 100)
                        validUser = c.checkValidUser(userId , password);
                    else
                        validUser = false;
                    count++;
                    if(count == MAXLIMIT)
                    {
                        cout<<"You have crossed maximum limit !!\n";
                        exit(0);
                    }
                    if(!validUser)
                    {
                        cout<<"Wrong User Id or Password !!";
                        delay(2);
                    }
                } while (!validUser);
            
                while (!logout)
                {
                    system("cls");
                    cout<<"\tWelcome to ABC class room\n\n";
                    cout<<"1. Assign an assignment\n";
                    cout<<"2. View attendence\n";
                    cout<<"3. Logout\n";
                    cout<<"Enter your choice: ";
                    cin>>choice;
                    switch (choice)
                    {
                    case 1:
                            c.assignAssignment(userId);
                            break;
                    case 2:
                            c.attendence();
                            delay(2);
                            break;
                    case 3:
                            logout = true;
                            cout<<"\nLogged Out Successfully";
                            delay(2);
                            break;
                    default:
                            cout<<"Wrong choice !!\n";
                    }
                }
                logout = false;
                choice = 1;
                break;
        case 2:
                count = 0;
                do
                {
                    system("cls");
                    cout<<"\tWelcome to ABC class room\n\n";
                    cout<<"Enter User Id: ";
                    cin>>userId;
                    cout<<"Enter Password: ";
                    cin>>password;
                    if(userId > 300)
                        validUser = c.checkValidUser(userId , password);
                    else
                        validUser = false;
                    count++;
                    if(count == MAXLIMIT)
                    {
                        cout<<"You have crossed maximum limit !!\n";
                        exit(0);
                    }
                    if(!validUser)
                    {
                        cout<<"Wrong User Id or Password !!";
                        delay(2);
                    }
                } while (!validUser);

                while (!logout)
                {
                    system("cls");
                    cout<<"\tWelcome to ABC class room\n\n";
                    cout<<"1. Check for assigned assignments\n";
                    cout<<"2. Courses Enrolled\n";
                    cout<<"3. Logout\n";
                    cout<<"Enter your choice: ";
                    cin>>choice;
                    switch (choice)
                    {
                    case 1:
                            c.assignedAssignment();
                            delay(3);
                            break;
                    case 2:
                            c.coursesEnrolled();
                            break;
                    case 3:
                            logout = true;
                            cout<<"\nLogged Out Successfully";
                            delay(2);
                            break;
                    default:
                            cout<<"Wrong choice !!\n";
                    }
                }
                logout = false;
                choice = 2;
                break;
        case 3:
                cout<<"App closed !!\n";
                exit(0);
        default:
                cout<<"Wrong choice !!\n";
        }
    }
    return 0;
}