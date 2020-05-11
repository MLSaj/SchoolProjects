/*
	CSC D84 - Unit 1 - Search

	This file contains stubs for implementing the different search
	algorithms covered in the course. Please read the assignment
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

	Starter code: F.J.E., Jul. 15
	Updated: F.J.E., Jan. 18
*/

/**********************************************************************
% COMPLETE THIS TEXT BOX:
%
% 1) Student Name: kumar surisetti
% 2) Student Name: Sajeed Bakht
%
% 1) Student number: 1000556490
% 2) Student number:1001527975
% 
% 1) UtorID: surisett
% 2) UtorID: bakhtsye
% 
% We hereby certify that the work contained here is our own
%
% ____________________             _____________________
% (sign with your name)            (sign with your name)
***********************************************************************/

#include "AI_search.h"


struct Pqueue{
	int length;
	int array[10240][3];
};

void printque(struct Pqueue *p){
    for(int i=1; i < p->length + 1;i++){
        printf(" (%d,%d, %d)", p->array[i][0], p->array[i][1], p->array[i][2]);
    }
    printf("\n");
}

void insert(struct Pqueue *p, int x,int y, int priority){
	//printf("We are inserting (%d,%d) \n", x,y);
	//printque(p);
	if(p->length == 0){
        //printf("Trying to insert (%d,%d)\n",x,y);
		p->array[1][0] = x;
		p->array[1][1] = y;
		p->array[1][2] = priority;
        //printf("%d %d %d\n", p->array[1][0], p->array[1][1], p->array[1][2]);
		p->length += 1; 
	}
	else{
        p->length += 1;
        //printf("Came into length not 0\n");
		p->array[p->length][0] = x;
		p->array[p->length][1] = y;
		p->array[p->length][2] = priority;
		int current_position = p->length;
        //printf("current value priority %d \n", p->array[current_position][2]);
        //printf("parent priority %d \n", p->array[current_position/2][2]);
		while(p->array[current_position/2][2] < p->array[current_position][2] && current_position != 1){
            //printf("im in the insert\n");
            //printf("Child needs to switch with parent\n");
            //printf("Current position %d\n", current_position);
			int parentx = p->array[current_position/2][0];
			int parenty = p->array[current_position/2][1];
			int parentpriority = p->array[current_position/2][2];
			p->array[current_position/2][0] = x;
			p->array[current_position/2][1] = y;
			p->array[current_position/2][2] = priority;
			p->array[current_position][0] = parentx;
			p->array[current_position][1] = parenty;
			p->array[current_position][2] = parentpriority;
			current_position = current_position/2;
		}
	}

}

