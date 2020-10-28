#include <iostream>
#include <string>
#include <vector>
using namespace std;

void FileIn(string file_in); //function to read in the file and output the formatted data
bool canColor(int iterate, int size, int** matrix, int color[], int i); //boolean function to determine if adjacent nodes have the same color as the current node
bool keepColoring(int size, int** matrix, int color[], int iterate); //recursive function that assigns each node a color by checking surrounding nodes
void finalColors(int color[], int size, int** matrix, vector<string> names, int degree[]); //function to print out the final colors of every country, their degree, and the average degree
