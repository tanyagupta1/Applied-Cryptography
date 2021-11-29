#include <bits/stdc++.h>
using namespace std;

int main()
{
    string s="3DC6697351FF4AEC29CDBAABF2FBE3467CC254F81BE8";
    for(int i=1;i<s.length();i+=5)
    {
        string start = s.substr(0,i+1);
        start+=",0x";
        start+=s.substr(i+1,(s.length()-i-1));
        s = start;
        
    }
    cout<<"0x"<<s.substr(0,s.length()-3)<<'\n';
}