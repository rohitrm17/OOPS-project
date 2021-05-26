#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Person
{
public:
    string name;
    int age;
    int type;
    void getPerson()
    {
        cout<<"Enter name: ";
        cin>>name;
        cout<<"Enter age: ";
        cin>>age;
    }
    virtual void display() = 0;
};

// ------------------------------------------------------------------------------------

class Student : public Person
{
public:
    static int rollCount;
    int rollNo;
    Student()
    {cout<<"Student\n";
        type = 2;
        getPerson();
        rollNo = rollCount++;
    }
    void display()
    {
        
        cout<<name<<"\t"<<age<<"\t"<<rollNo<<"\n";
    }
};
int Student::rollCount = 301;

// ------------------------------------------------------------------------------------

class Professor : public Person
{
public:
    static int idCount;
    int id;
    Professor()
    {
        type = 1;
        getPerson();
        id = idCount++;
    }
    void display()
    {
        cout<<name<<"\t"<<age<<"\t"<<id<<"\n";
    }
};
int Professor::idCount = 10;

// ------------------------------------------------------------------------------------

class ClassRoom
{
public:
    vector<Person*> person;
    ClassRoom(vector<Person*> p)
    {
        person = p;
    }
    void attendence()
    {
        for(int i=0 ; i<person.size() ; i++)
        {
            if(person[i]->type == 2)
                person[i]->display();
        }
    }
    void displayEveryoneInClass()
    {
        cout<<"Name \t Age \t Unique Id\n\n";
        for(int i=0 ; i<person.size() ; i++)
            person[i]->display();
    }
};

// ------------------------------------------------------------------------------------

int main()
{
    system("cls");
    vector<Person*> p;
    for(int i=0 ; i<2 ; i++)
    {
        Person *t = new Student();
        p.push_back(t);
        Person *te = new Professor();
        p.push_back(te);
    }
    ClassRoom c(p);
    c.attendence();
    c.displayEveryoneInClass();
    return 0;
}