int removeMax(struct Pqueue *p){
	//printque(p);
    //printf("Removing max\n");
	//printf("We are removing max look at the queue with length %d\n",p->length);
	//printf("\n");
	//printque(p);
	if(p->length == 0){
		printf("Length is 0\n");
	}
    if(p->length == 1){
        int returnx = p->array[1][0];
        int returny = p->array[1][1];
        p->array[1][0] = NULL;
        p->array[1][1] = NULL;
		p->length = 0;
        return returnx + (returny*32);
        
    }
	if(p->length == 2){
		int returnx = p->array[1][0];
        int returny = p->array[1][1];
		int secondx = p->array[2][0];
		int secondy = p->array[2][1];
		int second_prior = p->array[2][2];
		p->array[1][0] = secondx;
		p->array[1][1] = secondy;
		p->array[1][2] = second_prior;
		p->array[2][0] = 0;
		p->array[2][1] = 0;
		p->array[2][2] = 0;
		p->length = 1;
		return returnx + (returny*32);
	}
    int leafx = p->array[p->length][0];
    int leafy = p->array[p->length][1];
    int leafpriority = p->array[p->length][2];
    p->array[p->length][0] = 0;
    p->array[p->length][1] = 0;
    p->array[p->length][2] = 0;
    int returnx = p->array[1][0];
    int returny = p->array[1][1];
    int returnIndex = returnx + (returny*32);
    p->array[1][0] = leafx;
    p->array[1][1] = leafy;
    p->array[1][2] = leafpriority;
    int current_position = 1;

	
	if(p->length == 3 && p->array[1][2] < p->array[2][2] ){
		int parent_x = p->array[1][0];
		int parent_y = p->array[1][1];
		int parent_priority = p->array[1][2];

		p->array[1][0] = p->array[2][0];
		p->array[1][1] = p->array[2][1];
		p->array[1][2] = p->array[2][2];
		p->array[2][0] = parent_x;
		p->array[2][1] = parent_y;
		p->array[2][2] = parent_priority;
		p->length -= 1;
		return returnIndex;


	}

    while((p->array[current_position][2] < p->array[current_position*2][2] ||
	 p->array[current_position][2] < p->array[(current_position*2) + 1][2]) && (current_position*2 < (p->length-1))){

        //printf("im in remove max with length %d\n",p->length);
        //printque(p);
        if(p->array[current_position*2][2] >= p->array[(current_position*2)+1][2] && current_position*2 < p->length){
            int left_child_x = p->array[current_position*2][0];
            int left_child_y = p->array[current_position*2][1];
            int left_child_priority = p->array[current_position*2][2];
            //switch child and parent
            p->array[current_position*2][0] = p->array[current_position][0];
            p->array[current_position*2][1] = p->array[current_position][1];
            p->array[current_position*2][2] = p->array[current_position][2];
            p->array[current_position][0] = left_child_x;
            p->array[current_position][1] = left_child_y;
            p->array[current_position][2] = left_child_priority;
            current_position = current_position*2;
            //printf(" BRA1 does this accompany the remove statement\n");
            
        }
        else if(p->array[current_position*2][2] < p->array[(current_position*2)+1][2] && (current_position*2)+1 < p->length){
            int right_child_x = p->array[(current_position*2) + 1][0];
            int right_child_y = p->array[(current_position*2) + 1][1];
            int right_child_priority = p->array[(current_position*2) + 1][2];
            //switch child and parintf("%d\n", b);rent
            p->array[(current_position*2) + 1][0] = p->array[current_position][0];
            p->array[(current_position*2) + 1][1] = p->array[current_position][1];
            p->array[(current_position*2) + 1][2] = p->array[current_position][2];
            p->array[current_position][0] = right_child_x;
            p->array[current_position][1] = right_child_y;
            p->array[current_position][2] = right_child_priority;
            current_position = current_position*2 + 1;
            //printf("BRA2 does this accompany the remove statement\n");
            
        }


    }
	//printque(p);
    p->length -= 1;
    return returnIndex;

}


