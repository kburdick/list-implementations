//
// Created by Toby Dragon on 10/15/18.
//
#include <iostream>
#include "ArrayList.h"
#include "TestLib.h"
#include "List.h"
#include "LinkedList.h"

//assumes working constructor
void insertAtEndAndGetValueAtTest(int* numsToTest, int numsToTestSize, List& myList){
    std::cout << "-------insertAtEndAndGetValueAtTest---------" <<std::endl;
    try{
        myList.getValueAt(0);
        std::cout << "FAIL: getValueAt did not throw exception" << std::endl;
    }
    catch(std::out_of_range& e){
        printAssertEquals("Bad index given to getValueAt: 0", e.what());
    }
    for (int i=0; i<numsToTestSize; i++){
        myList.insertAtEnd(numsToTest[i]);
        printAssertEquals(numsToTest[i], myList.getValueAt(i));
    }
    //once more now that the list is complete
    for (int i=0; i<numsToTestSize; i++){
        printAssertEquals(numsToTest[i], myList.getValueAt(i));
    }

    try{
        myList.getValueAt(5);
        std::cout << "FAIL: getValueAt did not throw exception" << std::endl;
    }
    catch(std::out_of_range& e){
        printAssertEquals("Bad index given to getValueAt: 5", e.what());
    }
    try{
        myList.getValueAt(100);
        std::cout << "FAIL: getValueAt did not throw exception" << std::endl;
    }
    catch(std::out_of_range& e){
        printAssertEquals("Bad index given to getValueAt: 100", e.what());
    }
    try{
        myList.getValueAt(-1);
        std::cout << "FAIL: getValueAt did not throw exception" << std::endl;
    }
    catch(std::out_of_range& e){
        printAssertEquals("Bad index given to getValueAt: -1", e.what());
    }
    std::cout << "--done--" <<std::endl;
}

//assumes working constructor and insertAtEnd
void isEmptyTest(int* numsToTest, int numsToTestSize, List& myList){
    std::cout << "-------isEmptyTest---------" <<std::endl;
    printAssertEquals(true, myList.isEmpty());

    for (int i=0; i<numsToTestSize; i++){
        myList.insertAtEnd(numsToTest[i]);
        printAssertEquals(false, myList.isEmpty());
    }
    std::cout << "--done--" <<std::endl;
}

//assumes working constructor and insertAtEnd
void itemCountTest(int* numsToTest, int numsToTestSize, List& myList){
    std::cout << "-------itemCountTest---------" <<std::endl;
    for (int i=0; i<numsToTestSize; i++){
        printAssertEquals(i, myList.itemCount());
        myList.insertAtEnd(numsToTest[i]);
    }
    printAssertEquals(numsToTestSize, myList.itemCount());
    std::cout << "--done--" <<std::endl;
}

//assumes working insertAtEnd, itemCount
void clearListTest(int* numsToTest, int numsToTestSize, List& myList){
    std::cout << "-------clearListTest---------" <<std::endl;
    printAssertEquals(0, myList.itemCount());
    myList.clearList();
    printAssertEquals(0, myList.itemCount());
    for (int i=0; i<numsToTestSize; i++){
        myList.insertAtEnd(numsToTest[i]);
    }
    printAssertEquals(numsToTestSize, myList.itemCount());
    myList.clearList();
    printAssertEquals(0, myList.itemCount());

    //do it again
    for (int i=0; i<numsToTestSize; i++){
        myList.insertAtEnd(numsToTest[i]);
    }
    printAssertEquals(numsToTestSize, myList.itemCount());
    myList.clearList();
    printAssertEquals(0, myList.itemCount());
    std::cout << "--done--" <<std::endl;
}

//assumes working insertAtEnd
void toStringTest(List& testList){
    std::cout << "-------toStringTest---------" <<std::endl;
    printAssertEquals("{}", testList.toString());

    int a1[5]{5, 6, 7, 8, 9};
    std::string toStringOutputs[5]{"{5}","{5, 6}","{5, 6, 7}","{5, 6, 7, 8}","{5, 6, 7, 8, 9}"};
    for (int i=0; i<5; i++){
        testList.insertAtEnd(a1[i]);
        printAssertEquals(toStringOutputs[i], testList.toString());
    }
    std::cout << "--done--" <<std::endl;
}

//helper function, assumes working insertAtEnd
//@post the list is filled with values from the array
void fillList(List* listToFill, int* arr, int size){
    for (int i=0; i<size; i++){
        listToFill->insertAtEnd(arr[i]);
    }
}

