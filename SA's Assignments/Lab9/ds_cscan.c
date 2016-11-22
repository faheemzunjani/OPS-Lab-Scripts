#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#define DISK_END 199

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


	printf("Enter no. of requests: ");
	scanf("%d", &N);

	printf("Enter request queue: ");

	for (i = 0; i < N; i++) {
		scanf("%d", &queue[i].head_no);
		queue[i].visited = 0;
	}
	queue[i].head_no = DISK_END;
	queue[i].visited = 0;
	N++;

	printf("Enter current head location: ");
	scanf("%d", &cur_head);

	total_mov = 0;
	begin = cur_head;
	count = 0;

	while (cur_head != DISK_END) {
		min_st = INT_MAX;

		for (j = 0; j < N; j++) {
			if (queue[j].head_no > begin && queue[j].head_no <= DISK_END && queue[j].visited != 1 && abs(queue[j].head_no - cur_head) < min_st) {
				min_st = abs(queue[j].head_no - cur_head);
				min_st_i = j;
			}
		}

		total_mov += min_st;
		queue[min_st_i].visited = 1;
		cur_head = queue[min_st_i].head_no;
		count++;
	}

	total_mov += DISK_END;
	cur_head = 0;

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