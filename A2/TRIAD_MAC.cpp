#include<bits/stdc++.h>
using namespace std;
#define uc unsigned char

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
vector<vector<uc>> TriadPB(vector<uc>a,vector<uc>b,vector<uc>c)
{
    vector<vector<uc>> tmp = triadUpd(a,b,c,1);
    a = tmp[0];
    b = tmp[1];
    c = tmp[2];
    bool z  = tmp[3][0];
    for(int i=2;i<=1024;i++)
    {
        vector<vector<uc>> tmp = triadUpd(a,b,c,0);
        a = tmp[0];
        b = tmp[1];
        c = tmp[2];
        z  = tmp[3][0];
    }
    return vector<vector<uc>>{a,b,c};
}

vector<uc> Triad_MAC(vector<uc>K, vector<uc>N, vector<uc>M,vector<uc> A)
{
    vector<uc>T(8,0);
    int mlen = M.size();
    int adlen = A.size();
    vector<uc>con = {0xFE, 0xFF, 0xFF, 0xFF};
    vector<uc>a={N[0],K[4],con[3],K[3],con[2],K[2],con[1],K[1],con[0],K[0]};
    vector<uc>b(11);
    vector<uc>c(11);
    for(int i=0;i<11;i++)
    {
        b[i] = N[11-i];
        c[i] = K[15-i];
    }
    vector<vector<uc>> tmp = TriadPB(a,b,c);
    a = tmp[0]; b = tmp[1];c = tmp[2];

    for(int i=0;i<adlen;i++)
    {
        for(int j=7;j>=0;j--)
        {
            bool A_ij = (A[i] & (1<<(7-j)))>>(7-j);
            tmp = triadUpd(a,b,c,A_ij);
            a = tmp[0]; b = tmp[1]; c = tmp[2];
        }
    }
    for(int i=0;i<mlen;i++)
    {
        for(int j=7;j>=0;j--)
        {
            bool M_ij = (M[i] & (1<<(7-j)))>>(7-j);
            tmp = triadUpd(a,b,c,M_ij);
            a = tmp[0]; b = tmp[1];c = tmp[2];
        }
    }
    tmp = TriadPB(a,b,c);
    a = tmp[0]; b = tmp[1]; c = tmp[2];

    for(int i=0;i<8;i++)
    {
        for(int j=0;j<8;j++)
        {
            tmp = triadUpd(a,b,c,0);
            a = tmp[0]; b = tmp[1]; c = tmp[2];
            bool z = tmp[3][0];
            if(z)
            {
                T[i] = T[i] | (1<<j);
            }
        }
    }
    return T;
}
vector<uc> pad_A(vector<uc>A)
{
    int adlen = A.size();
    for(int i=0;i<49;i+=8)
    {
        A.push_back((adlen>>i)&0xFF);
    }

    return A;
}
int main()
{

    vector<uc> K={0xE6,0x05,0x3C,0x7C,0x94,0x75,0xD8,0xBE,0x61,0x89,0xF9,0x5C,0xBB,0xA8,0x99,0x0F};
    vector<uc> N={0xDB,0x5C,0x02,0x1A,0xFE,0x43,0xFB,0xFA,0xAA,0x3A,0xFB,0x29};
    vector<uc> M = {0x95,0x87,0x70,0xE9,0x3E,0xA1,0x41,0xE1,0xFC,0x67,0x3E,0x01,0x7E,0x97,0xEA,0xDC,0x6B,0x96,0x8F,0x38,0x5C,0x2A,0xEC};
    vector<uc> A={};
    A = pad_A(A);
    vector<uc> T = Triad_MAC(K,N,M,A);
    for(auto i: T) cout<<hex<<(int)i<< ' ';


}