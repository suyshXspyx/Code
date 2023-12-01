#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure to represent a student
struct Student {
    char student_name[50];
    int student_roll_no;
    float total_marks;
};

// Function to perform swaps and count the number of swaps
void swap(struct Student *a, struct Student *b, int *swapCount) {
    struct Student temp = *a;
    *a = *b;
    *b = temp;
    (*swapCount)++;
}

// Heapify a subtree rooted with node i
void heapify(struct Student arr[], int n, int i, int *swapCount) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arr[left].student_roll_no > arr[largest].student_roll_no)
        largest = left;

    if (right < n && arr[right].student_roll_no > arr[largest].student_roll_no)
        largest = right;

    if (largest != i) {
        swap(&arr[i], &arr[largest], swapCount);
        heapify(arr, n, largest, swapCount);
    }
}

// Main function to perform Heap Sort
void heapSort(struct Student arr[], int n, int *swapCount) {
    // Build heap (rearrange array)
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i, swapCount);

    // One by one extract an element from heap
    for (int i = n - 1; i > 0; i--) {
        // Move current root to end
        swap(&arr[0], &arr[i], swapCount);

        // call max heapify on the reduced heap
        heapify(arr, i, 0, swapCount);
    }
}

// Merge two subarrays of arr[]
void merge(struct Student arr[], int l, int m, int r, int *swapCount) {
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;

    // Create temporary arrays
    struct Student L[n1], R[n2];

    // Copy data to temporary arrays L[] and R[]
    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    // Merge the temporary arrays back into arr[l..r]
    i = 0;
    j = 0;
    k = l;
    while (i < n1 && j < n2) {
        if (L[i].student_roll_no <= R[j].student_roll_no) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
            (*swapCount) += n1 - i;  // Count swaps during merge
        }
        k++;
    }

    // Copy the remaining elements of L[], if there are any
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    // Copy the remaining elements of R[], if there are any
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

// Main function to perform Merge Sort
void mergeSort(struct Student arr[], int l, int r, int *swapCount) {
    if (l < r) {
        // Same as (l+r)/2, but avoids overflow for large l and r
        int m = l + (r - l) / 2;

        // Sort first and second halves
        mergeSort(arr, l, m, swapCount);
        mergeSort(arr, m + 1, r, swapCount);

        // Merge the sorted halves
        merge(arr, l, m, r, swapCount);
    }
}

// Function to print an array of students
void printArray(struct Student arr[], int size) {
    printf("Sorted Array:\n");
    for (int i = 0; i < size; i++) {
        printf("Name: %s, Roll No: %d, Total Marks: %.2f\n",
               arr[i].student_name, arr[i].student_roll_no, arr[i].total_marks);
    }
}

int main() {
    int n;
    printf("Enter the number of students: ");
    scanf("%d", &n);

    struct Student students[n];

    // Input student details
    for (int i = 0; i < n; i++) {
        printf("Enter details for student %d:\n", i + 1);
        printf("Name: ");
        scanf("%s", students[i].student_name);
        printf("Roll No: ");
        scanf("%d", &students[i].student_roll_no);
        printf("Total Marks: ");
        scanf("%f", &students[i].total_marks);
    }

    int swapCountHeap = 0;
    int swapCountMerge = 0;

    // Perform Heap Sort
    heapSort(students, n, &swapCountHeap);

    // Print the sorted array after Heap Sort
    printArray(students, n);
    printf("Number of swaps during Heap Sort: %d\n", swapCountHeap);

    // Perform Merge Sort
    mergeSort(students, 0, n - 1, &swapCountMerge);

    // Print the sorted array after Merge Sort
    printArray(students, n);
    printf("Number of swaps during Merge Sort: %d\n", swapCountMerge);

    return 0;
}
