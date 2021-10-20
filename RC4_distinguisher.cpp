#include<bits/stdc++.h>
using namespace std;
#define uc unsigned char

/* returns 0 if the list is a list of random bytes, returns 1 if it is a list of ciphertexts of some M */
bool RC4_distinguisher(vector<vector<uc>>L, vector<uc> M)
{
    for(int c=0;c<256;c++)
    {
        for(int i=0;i<16;i++)  L[c][i] = L[c][i]^M[i];
    }
    int n_zeroes=0;
    for(int i=0;i<256;i++)
    {
        if(L[i][1]==0) n_zeroes++;
    }
    if(n_zeroes>=2) return 1;
    else return 0;
}

int main()
{


}