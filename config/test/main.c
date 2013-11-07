#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int test_config()
{
}

int main(int argc, char **argv)
{
    printf("config testing started\n");
    int result = test_config(argc, argv);
    printf("config testing ended\n");
    return result;
}
