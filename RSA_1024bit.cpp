#include<bits/stdc++.h>
#include <boost/multiprecision/cpp_int.hpp>
using namespace std;
using namespace boost::multiprecision;
struct pk_sk
{
    int1024_t p ; int1024_t q; int1024_t n; int1024_t a; int1024_t b;
    void print()
    {
        cout<<"public keys: n= "<<n<<" b= "<<b<<'\n';
        cout<<"private keys: p= "<<p<<" q= "<<q<<" a= "<<a<<'\n';
    }
};
int1024_t gcd(int1024_t a,int1024_t b)
{
    if(b==0) return a;
    return gcd(b,a%b);
}
int1024_t modInverse(int1024_t a, int1024_t b)
{
    if(gcd(a,b)!=1) return 0;
    int1024_t a0= a;
    int1024_t b0 = b;
    int1024_t t0 = 0;
    int1024_t t = 1;
    int1024_t q = a0/b0;
    int1024_t r = a0 - q*b0;
    while(r>0)
    {
        int1024_t temp = (((t0-q*t)%a)+a)%a;
        t0 = t;
        t = temp;
        a0 = b0;
        b0 = r;
        q = a0/b0;
        r = a0 - q*b0;
    }
    return t;
}
pk_sk key_generation(int1024_t p, int1024_t q,int1024_t b=65537)
{
    pk_sk keys;
    keys.p = p;
    keys.q = q;
    keys.n = p*q;
    int1024_t phi_n = (p-1)*(q-1);
    keys.b = b;
    keys.a = modInverse(phi_n,keys.b);
    return keys;
}
int1024_t mod_exp(int1024_t x, int1024_t a, int1024_t n)
{
    int1024_t result = 1;
    while(a>0)
    {
        if(a%2==0)
        {
            a/=2;
            x = (x*x)%n;
        }
        else
        {
            a--;
            result = (result*x)%n;
            
        }
    }
    return result;
}
int1024_t encryption (int1024_t x,int1024_t b,int1024_t n)
{
    return mod_exp(x,b,n);
}
int1024_t decryption(int1024_t y, int1024_t a, int1024_t n)
{
    return mod_exp(y,a,n);
}
int main()
{
    int1024_t p = 178001;
    int1024_t q = 255523;
    int1024_t b =65537;
    int1024_t message = 6575738402;
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
    int1024_t ciphertext = encryption(message,keys.b,keys.n);
    cout<<"ciphertext "<<ciphertext<<'\n';
    int1024_t dec = decryption(ciphertext,keys.a,keys.n);
    cout<<(dec==message)<<'\n';

}
