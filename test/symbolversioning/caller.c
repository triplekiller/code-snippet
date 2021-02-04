void foo(int);
void internal_function_is_not_visible();

int main()
{
   foo(1);
   //internal_function_is_not_visible();

   return 0;
}
