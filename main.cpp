
/*  Assignment #5: This project simulates a program which lets you enter a conversation topic and view a list of related topics. */
/*  "main.cpp" tests the graph ADT.
    main.cpp privides the file name for importing a list of topics and topic trivia
    from an external file, adds related topics (adds to a topics edge list), 
    and also provides a ueser interface to display the topics, related topics, 
    add a new topic, and make a connection between topics.
*/


#include <iostream>
#include <cstring>
#include <cctype>
#include "graph.h"



using namespace std;



void show_menu();
int get_command();
int do_command( graph & myGraph, int command);



// main():
// Input: none, 	Output: int
int main()
{
	int command = 0; // users choice to continue or quit 

	graph myGraph;			// create a new graph
	topic topic_to_add; 	// create a topic
	
	char fileName[] = "topic.txt";		// input file name
	
	if( !myGraph.load_file(fileName, topic_to_add, myGraph) )
		cout << "\nFailed to open file ";

    // predfined values for related topics - adds to edge list
	myGraph.insert_edge("Skateboarding", "California");
	myGraph.insert_edge("California", "Arnold Schwarzenegger");
	myGraph.insert_edge("California", "Star Wars");
	myGraph.insert_edge("Star Wars", "California");
	myGraph.insert_edge("Arnold Schwarzenegger", "Conan the Barbarian");
	myGraph.insert_edge("Conan the Barbarian", "Arnold Schwarzenegger");
	myGraph.insert_edge("Conan the Barbarian", "James Earl Jones");
	myGraph.insert_edge("James Earl Jones", "Conan the Barbarian");
	myGraph.insert_edge("James Earl Jones", "Star Wars");

	while(command != 6)
	{
		show_menu();
        
		command = get_command();
		
        if(command < 1 || command > 6)
			cout << "\nSorry that is not a valid choice. Please try again \n";
		else
			do_command(myGraph, command);
	}
		
    return 0;
}



// get_command(): Gets user input based on menu selection
// Input: none      Output: int (for users choice)
int get_command()
{
    int cmd = 0;
    
	cout << "* Please make your selection. Enter a number (1 - 6): ";
    cin >> cmd;
    cin.ignore(100, '\n');
	
    return cmd;
}


// do_command():  process the users command, returns success or fail
// Input: graph & , int     Output: int
int do_command(graph & myGraph, int command)
{
	int result = 0;				// flag to controll the options success or fail
	int MAX_CHAR = 100;		// for user inputs and/or reading from file
	int MAX_TRIVIA = 400; 	// for user inputs and/or reading from file

	char aTopic[MAX_CHAR];			// topic for a vertex
	char someTrivia[MAX_TRIVIA];	// trivia for a topic
	char adjacent_topic[MAX_CHAR];	// a topic to connect 

	topic newTopic;	
		
	if(command == 1) // Show all Topics (display verticies) 
	{
		
		cout << "* You selected " << command << ", Show All Topics: \n "<< endl;
		
		myGraph.display_all_vtx();
		
		result = 1;	
	}


	else if(command == 2)
            // display all topics & related (print vertex with edge list)
	{
		cout << "* You selected " << command << ", Show all Topics & Related " << endl;
	
		if(!myGraph.display_all())
			result = 0;
		else
			result = 1;	
	}
	
	else if(command == 3) // Show Topics Related to a Specific Topic
	{
		
		cout << "* You selected " << command << ", Show a Related Topic" << endl;
		
		cout << "* Enter the main topic:  ";
		cin.get(aTopic, MAX_CHAR, '\n') ; 
		cin.ignore(100, '\n');

		cout << "\n* Here are the topics relating to \"" << aTopic <<"\": \n";
		
		if( !myGraph.display_adjacent(aTopic))
			cout << "* Sorry, there are topics related to \"" << aTopic <<"\" " << endl;

		result = 1;	
	}
	
	else if(command == 4) // Add a New Topic (insert vertex)
	{
		
		cout << "* You selected " << command << " add a new topic: " << endl;
		
		cout << "* Enter the topic:  ";
		cin.get(aTopic, MAX_CHAR, '\n') ; 
		cin.ignore(100, '\n');
		
		cout << "* Enter some trivia for this topic:  ";
		cin.get(someTrivia, MAX_TRIVIA, '\n') ; 
		cin.ignore(100, '\n');
		
		newTopic.create_topic(aTopic, someTrivia);

		if( !myGraph.insert_vertex(newTopic) )
			cout << "* Sorry, there is no more room to add a new topic to the list." << endl;
		
		result = 1;	
	}

	else if(command == 5) // Make a connection, add to edge list
	{
		
		cout << "* You selected " << command << " Make a connection: " << endl;
		
		cout << "* Enter the main topic:  ";
		cin.get(aTopic, MAX_CHAR, '\n') ; 
		cin.ignore(100, '\n');
		
		cout << "* Enter the related topic:  ";
		cin.get(adjacent_topic, MAX_CHAR, '\n') ; 
		cin.ignore(100, '\n');
		
		myGraph.insert_edge(aTopic, adjacent_topic);
		
		result = 1;	
	}

	else if(command == 6) // Quit
	{
		cout << "\nGood Bye..." << endl;
		
		result = 1;	
	}

	return result;
}



// show_menu():  displays program' menu
// Input: none      Output: none
void show_menu()
{
    cout << "\n-------------------------------- Main Menu --------------------------------" << endl;
    cout << " 1 | Show all Topics \t\t  4 | Add a New Topic \n";
    cout << " 2 | Show all Topics and Related  5 | Make a Connection Between Topics\n";
    cout << " 3 | Show Topics Related to a \t  6 | Quit \n" ;
    cout << "     Specific Topic \n";
	cout << 
"---------------------------------------------------------------------------" << endl;
}
