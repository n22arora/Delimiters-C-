#include <iostream>
#include<cassert>
#include "project_1.hpp"

// FUNCTION DECLARATION
#ifndef MARMOSET_TESTING
int main();
#endif

void print_program();
bool does_delimiter_match(char c);
bool do_delimiters_nest();

// FUNCTION DEFINITION
#ifndef MARMOSET_TESTING
int main(){
	print_program();
	std::cout<< does_delimiter_match('(')<<std::endl;
	std::cout<< does_delimiter_match('[')<<std::endl;
	std::cout<< does_delimiter_match('{')<<std::endl;
    std::cout<<do_delimiters_nest();
	return 0;
}
#endif

void print_program()
{
	ece150::start_reading_file();                         // STARTS READING THE FILE
	while(!ece150::at_eof())                              // READS THE FILE UNTIL THE END IS REACHED
	{
	std::cout<<ece150::get_next_character();              // PRINTS THE CONTENT OF FILE CHARACTER BY CHARACTER

	}

}

bool does_delimiter_match(char del)
{
	int counter=0;                                       // COUNTER VARIABLE
	char c; 									   // CHARACTER VARIABLE
	int k=1;                                      // HOLDS THE VALUE TO BE RETURNED
	ece150::start_reading_file();
	while(!ece150::at_eof())
	{
		c= ece150::get_next_character();           // c HOLDS THE VALUE OF NEXT CHARACTER

		if(c==del)                                 // IF c AND del (DELIMITER) IS SAME THEN 1 IS ADDED TO m
		{
			counter=counter+1;
		}
		else if(del=='(' && c==')')                // IF THE NUMBER OF OPENING AND CLOSING DELIMITERS IS SAME THEN 1 IS SUBTRACTED FROM m
		{
			counter=counter-1;
			if(counter<0)                                // IF m=-1 AT THIS STEP THEN IT MEANS THERE IS ONE CLOSING DELIMITER FOR WHICH THERE IS NO OPENING DELIMITER IN THE FILE
			{
				k=0;                                    // k=0 SHOWS THAT DELIMIETRS IN THE FILE ARE NOT PROPERLY MATCHED
				std::cout<<"Unmatched "<<c<<std::endl;  // PRINTS THE MESSAGE FOR THE UNMATCHED DELIMITER
				counter=0;                                    // m IS REINITIALIZED TO 0 FOR THE NEXT ITERATION
			}
		}
		else if(del=='{' && c=='}')
		{
			counter=counter-1;                                      // SAME PROCEDURE IS CARRIED OUT FOR {
			if(counter<0)
			{
				k=0;
				std::cout<<"Unmatched "<<c<<std::endl;
				counter=0;
			}
		}
		else if(del=='[' && c==']')
		{
			counter=counter-1;                                      // SAME PROCEDURE IS CARRIED OUT FOR [
			if(counter<0)
			{
				k=0;
				std::cout<<"Unmatched "<<c<<std::endl;
				counter=0;
			}
		}

	}
	if(counter>0)                             // IF m>0 THEN IT MEANS THERE IS AN OPENING DELIMITER IN FILE FOR WHICH THERE IS NO CLOSING DELIMITER
	{
		k=0;                            // k=0 SHOWS THAT THE DELIMITERS IN THE FILE ARE NOT PROPERLY MATCHED
		std::cout<<"Missing ";
		for(int i= 1; i<=counter; i++)        // THE VALUE OF m SHOWS THE NO OF OPENING DELIMITERS FOR WHICH THERE WERE NO CLOSING DELIMITERS IN THE FILE
		{                               // LOOP IS RUN TO PRINT THE MISSING CLOSING DELIMITERS FOR THE CORRESPONDING OPENING DELIMITERS TILL THE VALUE OF m
			if(del=='(')
			{
				std::cout<<")";
			}
			else if(del=='[')
			{
				std::cout<<"]";
			}
			else
			{
				assert(del=='{');
				std::cout<<"}";
			}
		}
		std::cout<<std::endl;
	}
	return k;                        // VALUE OF k IS RETURNED

}

