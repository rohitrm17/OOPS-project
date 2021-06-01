#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
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
        cout<<"\nCourse name: "<<courseName;
        cout<<"\nCourse code: "<<courseCode;

        if(Assignments.empty())
        {
            cout<<"\n\nNo Assignments !!";
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

class Class
{
    string classLink;
public:
    vector<int> personPresent;
    string generateLink(int userId)
    {
        if(find(personPresent.begin() , personPresent.end() , userId) != personPresent.end())
        {
            cout<<"\nYou are present in the class.\n";
            delay(2);
            return "";
        }
        if(classLink.size() != 0)
        {
            cout<<"\nA class is running.\n";
            delay(2);
            return "";
        }
        classLink = "";
        char ch='-' , c;
        int x;
        for(int i=0 ; i<11 ; i++)
        {
            if(i==3 || i==7)
                classLink += ch;
            else
            {
                x = rand()%26;
                c = 'a' + x;
                classLink += c;
            } 
        }
        personPresent.push_back(userId);
        return classLink;
    }

    bool joinClass(string link , int userId)
    {
        if(find(personPresent.begin() , personPresent.end() , userId) != personPresent.end())
            return true;

        string temp = classLink;
        
        bool validLink = false;
        
        temp.erase(temp.begin() + 7 , temp.begin() + 8);
        temp.erase(temp.begin() + 3 , temp.begin() + 4);
        
        if(link==classLink || link==temp)
        {
            personPresent.push_back(userId);
            validLink = true;
            sort(personPresent.begin() , personPresent.end());
        }
        return validLink;
    }

    void endClass(int userId)
    {
        if(classLink.size() == 0)
        {
            cout<<"\nClass not yet generated !!";
            return ;
        }
        if(find(personPresent.begin() , personPresent.end() , userId) == personPresent.end())
        {
            cout<<"\nYou can not end class. As you have not started this class.";
            return;
        }
        classLink = "";
        personPresent.clear();
        cout<<"\nClass ended !!";
        delay(2);
    }

};

// ------------------------------------------------------------------------------------
int ID;
bool comp(Person *t)
{
    return t->getId() == ID;
}

class ClassRoom
{
public:
    vector<Person*> person;
    vector<CourseRoom> courseRoom;
    Authentication authorize;
    Class currentClass;
    int noOfCourse;
    int noOfStudents;
    ClassRoom()
    {
        cout<<"\nEnter no. of courses: ";
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
    
    void attendence(int userId)
    {
        if(find(currentClass.personPresent.begin() , currentClass.personPresent.end() , userId) == currentClass.personPresent.end())
        {
            cout<<"\nClass not yet generated !!";
            return ;
        }

        if(currentClass.personPresent.size() == 0)
        {
            cout<<"\nClass not yet generated !!";
            return ;
        }
        if(currentClass.personPresent.size() == 1)
        {
            cout<<"\nNo one present !!";
            return ;
        }
        cout<<"\nName \t Age \t Unique Id\n";
        for(int i=1 ; i<currentClass.personPresent.size() ; i++)
        {
            int in;
            ID = currentClass.personPresent[i];
            auto it = find_if(person.begin() , person.end() , comp);
            in = it-person.begin();
            person[in]->display();
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

    void generateClassLink(int userId)
    {
        int wait = 1;
        string l = currentClass.generateLink(userId);
        if(l.size() == 0)
            return ;
        cout<<"\nGenerated link: "<<l<<endl;
        cout<<"\nIf you want to continue enter 0: ";
        while (wait)
        {
            cin>>wait;
        } 
    }
    
    void endClass(int userId)
    {
        currentClass.endClass(userId);
    }

    void assignAssignment(int userId)
    {
        system("cls");
        cout<<"\nYour are assigning an assignment\n\n";
        string docName , dueDate;
        cout<<"\nEnter Document name: ";
        cin>>docName;
        cout<<"\nEnter Due Date: ";
        cin>>dueDate;
        for(int i=0 ; i<noOfCourse ; i++)
        {
            if(person[i]->getId()==userId)
            {
                courseRoom[i].Assignments.insert({docName , dueDate});
                cout<<"\nAssignment assigned successfully\n";
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

    void joinClassWithLink(int userId)
    {
        string link;
        cout<<"\nEnter the link: ";
        cin>>link;
        if(currentClass.joinClass(link , userId))
        {
            cout<<"\nYou joined the class.\n";
            delay(2);
        }
        else
        {
            cout<<"\nInvalid link !!\n";
            delay(2);
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
    
    srand(time(0));

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
                        cout<<"\nYou have crossed maximum limit !!\n";
                        exit(0);
                    }
                    if(!validUser)
                    {
                        cout<<"\nWrong User Id or Password !!";
                        delay(2);
                    }
                } while (!validUser);
            
                while (!logout)
                {
                    system("cls");
                    cout<<"\tWelcome to ABC class room\n\n";
                    cout<<"1. Assign an assignment\n";
                    cout<<"2. View attendence\n";
                    cout<<"3. Generate class link\n";
                    cout<<"4. End the class\n";
                    cout<<"5. Logout\n";
                    cout<<"Enter your choice: ";
                    cin>>choice;
                    switch (choice)
                    {
                    case 1:
                            c.assignAssignment(userId);
                            break;
                    case 2:
                            c.attendence(userId);
                            delay(2);
                            break;
                    case 3:
                            c.generateClassLink(userId);
                            break;
                    case 4:
                            c.endClass(userId);
                            break;
                    case 5:
                            logout = true;
                            cout<<"\nLogged Out Successfully";
                            delay(2);
                            break;
                    default:
                            cout<<"\nWrong choice !!\n";
                            delay(2);
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
                        cout<<"\nYou have crossed maximum limit !!\n";
                        exit(0);
                    }
                    if(!validUser)
                    {
                        cout<<"\nWrong User Id or Password !!";
                        delay(2);
                    }
                } while (!validUser);

                while (!logout)
                {
                    system("cls");
                    cout<<"\tWelcome to ABC class room\n\n";
                    cout<<"1. Check for assigned assignments\n";
                    cout<<"2. Courses Enrolled\n";
                    cout<<"3. Join class\n";
                    cout<<"4. Logout\n";
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
                            delay(3);
                            break;
                    case 3:
                            c.joinClassWithLink(userId);
                            break;
                    case 4:
                            logout = true;
                            cout<<"\nLogged Out Successfully";
                            delay(2);
                            break;
                    default:
                            cout<<"\nWrong choice !!\n";
                            delay(2);
                    }
                }
                logout = false;
                choice = 2;
                break;
        case 3:
                cout<<"\n\tApp closed !!\n";
                exit(0);
        default:
                cout<<"\nWrong choice !!\n";
                delay(2);
        }
    }
    cout<<endl<<endl;
    return 0;
}