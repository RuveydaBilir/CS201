#include <cstdlib>
#include <algorithm>
#include <iostream>
#include <math.h>
using namespace std;

int* generate_random_array(int);
int* generate_almost_sorted_array(int);
int insertionSort(int*&, const int&);
int selectionSort(int*&, const int&);
int indexOfLongest(const int*, const int, int&);
void swap(int&, int&, int&);
int bubbleSort(int*&, const int&);
int quickSort(int*&, const int&);
void quickSortRec(int*&, const int, const int, int&);
void partition(int*&, int, int, int&, int&);

int* generate_random_array(int size) {
    srand((unsigned int)time(NULL)); // to generate different arrays every time
    if(size<1){
        return nullptr;
    }
    int* arr = new int[size];
    for(int i=0; i<size; i++){
        arr[i] = rand() % RAND_MAX + 1;
    }
    return arr;
}

int* generate_almost_sorted_array(int size) {
    srand((unsigned int)time(NULL));
    int *random_array = generate_random_array(size);
    // TODO: here, you have to sort this array.
    insertionSort(random_array, size);
    int swap_count = size * 0.03;
    if(swap_count<1){
        swap_count = 1;
    }

    for (int i = 0; i < swap_count; i++) {
        int first_index = rand() % size;
        int second_index = size - first_index;
        int temp = random_array[first_index];
        random_array[first_index] = random_array[second_index];
        random_array[second_index] = temp;
    }
    return random_array;
}

int insertionSort(int*& truck, const int& size){
    int time = 0;
    for(int index=1; index<size; ++index){
        int next = truck[index];
        time+=5;
        int i = index;
        for(; (i>0) && (truck[i-1]>next); --i){
            time++;
            truck[i]=truck[i-1];
            time += 5;
        }
        truck[i] = next;
        time += 5;
    }
    return time;
}

int selectionSort(int*& truck, const int& size){
    int time = 0;
    for(int last=size-1; last>0; --last){
        int largest = indexOfLongest(truck, last+1, time);
        swap(truck[largest], truck[last], time);
    }
    return time;
}

int indexOfLongest(const int* arr, const int size, int& time){
    int longest=0;
    for(int current=1; current<size; current++){
        time++; // for arr[current]>arr[longest] part 
        if(arr[current]>arr[longest]){
            longest=current;
        }
    }
    return longest;
}

void swap(int& x, int& y, int& time){
    int temp=x;
    x=y;
    y=temp;
    time += 15;
}

int bubbleSort(int*& truck, const int& size){
    int time = 0;
    bool sorted = false;
    for(int pass = 1; (pass<size) && !sorted; pass++){
        sorted=true;
        for(int i=0; i<size-pass; i++){
            time++;
            if(truck[i]>truck[i+1]){
                swap(truck[i],truck[i+1],time);
                sorted = false;
            }            
        }
    }
    return time;
}

int quickSort(int*& truck, const int& size){
    int time = 0;
    quickSortRec(truck, 0, size-1, time);
    return time;
}

void quickSortRec(int*& truck, const int firstIndex, const int lastIndex, int& time){
    int index;
    if(firstIndex<lastIndex){
        partition(truck, firstIndex, lastIndex, index, time);
        quickSortRec(truck, firstIndex, index-1, time);
        quickSortRec(truck, index+1, lastIndex, time);
    }
}

void partition(int*& truck,const int firstIndex,const int lastIndex, int& pivotIndex, int& time){
    int pivot = truck[firstIndex];
    time += 5;
    int arr1LastIndex = firstIndex;
    int firstUnknownIndex = firstIndex + 1;
    int current;
    while(firstUnknownIndex<=lastIndex){
        time++;
        current = truck[firstUnknownIndex];
        if(current < pivot){            
            arr1LastIndex++;
            swap(truck[firstUnknownIndex],truck[arr1LastIndex],time);
        }
        firstUnknownIndex++;
    }
    swap(truck[firstIndex],truck[arr1LastIndex],time);
    pivotIndex = arr1LastIndex;
}

int* createCopy(const int* arr, const int size){
    if(size<1 || arr == nullptr){
        return nullptr;
    }
    int* temp = new int[size];
    for(int i=0; i<size; i++){
        temp[i] = arr[i];
    }
    return temp;
}

void task1(int** truckArr, const int truckNum){
    int size;
    int *copyForBubble, *copyForInsertion,*copyForSelection, *copyForQuick;
   
    for(int i=0; i<truckNum; i++){
        size = pow(2,i+3);
        cout<<"Size: "<<size<<endl;
        cout<<endl;
    
        copyForBubble = createCopy(truckArr[i],size);
        copyForInsertion = createCopy(truckArr[i],size);
        copyForQuick = createCopy(truckArr[i],size);
        copyForSelection = createCopy(truckArr[i],size);
        
        cout<<"Insertion sort: " << insertionSort(copyForInsertion,size) << " seconds."<<endl;
        cout<<"Selection sort: " << selectionSort(copyForSelection, size) << " seconds."<<endl;
        cout<<"Bubble Sort: " << bubbleSort(copyForBubble, size) << " seconds."<<endl;
        cout<<"Quick sort: "<< quickSort(copyForQuick, size) << " seconds." << endl;

        delete[] copyForBubble;
        delete[] copyForQuick;
        delete[] copyForInsertion;
        delete[] copyForSelection;
        cout<<endl;
    }   
}

void efficientSort(int*& truck, const int& size, int& minTime, int& maxTime){
    int time = 0, time1=0, time2 = 0, pivotIndex;
    partition(truck,0,size-1,pivotIndex, time);
    quickSortRec(truck,0,pivotIndex-1,time1);
    quickSortRec(truck,pivotIndex+1,size-1,time2);
    if(time1>time2){
        maxTime = time1;
        minTime = time2;
    }
    else{
        maxTime = time2;
        minTime = time1;
    }
    minTime += time;
    if(minTime>maxTime){ // because I added the initial partition time, the previous line may lead to false answers 
    // Only important for small size arrays
        int temp = maxTime;
        maxTime = minTime;
        minTime = temp;
    }
}

void task3(int** truckArr, const int truckNum){
    int size;
    int* copy;
    int time, maxTime, minTime;

    for(int i=0; i<truckNum;i++){
        size = pow(2,i+3);
        cout<<"Size: "<<size<<endl;
        cout<<endl;

        copy = createCopy(truckArr[i],size);
        efficientSort(copy, size, minTime, maxTime);

        cout<<"Max Time: "<<maxTime<<endl;
        cout<<"Min Time: "<<minTime<<endl;
        cout<<endl;

        delete[] copy;
    }
}

int main(){
    const int truckNum = 10;
    int** truckArr = new int*[truckNum];
    int** truckArrAlmostSorted = new int*[truckNum];
    int size;
    
    // generates random tree sizes for each truck
    for(int i=0; i<truckNum; i++){
        size = pow(2,i+3);
        truckArr[i] = generate_random_array(size); 
    }
    for(int i=0; i<truckNum; i++){
        size = pow(2,i+3);
        truckArrAlmostSorted[i] = generate_almost_sorted_array(size); 
    }
    
    //TASK 1:
    //task1(truckArr, truckNum);

    //TASK 2:
    //task1(truckArrAlmostSorted, truckNum);

    //TASK 3:    
    task3(truckArr,truckNum);


    for(int i=0; i<truckNum; i++){
        delete[] truckArr[i];
        delete[] truckArrAlmostSorted[i];
    }
    delete[] truckArr;
    delete[] truckArrAlmostSorted;
}