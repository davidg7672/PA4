/*
David Sosa Vidal
CPSC 122
Professor Jacob Shea
Programming Assignment 4, Structs
Functions File
*/

#include "Structs.h"

/***********************************************************
Function: taskOne()
Inputs: Nothing
Outputs: Returns nothing
General Description: 

This is a driver function for task one. Essentially, the program
enters a while loop, if the user inputs a "quit" the program will stop,
if not, the user will enter a word/sentence to be computed.
This function processes the string, computes maximum occurences,
and prints the histogram.
***********************************************************/
void taskOne(void) {
    LetterOccurrence letOcc[123];
    string sentence;
    char largestCountedCharacter = '\0';
    int countOfHigestNum = 0;
    double highestFreq = 0.0;
    
    // Prompting User for sentence
    while(true) {
        cout << "Please enter a sentence or type 'quit' to quit and more onto the next task" << endl;
        getline(cin, sentence);

        if(sentence == "quit") {
            break;
        }
        processString(sentence, letOcc);
        computeMaximumOccurences(letOcc, &largestCountedCharacter, &countOfHigestNum, &highestFreq);
        printHistogram(letOcc, &largestCountedCharacter, &countOfHigestNum, &highestFreq);
    }
}

/***********************************************************
Function: processString()
Inputs: String of user input, and Letter Occs struct array
Outputs: Returns Nothing
General Description: 

This function iterates through the string, and based of that 
information, the letterOccs[] array at position i will get
updates for the apropiate properties
Computes the amount of times a letter pops up, and the frequency
of each letter
***********************************************************/
void processString(const string s, LetterOccurrence letterOccs[]) {
    int i = 0, counter = 0, sizeOfArr = 123;
    for(int i = 0; i < 123; i++) {
        letterOccs[i].count = 0;
        letterOccs[i].frequency = 0;
    }

    for(char c: s) {
        counter++;
        letterOccs[int(c)].count++;
    }

    for(char c: s) {
        letterOccs[int(c)].frequency = (double) letterOccs[int(c)].count / counter;
    }
    cout << endl << "Your Sentence: " << s << endl;
}

/***********************************************************
Function: computeMaximumOccurences()
Inputs: Letter occs array struct, char pointer to represent 
the highest counted letter, an int pointer to represent the
higest count, and a double pointer to represent the highest
frequency for each one
Outputs: Returns nothing
General Description: 

This package dynically allocates memory for each of the properties
that the Package struct has. It also close the input file
***********************************************************/
void computeMaximumOccurences(const LetterOccurrence letterOccs[], char *c, int *count, double *freq) {
    int largestValueCount = letterOccs[0].count, largestChar;
    double largestValueFrequency = letterOccs[0].frequency;
    for(int i = 65; i < 123; i++) {
        if(letterOccs[i].count > largestValueCount) {
            largestValueCount = letterOccs[i].count;
            largestChar = i;
        }
        if(letterOccs[i].frequency > largestValueFrequency) {
            largestValueFrequency = letterOccs[i].frequency;
        }
    }
    *count = largestValueCount;
    *freq = largestValueFrequency;
    *c = largestChar;
}

/***********************************************************
Function: *loadPackages()
Inputs: Letter of Occs array, highest counted, the freqeuncy
of letter, and the letter that was counted the highest.
Outputs: Returns Nothing
General Description: 

This function prints out a histogram of the letters that
were taken in as input. Then it output the higest counted
letter, the amount of times it was counted, and the frequency
of that letter
***********************************************************/
void printHistogram(LetterOccurrence letterOccs[], char *c, int *count, double *freq) {
    string letter = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
    int i = 0;
    cout << endl;

    // Max number of *count will determine how many rows there are, the higher the count,
    // the more rows there will be.
    for (int i = *count; i >= 1; i--) {
        for (int j = 65; j <= 90; j++) {
            if (letterOccs[j].count >= i) {
                cout << '*';
            } 
            else {
                cout << ' ';
            }
        }

        for(int j = 97; j <= 122; j++) {
            if(letterOccs[j].count >= i) {
                cout << '*';
            }
            else {
                cout << ' ';
            }
        }
        cout << endl;
    }    

    cout << letter << endl;
    cout << endl;
    cout << "Letter of Highest Count: " << *c << endl;
    cout << "Highest Count: " << *count << endl;
    cout << "Highest Frequency: " << fixed << setprecision(2) << *freq << endl;
}


