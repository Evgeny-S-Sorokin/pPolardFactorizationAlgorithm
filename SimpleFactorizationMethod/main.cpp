#include "GlobalVariables.h"
#include "CommonFunctions.hpp"

#include <vector>

using namespace SimpleFactorizationMethod;

int main( int argc, char* argv[] )
{
   srand( time( nullptr ) );

   std::vector< Types::pPolardRunInfo< decltype( Consts::PrimeNumbersArray16[0] * Consts::PrimeNumbersArray16[0] ) > > runInfo16;
   for ( int i = 1; i < Consts::PrimeNumbersArray16.size(); i += 2 )
   {
      runInfo16.push_back( StaticFunctions::pPolard( Consts::PrimeNumbersArray16[i - 1] * Consts::PrimeNumbersArray16[i] ) );
   }

   StaticFunctions::printRunInfo( runInfo16 );
   runInfo16.clear();

   std::vector< Types::pPolardRunInfo< decltype( Consts::PrimeNumbersArray32[0] * Consts::PrimeNumbersArray32[0] ) > > runInfo32;
   for ( int i = 1; i < Consts::PrimeNumbersArray32.size(); i += 2 )
   {
      runInfo32.push_back( StaticFunctions::pPolard( Consts::PrimeNumbersArray32[i - 1] * Consts::PrimeNumbersArray32[i] ) );
   }

   StaticFunctions::printRunInfo( runInfo32 );
   runInfo32.clear();

   std::vector< Types::pPolardRunInfo< decltype( Consts::PrimeNumbersArray64[0] * Consts::PrimeNumbersArray64[0] ) > > runInfo64;
   for ( int i = 1; i < Consts::PrimeNumbersArray64.size(); i += 2 )
   {
      runInfo64.push_back( StaticFunctions::pPolard( Consts::PrimeNumbersArray64[i - 1] * Consts::PrimeNumbersArray64[i] ) );
   }

   StaticFunctions::printRunInfo( runInfo64 );
   runInfo64.clear();

   return 0;
}