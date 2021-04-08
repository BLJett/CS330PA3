// Name: Brandon Luke Jett & Sierra Laney
// Emails: blj0013@uah.edu & sel0010@uah.edu
// Course: CS330-01
// Program: A* Pathfinding
// Purpose: Implement and test the A* pathfinding algorithm

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

// Constants needed used by pathfinding algorithms
const int UNDEFINED = 0;
const int UNVISTED = 1;
const int OPEN = 2;
const int CLOSED = 3;

// Initialize constants used for indexes in graph nodes data structure.
// Constants start at 3 because first two columns loaded from input nodes file are not used by algorithms.

// Status of node; UNVISITED, OPEN, or CLOSED
const int STATUS = -3;
// Cost of shortest path found so far to this node
const int COSTSOFAR = -4;
// Estimated heuristic cost
const int HEURISTIC = -5;
// Estimated total cost 
const int TOTAL = -6;
// Previous node in path from start to this node
const int PREVIOUS = -7;
// Location(position) x coordinate
const int LOCX = -8;
// Location(position) z coordinate
const int LOCZ = -9;

// Initialize constants used for indexes in graph connections data structure.
// Constants start at 3 because first two columns loaded from input nodes file are not used by algorithms.

// Connection from node number
const int FROMNODE = -3;
// Connection to node number
const int TONODE = -4;
// Connection cost
const int COST = -5;
// Estimated total cost
const int COSTPOS = -6;
// Previous node in path from start to this node
const int TYPE = -7;

// Includes the data for each connection
class Connections {
public:
	// Contains the "C" character for connections
	string connectionChar[200] = { "" };
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
public:
	// Contains the "N" character for nodes
	string nodeChar[200] = { "" };
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
	// Contains the x coordinates of the path
	double xcoord[200] = { -1 };
	// Contains the z coordinates of the path
	double zcoord[200] = { -1 };
	// Contains the number plot position
	// **NOTE: For the plot, might be easier to ignore later by capturing now
	int numberPlotPos[200] = { -1 };
	// Contains the name plot position 
	int namePlotPos[200] = { -1 };
	// Contains the name of the place the node references
	string nodeName[200] = { "" };
};