//assumes working constructor, insertAtEnd, and clearList
void findTest(List* myListPtr){
    std::cout << "-------findTest---------" <<std::endl;
    int a1[]={1, 2, 3, 22, 64, 33, 24, 9, 865, 23};
    fillList(myListPtr, a1, 10);
    int failCount = 0;
    for (int i=0; i< 10; i++){
        if (i != myListPtr->find(a1[i])){
            failCount++;
        }
    }
    if (failCount <= 0){
        std::cout << "pass\n";
    }
    else {
        std::cout << "FAIL, fail count:" << failCount << std::endl;
    }
    myListPtr->clearList();
    int a2[]={10, 20, 3, 22, 2, 33, 3, 9, 3, 2};
    fillList(myListPtr, a2, 10);

    printAssertEquals(2, myListPtr->find(3));
    printAssertEquals(-1, myListPtr->find(500));
    printAssertEquals(-1, myListPtr->find(100));
    std::cout << "--done--" <<std::endl;
}

//assumes working constructor and insertAtEnd
void findLastTest(List* testList){
    std::cout << "-------findLastTest---------" <<std::endl;
    int a1[]={1, 2, 3, 22, 64, 33, 24, 9, 865, 23};
    fillList(testList, a1, 10);
    int failCount = 0;
    for (int i=0; i< 10; i++){
        if (i != testList->findLast(a1[i])){
            failCount++;
            std::cout << a1[i];
        }
    }
    if (failCount <= 0){
        std::cout << "pass\n";
    }
    else {
        std::cout << "FAIL, fail count:" << failCount << std::endl;
    }

    testList->clearList();
    int a2[]={10, 20, 3, 22, 2, 33, 3, 9, 3, 2};
    fillList(testList, a2, 10);

    printAssertEquals(8, testList->findLast(3));
    printAssertEquals(-1, testList->findLast(500));
    printAssertEquals(-1, testList->findLast(100));
    std::cout << "--done--" <<std::endl;
}

//assumes working constructor, insertAtEnd, and clearList
void findMaxIndexTest(List& myList){
    std::cout << "-------findMaxIndexTest---------" <<std::endl;
    //{3, 2, 5, 12, 16, 10} added in one at a time
    myList.insertAtEnd(3);
    printAssertEquals(0, myList.findMaxIndex());
    myList.insertAtEnd(2);
    printAssertEquals(0,  myList.findMaxIndex());
    myList.insertAtEnd(5);
    printAssertEquals(2,  myList.findMaxIndex());
    myList.insertAtEnd(12);
    myList.insertAtEnd(16);
    myList.insertAtEnd(10);
    printAssertEquals(4, myList.findMaxIndex());

    myList.clearList();
    std::cout << "negatives:"<< std::endl;
    // {-300000, -200000, -500000, -1200, -160, -1000000} added one at a time
    myList.insertAtEnd(-30000);
    printAssertEquals(0, myList.findMaxIndex());
    myList.insertAtEnd(-20000);
    printAssertEquals(1,  myList.findMaxIndex());
    myList.insertAtEnd(-50000);
    printAssertEquals(1,  myList.findMaxIndex());
    myList.insertAtEnd(-1200);
    printAssertEquals(3,  myList.findMaxIndex());
    myList.insertAtEnd(-160);
    myList.insertAtEnd(-1000000);
    printAssertEquals(4, myList.findMaxIndex());

    std::cout << "Multiple occurrences of max:"<< std::endl;
    int a1[]={3, 2, 5, 1, 5, 1};
    myList.clearList();
    fillList(&myList, a1, 6);
    printAssertEquals(2, myList.findMaxIndex());
    //expect an exception to be thrown when size < 1
    std::cout << "Throws exception:"<< std::endl;
    myList.clearList();
    try{
        myList.findMaxIndex();
        std::cout << "FAIL: find maxIndex did not throw exception" << std::endl;
    }
    catch(std::out_of_range& e){
        printAssertEquals("In findMaxIndex, List must have items", e.what());
    }
    std::cout << "--done--" <<std::endl;
}

//assumes working constructor, toString, isEmpty, itemCount, clearList
void insertAtFrontTest(List& myList){
    std::cout << "-------insertAtFrontTest---------" <<std::endl;
    int a1[5]{5, 6, 7, 8, 9};
    for (int i=0; i<5; i++){
        myList.insertAtFront(a1[i]);
    }
    printAssertEquals("{9, 8, 7, 6, 5}", myList.toString());
    printAssertEquals(false, myList.isEmpty());
    printAssertEquals(5, myList.itemCount());

    //empty it
    myList.clearList();
    printAssertEquals(true, myList.isEmpty());
    printAssertEquals("{}", myList.toString());
    printAssertEquals(0, myList.itemCount());

    //do it again
    for (int i=0; i<5; i++){
        myList.insertAtFront(a1[i]);
    }
    printAssertEquals("{9, 8, 7, 6, 5}", myList.toString());
    printAssertEquals(false, myList.isEmpty());
    printAssertEquals(5, myList.itemCount());
    std::cout << "--done--" <<std::endl;
}

