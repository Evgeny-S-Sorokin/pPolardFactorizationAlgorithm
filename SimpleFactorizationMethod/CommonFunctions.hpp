#pragma once

#include "GlobalVariables.h"


#include <iostream>
#include <iomanip>
#include <cstdint>
#include <chrono>

#include <string>


namespace SimpleFactorizationMethod
{
   namespace StaticFunctions
   {
      template< class Type >
      [[nodiscard]] Type binPower( Type base, Type power, Type modulus ) noexcept( true )
      {
         Type localResult = 1;
         while ( power )
         {
            if ( power & 1 )
            {
               localResult *= base;
               localResult %= modulus;
            }
            base *= ( base % modulus );
            base %= modulus;
            power >>= 1;
         }
         return localResult % modulus;
      }

      template< class Type >
      [[nodiscard]] Type binGCD( Type A, Type B ) noexcept( true )
      {
         if ( ( A == 0 ) || ( B == 0 ) )
         {
            return A | B;
         }

         uint8_t offset = 0;
         for ( offset = 0; ( ( A | B ) & 1 ) == 0; ++offset )
         {
            A >>= 1;
            B >>= 1;
         }

         while ( ( A & 1 ) == 0 )
         {
            A >>= 1;
         }

         do
         {
            while ( ( B & 1 ) == 0 )
            {
               B >>= 1;
            }

            if ( A < B )
            {
               B -= A;
            }
            else
            {
               auto diff = A - B;
               A = B;
               B = diff;
            }
            B >>= 1;
         } while ( B != 0 );

         return A << offset;
      }

      template< class Type >
      [[nodiscard]] Type positiveDiff( Type A, Type B ) noexcept( true )
      {
         return ( A > B ? A - B : B - A );
      }

      template< class Type >
      [[nodiscard]] Types::pPolardRunInfo< Type > pPolard( const Type number ) noexcept( true )
      {
         auto start = std::chrono::steady_clock::now();

         int i = 0;
         int stage = 2;
         Type x = static_cast<Type>( ( rand() % ( number - 2 ) ) + 1 );
         Type y = 1;

         Type factor = binGCD( number, positiveDiff( x, y ) );
         while ( factor == 1 )
         {
            if ( i == stage )
            {
               y = x;
               stage *= 2;
            }
            x = binPower( x, static_cast<Type>( 2 ), number ) + 1;
            ++i;
            factor = binGCD( number, positiveDiff( x, y ) );
         }

         auto end = std::chrono::steady_clock::now();

         Types::pPolardRunInfo< Type > result;
         result.elapsedTime      = end - start;
         result.iterationNumber  = i;
         result.originalNumber   = number;
         result.factor           = factor;

         return result;
      }

      template< class Type >
      void printRunInfo( const std::vector < Types::pPolardRunInfo< Type > >& vecToPrint ) noexcept( false )
      {
         decltype( vecToPrint.at( 0 ).elapsedTime.count() ) elapsedTimeSum = 0;
         decltype( vecToPrint.at( 0 ).iterationNumber )     iterationNumberSum = 0;
         std::cout << "| " << std::setw( 21 ) << "Factorized number" << " | "
            << std::setw( 21 ) << "Elapsed time" << " | "
            << std::setw( 10 ) << "Iterations" << " | "
            << std::setw( 21 ) << "Factor 1" << " | "
            << std::setw( 21 ) << "Factor 2" << " | "
            << "\n";
         auto dividor = std::string( 110, '-' );
         std::cout << dividor << '\n';
         for ( const auto& singleRunInfo : vecToPrint )
         {
            elapsedTimeSum += singleRunInfo.elapsedTime.count();
            iterationNumberSum += singleRunInfo.iterationNumber;
            std::cout << "| " << std::setw( 21 ) << singleRunInfo.originalNumber << " | "
               << std::setw( 21 ) << singleRunInfo.elapsedTime.count() << " | "
               << std::setw( 10 ) << singleRunInfo.iterationNumber << " | "
               << std::setw( 21 ) << singleRunInfo.factor << " | "
               << std::setw( 21 ) << singleRunInfo.originalNumber / singleRunInfo.factor << " | "
               << "\n";
         }
         std::cout << dividor << '\n';
         std::cout << "| " << std::setw( 21 ) << " " << " | "
            << std::setw( 21 ) << elapsedTimeSum / vecToPrint.size() << " | "
            << std::setw( 10 ) << iterationNumberSum / vecToPrint.size() << " | "
            << std::setw( 21 ) << " " << " | "
            << std::setw( 21 ) << " " << " | "
            << "\n";
         std::cout << std::endl;
      }
   } // StaticFunctions
} // SimpleFactorizationMethod