// Loop through the array of nodes, update the lowestTotal to hold
// the lowest cost node so far until we find the lowest cost open
// node in the array of nodes.
// Params: Nodes node, Connection connection, int array openNodes
// Return: int, element of lowest  cost node with lowest index
int findLowestOpenNode(Nodes node, Connections connection, int openNodes[100])
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
	// Create an instance of connection 
	Connections* connection = new Connections();
	Nodes* node = new Nodes();

	// Create a text string for line input
	string line;

	// Create a temporary string for getline
	string temporary = "";

	//****************************************************
	// Get input and output for the CONNECTIONS
	//****************************************************

	// Input the file 
	ifstream infile("CS 330, Pathfinding AB, Connections v3.txt");

	// Create and populate the CSV textfile
	ofstream outfile;
	outfile.open("CS 330, Astar Connections Output.txt");

	// Set the iterator to 0 for index element
	int i = 0;
	int j = 0;

	// Check to see if the input file failed to open
	if (infile.fail())
	{
		//Display error message to console
		cout << "Error with input file." << endl;

		// Return 1 with error
		return -1;
	}

	// Check to see if the output file failed to open
	if (outfile.fail())
	{
		//Display error message to console
		cout << "Error with output file." << endl;

		// Return 1 with error
		return -2;
	}

	// Retrieve each line of the file
	while (getline(infile, line)) {

		// Erase the comments from the code that start with #
		line.erase(std::find(line.begin(), line.end(), '#'), line.end());

		// Using stringstream to operate on strings
		stringstream linestream(line);

		// Retrieve the character column element
		getline(linestream, connection->connectionChar[i], ',');

		// Retrieve the connection number column element as a string
		getline(linestream, temporary, ',');

		// Change the string into an int for the connection number
		connection->connectionNumber[i] = stoi(temporary);

		// Retrieve the from node column element as a string
		getline(linestream, temporary, ',');

		// Change the string into an int for the from node
		connection->fromNode[i] = stoi(temporary);

		// Retrieve the to node column element as a string
		getline(linestream, temporary, ',');

		// Change the string into an int for the to node
		connection->toNode[i] = stoi(temporary);

		// Retrieve the cost column element as a string
		getline(linestream, temporary, ',');

		// Change the string into an int for the cost
		connection->connectionCost[i] = stoi(temporary);

		// Retrieve the to cost plot position element as a string
		getline(linestream, temporary, ',');

		// Change the string into an int for the cost plot position
		connection->costPlotPosition[i] = stoi(temporary);

		// Retrieve the type of terrain column element as a string
		getline(linestream, temporary);

		// Change the string into an int for the to node
		connection->typeOfTerrain[i] = stoi(temporary);

		// Print out the line to the console
		// cout << line << endl;

		// Increment iterator
		i++;
	}

	while (j<200) {
		outfile << connection->connectionChar[j] << ","
			<< connection->connectionNumber[j] << ","
			<< connection->fromNode[j] << ","
			<< connection->toNode[j] << ","
			<< connection->connectionCost[j] << ","
			<< connection->costPlotPosition[j] << ","
			<< connection->typeOfTerrain[j]
			<< endl;
		j++;
	}

	// Close the connections input file
	infile.close();
	//outfile.close(); // I am pretty sure we want to only close this after we have done the nodes as well

	//****************************************************
	// Get input and output for the NODES
	//****************************************************

	// Input the file 
	ifstream infile2("CS 330, Pathfinding AB, Nodes v3.txt");

	i = 0;
	j = 0;

	// Check to see if the input file failed to open
	if (infile2.fail())
	{
		//Display error message to console
		cout << "Error with input file." << endl;

		// Return 1 with error
		return -3;
	}

	// Retrieve each line of the file
	while (getline(infile2, line)) {

		// Erase the comments from the code that start with #
		line.erase(std::find(line.begin(), line.end(), '#'), line.end());

		// Using stringstream to operate on strings
		stringstream linestream(line);

		// Retrieve the character column element
		getline(linestream, node->nodeChar[i], ',');

		// Retrieve the node number column element as a string
		getline(linestream, temporary, ',');

		// Change the string into an int for the node number
		node->nodeNumber[i] = stoi(temporary);

		// Retrieve the cost so far as a string
		getline(linestream, temporary, ',');

		// Change the string into an int for the cost so far
		node->nodeCostSoFar[i] = stoi(temporary);

		// Retrieve the estimated heuristic as a string
		getline(linestream, temporary, ',');

		// Change the string into an int for the estimated heuristic
		node->estimatedHeuristics[i] = stoi(temporary);

		// Retrieve the estimated total as a string
		getline(linestream, temporary, ',');

		// Change the string into an int for the estimated total
		node->estimatedTotal[i] = stoi(temporary);

		// Retrieve the estimated previous node in path
		getline(linestream, temporary, ',');

		// Change the string into an int for the previous node in path
		node->previousNode[i] = stoi(temporary);

		// Retrieve the location x as a string
		getline(linestream, temporary, ',');

		// Change the string into an int for the location x
		node->xcoord[i] = stoi(temporary);

		// Retrieve the location z as a string
		getline(linestream, temporary, ',');

		// Change the string into an int for the location z
		node->zcoord[i] = stoi(temporary);

		// Retrieve the number plot position as a string
		getline(linestream, temporary, ',');

		// Change the string into an int for the number plot position
		node->numberPlotPos[i] = stoi(temporary);

		// Retrieve the name plot position as a string
		getline(linestream, temporary, ',');

		// Change the string into an int for the name plot position
		node->namePlotPos[i] = stoi(temporary);

		// Retrieve the node name as a string
		getline(linestream, node->nodeName[i], ',');

		// Print out the line to the console
		cout << line << endl;

		// Increment iterator
		i++;
	}

	while (j<200) {
		cout << node->nodeChar[j] << ","
			<< node->nodeNumber[j] << ","
			<< node->nodeStatus[j] << ","
			<< node->nodeCostSoFar[j] << ","
			<< node->estimatedHeuristics[j] << ","
			<< node->estimatedTotal[j] << ","
			<< node->previousNode[j] << ","
			<< node->xcoord[j] << ","
			<< node->zcoord[j] << ","
			<< node->numberPlotPos[j] << ","
			<< node->namePlotPos[j] << ","
			<< node->nodeName[j]
			<< endl;
		j++;
	}

	infile2.close();
	outfile.close();
	system("pause");

	return 0;
}
