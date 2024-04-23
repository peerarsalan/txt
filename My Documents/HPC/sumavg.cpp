/*
  Windows does not support user defined reductions.
  This program may not run on MVSC++ compilers for Windows.
  Please use Linux Environment.[You can try using "windows subsystem for linux"]
*/

#include<iostream>
#include<omp.h>

using namespace std;
 
int sum(int arr[], int n){
  int sum = 0;
  #pragma omp parallel for reduction(+ : sum)
    for(int i = 0; i < n; i++){
      sum += arr[i];
    }
  return sum;
}

int Ssum(int arr[], int n){
  int sum = 0;
  // #pragma omp parallel for reduction(+ : sum)
    for(int i = 0; i < n; i++){
      sum += arr[i];
    }
  return sum;
}

int average(int arr[], int n){
  return (double)sum(arr, n) / n;
}

int Saverage(int arr[], int n){
  return (double)Ssum(arr, n) / n;
}

int main(){
 // int n = 5;
  //int arr[] = {1,2,3,4,5};
  int *arr,n;
    cout<<"\n enter total no of elements=>";
    cin>>n;
    arr=new int[n];
    cout<<"\n enter elements=>";
    for (int i=0; i<n;i++)
    {
   	 cin>>arr[i];
    }

  double start_time,end_time;

  start_time = omp_get_wtime();
  cout << "The summation is: " << Ssum(arr, n) << '\n';
  end_time = omp_get_wtime();

  cout<<"Parallel Time for sum: "<<end_time-start_time<<endl;

  start_time = omp_get_wtime();
  cout << "The summation is: " << sum(arr, n) << '\n';
  end_time = omp_get_wtime();

  cout<<"Sequential Time for sum : "<<end_time-start_time<<endl;

  start_time = omp_get_wtime();
  cout << "The average is: " << Saverage(arr, n) << '\n';
  end_time = omp_get_wtime();

  cout<<"Parallel Time for avg : "<<end_time-start_time<<endl;

  start_time = omp_get_wtime();
  cout << "The average is: " << average(arr, n) << '\n';
  end_time = omp_get_wtime();

  cout<<"Sequential Time for Savg : "<<end_time-start_time<<endl;

  return 0;
}
