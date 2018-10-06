
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> storage(n);
    for(int i=0; i<n; i++)
    {
        cin>>storage[i];
    }
    int m;
    cin>>m;
    bool find = false;
    for(int i=0; i<n-1; i++)
    {
        if( equal_range(storage.begin()+i, storage.end(), m-n).first > storage.begin()+i)
        {
            find = true;
            cout<<i<<" "<< equal_range(storage.begin()+i+1, storage.end(), m-n).first - storage.begin()<<endl;
        }
    }
    if(!find)
        cout<<"NO";
    return 0;
}