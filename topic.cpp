
/* "topic.cpp" implements the functions for the topic class: create_topic, copy_topic, compare, and display
*/



#include "topic.h"



using namespace std;



// constructor
// Input: none      Output: none
topic:: topic()
{
	aTopic = NULL;
	trivia = NULL;
}	



// destructor
// Input: none      Output: none
topic:: ~topic()
{
	if(aTopic) {
		delete [] aTopic;
		aTopic = NULL;
	}
	
	if(trivia) {
		delete [] trivia;
		trivia = NULL;
	}
}



// create_topic(): adds data to a topic's data fields, returns success or fail
// Input: char *, char * 		Output: int
int topic:: create_topic(char * inTopic, char * inTrivia)
{
	if(!inTopic || !inTrivia)
		return 0;
	
	if(aTopic) {
		delete [] aTopic;
		aTopic = NULL;
	}
	
	if(trivia) {
		delete [] trivia;
		trivia = NULL;
	}
	
	aTopic = new char[strlen(inTopic) + 1 ];
	strcpy(aTopic, inTopic);
	
	trivia = new char[strlen(inTrivia) + 1 ];
	strcpy(trivia, inTrivia);
	
	return 1;
}




// display(): displays the topic and trivia
// Input: none      Output: int
int topic:: display(void)
{
	cout << "Topic:\t " << aTopic << endl;
	cout << "Trivia:\t " << trivia << endl;
	cout << endl;
	
	return 1;
}




// copy_topic(): copies a topic object, returns success or fail
// Input: topic &       Output: int
int topic:: copy_topic(const topic & copy_from)
{
	if (!create_topic(copy_from.aTopic, copy_from.trivia) )
        return 0;
	
	return 1;
}




// compare(): returns 0 (false) if a match
// Input: const char * 		Output: int 
int topic:: compare(const char * topic_to_compare)
{
	return strcmp( aTopic, topic_to_compare);  

}