/***********************************************************
Function: taskTwo()
Inputs: Argument Vector/Input via command line
Outputs: Nothing 
General Description: 

This function takes in the arguments from the command line,
and computes task 2. This function, reads from file, opens files
dynically allocates memory, computes package stats, and
prints out information. This is a driver function for task2
***********************************************************/
void taskTwo(char *argv[]) {
    ifstream inputFile;
    string truckDriverName;
    int numPackages, heaviestId;
    double averageWeight, heaviestWeight;
    Package *loadedPackages = nullptr;

    // Checking to see if files are open
    inputFile.open(*(argv + 1));
    inputFileOpen(inputFile);
    
    cout << "Task 2:" << endl << endl;

    initialReadFromFile(inputFile, &numPackages);

    // Checking to see if files are open
    inputFile.open(*(argv + 1));
    inputFileOpen(inputFile);
    loadedPackages = loadPackages(inputFile, &truckDriverName, &numPackages);
    computePackageStats(loadedPackages, numPackages, &heaviestId, &heaviestWeight, &averageWeight);
    printInformation(loadedPackages, &numPackages, &truckDriverName, &heaviestId, &heaviestWeight, &averageWeight);

    // Deallocating memory
    delete [] loadedPackages;
    loadedPackages = nullptr;

    // Closing the inputfile
    inputFile.close();
}

/***********************************************************
Function: *loadPackages()
Inputs: Input file, truck driver name, number of packages
Outputs: Package pointer
General Description: 

This package dynically allocates memory for each of the properties
that the Package struct has. It also close the input file
***********************************************************/
Package *loadPackages(ifstream& inputFile, string *driverName, int *numPackages) {
    int counter = 0;

    getline(inputFile, *driverName);
    
    Package *packages = new Package[*numPackages];
    for(int i = 0; i < *numPackages; i++) {
        inputFile >> (packages + i)->idNumber;
        inputFile >> (packages + i)->weight;
        inputFile >> (packages + i)->width;
        inputFile >> (packages + i)->length;
        inputFile >> (packages + i)->height;
    }

    // Closing input file
    inputFile.close();

    return packages;
}

/***********************************************************
Function: computePackageStats()
Inputs: Package struct variable, number of packages, heaveist
Id, heaviest weight, and average weight

Outputs: Returns nothing
General Description: 

This function computes the stats for the heaviest weight, 
the heaviest weight Id, and the average weight. 
***********************************************************/
void computePackageStats(const Package * packages, const int numPackages, int * heaviestId, double * heaviestWeight, double * avgWeight) {
    double sum = 0;
    *heaviestWeight = packages[0].weight;
    for(int i = 0; i < numPackages; i++) {
        if(*heaviestWeight < packages[i].weight) {
            *heaviestWeight = packages[i].weight;
            *heaviestId = packages[i].idNumber;
        }
        sum += packages[i].weight;
    }

    *avgWeight = sum / numPackages;
}

/***********************************************************
Function: printInformation()
Inputs: Package struct pointer to reference the properties 
of the struct, pointer to numPackages, the truck drivers name, 
the heaviest weight id, heaviest weight, and the average weight.

Outputs: Returns nothing

General Description: This function prints out all information
***********************************************************/
void printInformation(const Package *packages, int *numPackages, string *driverName, int *heaviestId, double *heaviestWeight, double *avgWeight) {
    int numberOfPackages = *numPackages;
    string truckDriverName = *driverName;

    cout << "Truck Driver Name: "<< truckDriverName << endl;
    cout << "Number of Packages: " << numberOfPackages << endl << endl;

    cout << "Package Information" << endl << "_____________" << endl << endl;

    for(int i = 0; i < *numPackages; i++) {
        cout << "Package ID: " << packages[i].idNumber << endl;
        cout << "Package Weight: " << packages[i].weight << endl;
        cout << "Package Width: " << packages[i].width << endl;
        cout << "Package Length: " << packages[i].length << endl;
        cout << "Package Height: " << packages[i].height << endl;
        cout << endl;
    }
    cout << "Package Stats" << endl << "_____________" << endl << endl;

    cout << "ID of heaveiest package: " << *heaviestId << endl;
    cout << "Weight of heaviest package: " << *heaviestWeight << endl;
    cout << "Average weight of packages on truck: " << *avgWeight << endl;
}

/***********************************************************
Function: inputFileOpen()
Inputs: Input file
Outputs: Returns nothing
General Description: 

This function checks to see if the input file is open
***********************************************************/
void inputFileOpen(ifstream& inputFile) {
    if(!inputFile.is_open()) {
        cout << "File failed to open" << endl;
        exit(-1);
    }
}

/***********************************************************
Function: initialReadFromFile
Inputs: Input file, and the number of packages pointer
Outputs: Return Nothign
General Description: 

This function reads a file for the first time, and computes
the number of packages that there are. The *numPackages gets
updated and the inputfile is closed.
***********************************************************/
void initialReadFromFile(ifstream &inputFile, int *numPackages) {
    int trash, counter = 0;
    double moreTrash;
    string trashButItsAString;
    getline(inputFile, trashButItsAString);
    
    while(!inputFile.eof()) {   
        getline(inputFile, trashButItsAString);
        inputFile >> trash >> moreTrash >> trash >> trash >> trash;
        counter++;
    }
    *numPackages = counter;
    inputFile.close();
}