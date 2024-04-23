#include <bits/stdc++.h>
#include <iostream>
#include <omp.h>
using namespace std;

 
void merge(int arr[], int l, int m, int r) {
    int n1 = m - l + 1;
    int n2 = r - m;

    int L[n1], R[n2];

    for (int i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    int i = 0;
    int j = 0;
    int k = l;
    while (i < n1 && j < n2) 
    {
        if (L[i] <= R[j]) 
        {
            arr[k] = L[i];
            i++;
        } 
        else 
        {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

void mergeSort(int arr[], int l, int r) {
    if (l >= r)
        return;
    int m = l + (r - l) / 2;
    mergeSort(arr, l, m);
    mergeSort(arr, m + 1, r);
    merge(arr, l, m, r);
}

void parallelMergeSort(int arr[], int l, int r) {
    if (l >= r)
        return;
    int m = l + (r - l) / 2;
    #pragma omp parallel sections
    {
        #pragma omp section
        parallelMergeSort(arr, l, m);

        #pragma omp section
        parallelMergeSort(arr, m + 1, r);
    }
    merge(arr, l, m, r);
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

    
    // Reset array for merge sort
    //int arr_merge[] = {64, 34, 25, 12, 22, 11, 90,8,30,5,23,45,6,1,70,56};

    // Sequential merge sort with time measurement
    double start_seq_merge = omp_get_wtime();
   // mergeSort(arr_merge, 0, n - 1);
    mergeSort(arr, 0, n - 1);
    double end_seq_merge = omp_get_wtime();
    double diff_seq_merge = end_seq_merge - start_seq_merge;

    // Print sorted array
    std::cout << "\nSequential Merge Sort:" << std::endl;
    for (int i = 0; i < n; i++) {
        //std::cout << arr_merge[i] << " ";
        std::cout << arr[i] << " ";
    }
    std::cout << "\nTime taken for sequential merge sort: " << diff_seq_merge << " seconds" << std::endl;

    // Reset array for parallel merge sort
   // int arr_parallel_merge[] = {64, 34, 25, 12, 22, 11, 90,8,30,5,23,45,6,1,70,56};

    // Parallel merge sort with time measurement
    double start_par_merge = omp_get_wtime();
    //parallelMergeSort(arr_parallel_merge, 0, n - 1);
    parallelMergeSort(arr, 0, n - 1);
    double end_par_merge = omp_get_wtime();
    double diff_par_merge = end_par_merge - start_par_merge;

    // Print sorted array
    std::cout << "\nParallel Merge Sort:" << std::endl;
    for (int i = 0; i < n; i++) {
       // std::cout << arr_parallel_merge[i] << " ";
       std::cout << arr[i] << " ";
    
    }
    std::cout << "\nTime taken for parallel merge sort: " << diff_par_merge << " seconds" << std::endl;

    return 0;
}
