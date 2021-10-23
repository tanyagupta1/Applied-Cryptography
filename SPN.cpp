#include<bits/stdc++.h>
#include "print.h"
using namespace std;

map<int,int> S_box2={{0,0xE},{1,4},{2,0xD},{3,1},{4,2},{5,0xF},{6,0xB},{7,8},{8,3},{9,0xA},{0xA,6},{0xB,0xC},{0xC,5},{0xD,9},{0xE,0},{0xF,7}};

map<int,int> S_box={{0,0xC},{1,5},{2,6},{3,0xB},{4,9},{5,0},{6,0xA},{7,0xD},{8,3},{9,0xE},{0xA,0xF},{0xB,8},{0xC,4},{0xD,7},{0xE,1},{0xF,2}};
static inline uint32_t rotl (uint32_t n, unsigned int c)
{
  const unsigned int mask = (CHAR_BIT*sizeof(n) - 1); 
  c &= mask;
  return (n<<c) | (n>>( (-c)&mask ));
}

vector<bool>round_key(vector<bool>K,int i)
{
    uint32_t key =0;
    int base =1;
    for(int j=31;j>=0;j--)
    {
        key+=base * K[j];
        base*=2;
    }
    key = rotl(key,11*i);
    vector<bool> new_key(32,0);
    int j=31;
    while(key>0)
    {
        new_key[j]=key%2;
        key/=2;
        j--;
    }
    cout<<"i: "<<i<<'\n';
    print32(new_key);
    return new_key;
}
vector<bool> permutation(vector<bool>M)
{
vector<bool> tmp={M[0],M[4],M[8],M[12],M[16],M[20],M[24],M[28],M[1],M[5],M[9],M[13],M[17],M[21],M[25],M[29],M[2],M[6],M[10],M[14],M[18],M[22],M[26],M[30],M[3],M[7],M[11],M[15],M[19],M[23],M[27],M[31]};
return tmp;
}
vector<bool> SPN(vector<bool> K, vector<bool> M)
{
    int rounds = 4;
    for(int r=1;r<=rounds -1;r++)
    {
        vector<bool> rK = round_key(K,r);
        // key mixing
        for(int i=0;i<32;i++) M[i]= M[i]^rK[i];
        cout<<"r: "<<r<<"after key - mix"<<'\n';
        print32(M);
        //S_box
        for(int i=0;i<8;i++)
        {
            int input = 8*M[4*i]+4*M[4*i+1]+2*M[4*i+2]+M[4*i+3];
            int output = S_box[input];
            for(int j=3;j>=0;j--)
            {
                M[4*i+j]=output%2;
                output/=2;
            }
        }
        cout<<"r: "<<r<<"after S_box"<<'\n';
        print32(M);
        // permutation
        M = permutation(M);
        cout<<"r: "<<r<<"after permutation"<<'\n';
        print32(M);
    }
    //key mixing 4
    vector<bool> rK = round_key(K,4);
    for(int i=0;i<32;i++) M[i]= M[i]^rK[i];
    cout<<"r: "<<4<<"after key - mix"<<'\n';
    print32(M);
    //S-box
    for(int i=0;i<8;i++)
    {
        int input = 8*M[4*i]+4*M[4*i+1]+2*M[4*i+2]+M[4*i+3];
        int output = S_box[input];
        for(int j=3;j>=0;j--)
        {
            M[4*i+j]=output%2;
            output/=2;
        }
    }
    cout<<"r: "<<4<<"after S_box"<<'\n';
    print32(M);
    //key mixing 5
    rK = round_key(K,5);
    for(int i=0;i<32;i++) M[i]= M[i]^rK[i];
    cout<<"r: "<<5<<"after key - mix"<<'\n';
    print32(M);
    return M;   
}

void bias_finder()
{
    int dp[4][4]={};
    for(int i=0;i<16;i++)
    {
        int input = i;
        int output = S_box[i];
        vector<bool>X(4,0), Y(4,0);
        for(int j=3;j>=0;j--)
        {
            X[j]=input%2;
            Y[j]=output%2;
            input/=2; 
            output/=2;
        }
        for(int j=0;j<=3;j++)
        {
            for(int k=0;k<=3;k++) if(X[j]==Y[k]) dp[j][k]++;
        }
    }
    for(int j=0;j<=3;j++)
    {
        for(int k=0;k<=3;k++) cout<<dp[j][k]<<' ';
        cout<<'\n';
    }

}
int main()
{
    vector<bool> M={1,0,1,1, 0,1,0,0, 1,1,0,1, 0,1,0,1, 1,1,1,0, 0,0,1,1, 1,0,1,1, 1,1,1,1};

    vector<bool> K ={1,1,0,0, 0,1,0,1, 0,0,1,0, 1,1,0,0, 0,1,0,1, 0,1,1,1, 0,1,1,0, 1,1,1,0};
    cout<<M.size()<<' '<<K.size()<<'\n';
    M = SPN(K,M);
    
    print32(M);
    // bias_finder();
}