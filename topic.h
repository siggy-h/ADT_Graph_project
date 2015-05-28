
/* "topic.h" has the class definition and prototypes for a topic class.
	This contains a topic and a topic's trivia and functions to create, copy, 
    compare and display a topic
*/



#include <iostream>
#include <cstring>
#include <cctype>



class topic
{
	public:
		topic(); 	// constructor
		~topic();	// destructor
		int create_topic(char * inTopic, char * inTrivia);
		int display(void);	// displays the topic and trivia
		int copy_topic(const topic & copy_from);
		int compare(const char * topic_to_compare);

		
	private: 
		char * aTopic;
		char * trivia;
};
