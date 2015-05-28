
/* "graph.h" has the class definition and prototypes for a graph. The graph holds the vertices in an adjacency_list array (a topic with trivia for the topic). Each vertex has an edge list (a LLL with pointers to adjacent vertices). The graph class provides the client with the ability to load data from a file, insert vertices, insert adjacent vertices (insert_edge), display all the topics (verticies), display all topics and related topics (edge list), display related topics to a specific topic.
*/



#include <iostream>
#include <cstring>
#include <cctype>
#include <fstream>
#include "topic.h"


//VERTEX
struct vertex
{
    topic * vtx_topic;  // a topic object
    struct node * head; //edge list

};


//EDGE
struct node           // for the edge list
{
    vertex * adjacent;	// a vertex connection
    node * next;        // ptr to next of LLL
};



class graph
{
    public:
        graph(int size = 12);   // constructor
        ~graph();               // destructor
		int load_file (const char file_name[], topic & addTopic, graph myGraph);
							// loads topics and trivia from external file
		int insert_vertex (const topic & aTopic_to_add);
							// makes a vertex
		int insert_edge ( const char * current_vtx, const char * vtx_to_connect);
							// adds a connection to the edge list
		int find_location (const char * key_value);    
							// finds the index of a vertex in the adjacency_list
		int display_all_vtx(); 
							// wrapper - prints verticies only
		int display_adjacent (char * key_value);  
                            // wrapper - prints edge list
		int display_all(); 
							// wrapper - print vertex w/ edge list

    
    private:
        vertex * adjacency_list;	// pointer to an array of vertecies
    
        int list_size;				// size of graph table

        // Private Functions:
		int display_all_vtx(vertex * adjacency_list, int index); 
						// recursive - function to print verticies only
		int display_adjacent(node * head); 
						// recursive - prints an edge list
		int display_all(vertex * adj_list, int index);
					// recursive - prints all vertices w/ each edge list
};
