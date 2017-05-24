#include <stdlib.h>
#include <stdio.h>

int main()
{
    int i;
    int *p;

    p = malloc(10 * sizeof(int));

    for(i = 0; i < 10; i++)
        p[i] = i;

    for(i = 0; i < 10; i++)
        printf("%d\n", p[i]);
	
	p = (int *) realloc(p, 11 * sizeof(int));
	for(i = 0; i < 11; i++)
        p[i] = i;
	for(i = 0; i < 11; i++)
        printf("%d\n", p[i]);

    free(p);
	p = (int *) calloc(10, sizeof(int));
	for(i = 0; i < 10; i++)
        p[i] = i;

    for(i = 0; i < 10; i++)
        printf("%d\n", p[i]);
	free(p);
    return 0;
}
