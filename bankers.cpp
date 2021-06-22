// C++ program to illustrate Banker's Algorithm
#include <iostream>
using namespace std;

// Number of processes
const int P = 5;

// Number of resources
const int R = 4;

// Function to find the need of each process
void calculateNeed(int need[P][R], int maxm[P][R],
				int allot[P][R])
{
	// Calculating Need of each P
	for (int i = 0 ; i < P ; i++)
		for (int j = 0 ; j < R ; j++)

			// Need of instance = maxm instance -
			//				 allocated instance
			need[i][j] = maxm[i][j] - allot[i][j];
}

// Function to find the system is in safe state or not
bool isSafe(int processes[], int avail[], int maxm[][R],
			int allot[][R])
{
	int need[P][R];

	// Function to calculate need matrix
	calculateNeed(need, maxm, allot);

	// Mark all processes as infinish
	bool finish[P] = {0};

	// To store safe sequence
	int safeSeq[P];

	// Make a copy of available resources
	int work[R];
	for (int i = 0; i < R ; i++)
		work[i] = avail[i];

	// While all processes are not finished
	// or system is not in safe state.
	int count = 0;
	while (count < P)
	{
		// Find a process which is not finish and
		// whose needs can be satisfied with current
		// work[] resources.
		bool found = false;
		for (int p = 0; p < P; p++)
		{
			// First check if a process is finished,
			// if no, go for next condition
			if (finish[p] == 0)
			{
				// Check if for all resources of
				// current P need is less
				// than work
				int j;
				for (j = 0; j < R; j++) {
					// printf("After P%d -> Avail = %d\n", count, work[j]);
					if (need[p][j] > work[j])
						break;
				}
					
				// If all needs of p were satisfied.
				if (j == R)
				{
					// Add the allocated resources of
					// current P to the available/work
					// resources i.e.free the resources
					for (int k = 0 ; k < R ; k++)
						work[k] += allot[p][k];
					
					// Add this process to safe sequence.
					safeSeq[count++] = p;

					// Mark this p as finished
					finish[p] = 1;

					found = true;
				}
				// *** additional code added here (missionloyd) ***
				if(finish[p] == 1) {
					printf("After P%d -> Avail = (", p);

					for(int k = 0; k < R; k++) {
						printf("%d", work[k]);
						if(k < R-1) {
							printf(", ");
						}
					}

					printf(")\n");
				}
				// *** end additional code added here ***
			}
		}

		// If we could not find a next process in safe
		// sequence.
		if (found == false)
		{
			cout << "\n*** System is not in safe state *** \n";
			return false;
		}
	}

	// If system is in safe state then
	// safe sequence will be as below
	cout << "\n*** System is in safe state ***\n\nSafe"
		" sequence is: \n";
	for (int i = 0; i < P ; i++) {
		cout << safeSeq[i] << " ";
	}
	printf("\n");
	return true;
}

// Driver code
int main()
{
	int processes[] = {0, 1, 2, 3, 4};

	// Available instances of resources
	int avail[] = {0, 3, 0, 1};
	// int avail[] = {1, 0, 0, 2};

	// Maximum R that can be allocated
	// to processes 

	// *** MAX ***
	int maxm[][R] = {
		{5, 1, 1, 7},
		{3, 2, 1, 1},
		{3, 3, 2, 1},
		{4, 6, 2, 1},
		{6, 3, 2, 5}
	};

	// Resources allocated to processes

	// *** Allocation ***
	int allot[][R] = {
		{3, 0, 1, 4},
		{2, 2, 1, 0},
		{3, 1, 2, 1},
		{0, 5, 1, 0},
		{4, 2, 1, 2}};

	// Check system is in safe state or not
	printf("\n");
	isSafe(processes, avail, maxm, allot);
	printf("\n");
	return 0;
}

