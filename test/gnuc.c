#include <stdio.h>

int main()
{
#ifdef __GNUC__
    printf("__GNUC__ = %d\n",__GNUC__);
#endif
#ifdef __GNUC_MINOR__
    printf("__GNUC_MINOR__ = %d\n",__GNUC_MINOR__);
#endif
#ifdef __GNUC_PATCHLEVEL__
    printf("__GNUC_PATCHLEVEL__ = %d\n",__GNUC_PATCHLEVEL__);
#endif
 
    return 0;
}
