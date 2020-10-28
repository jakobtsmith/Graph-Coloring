#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <vector>
#include "functions.h"
#include "colormod.h"
using namespace std;

//function to read in the file and output the formatted data
void FileIn(string file_in)
{
	ifstream in; //input stream
	int size = 0; //number of countries in the input file
	int output; //number of output countries. helps with output format
	string contents; //string for the file name and contents within the file respectively
	vector<string> names; //vector to hold the names of the countries
	vector<int> weights; //vector to hold the weights for the adjacency matrix
	
	//prompt user to input file name
	//cout << "Enter the name of the input file:" << endl;
	//cin >> file_in;
	in.open(file_in);
	
	//while the input stream fails
	while(in.fail())
	{
		//prompt the user for a new file name
		cout << "Invalid file name. Reenter another file name:" << endl;
		cin >> file_in;
		in.open(file_in);
	}
	
	getline(in, contents); //get the entire first line of the file
	//copy that first line to a c string
	char *to_c = new char[contents.length()+1];
	strcpy(to_c, contents.c_str());
	
	char *singles = strtok(to_c,","); 
	//get each string delimited by a comma and push it onto the names vector
	while(singles != NULL)
	{
		names.push_back(singles);
		singles = strtok(NULL, ",");
		size++; //increment size to create the matrix and degree array;
	}
	
	int** matrix = new int*[size]; //nxn matrix to hold the borders between countries
	for(int i = 0; i < size; i ++)
	{
		matrix[i] = new int[size];
		for(int j = 0; j < size; j++)
		{
			matrix[i][j] = 0;
		}
	}
	int degree[size]; //array to hold the degree of each country node
	
	for(int i = 0; i < size; i++)
	{
		degree[i] = 0; //set the initial degree for each country to 0
		//get the entire line and copy it to a c string
		getline(in, contents);
		strcpy(to_c, contents.c_str());
		singles = strtok(to_c,","); 
		//get each number delimited by a comma and push it onto the weights vector
		while(singles != NULL)
		{
			weights.push_back(atoi(singles));
			if(atoi(singles) == 1)
			{
				degree[i]++;
			}
			singles = strtok(NULL, ",");
		}
		for(int j = 0; j < size; j++)
		{
			//set the weights into the matrix in their respective locations
			matrix[i][j] = weights.at(j+(i*size));
		}
	}
	
	in.close(); //close the input file
	
	//create an array of colors to be assigned to each color
	int *color = new int[size]; 
	for (int i = 0; i < size; i++)
	{
		color[i] = 0;
	}
	
	//call the keepColoring function
	keepColoring(size, matrix, color, 0);
	
	//print all the final colors
	finalColors(color, size, matrix, names, degree); 
	
	for(int i = 0; i < size; i ++)
	{
		delete[] matrix[i];
	}
	
	delete[] matrix;
}

//boolean function to determine if adjacent nodes have the same color as the current node
bool canColor(int iterate, int size, int** matrix, int color[], int i) 
{
	//loop through the countries in this countries adjacency list
    for (int j = 0; j < size; j++) 
	{
		//if there is an adjacent country with the same color as this one, return false
        if (matrix[iterate][j] == 1 && i == color[j])
		{
            return false;
		}
	}
    return true; 
} 

//recursive function that assigns each node a color by checking surrounding nodes
bool keepColoring(int size, int** matrix, int color[], int iterate) 
{ 
	if (iterate == size) //if every country has been assigned a color, return true
	{
		return true;
	}
	
	//iterate through the colors
	for (int i = 1; i <= 5; i++) 
	{
		//if there are no coloring conflicts with adjacent countries
		if (canColor(iterate, size, matrix, color, i)) 
		{
			//assign the color for the country to the current color
			color[iterate] = i;
			
			//recursively call the function again to determine the next country's color
			if (keepColoring(size, matrix, color, iterate+1))
			{
				return true;
			}
	  
			//if there is no next country, remove the color
			else
			{
				color[iterate] = 0;
			}
		} 
	}
	return false;
}

//function to print out the final colors of every country, their degree, and the average degree
void finalColors(int color[], int size, int** matrix, vector<string> names, int degree[]) 
{  
	int total_degree = 0; //total number of edges to be divided by the size for the average degree
	int output; //number of output countries
	string color_of; //string representing the assigned color
	Color::ColorNum out_color; //value to change the output color
	//loop through the matrix to output the adjacency list
	for(int i = 0; i < size; i++)
	{
		//set the ocean to it's own color that will be turned into blue
		if(names[i] == "Ocean")
		{
			color[i] = 17;
		}
		//assign each country it's corresponding color
		switch(color[i])
		{
			case 1: out_color = Color::RED; color_of = "Red"; break;
			case 2: out_color = Color::GREEN; color_of = "Green"; break;
			case 3: out_color = Color::MAGENTA; color_of = "Magenta"; break;
			case 4: out_color = Color::CYAN; color_of = "Cyan"; break;
			case 17: out_color = Color::BLUE; color_of = "Blue"; break;
		}
		output = 0; //set the number of output countries to 0
		cout << out_color << names[i] << ":" << color_of << " - "; //output the name of the country to print the list for
		for(int j = 0; j < size; j++)
		{
			//set the ocean to it's own color that will be turned into blue
			if(names[j] == "Ocean")
			{
				color[j] = 17;
			}
			//assign each country it's corresponding color
			switch(color[j])
			{
				case 1: out_color = Color::RED; color_of = "Red"; break;
				case 2: out_color = Color::GREEN; color_of = "Green"; break;
				case 3: out_color = Color::MAGENTA; color_of = "Magenta"; break;
				case 4: out_color = Color::CYAN; color_of = "Cyan"; break;
				case 17: out_color = Color::BLUE; color_of = "Blue"; break;
			}
			//if there is a border between countries
			if(matrix[i][j] == 1)
			{
				output++; //increment the output number
				total_degree++;
				cout << out_color << names[j] <<  ":" << color_of; //print the name of the country that shares a border
				//if the number of countries output is less than the total degree, print a comma
				if(output < degree[i])
				{
					cout << ", ";
				}
			}
		}
		cout << endl;
	}
	cout << endl;
	
	//print out the degree of every country
	for(int i = 0; i < size; i++)
	{
		cout << Color::DEFAULT << "Degree of " << names[i] << ": " << degree[i] << endl;
	}
	//print out the average degree of the entire graph
	cout << endl << "Average degree: " << total_degree/size << endl;
} 

