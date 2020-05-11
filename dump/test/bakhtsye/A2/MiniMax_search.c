/*
	CSC D84 - Unit 2 - MiniMax search and adversarial games

	This file contains stubs for implementing a MiniMax search
        procedure with alpha-beta pruning. Please read the assignment
	handout carefully - it describes the game, the data you will
	have to handle, and the search functions you must provide.

	Once you have read the handout carefully, implement your search
	code in the sections below marked with

	**************
	*** TO DO:
	**************

	Make sure to add it to your report.txt file - it will be marked!

	Have fun!

	DO NOT FORGET TO 'valgrind' YOUR CODE - We will check for pointer
	management being done properly, and for memory leaks.

	Starter code: F.J.E. Sep. 15
*/

#include "MiniMax_search.h"

int direction[4][2] = {
		{0, -1},
		{1, 0},
		{0, 1},
		{-1, 0}};
int min_or_max(double,double,double,double,int);

double MiniMax(double gr[graph_size][4], int path[1][2], double minmax_cost[size_X][size_Y], int cat_loc[10][2], int cats, int cheese_loc[10][2], int cheeses, int mouse_loc[1][2], int mode, double (*utility)(int cat_loc[10][2], int cheese_loc[10][2], int mouse_loc[1][2], int cats, int cheeses, int depth, double gr[graph_size][4]), int agentId, int depth, int maxDepth, double alpha, double beta)
{
 /*
   This function is the interface between your solution for the assignment and the driver code. The driver code
   in MiniMax_search_core_GL will call this function once per frame, and provide the following data
   
   Board and game layout:

	Exactly the same as for Assignment 1 - have a look at your code if you need a reminder of how the adjacency
	list and agent positions are stored.	

	Note that in this case, the path will contain a single move - at the top level, this function will provide
	an agent with the 'optimal' mini-max move given the game state.


   IMPORTANT NOTE: Mini-max is a recursive procedure. This function will need to fill-in the mini-max values for 
	 	   all game states down to the maximum search depth specified by the user. In order to do that,
		   the function needs to be called with the correct state at each specific node in the mini-max
		   search tree.

		   The game state is composed of:

			* Mouse, cat, and cheese positions (and number of cats and cheeses)
			
		   At the top level (when this function is called by the mini-max driver code), the game state
		   correspond to the current situation of the game. But once you start recursively calling
		   this function for lower levels of the search tree the positions of agents will have changed.
		   
		   Therefore, you will need to define local variables to keep the game state at each node of the
		   mini-max search tree, and you will need to update this state when calling recursively so that
		   the search does the right thing.

		   This function *must check* whether:
			* A candidate move results in a terminal configuration (cat eats mouse, mouse eats cheese)
			  at which point it calls the utility function to get a value
	 		* Maximum search depth has been reached (depth==maxDepth), at which point it will also call
			  the utility function to get a value
			* Otherwise, call recursively using the candidate configuration to find out what happens
			  deeper into the mini-max tree.

   Arguments:
		gr[graph_size][4]   		- This is an adjacency list for the maze
		path[1][2] 			- Your function will return the optimal mini-max move in this array.
		minmax_cost[size_X][size_Y]	- An array in which your code will store the
						  minimax value for maze locations expanded by
						  the search *when called for the mouse, not
						  for the cats!*

						  This array will be used to provide a visual 
						  display of minimax values during the game.

		cat_loc[10][2], cats   - Location of cats and number of cats (we can have at most 10,
					 but there can be fewer). Only valid cat locations are 0 to (cats-1)
		cheese_loc[10][2], cheeses - Location and number of cheese chunks (again at most 10,
					     but possibly fewer). Valid locations are 0 to (cheeses-1)
		mouse_loc[1][2] - Mouse location - there can be only one!
		mode - Search mode selection:
					mode = 0 	- No alpha-beta pruning
					mode = 1	- Alpha-beta pruning

		(*utility)(int cat_loc[10][2], int cheese_loc[10][2], int mouse_loc[1][2], int cats, int cheeses, int depth, double gr[graph_size][4]);
				- This is a pointer to the utility function which returns a value for a specific game configuration

				   NOTE: Unlike the search assignment, this utility function also gets access to the graph so you can do any processing 					 that requires knowledge of the maze for computing the utility values.

				  * How to call the utility function from within this function : *
					- Like any other function:
						u = utility(cat_loc, cheese_loc, mouse_loc, cats, cheeses, depth, gr);
						
		agentId: Identifies which agent we are doing MiniMax for. agentId=0 for the mouse, agentId in [1, cats] for cats. Notice that recursive calls
                         to this function should increase the agentId to reflect the fact that the next level down corresponds to the next agent! For a game
                         with two cats and a mouse, the agentIds for the recursion should look like 0, 1, 2, 0, 1, 2, ...
	
		depth: Current search depth - whether this is a MIN or a MAX node depends both on depth and agentId.
		
		maxDepth: maximum desired search depth - once reached, your code should somehow return
			  a minimax utility value for this location.
ouble alpha = -10000000000;
	double
		alpha. beta: alpha and beta values passed from the parent node to constrain search at this
			     level.

   Return values:
		Your search code will directly update data passed-in as arguments:
		
		- Mini-Max value	: Notice this function returns a double precision number. This is
					  the minimax value at this level of the tree. It will be used 
					  as the recursion backtracks filling-in the mini-max values back
					  from the leaves to the root of the search tree. 

		- path[1][2]		: Your MiniMax function will return the location for the agent's 
					  next location (i.e. the optimal move for the agent). 
		- minmax_cost[size_X][size_Y] 	:  Your search code will update this array to contain the
						   minimax value for locations that were expanded during
						   the search. This must be done *only* for the mouse.

						   Values in this array will be in the range returned by
						   your utility function.

		* Your code MUST NOT modify the locations or numbers of cats and/or cheeses, the graph,
	     	  or the location of the mouse - if you try, the driver code 
		bottomll know it *
			
		That's that, now, implement your solution!
 */

 /********************************************************************************************************
 * 
 * TO DO:	Implement code to perform a MiniMax search. This will involve a limited-depth BFS-like
 *              expansion. Once nodes below return values, your function will propagate minimax utilities
 *		as per the minimax algorithm.
 *	
 *		Note that if alpha-beta pruning is specified, you must keep track of alphas and betas
 *		along the path.
 *
 *		You can use helper functions if it seems reasonable. Add them to the MiniMax_search.h
 *		file and explain in your code why they are needed and how they are used.
 *
 *		Recursion should appear somewhere.
 *
 *		MiniMax cost: If the agentId=0 (Mouse), then once you have a MiniMax value for a location
 *		in the maze, you must update minmax_cost[][] for that location.
 *
 *		How you design your solution is up to you. But:
 *
 *		- Document your implementation by adding concise and clear comments in this file
 *		- Document your design (how you implemented the solution, and why) in the report
 *
 ********************************************************************************************************/

 // Stub so that the code compiles/runs - This will be removed and replaced by your code!

 	int current_loc[2];
	int neighbour_loc[1][2];
	int new_cat_loc[10][2];

	//printf("agent: %d, depth: %d, \n", agentId, depth);
	//printf("Mouses location is %d %d\n", mouse_loc[0][0],mouse_loc[0][1]);
	//for(int i = 0; i < cats; i++){
	//	printf("Cat %d locaton is %d %d \n", i, cat_loc[i][0],cat_loc[i][1]);
	//}
	//printf("Mouse_location is %d %d\n",mouse_loc[0][0], mouse_loc[0][1]);
	
	//index = x + (y*size_X) 		or in this case		index = x + (y*32)
	double top_utility,right_utility,bottom_utility,left_utility;
	double utility_val = 0.0;
	//alpha and beta when starting out.
	if(mode == 1){
		alpha = -10000000.00
		beta = 100000000.00
	}
	if (agentId == 0) {
		current_loc[0] = mouse_loc[0][0]; 
		current_loc[1] = mouse_loc[0][1];
	} else {
		current_loc[0] = cat_loc[agentId-1][0]; 
		current_loc[1] = cat_loc[agentId-1][1];
		for (int i = 0; i < cats; i++) {
			new_cat_loc[i][0] = cat_loc[i][0];
			new_cat_loc[i][1] = cat_loc[i][1];
		}
	}
	// base case for terminal nodes
	if (checkForTerminal(mouse_loc,cat_loc, cheese_loc,cats, cheeses) || maxDepth == depth) {	
		utility_val = utility(cat_loc, cheese_loc, mouse_loc, cats, cheeses, depth, gr);
		return utility_val;
	}
	else{
	int index = (current_loc[1] * size_X) + current_loc[0];
	int nextAgentId = (agentId + 1) % (cats + 1);
	double utility_val;
	double top_utility,right_utility,bottom_utility,left_utility;
	if(agentId == 0){
		//Mouse where we try to maximize
		//we recurse through the top right bottom and left locations looking for the direction with highest utility.
		int top_mouse_loc[1][2];
		top_mouse_loc[0][0] = current_loc[0] + direction[0][0];
		top_mouse_loc[0][1] = current_loc[1] + direction[0][1];
		//if its not a wall
		double zero = 0;
		int check = int(gr[index][0]);
		//To ensure we are not checking a wall
		if(check != 0){
			top_utility = MiniMax(gr,path,minmax_cost,cat_loc,cats,cheese_loc,cheeses,top_mouse_loc,mode,utility,nextAgentId,depth+1,maxDepth,alpha,beta);
			minmax_cost[top_mouse_loc[0][0]][top_mouse_loc[0][1]] = top_utility;
		}
		else{
			//if its a wall we pass on a fake value for it (used in our min max)
			top_utility = 10000000000.00;
		}

		int right_mouse_loc[1][2];
		right_mouse_loc[0][0] = current_loc[0] + direction[1][0];
		right_mouse_loc[0][1] = current_loc[1] + direction[1][1];
		check = int(gr[index][1]);
		if(check != 0){
			right_utility = MiniMax(gr,path,minmax_cost,cat_loc,cats,cheese_loc,cheeses,right_mouse_loc,mode,utility,nextAgentId,depth+1,maxDepth,alpha,beta);
			minmax_cost[right_mouse_loc[0][0]][right_mouse_loc[0][1]] = right_utility;
		}
		else{
			right_utility = 100000000.00;
		}


		int bottom_mouse_loc[1][2];
		bottom_mouse_loc[0][0] = current_loc[0] + direction[2][0];
		bottom_mouse_loc[0][1] = current_loc[1] + direction[2][1];
		int bottom_index = bottom_mouse_loc[0][0] + (bottom_mouse_loc[0][1] * 32);
		check = int(gr[index][2]);
		if(check != 0){
			bottom_utility = MiniMax(gr,path,minmax_cost,cat_loc,cats,cheese_loc,cheeses,bottom_mouse_loc,mode,utility,nextAgentId,depth+1,maxDepth,alpha,beta);
			minmax_cost[bottom_mouse_loc[0][0]][right_mouse_loc[0][1]] = bottom_utility;
		}
		else{
			bottom_utility = 100000000.00;
		}

		int left_mouse_loc[1][2];
		left_mouse_loc[0][0] = current_loc[0] + direction[3][0];
		left_mouse_loc[0][1] = current_loc[1] + direction[3][1];
		int left_index = left_mouse_loc[0][0] + (left_mouse_loc[0][1] * 32);
		check = int(gr[index][3]);
		if(check != 0){
			left_utility = MiniMax(gr,path,minmax_cost,cat_loc,cats,cheese_loc,cheeses,left_mouse_loc,mode,utility,nextAgentId,depth+1,maxDepth,alpha,beta);
			minmax_cost[left_mouse_loc[0][0]][left_mouse_loc[0][1]] = left_utility;
		}
		else{
			 left_utility = 100000000.00;
		}
		//After we get all utilities we pass them into min_or_max, where it returns a value signalling which is most optimal value
		int decision = min_or_max(top_utility, right_utility, bottom_utility, left_utility,agentId);
		if(decision == 0){
			//If decision is 0, the top position is one with highest utility(in the case of the mouse we are trying to minimize)
			path[0][0] = top_mouse_loc[0][0];
			path[0][1] = top_mouse_loc[0][1];
			utility_val = top_utility;
			return utility_val;
		}

		if(decision == 1){
			//if decision is 1 then right position is one with highest utility
			path[0][0] = right_mouse_loc[0][0];
			path[0][1] = right_mouse_loc[0][1];
			utility_val = right_utility;
			return utility_val;
		}

		if(decision == 2){
			path[0][0] = bottom_mouse_loc[0][0];
			path[0][1] = bottom_mouse_loc[0][1];			
			utility_val = bottom_utility;
			return utility_val;
		}
		
		if(decision == 3){
			path[0][0] = left_mouse_loc[0][0];
			path[0][1] = left_mouse_loc[0][1];
			utility_val = left_utility;
			return utility_val;
		}
		





		}
	else{
		//Cat position, very similar to mouse but we maximize instead of minimize;
		int top_cat_loc[cats][2];
		for (int i = 0; i < cats; i++) {
		top_cat_loc[i][0] = cat_loc[i][0];
			top_cat_loc[i][1] = cat_loc[i][1];
			}
		top_cat_loc[agentId-1][0] = cat_loc[agentId-1][0] + direction[0][0];
		top_cat_loc[agentId-1][1] + cat_loc[agentId-1][1] + direction[0][1];
		int top_cat_index = top_cat_loc[agentId-1][0] + (top_cat_loc[agentId-1][1] * 32);
		int check = int(gr[index][0]);
		if(check != 0){
			//printf("Cat at depth %d went top\n", depth);
			top_utility = MiniMax(gr,path,minmax_cost,top_cat_loc,cats,cheese_loc,cheeses,mouse_loc,mode,utility,nextAgentId,depth+1,maxDepth,alpha,beta);
		}
		else{
			//printf("Cat at depth %d didn't go top\n", depth);
			top_utility = -10000000.00;
		}

		int right_cat_loc[cats][2];
		for (int i = 0; i < cats; i++) {
			right_cat_loc[i][0] = cat_loc[i][0];
			right_cat_loc[i][1] = cat_loc[i][1];
			}
		right_cat_loc[agentId-1][0] = cat_loc[agentId-1][0] + direction[1][0];
		right_cat_loc[agentId-1][1] + cat_loc[agentId-1][1] + direction[1][1];
		int right_cat_index = right_cat_loc[agentId-1][0] + (right_cat_loc[agentId-1][1] * 32);
		check = int(gr[index][1]);
		if(check != 0){
			//printf("Cat at depth %d went right\n", depth);
			right_utility = MiniMax(gr,path,minmax_cost,right_cat_loc,cats,cheese_loc,cheeses,mouse_loc,mode,utility,nextAgentId,depth+1,maxDepth,alpha,beta);
		}
		else{
			//printf("Cat at depth %d didn't go right\n", depth);
			right_utility = -1000000.00;
		}

	int bottom_cat_loc[cats][2];
		for (int i = 0; i < cats; i++) {
			bottom_cat_loc[i][0] = cat_loc[i][0];
			bottom_cat_loc[i][1] = cat_loc[i][1];
			}
		bottom_cat_loc[agentId-1][0] = cat_loc[agentId-1][0] + direction[2][0];
		bottom_cat_loc[agentId-1][1] + cat_loc[agentId-1][1] + direction[2][1];
		int bottom_cat_index = bottom_cat_loc[agentId-1][0] + (bottom_cat_loc[agentId-1][1] * 32);
		check = int(gr[index][2]);
		if(check != 0){
			//printf("Cat at depth %d went bottom\n", depth);
			bottom_utility = MiniMax(gr,path,minmax_cost,bottom_cat_loc,cats,cheese_loc,cheeses,mouse_loc,mode,utility,nextAgentId,depth+1,maxDepth,alpha,beta);
		}
		else{
			//printf("Cat didn't go bottom\n");
			bottom_utility = -10000000.00;
		}

		int left_cat_loc[cats][2];
		for (int i = 0; i < cats; i++) {
			left_cat_loc[i][0] = cat_loc[i][0];
			left_cat_loc[i][1] = cat_loc[i][1];
			}
		left_cat_loc[agentId-1][0] = cat_loc[agentId-1][0] + direction[3][0];
		left_cat_loc[agentId-1][1] + cat_loc[agentId-1][1] + direction[3][1];
		int left_cat_index = left_cat_loc[agentId-1][0] + (left_cat_loc[agentId-1][1] * 32);
		check = gr[index][3];
		if(check != 0){
			//printf("Cat at depth %d went bottom\n", depth);
			left_utility = MiniMax(gr,path,minmax_cost,left_cat_loc,cats,cheese_loc,cheeses,mouse_loc,mode,utility,nextAgentId,depth+1,maxDepth,alpha,beta);
		}
		else{
			//printf("Cat at depth %d didn't go bottom\n",depth);
			left_utility = -10000000.00;
		}
		int decision = min_or_max(top_utility, right_utility, bottom_utility, left_utility,agentId);

		if(decision == 0){
			path[0][0] = top_cat_loc[agentId-1][0];
			path[0][1] = top_cat_loc[agentId-1][1];
			utility_val = top_utility;
			return utility_val;
		}

		if(decision == 1){
			path[0][0] = right_cat_loc[agentId-1][0];
			path[0][1] = right_cat_loc[agentId-1][1];
			utility_val = right_utility;
			return utility_val;
		}

		if(decision == 2){
			path[0][0] = bottom_cat_loc[agentId-1][0];
			path[0][1] = bottom_cat_loc[agentId-1][1];
			utility_val = bottom_utility;
			return utility_val;
		}
		
		if(decision == 3){
			path[0][0] = left_cat_loc[agentId-1][0];
			path[0][1] = left_cat_loc[agentId-1][1];
			utility_val = left_utility;
			return utility_val;
		}
		

		
	}
		
	}	
}

