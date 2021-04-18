// Name: Brandon Luke Jett & Sierra Laney
// Emails: blj0013@uah.edu & sel0010@uah.edu
// Course: CS330-01
// Program: Hard-coded state machine
// Purpose: Implement and test a hard-coded state machine

#include <iostream>
#include <stdio.h>      //printf, scanf, puts, NULL 
#include <stdlib.h>     //srand, rand
#include <time.h>       //time
#include <fstream>

using namespace std;

// Initialize constants used for states
const int FOLLOW = 1;
const int PULL_OUT = 2;
const int ACCELERATE = 3;
const int PULL_IN_AHEAD = 4;
const int PULL_IN_BEHIND = 5;
const int DECELERATE = 6;
const int DONE = 7;

// Initialize state and transition counts for each state and its transitions
int stateCount[7] = { 0 }; // holds the number of times we reached a certain state
int transitionCount[9] = { 0 }; // same as above
double transitionCountSum = 0;

// Initialize the variables
int randomNum = 0; // holds the randomly generated number
int scenarioIterationNum = 100; // will be set to go 100 times for first scenario and 1000000 for second scenario
int currentState = 0; // holds the int associated with the various states UNSURE ABOUT USING IT LIKE THIS
int transitionProbability[] = { 8,4,3,4,3,3,8,8,8 }; // holds the probability to transition from 1 point to another in scenario 1
int transitionProbability2[] = { 8,5,4,3,2,3,8,8,8 }; // holds the probability to transition from 1 point to another in scenario 2
int scenarioVersion = 0; // should contain either 1 or 2 depending on which of the scenarios we use. 1 is 100 iterations, 2 is 1,000,000
double stateTotal = 0; // holds the total number of times we reached all states

// This function will print out to a file when called, and increment
// a counter to track number of times that this function has been reached.
// Params: Output file
// Return: none
void followAction(ofstream &outfile)
{
	if (scenarioVersion == 1)
	{
		outfile << "State = 1 Follow" << endl;

	}
	stateCount[0] += 1;
}

// This function will print out to a file when called, and increment
// a counter to track number of times that this function has been reached.
// Params: Output file
// Return: none
void pullOutAction(ofstream &outfile)
{
	if (scenarioVersion == 1)
	{
		outfile << "State = 2 Pull Out" << endl;

	}
	stateCount[1] += 1;
}

// This function will print out to a file when called, and increment
// a counter to track number of times that this function has been reached.
// Params: Output file
// Return: none
void accelerateAction(ofstream &outfile)
{
	if (scenarioVersion == 1)
	{
		outfile << "State = 3 Accelerate" << endl;

	}
	stateCount[2] += 1;
}

// This function will print out to a file when called, and increment
// a counter to track number of times that this function has been reached.
// Params: Output file
// Return: none
void pullInAheadAction(ofstream &outfile)
{
	if (scenarioVersion == 1)
	{
		outfile << "State = 4 Pull Ahead" << endl;

	}
	stateCount[3] += 1;
}

// This function will print out to a file when called, and increment
// a counter to track number of times that this function has been reached.
// Params: Output file
// Return: none
void pullInBehindAction(ofstream &outfile)
{
	if (scenarioVersion == 1)
	{
		outfile << "State = 5 Pull Behind" << endl;

	}
	stateCount[4] += 1;
}

// This function will print out to a file when called, and increment
// a counter to track number of times that this function has been reached.
// Params: Output file
// Return: none
void decelerate(ofstream &outfile)
{
	if (scenarioVersion == 1)
	{
		outfile << "State = 6 Decelerate" << endl;

	}
	stateCount[5] += 1;
}

// This function will end the current iteration of state machine transitions.
// If it occurs in the main loop, there has been an error because the condition of the main loop should be until done.
// Params: Output file
// Return: none
void done(ofstream &outfile)
{
	if (scenarioVersion == 1)
	{
		outfile << "State = 7 Done" << endl;
	}
	stateCount[6] += 1;
}

