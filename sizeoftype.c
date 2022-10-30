#include	<unistd.h>
#include	<stdlib.h>
#include	<stdio.h>









int main()
{
	printf("int = %zu\n",sizeof(int));
	printf("long = %zu\n",sizeof(long));
	printf("long long = %zu\n",sizeof(long long));
	printf("char = %zu\n",sizeof(char));

	return (0);
}