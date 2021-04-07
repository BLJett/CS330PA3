// Name: Brandon Luke Jett && Sierra Laney
// Emails: blj0013@uah.edu & sel0010@uah.edu
// Course: CS330-01
// Program: A* Pathfinding
// Purpose: Implement and test the A* pathfinding algorithm

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

// Loop through the array of nodes, update the lowestTotal to hold
// the lowest cost node so far until we find the lowest cost open
// node in the array of nodes.
// Params: none
// Return: int, element of lowest  cost node with lowest index
int findLowestOpenNode()
{
	int lowestOpenNode = 0;
	int lowestTotal = 0;
	return lowestOpenNode;
}

// Calculates distance between two given nodes
// Params: none
// Return: int, distance between the two nodes
int calculateDistanceBetweenNodes()
{
	int distance = 0;
	return distance;
}

// Finds and returns a list of all outgoing connections
// from the given node.
// Params: none
// Return: ???
int getConnections() // probably doesnt return an int, adjust as necessary
{
	return 0;
}

// Find path from start to end node by initializing a start node, finding
// all outgoing connections, picking the lowest outgoing connection and taking it.
// We return an updated version of the graph 
// Params: none
// Return: object???
int findPath()
{
	return 0;
}

int main() 
{
	// Create a text string for line input
	string line;

	// Input the file 
	ifstream infile("CS 330, Pathfinding AB, Connections v3.txt");

	// Retrieve each line of the file
	while (getline(infile, line)) {

		// Erase the comments from the code that start with #
		line.erase(std::find(line.begin(), line.end(), '#'), line.end());

		// Print out the line to the console
		cout << line << endl;
	}

	infile.close(); 
	return 0;
}