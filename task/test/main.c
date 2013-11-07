#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int test_task()
{
}

int main(int argc, char **argv)
{
    printf("task testing started\n");
    int result = test_task(argc, argv);
    printf("task testing ended\n");
    return result;
}
