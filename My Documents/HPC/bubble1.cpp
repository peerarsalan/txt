#include <bits/stdc++.h>
#include <iostream>
#include <omp.h>
using namespace std;

void bubbleSort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                // Swap arr[j] and arr[j+1]
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;

            }
        }
    }
}

void parallelBubbleSort(int arr[], int n) 
{
    #pragma omp parallel
    {
        for (int i = 0; i < n - 1; i++) 
        {
            #pragma omp for
            for (int j = 0; j < n - i - 1; j++) {
                if (arr[j] > arr[j + 1]) {
                    // Swap arr[j] and arr[j+1]
                    int temp = arr[j];
                    arr[j] = arr[j + 1];
                    arr[j + 1] = temp;
                }
            }
        }
    }
}

 
int main() {
    //int arr[] = {64, 34, 25, 12, 22, 11, 90,8,30,5,23,45,6,1,70,56};
    //int n = sizeof(arr) / sizeof(arr[0]);
    int *arr,n;
   cout<<"\n enter total no of elements=>";
   cin>>n;
    arr=new int[n];
    cout<<"\n enter elements=>";
   for (int i=0; i<n;i++)
    {
   	cin>>arr[i];
    }

    // Sequential bubble sort with time measurement
    double start_seq_bubble = omp_get_wtime();
    bubbleSort(arr, n);
    double end_seq_bubble = omp_get_wtime();
    double diff_seq_bubble = end_seq_bubble - start_seq_bubble;

    // Print sorted array
    std::cout << "Sequential Bubble Sort:" << std::endl;
    for (int i = 0; i < n; i++) {
        std::cout << arr[i] << " ";
    }
    std::cout << "\nTime taken for sequential bubble sort: " << diff_seq_bubble << " seconds" << std::endl;

    // Parallel bubble sort with time measurement
    //int arr_par_bubble[] = {64, 34, 25, 12, 22, 11, 90,8,30,5,23,45,6,1,70,56}; // Reset array
    double start_par_bubble = omp_get_wtime();
   // parallelBubbleSort(arr_par_bubble, n);
    parallelBubbleSort(arr, n);
    double end_par_bubble = omp_get_wtime();
    double diff_par_bubble = end_par_bubble - start_par_bubble;

    // Print sorted array
    std::cout << "\nParallel Bubble Sort:" << std::endl;
    for (int i = 0; i < n; i++) {
        //std::cout << arr_par_bubble[i] << " ";
               std::cout << arr[i] << " ";
    }
    std::cout << "\nTime taken for parallel bubble sort: " << diff_par_bubble << " seconds" << std::endl;

    return 0;
}
