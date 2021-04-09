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
const int UNVISITED = 1;
const int OPEN = 2;
const int CLOSED = 3;
const int CONNECTIONSNUM = 153;
const int NODESNUM = 66;

// Initialize constants used for indexes in graph nodes data structure.
// Constants start at 3 because first two columns loaded from input nodes file are not used by algorithms.

// Status of node; UNVISITED, OPEN, or CLOSED
const int STATUS = 3;
// Cost of shortest path found so far to this node
const int COSTSOFAR = 4;
// Estimated heuristic cost
const int HEURISTIC = 5;
// Estimated total cost 
const int TOTAL = 6;
// Previous node in path from start to this node
const int PREVIOUS = 7;
// Location(position) x coordinate
const int LOCX = 8;
// Location(position) z coordinate
const int LOCZ = 9;

// Initialize constants used for indexes in graph connections data structure.
// Constants start at 3 because first two columns loaded from input nodes file are not used by algorithms.

// Connection from node number
const int FROMNODE = 3;
// Connection to node number
const int TONODE = 4;
// Connection cost
const int COST = 5;
// Estimated total cost
const int COSTPOS = 6;
// Previous node in path from start to this node
const int TYPE = 7;

// Includes the data for each connection
class Connections {
public:
	// Contains the "C" character for connections
	string connectionChar[CONNECTIONSNUM] = { "" };
	// Contains the connection id
	int connectionNumber[CONNECTIONSNUM] = { -1 };
	// Contains the from node (start node) of a connection
	int fromNode[CONNECTIONSNUM] = { -1 };
	// Contains the to node (goal node) of a connection
	int toNode[CONNECTIONSNUM] = { -1 };
	// Contains the cost of the connection
	int connectionCost[CONNECTIONSNUM] = { -1 };
	// Contains the cost plot position
	// **NOTE: For the plot, might be easier to ignore later by capturing now
	int costPlotPosition[CONNECTIONSNUM] = { -1 };
	// Contains the type of terrain 
	// **NOTE: For the plot, might be easier to ignore later by capturing now
	int typeOfTerrain[CONNECTIONSNUM] = { -1 };
};

// Includes the data for each node
class Nodes {
public:
	// Contains the "N" character for nodes
	string nodeChar[NODESNUM] = { "" };
	// Contains the node id 
	int nodeNumber[NODESNUM] = { -1 };
	// Contains the node status of 1=unvisited, 2=open, or 3=closed
	int nodeStatus[NODESNUM] = { -1 };
	// Contains the cost-so-far sum from the from node to the current node
	int nodeCostSoFar[NODESNUM] = { -1 };
	// Contains the estimated heuristics result from the euclidean distance formula
	int estimatedHeuristics[NODESNUM] = { -1 };
	// Contains the estimated total cost result from all open nodes
	int estimatedTotal[NODESNUM] = { -1 };
	// Contains the previous node in path 
	int previousNode[NODESNUM] = { -1 };
	// Contains the x coordinates of the path
	double xcoord[NODESNUM] = { -1 };
	// Contains the z coordinates of the path
	double zcoord[NODESNUM] = { -1 };
	// Contains the number plot position
	// **NOTE: For the plot, might be easier to ignore later by capturing now
	int numberPlotPos[NODESNUM] = { -1 };
	// Contains the name plot position 
	int namePlotPos[NODESNUM] = { -1 };
	// Contains the name of the place the node references
	string nodeName[NODESNUM] = { "" };
	// 
	int openNodes[NODESNUM] = { UNDEFINED };
};

// Loop through the array of nodes, update the lowestTotal to hold
// the lowest cost node so far until we find the lowest cost open
// node in the array of nodes.
// Params: Nodes node
// Return: int, element of lowest cost node with lowest index
int findLowestOpenNode(Nodes *node)
{
	int lowestOpenNode = INT_MAX;
	int lowestTotal = INT_MAX;

	for (int i = 0; i < NODESNUM; i++)
	{
		if (node->nodeStatus[i] == OPEN && node->estimatedTotal[i] < lowestTotal)
		{
			lowestTotal = node->estimatedTotal[i];
			lowestOpenNode = i;
		}
	}
	return lowestOpenNode;
}

// Calculates the heuristic (in our case) the 
// Euclidean distance between two given nodes
// Params: pointer to a node object and the elements of the two nodes
// Return: double, distance between the two nodes
int calculateDistanceBetweenNodes(Nodes *node, int node1, int node2)
{
	int xCoordNode2 = node->xcoord[node2];
	int xCoordNode1 = node->xcoord[node1];
	int zCoordNode2 = node->zcoord[node2];
	int zCoordNode1 = node->zcoord[node1];


	//double distance = sqrt((node->xcoord[node2] - node->xcoord[node1]) ^ 2 +
	//	(node->zcoord[node2] - node->zcoord[node1]) ^ 2);
	double distance = 0;
	int distance1 = 0;
	int distance2 = 0;

	// Calculate the distance between the nodes, we have to do this
	// in order to get the proper calculation, i dont know why
	distance2 = (xCoordNode2 - xCoordNode1);
	distance2 = distance2 * distance2;
	distance1 = (zCoordNode2 - zCoordNode1);
	distance1 = distance1 * distance1;
	distance = distance2 + distance1;
	distance = sqrt(distance);
	return distance;
}

