#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int test_checksum()
{
}

int main(int argc, char **argv)
{
    printf("checksum testing started\n");
    int result = test_checksum(argc, argv);
    printf("checksum testing ended\n");
    return result;
}
