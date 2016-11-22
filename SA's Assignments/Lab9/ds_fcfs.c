#include <stdio.h>
#include <stdlib.h>

int main()
{
	int req_queue[100];
	int N;
	int cur_head;
	int i;
	int total_mov;

	printf("Enter no. of requests: ");
	scanf("%d", &N);

	printf("Enter request queue: ");

	for (i = 0; i < N; i++) {
		scanf("%d", &req_queue[i]);
	}

	printf("Enter current head location: ");
	scanf("%d", &cur_head);

	total_mov = 0;

	for (i = 0; i < N; i++) {
		total_mov += abs(req_queue[i] - cur_head);
		cur_head = req_queue[i];
	}

	printf("Total head movement: %d\n", total_mov);

	return 0;
}