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

    vector<uc> K={0xE9,0x5E,0xD4,0xAB,0xB2,0xCD,0xC6,0x9B,0xB4,0x54,0x11,0x0E,0x82,0x74,0x41,0x21};
    vector<uc> N={0x66,0x32,0x0D,0xB7,0x31,0x58,0xA3,0x5A,0x25,0x5D,0x05,0x17};
    vector<uc> M = {0x3D,0xC6,0x69,0x73,0x51,0xFF,0x4A,0xEC,0x29,0xCD,0xBA,0xAB,0xF2,0xFB,0xE3,0x46,0x7C,0xC2,0x54,0xF8,0x1B,0xE8};
    vector<uc> A={};
    A = pad_A(A);
    vector<uc> T = Triad_MAC(K,N,M,A);
    for(auto i: T) cout<<hex<<(int)i<< ' ';


}