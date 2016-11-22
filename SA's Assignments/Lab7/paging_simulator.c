#include <stdio.h>
#include <stdlib.h>

int main()
{
	int i;
	int N;
	long long int page_size[100];
	void * page_table[100];

	printf("Enter no. of pages: ");
	scanf("%d", &N);

	printf("Enter page sizes: ");
	
	for (i = 0; i < N; i++) {
		scanf("%lld", &page_size[i]);
		page_table[i] = malloc(page_size[i]);
	}

	printf("Page No.\tPhysical Address\n");

	for (i = 0; i < N; i++) {
		printf("%d\t\t%p\n", i, page_table[i]);
	}

	return 0;
}
