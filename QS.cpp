#include <iostream>
#include <string>
#include <sstream>
#include "QS.h"
#include <array>
using namespace std;



/*
* sortAll()
*
* Sorts elements of the array.  After this function is called, every
* element in the array is less than or equal its successor.
*
* Does nothing if the array is empty.
*/
void QS::sortAll() {
    cout << "In sortAll" << endl;
    int size = getSize();
    if (size < 1) {
        cout << "Array is empty" << endl;
    }
    else {
        int left = 0;
        int right = size-1;
        recursiveSort(left,right);
    }

}

void QS::recursiveSort(int left, int right) {
    int pivot = medianOfThree(left, right);
    pivot = partition(left,right,pivot);
    if (right - left > 1) {
        recursiveSort(left, pivot -1);
        recursiveSort(pivot + 1, right);
    }
}

/*
* medianOfThree()
*
* The median of three pivot selection has two parts:
*
* 1) Calculates the middle index by averaging the given left and right indices:
*
* middle = (left + right)/2
*
* 2) Then bubble-sorts the values at the left, middle, and right indices.
*
* After this method is called, data[left] <= data[middle] <= data[right].
* The middle index will be returned.
*
* Returns -1 if the array is empty, if either of the given integers
* is out of bounds, or if the left index is not less than the right
* index.
*
* @param left
* 		the left boundary for the subarray from which to find a pivot
* @param right
* 		the right boundary for the subarray from which to find a pivot
* @return
*		the index of the pivot (middle index); -1 if provided with invalid input
*/
int QS::medianOfThree(int left, int right) {
    int size = getSize();
    if(size < 1)
        return -1;
    if(left < 0 || right >= index || left >= right)
        return -1;

    int middle = (left + right)/2;
    if (array[left] == array[right] && array[left] == array[middle])
        //cout << "Done with median of three" << endl;
        return middle;
    if (array[middle] < array[left]) {
        int temp = array[middle];
        array[middle] = array[left];
        array[left] = temp;
    }
    if (array[right] < array[middle]) {
        int temp = array[middle];
        array[middle] = array[right];
        array[right] = temp;
    }
    if (array[middle] < array[left]) {
        int temp = array[middle];
        array[middle] = array[left];
        array[left] = temp;
    }
    //cout << "Done with median of three" << endl;

    return middle;
}

/*
* Partitions a subarray around a pivot value selected according to
* median-of-three pivot selection.  Because there are multiple ways to partition a list,
* we will follow the algorithm on page 611 of the course text when testing this function.
*
* The values which are smaller than the pivot should be placed to the left
* of the pivot; the values which are larger than the pivot should be placed
* to the right of the pivot.
*
* Returns -1 if the array is null, if either of the given integers is out of
* bounds, or if the first integer is not less than the second integer, or if the
* pivot is not within the sub-array designated by left and right.
*
* @param left
* 		the left boundary for the subarray to partition
* @param right
* 		the right boundary for the subarray to partition
* @param pivotIndex
* 		the index of the pivot in the subarray
* @return
*		the pivot's ending index after the partition completes; -1 if
* 		provided with bad input
*/
int QS::partition(int left, int right, int pivotIndex) {
    if (array==NULL)
        return -1;
    if(left < 0 || right >= index || left >= right)
        return -1;
    if(pivotIndex > right || pivotIndex < left)
        return -1;
    if(right - left == 2 && array[right] == array[left] && array[right] == array[pivotIndex]) {
        return right;
    }
    
    //Moves pivot to front of array
    int temp = array[pivotIndex];
    array[pivotIndex] = array[left];
    array[left] = temp;

    int up = left + 1;
    int down = right;

    do {
        while (array[up] <= array[left] && up < right) {up++;}
        while (array[down] >= array[left] && down > left){down--;}
        if (up <= down) {
            temp = array[up];
            array[up] = array[down];
            array[down] = temp;
        }
    } 
    while(up < down);

    temp = array[left];
    array[left] = array[down];
    array[down] = temp;

    return down;
}

/*
* Produces a comma delimited string representation of the array. For example: if my array
* looked like {5,7,2,9,0}, then the string to be returned would look like "5,7,2,9,0"
* with no trailing comma.  The number of cells included equals the number of values added.
* Do not include the entire array if the array has yet to be filled.
*
* Returns an empty string, if the array is NULL or empty.
*
* @return
*		the string representation of the current array
*/
string QS::getArray() const {
    string arraystring;
    int size = getSize();

    if (size < 1)
        return arraystring;

    stringstream ss;
    for(int i=0; i < index-1; i++) {
        ss << array[i] << ",";
    }
    ss << array[index-1];
    ss >> arraystring;

    return arraystring;
}

/*
* Returns the number of elements which have been added to the array.
*/
int QS::getSize() const {
    int i=index;
    return i;
}

/*
* Adds the given value to the end of the array starting at index 0.
* For example, the first time addToArray is called,
* the give value should be found at index 0.
* 2nd time, value should be found at index 1.
* 3rd, index 2, etc up to its max capacity.
*
* If the array is filled, do nothing.
* returns true if a value was added, false otherwise.
*/
bool QS::addToArray(int value) {
    if (index < cap) {
        array[index] = value;
        if(array[index] == value) {
            index++;
            return true;
        }
        else
            return false;
    }
    else
        return false;
}

/*
* Dynamically allocates an array with the given capacity.
* If a previous array had been allocated, delete the previous array.
* Returns false if the given capacity is non-positive, true otherwise.
*
* @param
*		size of array
* @return
*		true if the array was created, false otherwise
*/

bool QS::createArray(int capacity) {
    if(array != NULL) {
        delete[] array;
        array = NULL;
        index = 0;
        cap = 0;
    }
    cap = capacity;
    array = new int[capacity];
    if(array != 0) {
        return true;
    }
    else {
        return false;
    }
}

/*
* Resets the array to an empty or NULL state.
*/
void QS::clear() {
    if(array != NULL) {
        delete[] array;
        array = NULL;
    }
    index = 0;
    cap = 0;
}