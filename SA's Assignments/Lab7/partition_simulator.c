#include <stdio.h>

int main()
{
	int N;
	int partitions[100];
	char choice;
	char dump;
	int max_part;
	int new_part;
	int min_part;
	int i;
	
	printf("Enter no. of partitions: ");
	scanf("%d", &N);	

	max_part = -1;

	printf("Enter partitions: ");

	for (i = 0; i < N; i++) {
		scanf("%d", &partitions[i]);
		
		if (partitions[i] > max_part) {
			max_part = partitions[i];
		}
	}

	printf("Enter size required by the process: ");
	scanf("%d", &new_part);

	printf("Enter choice f = First / b = Best / w = Worst Fit: ");
        scanf("%c%c", &dump, &choice);
	
	if (new_part > max_part) {
		printf("No free memory!\n");
	} else {
		if (choice == 'f') {
			for (i = 0; i < N; i++) {
				if (new_part <= partitions[i]) {
					printf("Allotted partition: %d\n", partitions[i]);
					break;
				}
			}
		} else if (choice == 'b') {
			min_part = partitions[0];
			
			for (i = 1; i < N; i++) {
				if (partitions[i] < min_part && partitions[i] >= new_part) {
					min_part = partitions[i];
				}
			}
			printf("Allotted partition: %d\n", min_part);
		} else if (choice == 'w') {
			printf("Allotted partition: %d\n", max_part);
		}

	}
	

	return 0;
}
