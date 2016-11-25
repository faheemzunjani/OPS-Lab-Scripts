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
	int begin;
	int count;
	int max_head_no;
	int min_head_no;
	int min_head_i;

	printf("Enter no. of requests: ");
	scanf("%d", &N);

	max_head_no = -1;
	min_head_no = INT_MAX;

	printf("Enter request queue: ");

	for (i = 0; i < N; i++) {
		scanf("%d", &queue[i].head_no);
		queue[i].visited = 0;

		if (queue[i].head_no > max_head_no) {
			max_head_no = queue[i].head_no;
		}

		if (queue[i].head_no < min_head_no) {
			min_head_no = queue[i].head_no;
			min_head_i = i;
		}
	}

	printf("Enter current head location: ");
	scanf("%d", &cur_head);

	total_mov = 0;
	begin = cur_head;
	count = 0;

	while (cur_head != max_head_no) {
		min_st = INT_MAX;

		for (j = 0; j < N; j++) {
			if (queue[j].head_no > begin && queue[j].head_no <= max_head_no && queue[j].visited != 1 && abs(queue[j].head_no - cur_head) < min_st) {
				min_st = abs(queue[j].head_no - cur_head);
				min_st_i = j;
			}
		}

		total_mov += min_st;
		queue[min_st_i].visited = 1;
		cur_head = queue[min_st_i].head_no;
		count++;
	}

	total_mov += (max_head_no - min_head_no);
	cur_head = min_head_no;
	queue[min_head_i].visited = 1;
	count++;

	while (count < N) {
		min_st = INT_MAX;

		for (j = 0; j < N; j++) {
			if (queue[j].visited != 1 && abs(queue[j].head_no - cur_head) < min_st) {
				min_st = abs(queue[j].head_no - cur_head);
				min_st_i = j;
			}
		}

		total_mov += min_st;
		queue[min_st_i].visited = 1;
		cur_head = queue[min_st_i].head_no;
		count++;
	}

	printf("Total head movement: %d\n", total_mov);

	return 0;
}
