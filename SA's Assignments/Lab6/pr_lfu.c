#include <stdio.h>

struct list {
	int page;
	int freq;
};

void insert_list(struct list l[100], int * N, int item);
int find_lfu(struct list l[100], int * N);
void replace_lfu(struct list l[100], int * N, int item);
int find_list(struct list l[100], int N, int item);
void print_list(struct list l[100], int N);

int main()
{
	int pages[100];
	struct list frame[100];
	int p_N;
	int f_size;
	int l_N;
	int j;
	int i;
	int p_faults;
	int loc;

	printf("Enter number of pages: ");
	scanf("%d", &p_N);

	printf("Enter page numbers: ");

	for (i = 0; i < p_N; i++) {
		scanf("%d", &pages[i]);
	}
	
	printf("Enter frame size: ");
	scanf("%d", &f_size);

	l_N = 0;

	printf("\nPage\tFrame\n");

	p_faults = 0;

	for (i = 0; i < p_N; i++) {
		printf("%d\t", pages[i]);

		loc = find_list(frame, l_N, pages[i]);
		
		if (loc == -1 && l_N < f_size) {
			insert_list(frame, &l_N, pages[i]);
			p_faults++;
		} else if (loc == -1) {
			replace_lfu(frame, &l_N, pages[i]);
			p_faults++;
		} else {
			frame[loc].freq++;
		}	

		print_list(frame, l_N);
	}

	printf("\nPage Faults: %d\n", p_faults);

	return 0;
}

void insert_list(struct list l[100], int * N, int item)
{
	struct list new_item;
	int i;

	new_item.page = item;
	new_item.freq = 1;

	l[*N] = new_item;
	(*N)++;
}

int find_lfu(struct list l[100], int * N)
{
	int i;
	int min_freq;
	int min_i;
	
	min_freq = l[0].freq;
	min_i = 0;

	for (i = 1; i < *N; i++) {
		if (l[i].freq < min_freq) {
			min_i = i;
			min_freq = l[i].freq;
		}
	}
	
	return min_i;
}

void replace_lfu(struct list l[100], int * N, int item)
{
        struct list new_item;
	int i;

        new_item.page = item;
        new_item.freq = 1;

	l[find_lfu(l, N)] = new_item;		
}

int find_list(struct list l[100], int N, int item)
{
        int i;

        for (i = 0; i < N; i++) {
                if (l[i].page == item) {
                        return i;
                }
        }

        return -1;
}

void print_list(struct list l[100], int N)
{
	int i;
	
	for (i = 0; i < N; i++) {
		printf("%d ", l[i].page);
	}
	printf("\n");
}
