#include <stdio.h>

struct list {
	int page;
};

void insert_list(struct list l[100], int * N, int item);
int find_pos(struct list l[100], int * N, int pages[100], int p_N, int cur);
void replace_page(struct list l[100], int * N, int pages[100], int p_N, int item, int cur);
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
			replace_page(frame, &l_N, pages, p_N, pages[i], i);
			p_faults++;
		} 

		print_list(frame, l_N);
	}

	printf("\nPage Faults: %d\n", p_faults);

	return 0;
}

void insert_list(struct list l[100], int * N, int item)
{
	struct list new_item;

	new_item.page = item;

	l[*N] = new_item;
	(*N)++;	
}

int find_pos(struct list l[100], int * N, int pages[100], int p_N, int cur)
{
	int pos;
	int i;
	int j;
	int max_dist;
	int temp_dist;

	pos = -1;
	max_dist = -1;

	for (i = 0; i < *N; i++) {
		temp_dist = -1;

		for (j = cur; j < p_N; j++) {
			if (l[i].page == pages[j]) {
				temp_dist = j - cur;
				break;
			}	
		}

		if (temp_dist == -1) {
			pos = i;
			break;
		} else if (temp_dist > max_dist) {
			pos = i;
			max_dist = temp_dist;
		}
	}
	
	return pos;
}

void replace_page(struct list l[100], int * N, int pages[100], int p_N, int item, int cur)
{
        struct list new_item;

        new_item.page = item;

	l[find_pos(l, N, pages, p_N, cur)] = new_item;		
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
