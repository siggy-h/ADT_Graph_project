// Siegby Hinds, Program Assignment #5
// CS 163, PSU Fall 2014
/* "graph.cpp" has the class definition and prototypes for the graph class
 */


#include "graph.h"



using namespace std;



// constructor
// Input: none	Output: none
graph:: graph(int size)
{
	adjacency_list = new vertex[size];
	
	for(int i = 0; i < size; ++i)
	{
		adjacency_list[i].head = NULL;
		adjacency_list[i].vtx_topic = NULL;
	}
	
	list_size = size;
}



// destructor
// Input: none	Output: none
graph:: ~graph()               
{
	for(int i = 0; i < list_size; ++i)
	{
		node * curr = adjacency_list[i].head;
        //node * temp = adjacency_list[i].head;
	
		while(curr) //deallocate the edge list for each array index
		{
			curr = curr->next;
			delete adjacency_list[i].head;
            adjacency_list[i].head = curr;
        }
		
		adjacency_list[i].head = NULL;
	}
	
    //delete [] adjacency_list;
    
	list_size = 0;
}



// load_file(): loads data from an external file, returns sucess or fail
// Input: const char [], topic &, graph     Output: int
int graph:: load_file(const char file_name[], topic & addTopic, graph myGraph)
{
	ifstream myFile;
	
	int MAX_CHAR = 100;		// for user inputs and/or reading from file
	int MAX_TRIVIA = 400; 	// for user inputs and/or reading from file

	char aTopic [MAX_CHAR];
	char topicTrivia [MAX_TRIVIA];
	
	myFile.open(file_name);
	
	if(!myFile)  // failed to open file
		return 0;
		
	myFile.get(aTopic, MAX_CHAR, ';'); // get first line
	
	while( !myFile.eof() )
	{
		myFile.get(); // throw away ';'
		
		myFile.get(topicTrivia, MAX_TRIVIA, ';');
		myFile.ignore(MAX_CHAR, '\n');

		//myFile.get();
		
		addTopic.create_topic (aTopic, topicTrivia);
		
		myGraph.insert_vertex(addTopic);
	
		myFile.get(aTopic, MAX_CHAR, ';');

	}
	
	
	myFile.close();
	
	return 1;
}



// insert_vertex(): inserts a vertex into the graph,
// returns success or fail
// Input: const topic &     Output: int
int graph:: insert_vertex(const topic & aTopic_to_add)
{
    int found = 0;
    
    for(int i = 0; i < list_size && !found; ++i)  // find the first empty index
    {
        if(adjacency_list[i].vtx_topic == NULL) // index is available
        {   
			adjacency_list[i].vtx_topic = new topic;
			adjacency_list[i].vtx_topic->copy_topic(aTopic_to_add);
			found = 1;
        }
    }
	
	return found;
}   




// insert_edge(): inserts an adjacent vertex into the edge list,
// takes a char * for current vertex & char * for adjacent vertex,
// returns success or fail
// Input: const char *, const char *	Output: int
int graph:: insert_edge( const char * current_vtx, const char * vtx_to_connect)   
{
    int vertex_index;
    int vertex_to_attach;

    vertex_index = find_location(current_vtx);
    vertex_to_attach = find_location(vtx_to_connect);

    if(vertex_index == -1 || vertex_to_attach == -1) // index was not found
        return 0; 

    node * temp = new node;
    temp->adjacent = &adjacency_list[vertex_to_attach];

	temp->next = adjacency_list[vertex_index].head;

	adjacency_list[vertex_index].head = temp;

	//temp->next = adjacency_list[vertex_index].head; 

	return 1;
}




// find_location():  finds the location of a vertex in the graph,
// takes char * key_value & returns success or fail
// Input: const char *	Output: int
int graph:: find_location(const char * key_value)
{
    //	int index = -1;  // a flag if vertex "key_value" was not found
	
	for(int i = 0; i < list_size && adjacency_list[i].vtx_topic != NULL; ++i)
	{
		if( !adjacency_list[i].vtx_topic->compare(key_value) )
		{    
			//index = i;
			return i;
		}
	}
	
	return -1;
	//return index;
}  




// display_adjacent(): Wrapper - prints edge list, returns success or fail
// Input: char * 		Output: int
int graph:: display_adjacent(char * key_value)
{
    int vertex_index;

    vertex_index = find_location(key_value);

    if(vertex_index == -1) // index was not found, get out... 
        return 0; 
	
	else
		return display_adjacent( adjacency_list[vertex_index].head ) ;
} 




// display_adjacent(): Recursive - prints edge list, returns success or fail
// Input: node * 		Output: int
int graph:: display_adjacent(node * head)
{
	int success = 0;

	if(!head)
		return 0;
	else
	{
		head->adjacent->vtx_topic->display();
		++success;
	}

	success += display_adjacent(head->next);

	return success;
}



// display_all_vtx(): Wrapper - prints verticies only
// Input: none		Output: int
int graph:: display_all_vtx()
{
	return display_all_vtx(adjacency_list, 0);
}




// display_all_vtx(): Recursive - prints verticies only
// Input: vertex *, int 	Output: int
int graph:: display_all_vtx(vertex * adjacency_list, int index)
{
	if(adjacency_list[index].vtx_topic == NULL || index == list_size)
		return 0;
	
	else
		adjacency_list[index].vtx_topic->display();
	
	return display_all_vtx(adjacency_list, ++index);
}




// display_all(): Wrapper - prints vertex along w/ edge list
// Input: none		Output: int
int graph:: display_all()
{
	int index = 0;

	return display_all(adjacency_list, index);
} 




// display_all(): Recursive - prints vertex w/edge list
// Input: vertex *, int 		Output: int
int graph:: display_all(vertex * adj_list, int index)
{

	if(adj_list[index].vtx_topic == NULL || index == list_size)
		return 0;
		
	cout << "\n---- Main Topic ---- " << endl;
	adj_list[index].vtx_topic->display();
	cout << "---- Related ---- " << endl;
	
	if (!display_adjacent(adj_list[index].head) )
		cout << "* none \n\n";		
 
	return display_all(adj_list, ++index);
}





/*
// displays each vertex in adjacency_list
int graph:: display_all_vtx(void) const
{
	for(int i = 0; i < list_size && adjacency_list[i].vtx_topic != NULL; ++i)
	{
		adjacency_list[i].vtx_topic->display();
	}

	return 1;

}
*/