void search(double gr[graph_size][4], int path[graph_size][2], int visit_order[size_X][size_Y], int cat_loc[10][2], int cats, int cheese_loc[10][2], int cheeses, int mouse_loc[1][2], int mode, int (*heuristic)(int x, int y, int cat_loc[10][2], int cheese_loc[10][2], int mouse_loc[1][2], int cats, int cheeses, double gr[graph_size][4]))
{
 /*
   This function is the interface between your solution for the assignment and the driver code. The driver code
   in AI_search_core_GL will call this function once per frame, and provide the following data
   
   Board and game layout:
	
	The game takes place on a grid of size 32x32, the file board_layout.h specifies the size and defines two
	constants 'size_X' and 'size_Y' for the horizontal and vertical size of the board, respectively. For our
	purposes, the grid of locations is represented by a graph with one node per grid location, so given
	the 32x32 cells, the graph has 1024 nodes. 

	To create a maze, we connect cell locations in the grid in such a way that a) there is a path from any
	grid locax = index % size_X	tion to any other grid location (i.e. there are no disconnected subsets of nodes in the graph),
	and b) there are loops.

	Since each node represents a grid location, each node can be connected to up to 4 neighbours in the
	top, right, bottom, and left directions respectively:

			node at (i,j-1)
				^
				|
	(node at i-1, j) <- node at (i,j) -> node at (i+1, j)
				|
				v
			node at (i,j+1)

	The graph is theredore stored as an adjacency list with size 1024 x 4, with one row per node in the
	graph, and 4 columns corresponding to the weight of an edge linking the node with each of its 4
	possible neighbours in the order towp, right, bottom, left (clockwise from top).

	Since all we care is whether nodes are connected. Weights will be either 0 or 1, if the weight is
	1, then the neighbouring nodes are connected, if the weight is 0, they are not. For example, if

	graph[i][0] = 0 
	graph[i][1] = 1
	graph[i][2] = 0
	graph[i][3] = 1

	then node i is connected to the right and left neighbours, but not to top or bottom.

	The index in the graph for the node corresponding to grid location (x,y) is

	index = x + (y*size_X) 		or in this case		index = x + (y*32)

	Conversely, if you have the index and want to figure out the grid location,

	x = index % size_X		or in this case		x = index % 32
	y = index / size_Y		or in this case		y = index / 32

	(all of the above are *integer* operations!)

	A path is a sequence of (x,y) grid locations. We store it using an array of size	
	1024 x 2 (since there are 1024 locations, this is the maximum length of any
	path that visits locations only once).

	Agent locations are coordinate pairs (x,y)	

   Arguments:
		gr[graph_size][4]   - This is an adjacency list for the maze
		path[graph_size][2] - An initially empty path for your code to fill.
				      In this case, empty means all entries are initially -1
		visit_order[size_X][size_Y]	- An array in which your code will store the
						  *order* in which grid locations were 
						  visited during search. For example, while
						  doing BFS, the initial location is the
						  start location, it's visit order is 1.
						  Then the search would expand the immediate
						  neighbours of the initial node in some order,
						  these would get a visit order of 2, 3, 4, and
						  5 respectively, and so on.
					
						  This array will be used to display the search
						  pattern generated by each search method.

		cat_loc[10][2], cats   - Location of cats and number of cats (we can have at most 10,
					 but there can be fewer). Only valid cat locations are 0 to (cats-1)
		cheese_loc[10][2], cheeses - Location and number of cheese chunks (again at most 10,
					     but possibly fewer). Valid locations are 0 to (cheeses-1)
		mouse_loc[1][2] - Mouse location - there can be only one!
		mode - Search mode selection:
					mode = 0 	- BFS
					mode = 1	- DFS
					mode = 2	- A*

		(*heuristic)(int x, int y, int cat_loc[10][2], int cheese_loc[10][2], int mouse_loc[10][2], int cats, int cheeses)
				- This is a pointer to one of the heuristic functions you will implement, either H_cost()
				  or H_cost_nokitty(). The driver in AI_search_core_GL will pass the appropriate pointer
				  depending on what search the user wants to run.
			
				  If the mode is 0 or 1, this pointer is NULL

				  * How to call the heuristic function from within this function : *
					- Like any other function:
						h = heuristic( x, y, cat_loc, cheese_loc, mouse_loc, cats, cheeses);

   Return values:
		Your search code will directly update data pasnsed-in as arguments:

		- path[graph_size][2]	: Your search code will update this array to contain the path from
					  the mou				return;se to one of the cheese chunks. The order matters, so
					  path[0][:] must be the mouse's current location, path[1][:]
					  is the next move for the mouse. Each successive row will contain
					  the next move toward the cheese, and the path ends at a location
					  whose coordinates correspond to one of the cheese chunks.
					  Any entries beyond that must remain set to -1
		- visit_order[size_X][size_Y] 	:  Your search code will update this array to contain the
						   order in which each location in the grid was expanded
						   during search. This means, when that particular location
						   was checked for being a goal, and if not a goal, had its
						   neighbours added as candidates for future expansion (in
						   whatever order is dictated by the search mode).

						   Note that since there are 1024 locations, the values in 
						   this array must always be in [0, 1023]. The driver code
						   will then display search order as a yellow-colored
						   brightness map where nodes expanded earlier will look
						   brighter.

		* Your code MUST NOT modify the locations or numbers of cats and/or cheeses, the graph,
	     	  or the location of the mouse - if you try, the driver code will know it *
			
		That's that, now, implement your solution!
 */

 /********************************************************************************************************
 * 
 * TO DO:	Implement code to carry out the different types of search depending on the
 *		mode.
 *
 *		You can do this by writing code within this single function (and being clever about it!)
 *		Or, you can use this function as a wrapper that calls a different search function
 *		 (BFS, DFS, A*) depending on the mode. Note that in the latter case, you will have
 *	    	  to inform your A* function somehow of what heuristic it's supposed to use.
 *
 *		Visiting Order: When adding the neighbours of a node to your list of candidates for
 *				expansion, do so in the order top, right, bottom, left.
 *
 *		NOTE: Your search functions should be smart enough to not choose a path that goes
 *		      through a cat! this is easily done without any heuristics.
 * 
 *		How you design your solution is up to you. But:
 *
 *		- Document your implementation by adding concise and clear comments in this file
 *		- Document your design (how you implemented the solution, and why) in the report
 *
 ********************************************************************************************************/

 // Stub so that the code compiles/runs - The code below will be removed and replaced by your code!
 /*path[0][0]=mouse_loc[0][0];
 path[0][1]=mouse_loc[0][1];
 path[1][0]=mouse_loc[0][0];
 path[1][1]=mouse_loc[0][1];*/
	//initialize all the visit_order to 0
	//printf("mouse is at %d %d\n",mouse_loc[0][0],mouse_loc[0][1]);
	//for (int i=0;i<size_X;i++){
	//	for (int j=0;j<size_Y;j++){
	//		visit_order[i][j]=0;
	//		path[i][j]=-1;
	//	}
	//}
	//printf("function start\n");
	int SOURCE_INDEX=mouse_loc[0][0]+(size_X)*mouse_loc[0][1];
	int counter=0;
	int pred[graph_size][2]={0};
	int priority=0;
	//visit_order[mouse_loc[0][0]][mouse_loc[0][1]]=counter+1;
	struct Pqueue p;
	p.length=0;
	//insert(&p,0,0,0);
	insert(&p,mouse_loc[0][0],mouse_loc[0][1],priority);
	//printf("original p length is %d\n",p.length);
	pred[SOURCE_INDEX][0]=0;
	pred[SOURCE_INDEX][1]=1;
	//printf("removing the start %d\n",removeMax(&p));
	while (p.length >= 1){
		//printf("Printing length in while %d\n", p.length);
		int head_index=removeMax(&p);
		int x=head_index%size_X;
		int y=head_index/size_Y;
		//printf("popped %d %d\n",x,y);
		//printf("now length is %d", p.length);
		//printque(&p);
		visit_order[x][y]=counter+1;
		//printf("popped %d %d \n",x,y);
		counter++;
		int neighbours[4][2];
		for (int i=0;i<4;i++){
			neighbours[i][0]=x;
			neighbours[i][1]=y;
		}
		neighbours[0][1]=y-1;
		neighbours[1][0]=x+1;
		neighbours[2][1]=y+1;
		neighbours[3][0]=x-1;


		for (int i=0;i<4;i++){
			if (neighbours[i][0] >= 0 && neighbours[i][0] <= size_X && neighbours[i][1] >= 0 && neighbours[i][1] <= size_Y){
				int flag=1;
				for (int j=0;j<cats;j++){
					if (neighbours[i][0] == cat_loc[j][0] && neighbours[i][0] == cat_loc[j][1]){
						flag=0;
					}
				}
				if (pred[neighbours[i][0]+(size_X)*neighbours[i][1]][1]==0 && gr[x+(size_X)*y][i] == 1){
					pred[neighbours[i][0]+(size_X)*neighbours[i][1]][0]=(x+(size_X)*y);
					pred[neighbours[i][0]+(size_X)*neighbours[i][1]][1]=pred[x+y*(size_X)][1]+1;
					int queue_priority=0;
					if (mode == 0){
						priority--;
						queue_priority=priority;
					}
					else if(mode == 1){
						priority++;
						queue_priority=priority;
					}
					else if(mode == 2){
						//printf("We are in mode 2\n");

						int heus_value= -(pred[neighbours[i][0]+(size_X)*neighbours[i][1]][1] + heuristic(neighbours[i][0],neighbours[i][1],cat_loc,cheese_loc,mouse_loc,cats,cheeses,gr));
						queue_priority=heus_value;
						//printf("priority is %d\n", priority);
						//printf("heus_val %d\n", heus_value);
					}
					//printf("\n queue priority is %d", queue_priority);
					//printf("KUMAR We are inserting (%d,%d)\n", neighbours[i][0], neighbours[i][1]);
					insert(&p,neighbours[i][0],neighbours[i][1],queue_priority);
					//printf("adding the neighbour %d %d with %d\n",neighbours[i][0],neighbours[i][1]); path[graph_size][2]
					
				}
			}
		}
		for (int i=0;i<cheeses;i++){
			if (cheese_loc[i][0] == x && cheese_loc[i][1] == y){
				int path_length=0;
				int cheese_index=x+(size_X)*y;
				int curr_index=cheese_index;

				while (curr_index != SOURCE_INDEX){
					path_length++;
					curr_index=pred[curr_index][0];
				}

				curr_index=cheese_index;
				for (int i=path_length;i!=-1;i--){
					path[i][0]=curr_index%size_X;
					path[i][1]=curr_index/size_Y;
					curr_index=pred[curr_index][0];
					//printf("path %d %d\n",path[i][0],path[i][1]);
				}/*
				printf("visit_order: \n");
				for (i = 0; i < size_X; i++) {
					for (j = 0; j < size_Y; j++) {
					printf("%d, ", visit_order[i][j]);
					}
					printf("\n");
				}
  				getchar();
				*/
				return;
				for (int i=0;i<=graph_size;i++){
					//printf("path at %d is %d %d\n",i,path[i][0],path[i][1]);
				}
			
			}
		}
	}
 return;
}

