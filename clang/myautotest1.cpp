//
// Created by jingbao on 18-12-8.
//

#include <iostream>
#include <vector>
#include <typeinfo>
using namespace std;

template<class T, class U>//template<typename T, typename U>
void add(T t, U u)
{
    auto s = t + u;
    cout << "type of t + u is " << typeid(s).name() << endl;
}
int autotest1()
{
    // 简单自动类型推断
    auto a = 123;
    cout << "type of a is " << typeid(a).name() << endl;
    auto s("fred");
    cout << "type of s is " << typeid(s).name() << endl;

    // 冗长的类型说明（如迭代器）
    vector<int> vec;
    auto iter = vec.begin();
    cout << "type of iter is " << typeid(iter).name() << endl;

    // 使用模板技术时，如果某个变量的类型依赖于模板参数，使用auto确定变量类型
    add(101, 1.1);
}

