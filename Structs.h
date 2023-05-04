/*
David Sosa Vidal
CPSC 122
Professor Jacob Shea
Programming Assignment 4, Structs
Header File
*/

#ifndef STRUCTS_H
#define STRUCTS_H

#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
#include <string.h>
#include <stdlib.h>

using namespace std;

struct LetterOccurrence {
    int count = 0;
    double frequency = 0.0;
};

struct Package {
    int idNumber = 0;
    double weight = 0.0;
    int width = 0;
    int length = 0;
    int height = 0;
};

void processString(const string s, LetterOccurrence letterOccs[]);
void computeMaximumOccurences(const LetterOccurrence letterOccs[], char * c, int * count, double * freq);
Package *loadPackages(ifstream& inputFile, string * driverName, int * numPackages);
void computePackageStats(const Package * packages, const int numPackages, int * heaviestId, double * heaviestWeight, double * avgWeight);
void taskOne(void);
void printHistogram(LetterOccurrence letterOccs[], char *c, int *count, double *freq);
void taskTwo(char *argv[]);
void inputFileOpen(ifstream& inputFile);
void printInformation(const Package *packages, int *numPackages, string *driverName, int *heaviestId, double *heaviestWeight, double *avgWeight);
void initialReadFromFile(ifstream &inputFile, int *numPackages) ;

#endif