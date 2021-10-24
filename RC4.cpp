#include<bits/stdc++.h>
#define uc unsigned char
using namespace std;

void print(vector<uc> v)
{
    for(auto i: v) cout<<i<<'|';
    cout<<'\n';
}
vector<uc> RC4_init(vector<uc>K)
{
    vector<uc>S(256);
    for(int i=0;i<256;i++)
    {
        S[i]=(uc)i;
        K[i]=K[i%16];
    }
    int j = 0;
    for(int i=0;i<256;i++)
    {
        j = (j + S[i] + K[i])%256;
        uc sw = S[i];
        S[i] = S[j];
        S[j] = sw;
    }

    return S;
}

vector<vector<uc>> RC4_get_bits(vector<uc>S,int i,int j)
{
    i = (i + 1)%256;
    j = (j + S[i])%256;
    uc sw = S[i];
    S[i] = S[j];
    S[j] = sw;
    uc t = (S[i] + S[j])%256;
    uc y = S[t];
    vector<vector<uc>> ans;
    ans.push_back(S);
    ans.push_back(vector<uc>{(uc)i});
    ans.push_back(vector<uc>{(uc)j});
    ans.push_back(vector<uc>{y});
    return ans;
}

vector<uc> RC4_encrypt(vector<uc> K,int n)
{
    vector<uc>n_bytes(n);

    vector<uc> S(256);
    S = RC4_init(K);
    int i=0;
    int j=0;
    for(int it=0;it<n;it++)
    {
        vector<vector<uc>> tmp = RC4_get_bits(S,i,j);
        n_bytes[it] = tmp[3][0];
        i = tmp[1][0];
        j = tmp[2][0];
        S = tmp[0];
    }
    return n_bytes;
}
int main()
{
    vector<uc> K(256,0);
    vector<uc>input={0xd7,0x64,0xc8,0xcc,0xe9,0x32,0x55,0xc4,0x47,0x8d,0x7a,0xa0,0x5d,0x83,0xf3,0xea};
    for(int i=0;i<16;i++) K[i]=input[i];

    vector<uc> ans = RC4_encrypt(K,16);
    for(auto i: ans) cout<<hex<<(int)i<<' ';
    cout<<'\n';
}

//test vectors: http://what-when-how.com/Tutorial/topic-3kns/RC4-Stream-Cipher-and-Its-Variants-292.html