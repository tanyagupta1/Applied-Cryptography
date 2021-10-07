#include<bits/stdc++.h>
using namespace std;
#define uc unsigned char

vector<uc> triad_encrypt(vector<uc>K, vector<uc>N, vector<uc> M);
vector<uc> triad_decrypt(vector<uc>K, vector<uc>N, vector<uc> C);
vector<uc> triad_sc(vector<uc>K, vector<uc>N, vector<uc> M);
vector<vector<uc>> triadUpd(vector<uc>a, vector<uc> b, vector<uc> c, bool msg);
vector<vector<uc>> triadP(vector<uc>a,vector<uc>b,vector<uc> c);

vector<uc> triad_encrypt(vector<uc>K, vector<uc>N, vector<uc> M)
{
    vector<uc> C = triad_sc(K,N,M);
    return C;
}

vector<uc> triad_decrypt(vector<uc>K, vector<uc>N, vector<uc> C)
{
    vector<uc> M = triad_sc(K,N,C);
    return M;
}
vector<uc> triad_sc(vector<uc>K, vector<uc>N, vector<uc> M)
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
    int mlen = M.size();
    vector<uc> C(mlen);
    for(int i=0;i<mlen;i++)
    {
        C[i] = 0;
        for(int j=7;j>=0;j--)
        {
            tmp = triadUpd(a,b,c,0);
            a = tmp[0];
            b = tmp[1];
            c = tmp[2];
            z = tmp[3][0];
            C[i] += pow(2,j) *(M[i] & (1<<j));
        }
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
vector<vector<uc>> triadUpd(vector<uc>a, vector<uc> b, vector<uc> c, bool msg)
{
    vector<bool>abit(81); vector<bool>bbit(89); vector<bool>cbit(89);
    bool t1, t2, t3, z;
    for(int i=0;i<10;i++)
    {
        for(int j=0;j<8;j++)
        {
            abit[i*8+j+1] = a[i] & (1<<(7-j));
        }
    }
    for(int i=0;i<11;i++)
    {
        for(int j=0;j<8;j++)
        {
            bbit[i*8+j+1] = b[i] & (1<<(7-j));
            cbit[i*8+j+1] = c[i] & (1<<(7-j));
        }
    }
    
    t1 = abit[68] ^ abit[80] ^ bbit[85]*cbit[85];
    t2 = bbit[64] ^ bbit[88];
    t3 = cbit[68] ^ cbit[88];
    z = t1 ^ t2 ^ t3;
    t1 = t1 ^ abit[73]*abit[79] ^ b[66] ^ msg;
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


}