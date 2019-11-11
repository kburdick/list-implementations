//
// Created by Kurt Burdick on 10/15/19.
//

#include <stdexcept>
#include <string>
#include "ArrayList.h"
#include "ArrayLib.h"

ArrayList::ArrayList(int initialCapacity) {

    if (initialCapacity < 1){
        throw std::invalid_argument("In ArrayList constructor, size must be > 0");
    }

    this->currCapacity = initialCapacity;
    this->array = new int[currCapacity];
    this->currItemCount = 0; //no valid items in the array
}

ArrayList::ArrayList(const ArrayList& arrayListToCopy) {
    this->currCapacity = arrayListToCopy.currCapacity;
    this->currItemCount = arrayListToCopy.currItemCount;
    this->array = new int[currCapacity];
    //remember to populate the copied array
    for(int i = 0; i < currItemCount; i++) {
        array[i] = arrayListToCopy.array[i];
    }
}

ArrayList& ArrayList::operator=(const ArrayList& arrayListToCopy) {
    if(this != &arrayListToCopy) {
        delete [] array;

        this->currCapacity = arrayListToCopy.currCapacity;
        this->currItemCount = arrayListToCopy.currItemCount;
        this->array = new int[currCapacity];
        //remember to populate the copied array
        for(int i = 0; i < currItemCount; i++) {
            array[i] = arrayListToCopy.array[i];
        }
    }

    return *this;

}

ArrayList::~ArrayList(){
    delete [] array;
}

void ArrayList::doubleCapacity() {
    int doubleCap = currCapacity * 2;

    int* arrCopy = new int[doubleCap];

    for(int i = 0; i < currCapacity; i++) {
        arrCopy[i] = array[i];
    }

    this->array = arrCopy;
}

void ArrayList::insertAtEnd(int itemToAdd) {
    if (currItemCount == currCapacity) {
        doubleCapacity();
        array[currItemCount] = itemToAdd;
        currItemCount += 1;
    }
    else{
        array[currItemCount] = itemToAdd;
        currItemCount += 1;
    }
}


int ArrayList::getValueAt(int index) {
    int value;

    if (index == 0 & currItemCount == 0) {
        throw std::out_of_range("Bad index given to getValueAt: 0");
    }

    if(index >= currItemCount) {
        throw std::out_of_range("invalid index");
    }

    if (index < 0) {
        throw std::out_of_range("invalid index");
    }

    if (index >= 0 & index < currItemCount) {
        value = array[index];
        return value;
    }
}

std::string ArrayList::toString() {

    std::string arrString;
    arrString += "{";
    //updates the string to contain the next values and allows it to be passed the the next function call

    if(currItemCount == 0){
        arrString += "}";
        return arrString;
    }

    if(currItemCount == 1){
        arrString += std::to_string(array[0]) + "}";
        return arrString;
    }

    else {
        for (int i = 0; i < currItemCount; i++) {

            if(i == (currItemCount - 1)) {
                arrString += std::to_string(array[i]) + "}";
                return arrString;
            }

            else {
                arrString += std::to_string(array[i]) + ", ";
            }
        }
    }
}

bool ArrayList::isEmpty() {

    if(currItemCount == 0) {
        return true;
    }
    else {
        return false;
    }
}

int ArrayList::itemCount() {
    return currItemCount;
}

void ArrayList::clearList() {
    this->array = new int[currCapacity];
    currItemCount = 0;
}

int ArrayList::find(int numToFind) {
    int unusedTimer = 0;

    return ::find(array, currItemCount, numToFind, unusedTimer);
}

int ArrayList::findLast(int numToFind) {
    int unusedTimer = 0;

    return ::findLast(array, currItemCount, numToFind, unusedTimer);

}

int ArrayList::findMaxIndex() {
    int unusedTimer = 0;

    if(currItemCount == 0){
        throw std::out_of_range("In findMaxIndex, List must have items");
    }
    else {
        return ::findMaxIndex(array, currItemCount, unusedTimer);
    }
}

void ArrayList::insertAtFront(int itemToAdd) {
    int unusedTimer = 0;

    if(currItemCount == currCapacity) {
        doubleCapacity();
    }

    int* arrCopy = new int[currItemCount + 1];
    currItemCount += 1;

    for(int i = 0; i < currItemCount; i++) {
        if(i == 0){
            arrCopy[0] = itemToAdd;
        }
        else{
            arrCopy[i] = array[i - 1];
        }
    }
    array = ::copyArray(arrCopy, currItemCount, unusedTimer);

    delete [] arrCopy;
}

void ArrayList::insertAt(int itemToAdd, int index) {
    int unusedTimer = 0;

    if(index < 0 || index > currItemCount) {
        throw std::out_of_range("No item to remove");
    }

    int* arrCopy = new int[currItemCount + 1];
    currItemCount += 1;

    for(int i = 0; i < currItemCount; i++) {

        if(i < index) {
            arrCopy[i] = array[i];
        }

        if(i == index) {
            arrCopy[index] = itemToAdd;
        }

        if(i > index) {
            arrCopy[i] = array[i - 1];
        }
    }

    array = copyArray(arrCopy, currItemCount, unusedTimer);

    delete [] arrCopy;
}

int ArrayList::removeValueAtEnd() {
    int unusedTimer = 0;

    int indexCopy = array[currItemCount - 1];

    if (currItemCount <= 0 | currItemCount > currCapacity) {
        throw std::out_of_range("In removeValueAtEnd, List must have items");
    }

    int* arrCopy = new int[currItemCount - 1];
    currItemCount = currItemCount - 1;

    for(int i = 0; i < currItemCount; i++) {
        arrCopy[i] = array[i];
    }

    array = copyArray(arrCopy, currItemCount, unusedTimer);
    delete [] arrCopy;

    return indexCopy;
}

int ArrayList::removeValueAtFront() {
    int unusedTimer = 0;

    int indexCopy = array[0];

    if (currItemCount <= 0 | currItemCount > currCapacity) {
        throw std::out_of_range("In removeValueAtFront, List must have items");
    }

    int* arrCopy = new int[currItemCount - 1];
    currItemCount = currItemCount - 1;

    for(int i = 0; i < currItemCount; i++) {
        arrCopy[i] = array[i + 1];
    }

    array = copyArray(arrCopy, currItemCount, unusedTimer);
    delete [] arrCopy;

    return indexCopy;
}

int ArrayList::removeValueAt(int index) {
    int unusedTimer = 0;

    if(index < 0 | index > currItemCount) {
        throw std::out_of_range("invalid index");
    }

    int* arrCopy = new int[currItemCount - 1];
    currItemCount = currItemCount - 1;
    int indexCopy;

    for(int i = 0; i <= currItemCount; i++) {
        if(i < index) {
            arrCopy[i] = array[i];
        }
        else {
            indexCopy = array[index];
            arrCopy[i] = array[i + 1];
        }
    }

    array = copyArray(arrCopy, currItemCount, unusedTimer);
    delete [] arrCopy;

    return indexCopy;
}
