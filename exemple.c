#include <stdlib.h>
#include <stdio.h>

int main()
{
    int i;
    int *p;
	printf("Llamada a malloc\n");
    p = malloc(10 * sizeof(int));

    for(i = 0; i < 10; i++)
        p[i] = i;

    for(i = 0; i < 10; i++)
        printf("%d\n", p[i]);
	printf("Llamada a realloc\n");
	p = (int *) realloc(p, 11 * sizeof(int));
	for(i = 0; i < 11; i++)
        p[i] = i;
	for(i = 0; i < 11; i++)
        printf("%d\n", p[i]);
	printf("Llamada a free\n");
    free(p);
	printf("Llamada a calloc\n");
	p = (int *) calloc(10, sizeof(int));
	for(i = 0; i < 10; i++)
	p[i] = i;

    for(i = 0; i < 10; i++)
        printf("%d\n", p[i]);
	printf("Llamada a free\n");
	free(p);
    return 0;
}
