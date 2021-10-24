#include<bits/stdc++.h>
using namespace std;
#define uc unsigned char
vector<bool> triad_encrypt(vector<uc>K, vector<uc>N, vector<bool> M);
vector<bool> triad_decrypt(vector<uc>K, vector<uc>N, vector<bool> C);
vector<bool> triad_sc(vector<uc>K, vector<uc>N, vector<bool> M);
vector<vector<uc>> triadUpd(vector<uc>a, vector<uc> b, vector<uc> c, bool msg);
vector<vector<uc>> triadP(vector<uc>a,vector<uc>b,vector<uc> c);

vector<bool> triad_encrypt(vector<uc>K, vector<uc>N, vector<bool> M)
{
    vector<bool> C = triad_sc(K,N,M);
    return C;
}

vector<bool> triad_decrypt(vector<uc>K, vector<uc>N, vector<bool> C)
{
    vector<bool> M = triad_sc(K,N,C);
    return M;
}
vector<bool> triad_sc(vector<uc>K, vector<uc>N, vector<bool> M)
{
    vector<uc>con = {0xFE, 0xFF, 0xFF, 0xFF};
    vector<uc>a ={N[0],K[4],con[3],K[3],con[2],K[2],con[1],K[1],con[0],K[0]} ;
    vector<uc> b(11);
    vector<uc> c(11);
    for(int i=0;i<11;i++)
    {
        b[i] = N[11-i];
        c[i] = K[15-i];
    }
    vector<vector<uc>> tmp = triadP(a,b,c);
    a = tmp[0];
    b = tmp[1];
    c = tmp[2];
    bool z;
    int mlen = M.size()/8;
    vector<bool> C(M.size());
    for(int i=0;i<mlen;i++)
    {
        for(int j=7;j>=0;j--)
        {
            tmp = triadUpd(a,b,c,0);
            a = tmp[0];
            b = tmp[1];
            c = tmp[2];
            z = tmp[3][0];
            C[i*8+j] = M[i*8+j]^z;
        }
        // cout<<'\n';
    }
    return C;
}
vector<vector<uc>>triadP(vector<uc>a,vector<uc>b,vector<uc> c)
{
    vector<uc> z;
    vector<vector<uc>> tmp={a,b,c,z};
    for(int i=1;i<=1024;i++)
    {
        tmp = triadUpd(a,b,c,0);
        a = tmp[0];
        b = tmp[1];
        c = tmp[2];
    }

    return vector<vector<uc>>{a,b,c};

}
int ccount=40;
vector<vector<uc>> triadUpd(vector<uc>a, vector<uc> b, vector<uc> c, bool msg)
{
    vector<bool>abit(81); vector<bool>bbit(89); vector<bool>cbit(89);
    bool t1, t2, t3, z;
    for(int i=0;i<10;i++)
    {
        for(int j=0;j<8;j++)
        {
            abit[i*8+j+1] = (a[i] & (1<<(7-j)))>>(7-j);
        }
    }
    for(int i=0;i<11;i++)
    {
        for(int j=0;j<8;j++)
        {
            bbit[i*8+j+1] = (b[i] & (1<<(7-j)))>>(7-j);
            cbit[i*8+j+1] = (c[i] & (1<<(7-j)))>>(7-j);
        }
    }
    t1 = abit[68] ^ abit[80] ^ bbit[85]*cbit[85];
    t2 = bbit[64] ^ bbit[88];
    t3 = cbit[68] ^ cbit[88];
    z = t1 ^ t2 ^ t3;
    t1 = t1 ^ abit[73]*abit[79] ^ bbit[66] ^ msg;
    t2 = t2 ^ bbit[65]*bbit[87] ^ cbit[84] ^ msg;
    t3 = t3 ^ cbit[77]*cbit[87] ^ abit[74] ^ msg;
    for(int i=80;i>=2;i--)
    {
        abit[i]=abit[i-1];
    }
    abit[1] = t3;
    for(int i=88; i>=2;i--)
    {
        bbit[i] = bbit[i-1];
    }
    bbit[1]=t1;
    for(int i=88;i>=2;i--)
    {
        cbit[i]=cbit[i-1];
    }
    cbit[1] = t2;
    for(int i=0;i<10;i++)
    {
        int base = 1;
        a[i]=0;
        for(int j=8;j>=1;j--)
        {
            a[i]+=abit[8*i+j]*base;
            base*=2;
        }
    }
    for(int i=0;i<11;i++)
    {
        int base = 1;
        b[i]=0;
        c[i]=0;
        for(int j=8;j>=1;j--)
        {
            b[i]+=bbit[8*i+j]*base;
            c[i]+=cbit[8*i+j]*base;
            base*=2;
        }
    }

    return vector<vector<uc>>{a,b,c,vector<uc>{z}};
}
int main()
{
    // Key = 62802944DE7CA5894E5759D351ADAC86
    // Nonce = 66826498D9A8877565705A8A
    vector<uc> K={0xC3,0x80,0x5E,0x6E,0x03,0x28,0xDA,0x4C,0xD7,0x6A,0x19,0xED,0xD2,0xD3,0x99,0x4C};
    
    vector<uc> N= {0xB4,0xA8,0xCA,0x99,0xB2,0xC2,0x37,0x2A,0xCB,0x08,0xCF,0x61};
    //05F1ECD96733B79950A3E314D3D934F7
    vector<uc>hex_M={0x79,0x39,0x02,0xD8,0xE5,0x0A,0xF8,0x9D,0x77,0x09,0xD1,0xA5,0x96,0xC1,0xF4,0x1F,0x95,0xAA,0x82,0xCA,0x6C,0x49,0xAE,0x90,0xCD,0x16,0x68,0xBA,0xAC,0x7A};
    vector<bool> M ;
    for(auto i: hex_M)
    {
        int inp=i;
        vector<bool>tmp(8,0);
        int ind=7;
        while(ind>=0)
        {
            tmp[ind]=inp%2;
            inp/=2;
            ind--;
        }
        for(auto i: tmp )M.push_back(i);
    }
    int l =M.size();
    // vector<bool> M;
    cout<<K.size()<<' '<<N.size()<<' '<<M.size()<<'\n';
    vector<bool> C = triad_encrypt(K,N,M);
    cout<<C.size()<<'\n';
    // for(int i=0;i<l;i++) cout<<(int)C[i]<<' ';
     cout<<'\n';
    ccount=40;
    for(int i=0;i<l;i+=8)
    {
        int mult=128;
        uc ans=0;
        for(int j=0;j<8;j++)
        {
            ans+=C[i+j]*mult;
            mult/=2;
        }
        // cout<<(int)ans<<' ';
        cout<<hex<<(int)ans<<' ';
    }
   
    vector<bool> dec= triad_decrypt(K,N,C);
    
    // for(int i=0;i<l;i++) cout<<(int)dec[i]<<' ';
    cout<<'\n';
    cout<<'\n';

}