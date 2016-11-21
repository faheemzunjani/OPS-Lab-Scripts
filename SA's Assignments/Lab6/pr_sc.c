#include <stdio.h>

struct list {
	int page;
	int sc;
};

void insert_list(struct list l[100], int f_size, int * N, int item, int * cur);
int find_pos(struct list l[100], int * N, int * cur);
void replace_page(struct list l[100], int * N, int item, int * cur);
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
	int cur_i;

	printf("Enter number of pages: ");
	scanf("%d", &p_N);

	printf("Enter page numbers: ");

	for (i = 0; i < p_N; i++) {
		scanf("%d", &pages[i]);
	}
	
	printf("Enter frame size: ");
	scanf("%d", &f_size);

	l_N = 0;
	cur_i = 0;

	printf("\nPage\tFrame\n");

	p_faults = 0;

	for (i = 0; i < p_N; i++) {
		printf("%d\t", pages[i]);

		loc = find_list(frame, l_N, pages[i]);
		
		if (loc == -1 && l_N < f_size) {
			insert_list(frame, f_size, &l_N, pages[i], &cur_i);
			p_faults++;
		} else if (loc == -1) {
			replace_page(frame, &l_N, pages[i], &cur_i);
			p_faults++;
		} else {
			frame[loc].sc = 1;
		}	

		print_list(frame, l_N);
	}

	printf("\nPage Faults: %d\n", p_faults);

	return 0;
}

void insert_list(struct list l[100], int f_size, int * N, int item, int * cur)
{
	struct list new_item;

	new_item.page = item;
	new_item.sc = 0;

	l[*N] = new_item;
	(*N)++;
	
	if (*N == f_size) {
		(*cur) = 0;
	} else {
		(*cur)++;
	}
}

int find_pos(struct list l[100], int * N, int * cur)
{
	int pos;

	pos = -1;

	while (pos == -1) {
		if (l[*cur].sc == 0) {
			pos = *cur;
		} else if (l[*cur].sc == 1) {
			l[*cur].sc = 0;
		}

		if (*cur == (*N) - 1) {
			*cur = 0;
		} else {
			(*cur)++;
		}	
	}
	
	return pos;
}

void replace_page(struct list l[100], int * N, int item, int * cur)
{
        struct list new_item;

        new_item.page = item;
        new_item.sc = 0;

	l[find_pos(l, N, cur)] = new_item;		
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
