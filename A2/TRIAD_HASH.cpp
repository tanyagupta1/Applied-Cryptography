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

vector<uc> Triad_HASH(vector<uc>M)
{
    int hlen = (8*M.size())/32;
    vector<uc> a(10,0);
    vector<uc>b={0xb7,0xe1,0x51,0x62,0x8a,0xe2,0x43,0xf6,0xa8,0x88,0x5a};
    vector<uc>c(11,0);
    for(int i=0;i<hlen;i++)
    {
        a[0] = a[0]^M[4*i+3];
        a[1] = a[1]^M[4*i+2];
        a[2] = a[2]^M[4*i+1];
        a[3] = a[3]^M[4*i];

        vector<vector<uc>> tmp =triadP(a,b,c);
        a = tmp[0];
        b = tmp[1];
        c = tmp[2];
    }
    vector<uc> Z(32);
    for(int i=15;i>5;i--)
    {
        Z[i] = a[15-i];
    }
    for(int i=5;i>=0;i--)
    {
        Z[i] = b[5-i];
    }
    
    vector<vector<uc>> tmp =triadP(a,b,c);
    a = tmp[0];
    b = tmp[1];
    c = tmp[2];

    for(int i=31;i>21;i--)
    {
        Z[i] = a[31-i];
    }
    for(int i=21;i>15;i--)
    {
        Z[i] = b[21-i];
    }
    return Z;

}
vector<uc> pad_to_32bits(vector<uc>M)
{
    int m = M.size();
    int bytes_to_pad = 4-(m%4);
    M.push_back(0x80);
    for(int i=1;i<bytes_to_pad;i++) M.push_back(0x00);
    return M;
}
int main()
{
    vector<uc> M= {0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09,0x0A,0x0B,0x0C,0x0D,0x0E,0x0F,0x10,0x11,0x12,0x13,0x14,0x15,0x16,0x17,0x18,0x19,0x1A,0x1B,0x1C,0x1D,0x1E,0x1F,0x20,0x21,0x22,0x23,0x24};
    cout<<M.size()<<'\n';
    M = pad_to_32bits(M);
    vector<uc> hash = Triad_HASH(M);
    for(auto i: hash) cout<<hex<<(int)i<<' ';
    cout<<'\n';
}