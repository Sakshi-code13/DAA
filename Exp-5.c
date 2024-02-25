#include <stdio.h>

// Structure to represent a job
struct Job {
    char id;
    int deadline;
    int profit;
};

// Function to perform job sequencing with a deadline
void jobSequencing(struct Job jobs[], int n) {
    // Sort jobs based on their profits in descending order
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (jobs[j].profit < jobs[j + 1].profit) {
                struct Job temp = jobs[j];
                jobs[j] = jobs[j + 1];
                jobs[j + 1] = temp;
            }
        }
    }

    // Array to store the result sequence of jobs
    char result[n];
    // Array to keep track of the time slots
    int timeSlots[n];

    // Initialize all time slots to be empty
    for (int i = 0; i < n; i++) {
        timeSlots[i] = -1;
    }

    // Iterate through all the jobs
    for (int i = 0; i < n; i++) {
        // Find a time slot for the current job, starting from the deadline
        for (int j = jobs[i].deadline - 1; j >= 0; j--) {
            // If the time slot is empty, assign the job to it
            if (timeSlots[j] == -1) {
                timeSlots[j] = i;
                result[j] = jobs[i].id;
                break;
            }
        }
    }

    // Print the sequence of jobs and their associated profits
    int totalProfit = 0;
    printf("Job Sequence: ");
    for (int i = 0; i < n; i++) {
        if (timeSlots[i] != -1) {
            printf("%c ", result[i]);
            totalProfit += jobs[timeSlots[i]].profit;
        }
    }
    printf("\nTotal Profit: %d\n", totalProfit);
}

int main() {
    // Example usage
    struct Job jobs[] = { {'a', 2, 100}, {'b', 1, 19}, {'c', 1, 27}, {'d', 2, 25}, {'e', 3, 15} };
    int n = sizeof(jobs) / sizeof(jobs[0]);

    printf("Given Jobs: ");
    for (int i = 0; i < n; i++) {
        printf("%c ", jobs[i].id);
    }
    printf("\n");

    jobSequencing(jobs, n);

    return 0;
}

