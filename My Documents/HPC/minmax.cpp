#include<iostream>
#include<omp.h>

using namespace std;
int minval(int arr[], int n){
  int minval = arr[0];
  #pragma omp parallel for reduction(min : minval)
    for(int i = 0; i < n; i++){
      if(arr[i] < minval) minval = arr[i];
    }
  return minval;
}

int Sminval(int arr[], int n){
  int minval = arr[0];
  // #pragma omp parallel for reduction(min : minval)
    for(int i = 0; i < n; i++){
      if(arr[i] < minval) minval = arr[i];
    }
  return minval;
}

int maxval(int arr[], int n){
  int maxval = arr[0];
  #pragma omp parallel for reduction(max : maxval)
    for(int i = 0; i < n; i++){
      if(arr[i] > maxval) maxval = arr[i];
    }
  return maxval;
}

int Smaxval(int arr[], int n){
  int maxval = arr[0];
  // #pragma omp parallel for reduction(max : maxval)
    for(int i = 0; i < n; i++){
      if(arr[i] > maxval) maxval = arr[i];
    }
  return maxval;
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
  cout << "The minimum value is: " << minval(arr, n)<<endl;
  end_time = omp_get_wtime();

  cout<<"Prallel Time for min : "<<end_time-start_time<<endl;

  start_time = omp_get_wtime();
  cout << "The minimum value is: " << Sminval(arr, n)<<endl;
  end_time = omp_get_wtime();

  cout<<"Sequential Time for min : "<<end_time-start_time<<endl;

  start_time = omp_get_wtime();
  cout << "The maximum value is: " << Smaxval(arr, n) << '\n';
  end_time = omp_get_wtime();

  cout<<"Prallel Time for max : "<<end_time-start_time<<endl;

  start_time = omp_get_wtime();
  cout << "The maximum value is: " << maxval(arr, n) << '\n';
  end_time = omp_get_wtime();

  cout<<"Sequential Time for max : "<<end_time-start_time<<endl;

  return 0;
}