int H_cost(int x, int y, int cat_loc[10][2], int cheese_loc[10][2], int mouse_loc[1][2], int cats, int cheeses, double gr[graph_size][4])
{
 /*
	This function computes and returns the heuristic cost for location x,y.
	As discussed in lecture, this means estimating the cost of getting from x,y to the goal. 
	The goal is cheese. Which cheese is up to you.
	Whatever you code here, your heuristic must be admissible.

	Input arguments:

		x,y - Location for which this function will compute a heuristic search cost
		cat_loc - Cat locations
		cheese_loc - Cheese locations
		mouse_loc - Mouse location
		cats - # of cats
		cheeses - # of cheeses
		gr - The graph's adjacency list for the maze

		These arguments are as described in the search() function above
 */
	//printf("We are in H_cost\n");
	int start_x = x;
	int start_y = y;
	int closest_cheese = 0;
	//find the closest cheese
	for(int i = 0; i < cheeses;i++){
		//printf("We are in loop\n");
		int distance = (abs(start_x - cheese_loc[i][0]) + abs(start_y - cheese_loc[i][1]));
		if(distance < (abs(start_x - cheese_loc[closest_cheese][0]) + abs(start_y - cheese_loc[closest_cheese][1]))){
			closest_cheese = i;
		}
	}
	//printf("find closest_cheese at %d\n", closest_cheese);
	int final_distance = abs(start_x - cheese_loc[closest_cheese][0]) + abs(start_y - cheese_loc[closest_cheese][1]);
	//printf("find distance %d\n", final_distance);
	return final_distance;

 		// <-- Evidently you will need to update this.
}

