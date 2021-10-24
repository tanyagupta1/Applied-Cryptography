#include<bits/stdc++.h>
#include "print.h"
using namespace std;
map<int,int> S_box={{0,0xC},{1,5},{2,6},{3,0xB},{4,9},{5,0},{6,0xA},{7,0xD},{8,3},{9,0xE},{0xA,0xF},{0xB,8},{0xC,4},{0xD,7},{0xE,1},{0xF,2}};
map<int,int> S_rev={{0,0x5},{1,0xE},{2,0xF},{3,0x8},{4,0xC},{5,6},{6,0x2},{7,0xD},{8,0xB},{9,0x4},{0xA,0x6},{0xB,3},{0xC,0},{0xD,7},{0xE,9},{0xF,0xA}};
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
        for(int i=0;i<32;i++) M[i]= M[i]^rK[i];
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
        M = permutation(M);
    }
    vector<bool> rK = round_key(K,4);
    for(int i=0;i<32;i++) M[i]= M[i]^rK[i];
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
    rK = round_key(K,5);
    for(int i=0;i<32;i++) M[i]= M[i]^rK[i];
    return M;   
}

vector<pair<vector<bool>,vector<bool>>> c_p;
vector<pair<int,int>> S_box_trail={{0,0},{8,4},{16,8},{24,12},{1,16},{9,20}};
void generate_pairs(vector<bool>K)
{
    for(unsigned int i=0;i<40000;i++)
    {
        unsigned int input =i;
        vector<bool>plaintext(32,0);
        int ind=31;
        while(input>0) 
        {
            plaintext[ind]=input%2;
            input/=2;
            ind--;
        }
        vector<bool> ciphertext(32,0);
        ciphertext=SPN(K,plaintext);
        c_p.push_back(make_pair(plaintext,ciphertext));
        if(i>=0) continue;
        cout<<"pair:"<<'\n';
        print32(plaintext);
        print32(ciphertext);
    }
    for(unsigned int i=UINT32_MAX;i>UINT32_MAX-40000;i--)
    {
        unsigned int input =i;
        vector<bool>plaintext(32,0);
        int ind=31;
        while(input>0) 
        {
            plaintext[ind]=input%2;
            input/=2;
            ind--;
        }
        vector<bool> ciphertext(32,0);
        ciphertext=SPN(K,plaintext);
        c_p.push_back(make_pair(plaintext,ciphertext));
        if(i>=0) continue;
        cout<<"pair:"<<'\n';
        print32(plaintext);
        print32(ciphertext);
    }

}
int CC=0;
int subkey(int s_box_no)
{
    double prob_max=0.0;
    int my_pk=0;
    for(int i=0;i<16;i++)
    {
        int count=0;
        vector<bool> key_pot(4,0);
        int input=i;
        int ind=3;
        while(input>0)
        {
            key_pot[ind]=input%2;
            input/=2;
            ind--;
        }
        for(auto p: c_p)
        {
            vector<bool> plain=p.first;
            vector<bool>cipher=p.second;
            vector<bool>inter(4,0);
            for(int j=0;j<4;j++) inter[j]=cipher[4*s_box_no+j]^key_pot[j];
            int rev_s = S_rev[8*inter[0]+4*inter[1]+2*inter[2]+inter[3]];
            vector<bool>ret(4,0);
            int in=3;
            while(in>=0)
            {
                ret[in]=rev_s%2;
                rev_s/=2;
                in--;
            }
            if(ret[0]==plain[S_box_trail[s_box_no].first]) count++;
        }
        double tmp_prob = abs(count-40000)/80000.0;
        cout<<i<<' '<<tmp_prob<<'\n';
        if(tmp_prob>prob_max)
        {
            prob_max=tmp_prob;
            my_pk=i;
        }

    }
    return my_pk;
}
bool not_found = false;
vector<bool> get_key_by_crypt()
{
    vector<bool>kk(32,0);
    for(int i=0;i<6;i++)
    {
        cout<<"biases for S_box "<<i+1<<'\n';
        int part_key = subkey(i);
        cout<<i<<' '<<part_key<<'\n';
        for(int j=3;j>=0;j--)
        {
            kk[4*i+j]=part_key%2;
            part_key/=2;
        }
    }
    cout<<"part key: ";
    for(int i=0;i<24;i++)cout<<kk[i]<<' ';
    cout<<'\n';

    for(int i=0;i<256;i++)
    {
        int inp =i;
        for(int j=31;j>=24;j--)
        {
            kk[j]=inp%2;
            inp/=2;
        }
        bool violated = false;
        for(auto cp: c_p)
        {
            vector<bool>tmp_c=SPN(kk,cp.first);
            vector<bool>cipher=cp.second;
            for(int k=0;k<32;k++) if(cipher[k]!=tmp_c[k]) 
            {
                violated=true;
                break;
            }
            if(violated) break;
        }
        if(violated) continue;
        else return kk;
    }
    not_found=true;
    for(int i=0;i<32;i++) kk[i]=0;
    return kk;
}

int main()
{
    vector<bool> K(32,0);
    for(int k=0;k<32;k+=2) K[k]=1;
    generate_pairs(K);
    cout<<c_p.size()<<'\n';
    vector<bool>kk=get_key_by_crypt();
    if(not_found) 
    {
        for(int i=0;i<32;i++) cout<<"-1"<<' ';
        cout<<'\n';
    }
    else
    {
        print32(kk);
    }
    
    
}