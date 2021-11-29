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
ll modInverse(ll a, ll b)
{
    if(gcd(a,b)!=1) return 0;
    ll a0= a;
    ll b0 = b;
    ll t0 = 0;
    ll t = 1;
    ll q = a0/b0;
    ll r = a0 - q*b0;
    while(r>0)
    {
        ll temp = (((t0-q*t)%a)+a)%a;
        t0 = t;
        t = temp;
        a0 = b0;
        b0 = r;
        q = a0/b0;
        r = a0 - q*b0;
    }
    return t;
}
pk_sk key_generation(ll p, ll q, ll b=65537)
{
    pk_sk keys;
    keys.p = p;
    keys.q = q;
    keys.n = p*q;
    ll phi_n = (p-1)*(q-1);

    keys.b = b;
    keys.a = modInverse(phi_n,keys.b);
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
    ll p = 178001;
    ll q = 255523;
    ll b =65537;
    ll message = 6575738402;
    cout<<"Enter p:"<<'\n';
    cin>>p;
    cout<<"Enter q:"<<'\n';
    cin>>q;
    cout<<"Enter b"<<'\n';
    cin>>b;
    cout<<"Enter message"<<'\n';
    cin>>message;
    pk_sk keys = key_generation(p,q,b);
    keys.print();
    
    ll ciphertext = encryption(message,keys.b,keys.n);
    cout<<"ciphertext "<<ciphertext<<'\n';
    ll dec = decryption(ciphertext,keys.a,keys.n);
    cout<<(dec==message)<<'\n';

}
