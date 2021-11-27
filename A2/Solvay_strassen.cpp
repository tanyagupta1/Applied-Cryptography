#include<bits/stdc++.h>
using namespace std;
#define ll long long
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
ll power_mod(ll a,ll n, ll p)
{
    ll result =1;

    while(n>0)
    {
        if(n%2==0)
        {
            a = mod_multiply(a,a,p);
            n/=2;
        }
        else
        {
            result=mod_multiply(result,a,p);
            n--;
        }
    }
    return result;
}
ll jacobi(ll a, ll n)
{
        ll t = 1;
        while (a != 0)
        {
            while (a % 2 == 0)
            {
                a /= 2;
                ll r = n % 8;
                if (r == 3 or r == 5) t = -t;
            }
            ll c = n;
            n = a;
            a = c;
            if ((a % 4 == n % 4) &&( n%4 == 3)) t = -t;
            a %= n;
        }
        if (n == 1) return t;
        else return 0;
}

bool solvay_strassen(ll n)  //true if composite
{
    if(n%2==0) {cout<<"composite"<<'\n';return true;}
    ll a = (rand()%(n-2))+1;
    cout<<"a is "<<a<<'\n';
    ll x = jacobi(a,n);
    // cout<<"x is "<<x<<'\n';
    if(x==0)
    {
        cout<<n<<" is composite x=0"<<'\n';
        return true;
    }
    ll y = power_mod(a,(n-1)/2,n);
    // cout<<"y is "<<y<<" "<<"x%n"<<((x+n)%n)<<' '<<"y%n"<<(y%n)<<'\n';
    if(((x+n)%n)==(y%n))  
    {
        cout<<n<<" is prime"<<'\n';
        return false;
    }
    else 
    {
        cout<<n<<" is composite"<<'\n';
        return true;
    }
}

int main()
{
    //call it 5 times
    bool is_composite = false;
    ll n=101;
    cout<<"input n : ";
    cin>>n;
    for(ll i=0;i<5;i++)
    {  
        cout<<"Iteration "<<i+1<<" :"<<'\n';
        is_composite = is_composite || (solvay_strassen(n));

    }
    cout<<n<<" is "<<(is_composite?"composite":"prime")<<'\n';

}