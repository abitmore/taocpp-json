// Copyright (c) 2016 Dr. Colin Hirsch and Daniel Frey
// Please see LICENSE for license or visit https://github.com/taocpp/json/

#include "test.hh"

#include <tao/json/value.hh>
#include <tao/json/from_string.hh>
#include <tao/json/reference.hh>

namespace tao
{
   namespace json
   {
      void test( const std::string & s1, const std::string & s2 )
      {
         auto v1 = from_string( s1 );
         const auto v2 = from_string( s2 );
         resolve_references( v1 );
         TEST_ASSERT( v1 == v2 );
      }

      void unit_test()
      {
         test( "{\"foo\":1,\"bar\":2}", "{\"foo\":1,\"bar\":2}" );
         test( "{\"foo\":1,\"bar\":{\"$ref\":\"#/foo\"}}", "{\"foo\":1,\"bar\":1}" );
         test( "{\"foo\":\"#/foo\",\"bar\":{\"$ref\":{\"$ref\":\"#/foo\"}}}", "{\"foo\":\"#/foo\",\"bar\":\"#/foo\"}" );
      }

   } // json

} // tao

#include "main.hh"