bool do_delimiters_nest(){
	int p,k,l;                               // TO CHECK THE VALUE TO BE RETURNED
	ece150::start_reading_file();            // STARTS READING THE FILE

	ece150::initialize_table();              // INTIALIZES THE TABLE

	while(!ece150::at_eof())                               // LOOP RUNS UNTIL THE END OF THE FILE
	{
		{
		char del = ece150::get_next_character();           // del HOLDS THE VALUE OF THE NEXT CHARACTER
		char c;
		if(del=='(' || del== '{' || del=='[')              // IF del IS AN OPENING DELIMITER THEN IT IS PLACED IN THE TABLE
		{
			ece150::place_character(del);
		}
		if(del==')' || del=='}' || del==']')                // IF del IS A CLOSING DELIMITER THEN IT IS COMPARED WITH THE RIGHMOST OPENING DELIMITER
		{
			c= ece150::get_right_most_character();
			if(c=='(' && del==')')                          // IF del IS THE CORRESPONDING CLOSING DELIMITER FOR THE RIGHTMOST OPENING DELIMITER THEN THE RIGHTMOST DELIMITER IS ERASED FROM THE TABLE
			{
				ece150::erase_right_most_character();
			}
			else if(c=='{' && del=='}')                     // SAME PROCEDURE IS FOR {
			{
				ece150::erase_right_most_character();
			}
			else if(c=='['&& del==']')                      // SAME PROCEDURE IS FOR [
			{
				ece150::erase_right_most_character();
			}
			else
			{                                              // IF THERE IS AN CLOSING DELIMITER FOR WHICH THERE IS NO CORRESPONDING OPENING DELIMITER AT THE RIGHTMOST SIDE OF THE TABLE THEN THAT CLOSING DELIMITER IS UNMATCHED
				k=0;                                       // k IS INITIALIZED TO 0 TO SHOW THAT THE DELIMITERS IN THE FILE ARE NOT PROPERLY NESTED
			 	std::cout<<"Unmatched "<<del<<std::endl;
			}
		}

		}
	}

		if(!ece150::is_table_empty())              // THIS BLOCK OF STATEMENTS RUN IF THE TABLE IS NOT EMPTY
		{
			l=0;                                   // l INITIALIZED TO 0 TO SHOW THAT DELIMITERS IN THE FILE ARE NOT PROPERLY NESTED
			std::cout<<"Missing ";
			while(!ece150::is_table_empty())                  // LOOP IS RUN UNTIL THE TABLE IS EMPTY
			{
				char a= ece150::get_right_most_character();   // a HOLDS THE VALUE OF THE RIGHTMOST CHARACTER
				if(a=='(')
				{                                             // IF THE RIGHMOST CHARACTER IS ( THEN THE MISSING CLOSING DELIMITER ) IS PRINTED AND THE OPENING DELIMITER IS ERASED
					std::cout<<")";
					ece150::erase_right_most_character();
				}
				else if(a=='[')
				{										     // IF THE RIGHMOST CHARACTER IS [ THEN THE MISSING CLOSING DELIMITER ] IS PRINTED AND THE OPENING DELIMITER IS ERASED
					std::cout<<"]";
					ece150::erase_right_most_character();
				}
				else
				{
					assert(a=='{');                          // IF THE RIGHMOST CHARACTER IS { THEN THE MISSING CLOSING DELIMITER } IS PRINTED AND THE OPENING DELIMITER IS ERASED
					std::cout<<"}";
					ece150::erase_right_most_character();
				}
		    }
			std::cout<<std::endl;

		}
		if(k==0 || l==0)                  // k=0 OR l=0 SHOWS THAT THE DELIMITERS ARE NOT PROPERLY NESTED
		{
			p=0;                          // p=0 SHOWS THAT THE DELIMITERS ARE NOT PROPERLY NESTED OR MATCHED
		}
		else
		{
			p=1;                          // p=1 SHOWS THAT THE DELIMITERS ARE PROPERLY MATCHED AND PROPERLY NESTED IN THE FILE
		}
		return p;                         // VALUE OF p IS RETURNED
}
