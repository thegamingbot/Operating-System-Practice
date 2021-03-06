#include <iostream>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <sstream>
using namespace std;

// A bubble sort function that sorts a typename T in ascending order
template <typename T>
void bubbleSortAsc(T* arr, int n){
    for (int i = 0; i < n - 1; i++)
        for (int j = 0; j < n - i - 1; j++)
            if (arr[j] > arr[j+1]){
                T c = arr[j + 1];
                arr[j + 1] = arr[j];
                arr[j] = c;
            }
}

// A bubble sort function that sorts a typename T in descending order
template <typename T>
void bubbleSortDesc(T* arr, int n){
    for (int i = 0; i < n - 1; i++)
        for (int j = 0; j < n - i - 1; j++)
            if (arr[j] < arr[j+1]){
                T c = arr[j + 1];
                arr[j + 1] = arr[j];
                arr[j] = c;
            }
}

// A function that prints the contents on typename T array
template <typename T>
void print(T* arr, int n){
    for(int i = 0; i < n; i++)
        cout << arr[i] << " ";
    cout << endl;
}

bool isAllLen1(int argc, char* argv[]);
bool isAnyAlpha(int argc, char* argv[]);
bool isAllInt(int argc, char* argv[]);
bool isAllFloat(int argc, char* argv[]);
void displayHelp();

// Main driver program with arguments
int main(int argc, char* argv[]){
    // If the user ask for help on usage of the command
    if(strncmp(argv[1], "--help", 6) == 0 || argc < 4){
        // Print the instructions on how to use the command
        displayHelp();
		exit(EXIT_SUCCESS);
    }

    // Convert the size from string to int
    int size = atoi(argv[1]);
    char qw[] = {'.'};

    // If the size is negative or if there exists a floating point in the size
	if(size <= 0 || strstr(argv[1], qw)){
        // Print an error
        printf("\033[1;31m");
        printf("Error: ");
        printf("\033[0;31m");
        printf("The size of the array should be a positive non-zero integer.\n");
        // Print the instructions on how to use the command
        displayHelp();
        exit(EXIT_FAILURE);
    }

    // Convert the choice from string to int
    int choice = atoi(argv[2]);

    // If the choice is less than 1 or greater than two or if there exists a floating point in the choice
    if(choice < 1 || choice > 2 || strstr(argv[2], qw)){
        // Print an error
        printf("\033[1;31m");
        printf("Error: ");
        printf("\033[0;31m");
        printf("Choice should either be 1 for ascending sort or 2 for descending sort.\n");
        // Print the instructions on how to use the command
        displayHelp();
        exit(EXIT_FAILURE);
    }

    int iarr[size];
    float farr[size];
    char carr[size];

    // If the length of all array elements are 1
    if(isAllLen1(argc, argv)){
        // If any one of them is an alphabet or character
        if(isAnyAlpha(argc, argv)){
            // Copy the contents to a char array
            for(int i = 3; i < argc; i++)
                carr[i - 3] = argv[i][0];
            // If the choice is ascending
            if(choice == 1)
                bubbleSortAsc<char>(carr, size);
            // If the choice is descending
            if(choice == 2)
                bubbleSortDesc<char>(carr, size);
            // Print the sorted array
            print<char>(carr, size);
            exit(EXIT_SUCCESS);
        }
        // If all of them are numbers
        else{
            // Copy the contents to an integer array
            for(int i = 3; i < argc; i++)
                iarr[i - 3] = atoi(argv[i]);
            // If the choice is ascending
            if(choice == 1)
                bubbleSortAsc<int>(iarr, size);
            // If the choice is descending
            if(choice == 2)
                bubbleSortDesc<int>(iarr, size);
            // Print the sorted array
            print<int>(iarr, size);
            exit(EXIT_SUCCESS);
        }
    }
    // It the length of the content is more than one
    else{
        // If all the inputs are integers
        if(isAllInt(argc, argv)){
            // Copy the contents to an integer array
            for(int i = 3; i < argc; i++)
                iarr[i - 3] = atoi(argv[i]);
            // If the choice is ascending
            if(choice == 1)
                bubbleSortAsc<int>(iarr, size);
            // If the choice is descending
            if(choice == 2)
                bubbleSortDesc<int>(iarr, size);
            // Print the sorted array
            print<int>(iarr, size);
            exit(EXIT_SUCCESS);
        }
        // If all the inputs are floating numbers
        else if(isAllFloat(argc, argv)){
            // Copy the contents to a floating array
            for(int i = 3; i < argc; i++)
                farr[i - 3] = atof(argv[i]);
            // If the choice is ascending
            if(choice == 1)
                bubbleSortAsc<float>(farr, size);
            // If the choice is descending
            if(choice == 2)
                bubbleSortDesc<float>(farr, size);
            // Print the sorted array
            print<float>(farr, size);
            exit(EXIT_SUCCESS);
        }
        // If the numbers are not floating nor int nor characters
        else{
            // Print an error
            printf("\033[1;31m");
            printf("Error: ");
            printf("\033[0;31m");
            printf("Enter a int array or float array or character array.\n");
            // Display the usage
            displayHelp();
            exit(EXIT_FAILURE);
        }
    }
}

// A function that checks if length of all strings are 1
bool isAllLen1(int argc, char* argv[]){
    // Loop through the array
    for(int i = 3; i < argc; i++)
        // If any of the string length is not one, return false
        if(strlen(argv[i]) != 1)
            return false;
    return true;
}

// A function that checks if the contents contains an alphabet
bool isAnyAlpha(int argc, char* argv[]){
    // Loop through the array
    for(int i = 3; i < argc; i++)
        // If any of the content is an alphabet, return true
        if(isalpha(argv[i][0]) != 0)
            return true;
    return false;
}

// A function that checks if the contents are all integers
bool isAllInt(int argc, char* argv[]){
    int x;
    string a;
    // Loop through the contents
    for(int i = 3; i < argc; i++){
        // Convert the number from string to int
        x = atoi(argv[i]);
        // Convert the number back to string from int
        a = to_string(x);
        // Convert the original argument to a string 
        string y = string(argv[i]);
        // If the original argument is different from the converted argument, return false
        if(y.compare(a) != 0)
            return false;
    }
    return true;
}

// A function that checks if the contents are all floating numbers
bool isAllFloat(int argc, char* argv[]){
    double x;
    string a;
    // Loop through the contents
    for(int i = 3; i < argc; i++){
        // Convert the number from string to float
        x = atof(argv[i]);
        char* a;
        // Convert the number back to string from float
        sprintf(a, "%f", x);
        // Convert the original argument to a string
        // If the original argument is different from the converted argument, return false
        if(strncmp(argv[i], a, strlen(argv[i])) != 0)
            return false;
    }
    return true;
}

// A function to display help on usage of the command
void displayHelp(){
    printf("\033[1;36m");
    printf("\nUsage: ");
    printf("\033[0;36m");
    printf("./sort3 array_length choice array_elements\n");
    printf("\033[0m");
    printf("\nArray length must be an integer and greater than 0.\n");
    printf("Choice: 1 for ascending sort and 2 for descending sort.\n");
    printf("Array elements must be separated by a space and must be integers or floating numbers or characters.\n");
}