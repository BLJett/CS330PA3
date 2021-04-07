// Name: Brandon Luke Jett & Sierra Laney
// Emails: blj0013@uah.edu & sel0010@uah.edu
// Course: CS330-01
// Program: A* Pathfinding
// Purpose: Implement and test the A* pathfinding algorithm

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

// Create a graph structure to hold the connections and nodes
class Graph {
	// Includes the data for each connection
	class Connections {
		// Contains the "C" character for connections
		char connectionChar[200] = ""; 
		// Contains the connection id
		int connectionNumber[200] = { -1 };
		// Contains the from node (start node) of a connection
		int fromNode[200] = { -1 };
		// Contains the to node (goal node) of a connection
		int toNode[200] = { -1 };
		// Contains the cost of the connection
		int connectionCost[200] = { -1 }; 
		// Contains the cost plot position
		// **NOTE: For the plot, might be easier to ignore later by capturing now
		int costPlotPosition[200] = { -1 }; 
		// Contains the type of terrain 
		// **NOTE: For the plot, might be easier to ignore later by capturing now
		int typeOfTerrain[200] = { -1 };
	};

	// Includes the data for each node
	class Nodes {
		// Contains the "N" character for nodes
		char nodeChar[200] = { "" };
		// Contains the node id 
		int nodeNumber[200] = { -1 };
		// Contains the node status of 1=unvisited, 2=open, or 3=closed
		int nodeStatus[200] = { -1 };
		// Contains the cost-so-far sum from the from node to the current node
		int nodeCostSoFar[200] = { -1 };
		// Contains the estimated heuristics result from the euclidean distance formula
		int estimatedHeuristics[200] = { -1 };
		// Contains the estimated total cost result from all open nodes
		int estimatedTotal[200] = { -1 }; 
		// Contains the previous node in path 
		int previousNode[200] = { -1 }; 
		// Contains the x and y coordinates of the path
		double xycoord[200][200] = { -1, -1 };
		// Contains the number plot position
		// **NOTE: For the plot, might be easier to ignore later by capturing now
		int numberPlotPos[200] = { -1 };
		// Contains the name plot position 
		int namePlotPos[200] = { -1 }; 
		// Contains the name of the place the node references
		string nodeName[200] = { "" };
	};
};

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

	// Check to see if the input file failed to open
	if (infile.fail())
	{
		//Display error message to console
		cout << "Error with input file." << endl;

		// Return 1 with error
		return 1; 
	}

	// Retrieve each line of the file
	while (getline(infile, line)) {

		// Erase the comments from the code that start with #
		line.erase(std::find(line.begin(), line.end(), '#'), line.end());

		// Print out the line to the console
		cout << line << endl;
	}

	// Close the input file
	infile.close(); 

	return 0;
}