// Finds and returns a list of all outgoing connections
// from the given node.
// Params: Connection, Node, int
// Return: Int array
int* getConnections(Connections *connection, Nodes *node, int currentNode, int result[8]) 
{
	int j = 0;
	//int result[8] = { UNDEFINED };
	for (int i = 0; i < CONNECTIONSNUM; i++)
	{
		if (connection->fromNode[i] == node->nodeNumber[currentNode])
		{
			//result[j] = connection->fromNode[i];
			result[j] = i + 1;
			j++;
		}
	}
	return result;
}

// Find path from start to end node by initializing a start node, finding
// all outgoing connections, picking the lowest outgoing connection and taking it.
// We return an updated version of the graph 
// Params: connection object, node object, start node, goal note
// Return: updated graph? (connections and nodes)
int findPath(Connections *connection, Nodes *node, int startNode, int goalNode)
{
	// Setting the initial values unvisited, infinity, and undefined to status,
	// cost so far, and previous; setting the iterator
	int j = 0; 
	int k = 0; 
	int counter = 0;
	int counter2 = 0;
	int currentNode = UNDEFINED;
	int currentConnections[8] = { -1 }; 
	int toNode = -1;
	int toCost = -1; 
	
	for (int i = 0; i < NODESNUM; i++)
	{
		node->nodeStatus[i] = UNVISITED;
		node->nodeCostSoFar[i] = INT_MAX;
		node->previousNode[i] = UNDEFINED;
	}

	// Initialize the start node as open 
	node->nodeStatus[startNode] = OPEN;
	node->nodeCostSoFar[startNode] = 0;
	
	// Set the first element of the array to the start node
	node->openNodes[startNode];

	// Check to see if there are any nodes set to open 
	while (j < NODESNUM)
	{
		// If yes, set the counter to j 
		if (node->nodeStatus[j] == OPEN)
		{
			counter++;
		}
		j++;
	}

	// Use j to see how many nodes are open and iterate to that number
	while (k < counter)
	{
		currentNode = findLowestOpenNode(node);

		// If our current node is our goal node main loop is complete
		if (currentNode == goalNode)
			break;
		
		// Pass current connections into get connections to update the array
		getConnections(connection, node, currentNode, currentConnections);

		// Increment for next iteration
		k++;

		// Determine how many connections are in currentConnections
		for (int x = 0; x < 8; x++)
		{
			if (currentConnections[x] != 0)
			{
				counter2++;
			}
		}

		// Execute once for every connection in the currentConnections
		for (int y = 0; y < counter2; y++)
		{
			toNode = connection->toNode[currentConnections[y]];
			toCost = node->nodeCostSoFar[currentNode] + connection->connectionCost[currentConnections[y]];
			if (toCost < node->nodeCostSoFar[toNode])
			{
				node->nodeStatus[toNode] = OPEN;
				node->nodeCostSoFar[toNode] = toCost;
				node->estimatedHeuristics[toNode] = calculateDistanceBetweenNodes(node, toNode, goalNode);
				node->estimatedTotal[toNode] = node->nodeCostSoFar[toNode] + node->estimatedHeuristics[toNode];
				node->previousNode[toNode] = currentNode;
				node->openNodes[toNode] = OPEN;
			}
		}

		node->nodeStatus[currentNode] = CLOSED;
		node->openNodes[currentNode] = CLOSED;
	}

	return 0;
}

// Retrieve path from start node to end node
// with A* algorithm
// Param: 
// Return:
int *retrievePath(Nodes *node, int startNode, int goalNode, int path[20])
{
	// int path[20] = { -1 };
	int current = goalNode;

	while ((current != startNode) && (current != UNDEFINED))
	{
		path[current];
		current = node->previousNode[current];
	}
	if (current == startNode)
	{
		path[startNode]; 
		return path;
	}
	else
	{
		int i = 0;
		while (i < 20)
		{
			path[i] = -1;
			i++;
		}
	}
	return path;
}

int main()
{
	// Create an instance of connection 
	Connections* connection = new Connections();
	Nodes* node = new Nodes();
	int path[20] = { -1 };


	// Create a text string for line input
	string line;
	string testInput = " ";

	// Create a temporary string for getline
	string temporary = "";

	//****************************************************
	// Get input and output for the CONNECTIONS
	//****************************************************

	// Input the file 
	ifstream infile("CS 330, Pathfinding AB, Connections v3.txt");

	// Create and populate the CSV textfile
	ofstream outfile;
	outfile.open("CS 330, Pathfinding AB, Output.txt");

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

	while (j<CONNECTIONSNUM) {
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

	cout << endl << endl;

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
		//line.erase(std::find(line.begin(), line.end(), '#'), line.end());

		// Using stringstream to operate on strings
		stringstream linestream(line);

		// Retrieve the character column element
		getline(linestream, node->nodeChar[i], ',');

		// Retrieve the node number column element as a string
		getline(linestream, temporary, ',');

		// Change the string into an int for the node number
		node->nodeNumber[i] = stoi(temporary);
		
		// Retrieve the node status column element as a string
		getline(linestream, temporary, ',');

		// Change the string into an int for the node number
		node->nodeStatus[i] = stoi(temporary);

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
		//getline(linestream, node->nodeName[i], ',');
		getline(linestream, node->nodeName[i], ',');

		// Increment iterator
		i++;
	}

	while (j< NODESNUM) {
		outfile << node->nodeChar[j] << ","
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

	// path 1
	findPath(connection, node, 1, 23);
	retrievePath(node, 1, 23, path);

	outfile << endl << "From node: 1; To node: 23 " << endl; 
	for (int z=0; z < 20; z++) 
	{
		outfile << path[z] << " " << endl;
	} 

	outfile << "Total cost: " << node->nodeCostSoFar[23] << endl;



	infile2.close();
	outfile.close();

	system("pause");

	return 0;
}