int main()
{
	srand(time(NULL)); // initializes a random seed
	scenarioVersion = 1;

	// Create and populate the CSV textfile
	ofstream outfile;
	outfile.open("CS 330, Hard-coded State Machine Part 1, 1 Hundo Output.txt");

	// Outfile contains the requirement of our names and section
	outfile << "Names: Brandon Luke Jett & Sierra Laney" << endl;
	outfile << "Class section: CS330-1" << endl << endl;

	// Check to see if the output file failed to open
	if (outfile.fail())
	{
		//Display error message to console
		cout << "Error with output file." << endl;

		// Return 1 with error
		return -2;
	}

	// Loop through for the number of iterations we expect
	for (int i = 0; i < scenarioIterationNum; i++)
	{
		outfile << "Iteration " << i + 1 << endl;

		// Set initial state to follow
		currentState = FOLLOW;
		followAction(outfile);

		while (currentState != DONE)
		{
			// Get random number between 0 and 10
			randomNum = rand() % 10 - 1;

			// Check for what state we are in, then check what random number we got
			// Go to the function that the random number selects.
			if (currentState == FOLLOW)
			{
				if (randomNum < transitionProbability[0]) // Check which state we go to next
				{
					currentState = PULL_OUT;
					transitionCount[0] += 1;
					pullOutAction(outfile);
				}
				else
				{
					currentState = FOLLOW;
					followAction(outfile);
				}
			}
			else if (currentState == PULL_OUT)
			{
				if (randomNum < transitionProbability[1]) // randomNum < 4
				{
					currentState = ACCELERATE;
					transitionCount[1] += 1;
					accelerateAction(outfile);
				}
				else if (randomNum < transitionProbability[1] + transitionProbability[3]) // randomNum < 8
				{
					currentState = PULL_IN_BEHIND;
					transitionCount[3] += 1;
					pullInBehindAction(outfile);
				}
				else
				{
					currentState = PULL_OUT;
					pullOutAction(outfile);
				}
			}
			else if (currentState == ACCELERATE)
			{
				if (randomNum < transitionProbability[2]) // randomNum < 3
				{
					currentState = PULL_IN_AHEAD;
					transitionCount[2] += 1;
					pullInAheadAction(outfile);
				}
				else if (randomNum < transitionProbability[2] + transitionProbability[4]) // randomNum < 6
				{
					currentState = PULL_IN_BEHIND;
					transitionCount[4] += 1;
					pullInBehindAction(outfile);
				}
				else if (randomNum < transitionProbability[2] + transitionProbability[4] + transitionProbability[5]) // randomNum < 9
				{
					currentState = DECELERATE;
					transitionCount[5] += 1;
					decelerate(outfile);
				}
				else
				{
					currentState = ACCELERATE;
					accelerateAction(outfile);
				}
			}
			else if (currentState == PULL_IN_AHEAD)
			{
				if (randomNum < transitionProbability[8]) // randomNum < 5
				{
					currentState = DONE;
					transitionCount[8] += 1;
					done(outfile);
				}
				else
				{
					currentState = PULL_IN_AHEAD;
					transitionCount[6] += 1;
					pullInAheadAction(outfile);
				}
			}
			else if (currentState == PULL_IN_BEHIND)
			{
				if (randomNum < transitionProbability[6]) // randomNum < 8
				{
					currentState = FOLLOW;
					transitionCount[6] += 1;
					followAction(outfile);
				}
				else
				{
					currentState = PULL_IN_BEHIND;
					pullInBehindAction(outfile);
				}
			}
			else if (currentState == DECELERATE)
			{
				if (randomNum < transitionProbability[7])
				{
					currentState = PULL_IN_BEHIND;
					transitionCount[7] += 1;
					pullInBehindAction(outfile);
				}
				else
				{
					currentState = DECELERATE;
					decelerate(outfile);
				}
			}
			else if (currentState == DONE)
			{
				cout << "Error, unexpected state: DONE" << endl;
				return -1;
			}
			else
			{
				cout << "Error, unexpected state: UNKNOWN" << endl;
				return -1;
			}
		}

		outfile << endl << endl;



	}


	outfile << "Scenario = " << scenarioVersion << endl;
	outfile << "Iterations = " << scenarioIterationNum << endl;
	outfile << "State Count = ";

	// print the number of times we reached a particular state, add them into a total as well
	for (int i = 0; i < 7; i++)
	{
		outfile << stateCount[i] << " ";
		stateTotal += stateCount[i];
	}

	outfile << endl << "State Frequency = ";

	// calculate and print out the frequency we reached each state
	for (int i = 0; i < 7; i++)
	{
		outfile << stateCount[i] / stateTotal << " ";
	}

	outfile << endl << "Transition Count = ";
	for (int i = 0; i < 9; i++)
	{
		outfile << transitionCount[i] << " ";
	}
	for (int i = 0; i < 9; i++)
	{
		transitionCountSum += transitionCount[i];
	}
	outfile << endl << "Transition Frequency = ";
	for (int i = 0; i < 9; i++)
	{
		outfile << transitionCount[i] / transitionCountSum << " ";
	}
	outfile << endl;

	outfile.close();
	system("pause");

	//******************************************
	// SCENARIO 2, 1,000,000 ITERATIONS, DO NOT OUTPUT INDIVIDUAL ITERATIONS
	//******************************************
	ofstream outfile2;
	outfile2.open("CS 330, Hard-coded State Machine Part 2, 1 Mil Output.txt");

	// Outfile contains the requirement of our names and section
	outfile2 << "Names: Brandon Luke Jett & Sierra Laney" << endl;
	outfile2 << "Class section: CS330-1" << endl << endl;


	for (int i = 0; i < 7; i++)
	{
		stateCount[i] = 0;
	}

	for (int i = 0; i < 9; i++)
	{
		transitionCount[i] = 0;
	}

	scenarioVersion = 2;
	scenarioIterationNum = 1000000;

	// Loop through for the number of iterations we expect
	// Loop through for the number of iterations we expect
	for (int i = 0; i < scenarioIterationNum; i++)
	{
		// Set initial state to follow
		currentState = FOLLOW;
		followAction(outfile2);

		while (currentState != DONE)
		{
			// Get random number between 0 and 10
			randomNum = rand() % 10 - 1;

			// Check for what state we are in, then check what random number we got
			// Go to the function that the random number selects.
			if (currentState == FOLLOW)
			{
				if (randomNum < transitionProbability[0]) // Check which state we go to next
				{
					currentState = PULL_OUT;
					transitionCount[0] += 1;
					pullOutAction(outfile2);
				}
				else
				{
					currentState = FOLLOW;
					followAction(outfile2);
				}
			}
			else if (currentState == PULL_OUT)
			{
				if (randomNum < transitionProbability[1]) // randomNum < 4
				{
					currentState = ACCELERATE;
					transitionCount[1] += 1;
					accelerateAction(outfile2);
				}
				else if (randomNum < transitionProbability[1] + transitionProbability[3]) // randomNum < 8
				{
					currentState = PULL_IN_BEHIND;
					transitionCount[3] += 1;
					pullInBehindAction(outfile2);
				}
				else
				{
					currentState = PULL_OUT;
					pullOutAction(outfile2);
				}
			}
			else if (currentState == ACCELERATE)
			{
				if (randomNum < transitionProbability[2]) // randomNum < 3
				{
					currentState = PULL_IN_AHEAD;
					transitionCount[2] += 1;
					pullInAheadAction(outfile2);
				}
				else if (randomNum < transitionProbability[2] + transitionProbability[4]) // randomNum < 6
				{
					currentState = PULL_IN_BEHIND;
					transitionCount[4] += 1;
					pullInBehindAction(outfile2);
				}
				else if (randomNum < transitionProbability[2] + transitionProbability[4] + transitionProbability[5]) // randomNum < 9
				{
					currentState = DECELERATE;
					transitionCount[5] += 1;
					decelerate(outfile2);
				}
				else
				{
					currentState = ACCELERATE;
					accelerateAction(outfile2);
				}
			}
			else if (currentState == PULL_IN_AHEAD)
			{
				if (randomNum < transitionProbability[8]) // randomNum < 5
				{
					currentState = DONE;
					transitionCount[8] += 1;
					done(outfile2);
				}
				else
				{
					currentState = PULL_IN_AHEAD;
					transitionCount[6] += 1;
					pullInAheadAction(outfile2);
				}
			}
			else if (currentState == PULL_IN_BEHIND)
			{
				if (randomNum < transitionProbability[6]) // randomNum < 8
				{
					currentState = FOLLOW;
					transitionCount[6] += 1;
					followAction(outfile2);
				}
				else
				{
					currentState = PULL_IN_BEHIND;
					pullInBehindAction(outfile2);
				}
			}
			else if (currentState == DECELERATE)
			{
				if (randomNum < transitionProbability[7])
				{
					currentState = PULL_IN_BEHIND;
					transitionCount[7] += 1;
					pullInBehindAction(outfile2);
				}
				else
				{
					currentState = DECELERATE;
					decelerate(outfile2);
				}
			}
			else if (currentState == DONE)
			{
				cout << "Error, unexpected state: DONE" << endl;
				return -1;
			}
			else
			{
				cout << "Error, unexpected state: UNKNOWN" << endl;
				return -1;
			}
		}
	}

	outfile2 << "Scenario = " << scenarioVersion << endl;
	outfile2 << "Iterations = " << scenarioIterationNum << endl;
	outfile2 << "State Count = ";

	// print the number of times we reached a particular state, add them into a total as well
	for (int i = 0; i < 7; i++)
	{
		outfile2 << stateCount[i] << "  ";
		stateTotal += stateCount[i];
	}

	outfile2 << endl << "State Frequency = ";

	// calculate and print out the frequency we reached each state
	for (int i = 0; i < 7; i++)
	{
		outfile2 << stateCount[i] / stateTotal << "  ";
	}

	outfile2 << endl << "Transition Count = ";
	for (int i = 0; i < 9; i++)
	{
		outfile2 << transitionCount[i] << " ";
	}
	for (int i = 0; i < 9; i++)
	{
		transitionCountSum += transitionCount[i];
	}
	outfile2 << endl << "Transition Frequency = ";
	for (int i = 0; i < 9; i++)
	{
		outfile2 << transitionCount[i] / transitionCountSum << " ";
	}
	outfile2 << endl;

	outfile2.close();
	system("pause");

	return 0;
}