int min_or_max(double top, double right, double bottom, double left, int agentId) {
	//returns number indicating which direction is of highest or lowest utility
	//mouse tries to minimize
	//cat tries to maximize
	int returnval;
	if (agentId == 0) {
		double min = top;
		returnval = 0;
		if (min > right){
			min = right;
			returnval = 1;
		} 
		if (min > bottom){
			min = bottom;
			returnval = 2;
		} 
		if (min > left){
			min = left;
			returnval = 3;
		}
		return returnval;
	} else {
		double max = top;
		returnval = 0;
		if (max < right){
			max = right;
			returnval = 1;
		}
		if (max < bottom){
			max = bottom;
			returnval = 2;
		}
		if (max < left){
			max = left;
			returnval = 3;
		} 
		return returnval;
	}
} 
	
	

double utility(int cat_loc[10][2], int cheese_loc[10][2], int mouse_loc[1][2], int cats, int cheeses, int depth, double gr[graph_size][4])
{
 /*
	This function computes and returns the utility value for a given game configuration.
	As discussed in lecture, this should return a positive value for configurations that are 'good'
	for the mouse, and a negative value for locations that are 'bad' for the mouse.

	How to define 'good' and 'bad' is up to you. Note that you can write a utility function
	that favours your mouse or favours the cats, but that would be a bad idea... (why?)

	Input arguments:

		cat_loc - Cat locations
		cheese_loc - Cheese locations
		mouse_loc - Mouse location
		cats - # of cats
		cheeses - # of cheeses
		depth - current search depth
		gr - The graph's adjacency list for the maze

		These arguments are as described in A1. Do have a look at your solution!
 */

	//this utility function attempts to do tradeoff between cheese distance and cat to mouse distance.
	//mouses try to maximize distance from cat while trying to minimize distance from cheese.
	//we also add boosts whether cheese is found or cat eats mouse
 	double average_cat;
	int average_cheese;
	double final_dist;
	int start_x = mouse_loc[0][0];
	int start_y = mouse_loc[0][1];
	int closest_cheese = 0;
	double alpha = 2.0;
	double beta = 2.0;
	double cheese_found = 0.0;
	double mouse_ate = 0.0;

	//implement dead ends
	
	double cheese_double = double(cheeses);
	 for (int i=0; i<cheeses; i++){
  		if (mouse_loc[0][0]==cheese_loc[i][0]&&mouse_loc[0][1]==cheese_loc[i][1]){
			  cheese_found = -28000.00/cheeses;
		  }
	 
	 }

	  for (int i=0; i<cheeses; i++){
	  	if (mouse_loc[0][0]==cheese_loc[i][0]&&mouse_loc[0][1]==cheese_loc[i][1]){
			  mouse_ate = 4000.00;
		  }
	  }



	for(int i = 0; i < cheeses;i++){
		//printf("We are in loop\n");
		int distance = (abs(start_x - cheese_loc[i][0]) + abs(start_y - cheese_loc[i][1]));
		if(distance < (abs(start_x - cheese_loc[closest_cheese][0]) + abs(start_y - cheese_loc[closest_cheese][1]))){
			closest_cheese = i;
			}
	}
	int dist_from_cheese = (abs(start_x - cheese_loc[closest_cheese][0]) + abs(start_y - cheese_loc[closest_cheese][1]));
	double dist_cheese = double(dist_from_cheese);

	if(cats == 1){
		int cat_distance = (abs(start_x - cat_loc[0][0]) + abs(start_y - cat_loc[0][1]));
		double cat_double_distance = double(cat_distance);
		if(cat_double_distance < 7){
			cat_double_distance = cat_double_distance*1.5;
		}

		if(cat_double_distance < 6){
			cat_double_distance = cat_double_distance*1.5;
		}
		if(cat_double_distance < 4){
			cat_double_distance = cat_double_distance * 1.5;
		}
		if(cat_double_distance < 3){
			cat_double_distance = cat_double_distance * 1.5;
		}
		if(cat_double_distance < 2){
			cat_double_distance = cat_double_distance * 2.0;
		}

		final_dist = -6.0*alpha*(cat_double_distance) + (10.0*dist_cheese) + cheese_found + mouse_ate;
		return final_dist;
	}
	else{
	for(int i = 0; i < cats;i++){
		//printf("We are in loop\n");
		int distance = (abs(start_x - cat_loc[i][0]) + abs(start_y - cat_loc[i][1]));
		//printf("print cat is away from mouse by %d\n", distance);
		double dist_double = double(distance);
		//weights for cats that are closing in on cat
		if(dist_double < 10.0){
			dist_double = dist_double*1.5;
		}
		if(dist_double < 7.0)
		{
			dist_double = dist_double*1.5;
		}
		if(dist_double < 6.0){
			dist_double = dist_double*1.5;
		}
		if(dist_double < 4.0){
			dist_double = dist_double*2.0;
		}
		if(dist_double < 3.0){
			dist_double = dist_double*3.5;
		}
		if(dist_double < 2.0){
			dist_double = dist_double*4.0;
		}
		average_cat += dist_double;
		}
		double cat_double = double(cats);
		//printf("Double cats are %f\n", cat_double);
		average_cat = average_cat/cat_double;
		//printf("cats are %d\n", cats);
		//printf("Average cat dist away %f\n",average_cat);
		final_dist = -alpha*(average_cat) + (beta*dist_cheese) + cheese_found + mouse_ate;
		//printf("Computed final distance of %f\n", final_dist);
		return final_dist;

	}
		
}

int checkForTerminal(int mouse_loc[1][2],int cat_loc[10][2],int cheese_loc[10][2],int cats,int cheeses)
{
 /* 
   This function determines whether a given configuration constitutes a terminal node.
   Terminal nodes are those for which:
     - A cat eats the mouse
     or
     - The mouse eats a cheese
   
   If the node is a terminal, the function returns 1, else it returns 0
 */

 // Check for cats having lunch
 for (int i=0; i<cats; i++)
  if (mouse_loc[0][0]==cat_loc[i][0]&&mouse_loc[0][1]==cat_loc[i][1]) return(1);

 // Check for mouse having lunch
 for (int i=0; i<cheeses; i++)
  if (mouse_loc[0][0]==cheese_loc[i][0]&&mouse_loc[0][1]==cheese_loc[i][1]) return(1);

 return(0);

}