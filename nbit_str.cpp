#include <iostream>
#include <string>
#include <cstring>
#include <utility>
#include <bitset>
#include <algorithm>
using namespace std;
constexpr int MAX = 256;
bool visited[MAX] = {false};

void sub_str(const string & s,int from,int start,int end)
{
    if(from == end)
    {
        return ;
    }

    if(start == end)//reach tail
    {
        for(int i = from;i<end;++i)
        {
                if(visited[i])
                {
                    cout<<s[i];
                }
        }
        cout <<endl;
    }else{
        visited[start] = true;
        sub_str(s,from,start+1,end);
        visited[start] = false;
        sub_str(s,0,start,start);
        sub_str(s,start+1,start+1,end);
        
    }
}
int main()
{
    ios::sync_with_stdio(false);
    string s;
    int n;
    cout << "input the expect length of string and the chars:n chars"<<endl;
    cin >> n;
    cin >> s;
    sub_str(s,0,0,s.length());
    return 0;
}