//assumes working constructor, getValueAt, toString, isEmpty, itemCount, clearList
void insertAtTest(List& myList){
    std::cout << "-------insertAtTest---------" <<std::endl;
    //copy of insertAtEnd
    int numsToTest[5]{5, 6, 7, 8, 9};
    int numsToTestSize = 5;

    for (int i=0; i<numsToTestSize; i++){
        myList.insertAt(numsToTest[i], i);
        printAssertEquals(numsToTest[i], myList.getValueAt(i));
    }

    try{
        myList.insertAt(100, 6);
        std::cout << "FAIL: insertAt did not throw exception" << std::endl;
    }
    catch(std::out_of_range& e){
        printAssertEquals("Bad index given to insertAt: 6", e.what());
    }
    try{
        myList.insertAt(100, 100);
        std::cout << "FAIL: insertAt did not throw exception" << std::endl;
    }
    catch(std::out_of_range& e){
        printAssertEquals("Bad index given to insertAt: 100", e.what());
    }
    try{
        myList.insertAt(100, -1);
        std::cout << "FAIL: insertAt did not throw exception" << std::endl;
    }
    catch(std::out_of_range& e){
        printAssertEquals("Bad index given to insertAt: -1", e.what());
    }

    //copy of insertAtFront
    int a1[5]{5, 6, 7, 8, 9};
    myList.clearList();
    for (int i=0; i<5; i++){
        myList.insertAt(a1[i], 0);
    }
    printAssertEquals("{9, 8, 7, 6, 5}", myList.toString());
    printAssertEquals(false, myList.isEmpty());
    printAssertEquals(5, myList.itemCount());

    //empty it
    myList.clearList();
    printAssertEquals(true, myList.isEmpty());
    printAssertEquals("{}", myList.toString());
    printAssertEquals(0, myList.itemCount());

    //do it again
    for (int i=0; i<5; i++){
        myList.insertAtFront(a1[i]);
    }
    printAssertEquals("{9, 8, 7, 6, 5}", myList.toString());
    printAssertEquals(false, myList.isEmpty());
    printAssertEquals(5, myList.itemCount());

    //insert everywhere in the middle and on ends
    for(int i=5; i>=0; i--){
        myList.insertAt(33, i);
    }
    printAssertEquals("{33, 9, 33, 8, 33, 7, 33, 6, 33, 5, 33}", myList.toString());
    printAssertEquals(false, myList.isEmpty());
    printAssertEquals(11, myList.itemCount());

    //insert at other locations
    std::cout << "--done--" <<std::endl;
}

void removeValueAtEndTest(List* myListPtr){
    std::cout << "-------removeValueAtEndTest---------" <<std::endl;
    int a1[]={1, 2, 3, 22, 64, 33, 24, 9, 865, 23};
    fillList(myListPtr, a1, 10);
    int failCount = 0;
    for (int i=0; i < 10; i++){
        if (a1[9-i] != myListPtr->removeValueAtEnd()){
            failCount++;
        }
        printAssertEquals(9-i, myListPtr->itemCount());
    }
    printAssertEquals(true, myListPtr->isEmpty());
    printAssertEquals(0, myListPtr->itemCount());
    if (failCount <= 0){
        std::cout << "pass\n";
    }
    else {
        std::cout << "FAIL, fail count:" << failCount << std::endl;
    }

    try{
        myListPtr->removeValueAtEnd();
        std::cout << "FAIL: removeValueAtEnd did not throw exception" << std::endl;
    }
    catch(std::out_of_range& e){
        printAssertEquals("In removeValueAtEnd, List must have items", e.what());
    }
    std::cout << "--done--" <<std::endl;
}

