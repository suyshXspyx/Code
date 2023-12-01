#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure representing a student
typedef struct {
    char student_name[50];
    int student_roll_no;
    int total_marks;
} Student;

// Function prototypes for Heap Sort
void heapify(Student arr[], int n, int i, int* swapCount);
void heapSort(Student arr[], int n, int* swapCount);

// Function prototypes for Quick Sort
int partition(Student arr[], int low, int high, int* swapCount);
void quickSort(Student arr[], int low, int high, int* swapCount);

// Function to print an array of students
void printStudents(Student arr[], int n);

int main() {
    int n, i;

    printf("Enter the number of students: ");
    scanf("%d", &n);

    Student* studentsHeap = (Student*)malloc(n * sizeof(Student));
    Student* studentsQuick = (Student*)malloc(n * sizeof(Student));

    // Input data for students
    printf("Enter student details (name, roll number, total marks):\n");
    for (i = 0; i < n; i++) {
        scanf("%s %d %d", studentsHeap[i].student_name, &studentsHeap[i].student_roll_no, &studentsHeap[i].total_marks);
        studentsQuick[i] = studentsHeap[i]; // Copy data for Quick Sort
    }

    // Perform Heap Sort
    int heapSwapCount = 0;
    heapSort(studentsHeap, n, &heapSwapCount);

    // Perform Quick Sort
    int quickSwapCount = 0;
    quickSort(studentsQuick, 0, n - 1, &quickSwapCount);

    // Print sorted arrays
    printf("\nHeap Sort Output:\n");
    printStudents(studentsHeap, n);
    printf("Number of swaps in Heap Sort: %d\n", heapSwapCount);

    printf("\nQuick Sort Output:\n");
    printStudents(studentsQuick, n);
    printf("Number of swaps in Quick Sort: %d\n", quickSwapCount);

    // Free allocated memory
    free(studentsHeap);
    free(studentsQuick);

    return 0;
}

// Helper function to swap two students
void swapStudents(Student* a, Student* b) {
    Student temp = *a;
    *a = *b;
    *b = temp;
}

// Function to perform Heapify operation in Heap Sort
void heapify(Student arr[], int n, int i, int* swapCount) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    // Compare with left child
    if (left < n && arr[left].student_roll_no > arr[largest].student_roll_no)
        largest = left;

    // Compare with right child
    if (right < n && arr[right].student_roll_no > arr[largest].student_roll_no)
        largest = right;

    // Swap if needed and recursively heapify the affected sub-tree
    if (largest != i) {
        (*swapCount)++;
        swapStudents(&arr[i], &arr[largest]);
        heapify(arr, n, largest, swapCount);
    }
}

// Function to perform Heap Sort
void heapSort(Student arr[], int n, int* swapCount) {
    // Build heap
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i, swapCount);

    // Extract elements from heap one by one
    for (int i = n - 1; i > 0; i--) {
        (*swapCount)++;
        swapStudents(&arr[0], &arr[i]);
        heapify(arr, i, 0, swapCount);
    }
}

// Function to perform partition operation in Quick Sort
int partition(Student arr[], int low, int high, int* swapCount) {
    Student pivot = arr[high];
    int i = (low - 1);

    for (int j = low; j <= high - 1; j++) {
        if (arr[j].student_roll_no <= pivot.student_roll_no) {
            (*swapCount)++;
            i++;
            swapStudents(&arr[i], &arr[j]);
        }
    }

    (*swapCount)++;
    swapStudents(&arr[i + 1], &arr[high]);
    return (i + 1);
}

// Function to perform Quick Sort
void quickSort(Student arr[], int low, int high, int* swapCount) {
    if (low < high) {
        int pi = partition(arr, low, high, swapCount);

        quickSort(arr, low, pi - 1, swapCount);
        quickSort(arr, pi + 1, high, swapCount);
    }
}

// Function to print an array of students
void printStudents(Student arr[], int n) {
    printf("Student Details:\n");
    printf("Name\tRoll No\tTotal Marks\n");
    for (int i = 0; i < n; i++)
        printf("%s\t%d\t%d\n", arr[i].student_name, arr[i].student_roll_no, arr[i].total_marks);
}
//Enter the number of students: 5
//Enter student details (name, roll number, total marks):
//John 101 90
//Alice 105 85
//Bob 103 75
//Charlie 102 95
//David 104 80
