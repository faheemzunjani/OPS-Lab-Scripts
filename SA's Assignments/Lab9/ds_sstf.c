#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

struct req_queue {
	int head_no;
	int visited;
};

int main()
{
	struct req_queue queue[100];
	int N;
	int cur_head;
	int i;
	int total_mov;
	int min_st;
	int min_st_i;
	int j;


	printf("Enter no. of requests: ");
	scanf("%d", &N);

	printf("Enter request queue: ");

	for (i = 0; i < N; i++) {
		scanf("%d", &queue[i].head_no);
		queue[i].visited = 0;
	}

	printf("Enter current head location: ");
	scanf("%d", &cur_head);

	total_mov = 0;

	for (i = 0; i < N; i ++) {
		min_st = INT_MAX;

		for (j = 0; j < N; j++) {
			if (abs(queue[j].head_no - cur_head) < min_st && queue[j].visited != 1) {
				min_st = abs(queue[j].head_no - cur_head);
				min_st_i = j;
			}
		}

		total_mov += min_st;
		queue[min_st_i].visited = 1;
		cur_head = queue[min_st_i].head_no;
	}

	printf("Total head movement: %d\n", total_mov);

	return 0;
}