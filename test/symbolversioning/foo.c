#include <stdio.h>

void internal_function_is_not_visible()
{
   printf( "You can't call me directly.\n" );
}

void foo( int x )
{
   internal_function_is_not_visible();

   printf( "foo@@V1: %d\n", x );
}
