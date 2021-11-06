#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <bits/stdc++.h>
using namespace std;
void printArray(int **a){

    int arrSize = 5;
    for(int i = 0 ; i<arrSize ; i++){
        for(int j = 0 ; j<arrSize ; j++){
            cout<<a[i][j] << " ";
        }
        cout << endl;
    }
}
void splitString(string line){
    string delimiter = " ";

    size_t pos = 0;
    string token;
    while ((pos = line.find(delimiter)) != std::string::npos) {
        token = line.substr(0, pos);
        std::cout << token << std::endl;
        line.erase(0, pos + delimiter.length());
    }
}
void simple_tokenizer(string s)
{
    stringstream ss(s);
    string word;
    while (ss >> word) {
        cout << word << endl;
    }
}
void placeBombAndCalculate(int **array,int row, int column, int* total, int size){
    int tempTotal = 0;
    int bombValue = (array[row][column]);
    if(bombValue == 0){
        return;
    }else{ // cell value is different then 0 ,we will check all directions
        int tempRow = row;
        int tempColumn = column;
        tempTotal+= bombValue;
        array[row][column] = 0;
        for(int i = row-1 , j = column-1; i>=0 && j>=0 ; j--, i--){ // left upper diagonal
            if(array[i][j] == bombValue){
                tempTotal+= bombValue;
                array[i][j] = 0;
            }
        }
        for(int i = row+1, j = column+1; j<size && i<size ; j++, i++){ // right down diagonal
            if(array[i][j] == bombValue){
                tempTotal+= bombValue;
                array[i][j] = 0;
            }
        }
        for(int i = row-1, j = column+1 ; j<size && i>=0 ; i-- , j++){ // right upper diagonal
            if(array[i][j] == bombValue){
                tempTotal+= bombValue;
                array[i][j] = 0;
            }
        }
        for(int i = row+1, j = column-1 ; j>=0 && i<size ; i++ , j--){ // left down diagonal
            if(array[i][j] == bombValue){
                tempTotal+= bombValue;
                array[i][j] = 0;
            }
        }
        for(int i = column-1 ; i>= 0 ; i--){ // left direction
            if(array[row][i] == bombValue){
                tempTotal+= bombValue;
                array[row][i] = 0;
            }
        }
        for(int i = column+1 ; i<size ; i++){ // right direction
            if(array[row][i] == bombValue){
                tempTotal+= bombValue;
                array[row][i] = 0;
            }
        }
        for(int i = row-1 ; i>=0 ; i--){ // upper direction
            if(array[i][column] == bombValue){
                tempTotal+= bombValue;
                array[i][column] = 0;
            }
        }
        for(int i = row+1 ; i<size ; i++){ // down direction
            if(array[i][column] == bombValue){
                tempTotal+= bombValue;
                array[i][column] = 0;
            }
        }

    }
    cout << "temp: " << tempTotal << endl ;
    *total += tempTotal;
}
void secondPart(string fileName){
    ifstream file(fileName);
    if(!file) {
        cout << "Cannot open input file.\n";
        exit(1);
    }
    string str;
    int size = 0;
    int count = 0;
    int total = 0;
    if (getline(file, str)){
        size = stoi(str);
    }
    int** array = new int*[size];
    for(int i = 0 ; i<size ; i++){ //creating 2d array
        array[i] = new int[size];
    }
    for(int i = 0 ; i<size ; i++){ // initalizing array with -1 as empty values
        for(int j = 0 ; j<size ; j++){
            array[i][j] = -1;
        }
    }
    while (getline(file, str)) {
        if(size != 0 && count<size){
            // creating array here
            int tempCount = 0;
            cout << str << "\n";
            stringstream ss(str);
            string word;
            while (ss >> word) {
                //cout << word << endl;
                //cout << "array[" <<count<< "][" << tempCount<<"] = "<< word <<endl;
                array[count][tempCount] = stoi(word);
                tempCount++;
            }
            count++;
        }else{
            //placing bombs from here
            stringstream ss(str);
            string word;
            int row = -1;
            int column = -1;
            while (ss >> word) {
                if(row!= -1){
                    column = stoi(word);
                }else{
                    row = stoi(word);
                }
            }
            cout<< "row : " << row << ", column: " << column << endl;
            placeBombAndCalculate(array,row,column,&total,size);
        }
    }
    file.close();
    printArray(array);
    cout<< total<< endl;
}
int main(int argc, char **argv) {
    secondPart(argv[2]);
//    ifstream file("input1.txt");
//    if(!file) {
//        cout << "Cannot open input file.\n";
//        return 1;
//    }
//    string str;
//    string size = "";
//    while (getline(file, str)) {
//        if(size != ""){
//            //cout << str << "\n";
//            //simple_tokenizer(str);
//            //splitString(str);
//        }else{
//            size = str;
//        }
//
//    }
//    file.close();
//    int arraySize = stoi(size);
//    //cout << "array size : " << arraySize << endl;
//    int** array = new int*[arraySize];
//    for(int i = 0 ; i<arraySize ; i++){ //creating 2d array
//        array[i] = new int[arraySize];
//    }
//    for(int i = 0 ; i<arraySize ; i++){ // initalizing array with -1 as empty values
//        for(int j = 0 ; j<arraySize ; j++){
//            array[i][j] = -1;
//        }
//    }
    //printArray(array);
    return 0;
}