void removeValueAtFrontTest(List* myListPtr){
    std::cout << "-------removeValueAtFrontTest---------" <<std::endl;
    int a1[]={1, 2, 3, 22, 64, 33, 24, 9, 865, 23};
    fillList(myListPtr, a1, 10);
    int failCount = 0;
    for (int i=0; i< 10; i++){
        if (a1[i] != myListPtr->removeValueAtFront()){
            failCount++;
        }
        printAssertEquals(9-i, myListPtr->itemCount());
    }
    printAssertEquals(true, myListPtr->isEmpty());
    printAssertEquals(0, myListPtr->itemCount());
    if (failCount <= 0){
        std::cout << "pass\n";
    }
    else {
        std::cout << "FAIL, fail count:" << failCount << std::endl;
    }

    try{
        myListPtr->removeValueAtEnd();
        std::cout << "FAIL: removeValueAtFront did not throw exception" << std::endl;
    }
    catch(std::out_of_range& e){
        printAssertEquals("In removeValueAtFront, List must have items", e.what());
    }
    std::cout << "--done--" <<std::endl;
}

void removeValueAtTest(List* myListPtr){
    std::cout << "-------removeValueAtTest---------" <<std::endl;
    int a1[]={10, 20, 30, 40, 50};
    fillList(myListPtr, a1, 5);

    printAssertEquals(30, myListPtr->removeValueAt(2));
    printAssertEquals(4, myListPtr->itemCount());
    printAssertEquals("{10, 20, 40, 50}", myListPtr->toString());

    printAssertEquals(40, myListPtr->removeValueAt(2));
    printAssertEquals(3, myListPtr->itemCount());
    printAssertEquals("{10, 20, 50}", myListPtr->toString());

    printAssertEquals(50, myListPtr->removeValueAt(2));
    printAssertEquals(2, myListPtr->itemCount());
    printAssertEquals("{10, 20}", myListPtr->toString());

    printAssertEquals(10, myListPtr->removeValueAt(0));
    printAssertEquals(1, myListPtr->itemCount());
    printAssertEquals("{20}", myListPtr->toString());
    printAssertEquals(false, myListPtr->isEmpty());

    printAssertEquals(20, myListPtr->removeValueAt(0));
    printAssertEquals(0, myListPtr->itemCount());
    printAssertEquals("{}", myListPtr->toString());
    printAssertEquals(true, myListPtr->isEmpty());
    std::cout << "--done--" <<std::endl;

}


//assume working insertAtEnd, insertAtFront, toString, itemCount, isEmpty, clearList
void moreCapacityTest(List& myList){
    std::cout << "-------moreCapacityTest---------" <<std::endl;
    for(int i=0; i<10; i++){
        myList.insertAtFront(i);
        myList.insertAtEnd(i);
    }
    printAssertEquals("{9, 8, 7, 6, 5, 4, 3, 2, 1, 0, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9}", myList.toString());
    printAssertEquals(20, myList.itemCount());
    printAssertEquals(false, myList.isEmpty());

    std::cout << "--done--" <<std::endl;

}


List* createEmptyList(std::string listType){
    if (listType == "ArrayList"){
        return new ArrayList(11);
    }
    else if (listType == "LinkedList"){
        return new LinkedList();
    }
    else {
        throw std::invalid_argument("Must request either ArrayList or LinkedList");
    }
}

void runAllListTests(std::string listType){

    int a1[5]{5, 6, 7, 8, 9};

    List* testList = createEmptyList(listType);
    insertAtEndAndGetValueAtTest(a1, 5, *testList);
    delete testList;

    testList = createEmptyList(listType);
    isEmptyTest(a1, 5, *testList);
    delete testList;

    testList = createEmptyList(listType);
    itemCountTest(a1, 5, *testList);
    delete testList;

    testList = createEmptyList(listType);
    clearListTest(a1, 5, *testList);
    delete testList;

    //TODO: convert to work on generic list sent as parameter, rather than using ArrayList
    testList = createEmptyList(listType);
    toStringTest(*testList);
    delete testList;

    testList = createEmptyList(listType);
    findTest(testList);
    delete testList;

    //TODO: convert to work on generic list sent as parameter, rather than using ArrayList
    testList = createEmptyList(listType);
    findLastTest(testList);
    delete testList;

    testList = createEmptyList(listType);
    findMaxIndexTest(*testList);
    delete testList;

    testList = createEmptyList(listType);
    insertAtFrontTest(*testList);
    delete testList;

    testList = createEmptyList(listType);
    insertAtTest(*testList);
    delete testList;

    testList = createEmptyList(listType);
    removeValueAtEndTest(testList);
    delete testList;

    testList = createEmptyList(listType);
    removeValueAtFrontTest(testList);
    delete testList;

    testList = createEmptyList(listType);
    removeValueAtTest(testList);
    delete testList;

    testList = createEmptyList(listType);
    moreCapacityTest(*testList);
    delete testList;

}

int main(){
    runAllListTests("ArrayList");
    std::cout << "\n\n======================= LinkedList tests ===========================\n\n" << std::endl;
    runAllListTests("LinkedList");
}
