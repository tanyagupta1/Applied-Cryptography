#include<bits/stdc++.h>
using namespace std;
#define ll long long
struct pk_sk
{
    ll p ; ll q; ll n; ll a; ll b;
    void print()
    {
        cout<<"public keys: n= "<<n<<" b= "<<b<<'\n';
        cout<<"private keys: p= "<<p<<" q= "<<q<<" a= "<<a<<'\n';
    }
};
ll gcd(ll a,ll b)
{
    if(b==0) return a;
    return gcd(b,a%b);
}
ll modInverse(ll a, ll m)
{
    ll m0 = m; ll y = 0; ll  x = 1;
    if (m == 1) return 0;
    while (a > 1) 
    {
        ll q = a / m;
        ll t = m;
        m = a % m;
        a = t;
        t = y;
        y = x - q * y;
        x = t;
    }
    if (x < 0)x += m0;
    return x;
}
pk_sk key_generation(ll p, ll q)
{
    pk_sk keys;
    keys.p = p;
    keys.q = q;
    keys.n = p*q;
    ll phi_n = (p-1)*(q-1);
    int b =0;
    // for(int i=2;i<phi_n;i++)
    // {
    //     if(gcd(i,phi_n)==0) 
    //     {
    //         b = i;
    //         break;
    //     }
    // }

    keys.b = 18154205245;
    keys.a = modInverse(keys.b,phi_n);
    return keys;
}
ll mod_multiply(ll a, ll b,ll n)
{
    ll result =0;
    while(b>0)
    {
        if(b%2==0)
        {
            a =(a*2)%n;
            b/=2;
        }
        else
        {
            result =(result+a)%n;
            b--;
        }
    }
    return result;
}
ll mod_exp(ll x, ll a, ll n)
{
    ll result = 1;
    while(a>0)
    {
        if(a%2==0)
        {
            a/=2;
            x = mod_multiply(x,x,n);
        }
        else
        {
            a--;
            result = mod_multiply(result,x,n);
            
        }
    }
    return result;
}
ll encryption (ll x,ll b,ll n)
{
    return mod_exp(x,b,n);
}
ll decryption(ll y, ll a, ll n)
{
    return mod_exp(y,a,n);
}
int main()
{
    ll p = 135623;
    ll q = 227629;
    pk_sk keys = key_generation(p,q);
    keys.print();
    ll message = 1390965409;
    ll ciphertext = encryption(message,keys.b,keys.n);
    cout<<"ciphertext "<<ciphertext<<'\n';
    ll dec = decryption(ciphertext,keys.a,keys.n);
    cout<<(dec==message)<<'\n';

}
