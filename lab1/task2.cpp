#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin>>n;
    vector<int> nums(n);
    int sum1 = 0;
    int sum2 = 0;
    for(int i=0; i<n; i++)
    {
        cin>>nums[i];
        if(i<n/2)
            sum1+=nums[i];
        else
            sum2+=nums[i];
    }
    bool print = false;
    for(int i=0;i<10;i++)
    {
        for(int j =0; j<10; j++)
        {
            if(sum1+i == sum2+j)
            {
                cout<<i;
                for(int t: nums)
                    cout<<t;
                cout<<j<<endl;
                print =true;
            }
        }
    }
    if(!print)
        cout<<"NO";
    return 0;
}