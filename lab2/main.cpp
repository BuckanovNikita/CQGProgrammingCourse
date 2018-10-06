#include <iostream>
#include "simple_vector.h"
#include "simple_vector.cpp"
#include <vector>
using std::cout;
using std::vector;
using std::endl;

const int N = 20;

int main() {
    std::vector<int> c;
    simple_vector<int> t;
    cout<<"empty check"<<endl;
    cout<<t.empty()<<" "<<c.empty()<<endl;
    cout<<"push_back check"<<endl;
    for(int i = 0;i<N; i++) {
        t.push_back(i);
        c.push_back(i);
    }
    cout<<t.size()<<" "<<c.size()<<endl;
    for(int i=0; i<t.size(); i++)
        cout<<t[i]<<" ";
    cout<<endl;
    for(int i=0; i<c.size(); i++)
        cout<<c[i]<<" ";
    cout<<endl;
    cout<<"increase resize check"<<endl;
    t.resize(26, 9);
    c.resize(26, 9);
    cout<<t.size()<<" "<<c.size()<<endl;
    for(int i=0; i<t.size(); i++)
        cout<<t[i]<<" ";
    cout<<endl;
    for(int i=0; i<c.size(); i++)
        cout<<c[i]<<" ";
    cout<<endl;
    cout<<"decrease resize check"<<endl;
    t.resize(0, 9);
    c.resize(0, 9);
    cout<<t.capacity()<<" "<<c.capacity()<<endl;
    cout<<t.size()<<" "<<c.size()<<endl;
    for(int i=0; i<t.size(); i++)
        cout<<t[i]<<" ";
    cout<<endl;
    for(int i=0; i<c.size(); i++)
        cout<<c[i]<<" ";
    cout<<endl;
    cout<<"reserve check"<<endl;
    cout<<t.capacity()<<" "<<c.capacity()<<endl;
    t.reserve(55);
    c.reserve(55);
    cout<<t.capacity()<<" "<<c.capacity()<<endl;
    t[54] = 10;
    c[54] = 10;
    cout<<t.capacity()<<" "<<c.capacity()<<endl;
    cout<<t.size()<<" "<<c.size()<<endl;
    return 0;
}