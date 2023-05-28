#include <iostream>
#include <omp.h>
#include <climits>
using namespace std;


int main() {
	
	int n;
	cout<<"Enter the size of array"<<endl;
	cin>>n;
	
	int data[n];
	
    // Set the number of threads to use
    omp_set_num_threads(4);
    
  	
  	cout<<"Enter the value:"<<endl;
    for (int i = 0; i <n; i++) {
        cin>>data[i] ;
    }
    
    // Compute the minimum value
    int min_value = INT_MAX;
    
    #pragma omp parallel for reduction(min:min_value)
    for (int i = 0; i <n; i++) {    	
//    	cout<<"thread_id "<<omp_get_thread_num()<<" and i= "<<i<<endl;
        if (data[i] < min_value) {
            min_value = data[i];
        }
    }

    
    // Compute the maximum value
    int max_value = INT_MIN;
    
    #pragma omp parallel for reduction(max:max_value)
    for (int i = 0; i < n; i++) {    	
        if (data[i] > max_value) {
            max_value = data[i];
        }
    }
   
    
    // Compute the sum of values
    int sum = 0;
    
    #pragma omp parallel for reduction(+:sum)
    for (int i = 0; i < n; i++) {
        sum += data[i];
    }

    
    // Compute the average value
    double average = 0.0;
    #pragma omp parallel for reduction(+:average)
    for (int i = 0; i < n; i++) {
        average += data[i];
    }
    average /= 10;

    

    cout << "Number of threads used: " << omp_get_max_threads() <<endl;
    cout<<"Total Sum: "<<sum<<endl;
    cout<<"Average: "<<average<<endl;
    cout<<"Maximum Value: "<<max_value<<endl;
    cout<<"Minimum Value: "<<min_value<<endl; 
    
    return 0;
}