int H_cost_nokitty(int x, int y, int cat_loc[10][2], int cheese_loc[10][2], int mouse_loc[1][2], int cats, int cheeses, double gr[graph_size][4])
{
 /*
	This function computes and returns the heuristic cost for location x,y.
	As discussed in lecture, this means estimating the cost of getting from x,y to the goal. 
	The goal is cheese. 

	However - this time you want your heuristic function to help the mouse avoid being eaten.
	Therefore: You have to somehow incorporate knowledge of the cats' locations into your
	heuristic cost estimate. How well you do this will determine how well your mouse behaves
	and how good it is at escaping kitties.

	This heuristic *does not have to* be admissible.

	Input arguments have the same meaning as in the H_cost() function above.
 */
	
	int alpha=1000;
	int beta=1000;

	int start_x = x;
	int start_y = y;
	int closest_cheese = 0;
	//find the closest cheese
	for(int i = 0; i < cheeses;i++){
		//printf("We are in loop\n");
		int distance = (abs(start_x - cheese_loc[i][0]) + abs(start_y - cheese_loc[i][1]));
		if(distance < (abs(start_x - cheese_loc[closest_cheese][0]) + abs(start_y - cheese_loc[closest_cheese][1]))){
			closest_cheese = i;
		}
	}
	//find the closest cat
	int closest_cat = 0;
	int close=0;
	//find the closest cheese
	for(int i = 0; i < cats;i++){
		//printf("We are in loop\n");
		int distance = (abs(start_x - cat_loc[i][0]) + abs(start_y - cat_loc[i][1]));
		if(distance < (abs(start_x - cat_loc[closest_cat][0]) + abs(start_y - cat_loc[closest_cat][1]))){
			closest_cat = i;
		}
		if(distance < 3){
			close=1;
		}
	}

	int euc_cat=sqrt(pow(abs(start_x - cat_loc[closest_cat][0]),2) + pow(abs(start_y - cat_loc[closest_cat][1]),2));
	int euc_cheese=sqrt(pow(abs(start_x - cheese_loc[closest_cheese][0]),2) + pow(abs(start_y - cheese_loc[closest_cheese][1]),2));

	int final_distance = abs(start_x - cheese_loc[closest_cheese][0]) + abs(start_y - cheese_loc[closest_cheese][1]) - 3*euc_cat + 4*close*euc_cheese;

	return final_distance;

}

