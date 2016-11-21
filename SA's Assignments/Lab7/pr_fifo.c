#include <stdio.h>

void insert_queue(int q[100], int * N, int item);
int find_queue(int q[100], int N, int item);
int delete_queue(int q[100], int * N);
void print_queue(int q[100], int N);

int main()
{
	int pages[100];
	int frame[100];
	int p_N;
	int f_size;
	int q_N;
	int i;
	int p_faults;

	printf("Enter number of pages: ");
	scanf("%d", &p_N);

	printf("Enter page numbers: ");

	for (i = 0; i < p_N; i++) {
		scanf("%d", &pages[i]);
	}
	
	printf("Enter frame size: ");
	scanf("%d", &f_size);

	q_N = 0;

	printf("\nPage\tFrame\n");

	p_faults = 0;

	for (i = 0; i < p_N; i++) {
		printf("%d\t", pages[i]);

		if (!find_queue(frame, q_N, pages[i])) {
			if (q_N == f_size) {
				delete_queue(frame, &q_N);
			}

			insert_queue(frame, &q_N, pages[i]);	
			p_faults++;
		}

		print_queue(frame, q_N);
	}

	printf("\nPage Faults: %d\n", p_faults);

	return 0;
}

void insert_queue(int q[100], int * N, int item)
{
	q[*N] = item;
	(*N)++;
}

int find_queue(int q[100], int N, int item)
{
	int i;

	for (i = 0; i < N; i++) {
		if (q[i] == item) {
			return 1;
		}
	}
	
	return 0;
}

int delete_queue(int q[100], int * N)
{
	int i;
	int d_element;
	
	d_element = q[0];

	for (i = 0; i < (*N) - 1; i++) {
		q[i] = q[i + 1];
	}
	
	(*N)--;

	return d_element;
}

void print_queue(int q[100], int N)
{
	int i;
	
	for (i = 0; i < N; i++) {
		printf("%d ", q[i]);
	}
	printf("\n");
}
