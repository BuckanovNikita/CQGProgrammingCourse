
#include <bits/stdc++.h>
using namespace std;

struct Friend {
    int count;
    int last_visit;
    int id;
    Friend()
    {
        count=0;
        last_visit=0;
        id=0;
    }
    Friend(int x) : id(x)
    {
        count = 0;
        last_visit = 0;
    }
    void inc(const int &last)
    {
        count+=1;
        last_visit = last;
    }

};
bool compare(const Friend &a, const Friend &b)
{
    if(a.count!= b.count)
        return a.count>b.count;
    else
        return  a.last_visit>b.last_visit;
}
int main() {
    int friendsCount;
    cin>>friendsCount;
    int n;
    cin >> n;
    vector<Friend> history(friendsCount+1);
    for(int i=0;i<=friendsCount;i++)
    {
        history[i] = Friend(i);
    }
    for(int i=0; i<n; i++)
    {
        int q;
        cin>>q;
        history[q].inc(i);
    }
    sort(history.begin(), history.end(), compare);
    for(Friend q: history)
    {
        if(q.id!=0)
            cout<<q.id<<" ";
    }
    return 0;
}