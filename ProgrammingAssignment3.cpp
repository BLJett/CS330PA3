// Name: Brandon Luke Jett & Sierra Laney
// Emails: blj0013@uah.edu & sel0010@uah.edu
// Course: CS330-01
// Program: A* Pathfinding
// Purpose: Implement and test the A* pathfinding algorithm

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>

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
};

// Loop through the array of nodes, update the lowestTotal to hold
// the lowest cost node so far until we find the lowest cost open
// node in the array of nodes.
// Params: pointer to node object, vector of open nodes
// Return: int, lowest index of the lowest total cost node
int findLowestOpenNode(Nodes *node, vector <int> openNodesVector)
{
	int lowestTotalCost = INT_MAX;
	int lowestOpenNodeIndex = INT_MAX;

	for (int i = 0; i < openNodesVector.size(); i++)
	{
		if (node->nodeStatus[openNodesVector.operator[](i)] && node->estimatedTotal[openNodesVector.operator[](i)] < lowestTotalCost)
		{
			lowestTotalCost = node->estimatedTotal[openNodesVector.operator[](i)];
			lowestOpenNodeIndex = node->nodeNumber[openNodesVector.operator[](i)];
		}
	}

	return lowestOpenNodeIndex;
}

// Calculates the heuristic (in our case) the 
// Euclidean distance between two given nodes
// Params: pointer to a node object, two ints that are the nodeNumber of 2 nodes
// Return: double, distance between the two nodes
double calculateDistanceBetweenNodes(Nodes *node, int node1, int node2)
{
	int xCoordNode2 = node->xcoord[node2];
	int xCoordNode1 = node->xcoord[node1];
	int zCoordNode2 = node->zcoord[node2];
	int zCoordNode1 = node->zcoord[node1];

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
// Params: pointer to connection object, int of the current node 
// Return: vector of integers that are connections to a node such that the
// from node matches current node

vector<int> getConnections(Connections *connection, int currentNode)
{
	vector <int> resultVector;
	for (int i = 0; i < CONNECTIONSNUM; i++)
	{
		if (connection->fromNode[i] == currentNode)
		{
			resultVector.push_back(i);
		}
	}
	return resultVector;
}


// Find path from start to end node by initializing a start node, finding
// all outgoing connections, picking the lowest outgoing connection and taking it.
// We update connections and nodes when necessary 
// Params: pointer to connection object, pointer to node object, an int start node, an int goal note
// Return: the value 0 to show it executed correctly 
int findPath(Connections *connection, Nodes *node, int startNode, int goalNode)
{
	vector <int> openNodes;
	vector <int> currentConnections;
	int currentNode = UNDEFINED;
	int toNode = UNDEFINED;
	int toCost = UNDEFINED;

	for (int i = 0; i < NODESNUM; i++)
	{
		node->nodeStatus[i - 1] = UNVISITED;
		node->nodeCostSoFar[i - 1] = INT_MAX;
		node->previousNode[i - 1] = UNDEFINED;
	}

	// Initialize the start node as open 
	node->nodeStatus[startNode] = OPEN;
	node->nodeCostSoFar[startNode] = 0;
	openNodes.push_back(startNode);

	while (openNodes.size() > 0)
	{
		currentNode = findLowestOpenNode(node, openNodes);
		if (currentNode == goalNode)
			break;

		currentConnections = getConnections(connection, currentNode);

		for (int i = 0; i < currentConnections.size(); i++)
		{
			toNode = connection->toNode[currentConnections.operator[](i)];
			toCost = node->nodeCostSoFar[currentNode] + connection->connectionCost[currentConnections.operator[](i)];

			if (toCost < node->nodeCostSoFar[toNode])
			{
				node->nodeStatus[toNode] = OPEN;
				node->nodeCostSoFar[toNode] = toCost;
				node->estimatedHeuristics[toNode] = calculateDistanceBetweenNodes(node, toNode, goalNode);
				node->estimatedTotal[toNode] = node->nodeCostSoFar[toNode] + node->estimatedHeuristics[toNode];
				node->previousNode[toNode] = currentNode;
				openNodes.push_back(toNode);
			}
		}
		node->nodeStatus[currentNode] = CLOSED;
		vector<int>::iterator it = std::find(openNodes.begin(), openNodes.end(), currentNode);
		openNodes.erase(it);
	}

	return 0;
}

// Retrieve path from start node to end node
// with A* algorithm
// Param: pointer to nodes object, int of a start node, int of a goal node
// Return: vector of integers of the correct path taken
vector <int> retrievePath(Nodes *node, int startNode, int goalNode)
{
	vector <int> path;
	int current = goalNode;

	while ((current != startNode) && (current != UNDEFINED))
	{
		path.push_back(current);
		current = node->previousNode[current];
	}
	if (current == startNode)
	{
		path.push_back(startNode);
		return path;
	}
	else
	{
		path.clear();
		cout << "I broke everything lul" << endl;
	}
	return path;
}

int main()
{

	// Create an instance of connection, nodes, and vector to store path
	Connections* connection = new Connections();
	Nodes* node = new Nodes();
	vector<int>path;


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

	// Outfile contains the requirement of our names and section
	outfile << "Names: Brandon Luke Jett & Sierra Laney" << endl;
	outfile << "Class section: CS330-1" << endl << endl;

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
		connection->connectionNumber[i] -= 1;

		// Retrieve the from node column element as a string
		getline(linestream, temporary, ',');

		// Change the string into an int for the from node
		connection->fromNode[i] = stoi(temporary);
		connection->fromNode[i] -= 1;

		// Retrieve the to node column element as a string
		getline(linestream, temporary, ',');

		// Change the string into an int for the to node
		connection->toNode[i] = stoi(temporary);
		connection->toNode[i] -= 1;

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

	// Outfile meets requirements of printing the connections after loaded
	outfile << "Connection input data: " << endl;

	while (j<CONNECTIONSNUM) {
		outfile << connection->connectionChar[j] << ","
			<< connection->connectionNumber[j] +1 << ","
			<< connection->fromNode[j]+1 << ","
			<< connection->toNode[j]+1 << ","
			<< connection->connectionCost[j] << ","
			<< connection->costPlotPosition[j] << ","
			<< connection->typeOfTerrain[j]
			<< endl;
		j++;
	}

	outfile << endl;

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
		node->nodeNumber[i] -= 1;


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

	// Outfile completes requirement by printing nodes after loaded
	outfile << "Node input data: " << endl;

	while (j< NODESNUM) {
		outfile << node->nodeChar[j] << ","
			<< node->nodeNumber[j]+1 << ","
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

	outfile << endl;

	// Call to find path to retrieve nodes path of path 1
	// Print the path in ascending order from from node to to node
	// Print total path cost 
	outfile << "Path 1: From node 1 to node 23" << endl;

	findPath(connection, node, 0, 22);
	path = retrievePath(node, 0, 22);
	for (i = path.size()-1; i >= 0; i--)
	{
		outfile << path.operator[](i) + 1 << " ";
	}
	outfile << endl;
	outfile << "Total cost of the path: " << node->estimatedTotal[22] << endl;
	outfile << endl;

	// Call to find path to retrieve nodes path of path 2
	// Print the path in ascending order from from node to to node
	// Print total path cost 
	outfile << "Path 2: From node 1 to node 59" << endl;
		 
	findPath(connection, node, 0, 58);
	path = retrievePath(node, 0, 58);
	for (i = path.size() - 1; i >= 0; i--)
	{
		outfile << path.operator[](i) + 1 << " ";
	}
	outfile << endl;
	outfile << "Total cost of the path: " << node->estimatedTotal[58] << endl;
	outfile << endl;

	// Call to find path to retrieve nodes path of path 3
	// Print the path in ascending order from from node to to node
	// Print total path cost 
	outfile << "Path 3: From node 8 to node 58" << endl;

	findPath(connection, node, 7, 57);
	path = retrievePath(node, 7, 57);
	for (i = path.size() - 1; i >= 0; i--)
	{
		outfile << path.operator[](i) + 1 << " ";
	}
	outfile << endl;
	outfile << "Total cost of the path: " << node->estimatedTotal[57] << endl;
	outfile << endl;

	// Call to find path to retrieve nodes path of path 4
	// Print the path in ascending order from from node to to node
	// Print total path cost 
	outfile << "Path 4: From node 9 to 65" << endl; 

	findPath(connection, node, 8, 64);
	path = retrievePath(node, 8, 64);
	for (i = path.size() - 1; i >= 0; i--)
	{
		outfile << path.operator[](i) + 1 << " ";
	}
	outfile << endl;
	outfile << "Total cost of the path: " << node->estimatedTotal[64] << endl;
	outfile << endl;

	// Call to find path to retrieve nodes path of path 5
	// Print the path in ascending order from from node to to node
	// Print total path cost 
	outfile << "Path 5: From node to 27 to 33" << endl;

	findPath(connection, node, 26, 32);
	path = retrievePath(node, 26, 32);
	for (i = path.size() - 1; i >= 0; i--)
	{
		outfile << path.operator[](i) + 1 << " ";
	}
	outfile << endl;
	outfile << "Total cost of the path: " << node->estimatedTotal[32] << endl;
	outfile << endl;

	// Pause screen and close outfile
	system("pause");
	outfile.close();
	return 0;
}
