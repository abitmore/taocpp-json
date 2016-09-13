// Copyright (c) 2016 Dr. Colin Hirsch and Daniel Frey
// Please see LICENSE for license or visit https://github.com/taocpp/json/

#ifndef TAOCPP_JSON_INCLUDE_INTERNAL_PRETTY_WRITER_HH
#define TAOCPP_JSON_INCLUDE_INTERNAL_PRETTY_WRITER_HH

#include <ostream>

#include "escape.hh"

#include "../external/double.hh"

namespace tao
{
   namespace json
   {
      namespace internal
      {
         class pretty_writer
         {
         private:
            std::ostream & os;
            const std::size_t indent;
            std::string current;
            bool first = true;
            bool after_key = false;

            void next()
            {
               if ( after_key ) {
                  after_key = false;
               }
               else {
                  os << current;
               }
            }

         public:
            pretty_writer( std::ostream & os, const std::size_t indent )
              : os( os ),
                indent( indent )
            { }

            void null()
            {
               next();
               os.write( "null", 4 );
            }

            void boolean( const bool v )
            {
               next();
               if ( v ) {
                  os.write( "true", 4 );
               }
               else {
                  os.write( "false", 5 );
               }
            }

            void number( const std::int64_t v )
            {
               next();
               os << v;
            }

            void number( const std::uint64_t v )
            {
               next();
               os << v;
            }

            void number( const double v )
            {
               next();
               json_double_conversion::Dtostr( os, v );
            }

            void string( const std::string & v )
            {
               next();
               internal::escape( os, v );
            }

            // array
            void begin_array()
            {
               next();
               os.put( '[' );
               if ( current.empty() ) {
                  current = '\n';
               }
               current.resize( current.size() + indent, ' ' );
               first = true;
            }

            void element()
            {
               os.put( ',' );
               first = false;
            }

            void end_array()
            {
               current.resize( current.size() - indent );
               if ( ! first ) {
                  os.seekp( -1, std::ios_base::cur );
                  os << current;
               }
               os.put( ']' );
               first = false;
            }

            // object
            void begin_object()
            {
               next();
               os.put( '{' );
               if ( current.empty() ) {
                  current = '\n';
               }
               current.resize( current.size() + indent, ' ' );
               first = true;
            }

            void key( const std::string & v )
            {
               next();
               internal::escape( os, v );
               os.write( ": ", 2 );
               after_key = true;
            }

            void value()
            {
               os.put( ',' );
               first = false;
            }

            void end_object()
            {
               current.resize( current.size() - indent );
               if ( ! first ) {
                  os.seekp( -1, std::ios_base::cur );
                  os << current;
               }
               os.put( '}' );
               first = false;
            }
         };

      } // internal

   } // json

} // tao

#endif
