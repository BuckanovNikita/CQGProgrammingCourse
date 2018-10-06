#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin>>n;
    if(n < 0)
        cout<<"-";
    //n = abs(n);
    list<int> t;
    while(n!=0)
    {
        t.push_back(n%10);
        n/=10;
    }
    int i=0;
    while(t.front() == 0)
        t.pop_front();
    for(int q : t)
        cout<<q;
    return 0;
}