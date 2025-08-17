#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// ---------- Utility Functions ----------
void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Generate random permutation of [1..n]
int* generateArray(int n) {
    int *arr = (int*)malloc(n * sizeof(int));
    if (!arr) {
        printf("Memory allocation failed!\n");
        exit(1);
    }

    for (int i = 0; i < n; i++)
        arr[i] = i + 1;

    // Fisher-Yates Shuffle
    for (int i = n - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        swap(&arr[i], &arr[j]);
    }

    return arr;
}

// Copy array
int* copyArray(int *src, int n) {
    int *dest = (int*)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) dest[i] = src[i];
    return dest;
}

// Print array
void display(int arr[], int n) {
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

// ---------- Sorting Algorithms ----------
int bubbleSort(int arr[], int n) {
    int comparisons = 0;
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            comparisons++;
            if (arr[j] > arr[j + 1])
                swap(&arr[j], &arr[j + 1]);
        }
    }
    return comparisons;
}

int improvedBubbleSort(int arr[], int n) {
    int comparisons = 0, swapped;
    for (int i = 0; i < n - 1; i++) {
        swapped = 0;
        for (int j = 0; j < n - i - 1; j++) {
            comparisons++;
            if (arr[j] > arr[j + 1]) {
                swap(&arr[j], &arr[j + 1]);
                swapped = 1;
            }
        }
        if (!swapped) break;
    }
    return comparisons;
}

int cocktailShakerSort(int arr[], int n) {
    int comparisons = 0, start = 0, end = n - 1, swapped = 1;
    while (swapped) {
        swapped = 0;
        for (int i = start; i < end; i++) {
            comparisons++;
            if (arr[i] > arr[i + 1]) {
                swap(&arr[i], &arr[i + 1]);
                swapped = 1;
            }
        }
        if (!swapped) break;
        swapped = 0;
        end--;
        for (int i = end - 1; i >= start; i--) {
            comparisons++;
            if (arr[i] > arr[i + 1]) {
                swap(&arr[i], &arr[i + 1]);
                swapped = 1;
            }
        }
        start++;
    }
    return comparisons;
}

int selectionSort(int arr[], int n) {
    int comparisons = 0;
    for (int i = 0; i < n - 1; i++) {
        int minIndex = i;
        for (int j = i + 1; j < n; j++) {
            comparisons++;
            if (arr[j] < arr[minIndex])
                minIndex = j;
        }
        swap(&arr[i], &arr[minIndex]);
    }
    return comparisons;
}

int insertionSort(int arr[], int n) {
    int comparisons = 0;
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0) {
            comparisons++;
            if (arr[j] > key) {
                arr[j + 1] = arr[j];
                j--;
            } else break;
        }
        arr[j + 1] = key;
    }
    return comparisons;
}

// ---------- Wrapper to Run & Measure ----------
void runSort(const char *name, int (*sortFunc)(int*, int), int *arr, int n) {
    int *temp = copyArray(arr, n);

    clock_t start = clock();
    int comparisons = sortFunc(temp, n);
    clock_t end = clock();

    double timeTaken = (double)(end - start) / CLOCKS_PER_SEC;

    printf("\n--- %s ---\n", name);
    printf("Sorted Array: ");
    display(temp, n);
    printf("Comparisons: %d\n", comparisons);
    printf("Time Taken: %.6f seconds\n", timeTaken);

    free(temp);
}

// ---------- Main ----------
int main() {
    srand(time(NULL));
    int n, choice;
    int *arr;

    printf("Enter size of array (n): ");
    scanf("%d", &n);

    arr = generateArray(n);

    do {
        printf("\n===== Sorting Menu =====\n");
        printf("1. Bubble Sort\n");
        printf("2. Improved Bubble Sort\n");
        printf("3. Cocktail Shaker Sort\n");
        printf("4. Selection Sort\n");
        printf("5. Insertion Sort\n");
        printf("6. Generate New Random Array\n");
        printf("7. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: runSort("Bubble Sort", bubbleSort, arr, n); break;
            case 2: runSort("Improved Bubble Sort", improvedBubbleSort, arr, n); break;
            case 3: runSort("Cocktail Shaker Sort", cocktailShakerSort, arr, n); break;
            case 4: runSort("Selection Sort", selectionSort, arr, n); break;
            case 5: runSort("Insertion Sort", insertionSort, arr, n); break;
            case 6:
                free(arr);
                arr = generateArray(n);
                printf("\nNew Random Array Generated:\n");
                display(arr, n);
                break;
            case 7: printf("Exiting...\n"); break;
            default: printf("Invalid choice! Try again.\n");
        }

    } while (choice != 7);

    free(arr);
    return 0;
}
