//
// Created by jingbao on 18-12-22.
//
//
// Created by jingbao on 18-12-8.
//
#include <iostream>

using namespace std;

class Student{
public:
    int age;
    Student(){}
    Student(int age){
        age=age;
    }
    ~Student(){}
    void disPlay(){
        cout<<age<<endl;

    }

    int getAge();
};

int Student::getAge(){
    return age;
}

class Father{
public:
    string name;
    void say(){
        cout<<name<<endl;
    }
};

class Son :public Father{
public:
    string name;
    void disPlay();
};
void Son::disPlay() {
    cout<<name<<endl;
}


int test(){
    Student s;
    s.age=10;
    s.disPlay();
    Son s1;
    s1.name="xxxxxxxx";
    s1.disPlay();



}
