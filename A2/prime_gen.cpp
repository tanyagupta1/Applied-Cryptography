#include <boost/multiprecision/cpp_int.hpp>
#include <boost/multiprecision/miller_rabin.hpp>
#include<bits/stdc++.h>

int main()
{
   
   using namespace boost::random;
   using namespace boost::multiprecision;

   typedef cpp_int int_type;
   mt11213b base_gen(clock());
   independent_bits_engine<mt11213b, 1024, int_type> gen(base_gen);
   mt19937 gen2(clock());
   int count =0;
   for(unsigned i = 0; i <100000; ++i)
   {
      int_type n = gen();
      if(miller_rabin_test(n, 50, gen2))
      {
          count++;
         std::cout << "We have a probable prime with value: " << std::hex << std::showbase << n << std::endl;
         if(count>1) break;
        
      }
   }
}

/*
src: boost library documentation
*/