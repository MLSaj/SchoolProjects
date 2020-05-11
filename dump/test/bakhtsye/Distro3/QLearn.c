/*
	CSC D84 - Unit 3 - Reinforcement Learning
	
	This file contains stubs for implementing the Q-Learning method
	for reinforcement learning as discussed in lecture. You have to
	complete two versions of Q-Learning.
	
	* Standard Q-Learning, based on a full-state representation and
	  a large Q-Table
	* Feature based Q-Learning to handle problems too big to allow
	  for a full-state representation
	    
	Read the assignment handout carefully, then implement the
	required functions below. Sections where you have to add code
	are marked

	**************
	*** TO DO:
	**************

	If you add any helper functions, make sure you document them
	properly and indicate in the report.txt file what you added.
	
	Have fun!

	DO NOT FORGET TO 'valgrind' YOUR CODE - We will check for pointer
	management being done properly, and for memory leaks.

	Starter code: F.J.E. Jan. 16
*/

#include "QLearn.h"
#include "time.h"

void QLearn_update(int s, int a, double r, int s_new, double *QTable)
{
 /*
   This function implementes the Q-Learning update as stated in Lecture. It 
   receives as input a <s,a,r,s'> tuple, and updates the Q-table accordingly.
   
   Your work here is to calculate the required update for the Q-table entry
   for state s, and apply it to the Q-table
     
   The update involves two constants, alpha and lambda, which are defined in QLearn.h - you should not 
   have to change their values. Use them as they are.
     
   Details on how states are used for indexing into the QTable are shown
   below, in the comments for QLearn_action. Be sure to read those as well!
 */
 
  /***********************************************************************************************
   * TO DO: Complete this function
   ***********************************************************************************************/

  //*(QTable+(4*state)+a)

  double s_value = *(QTable + (4 * s) + a);
  
  // pick the maximum Q(s',a')
  double max_snew_value = *(QTable + (4 * s_new) + 0);
  for (int i = 1; i < 4; i ++){
    double curr_snew_value = *(QTable + (4 * s_new) + i);
    if (curr_snew_value > max_snew_value){
      max_snew_value = curr_snew_value;
    }
  }
  
  *(QTable + (4 * s) + a) +=
    alpha * (r + (lambda * max_snew_value) - s_value);
}

int QLearn_action(double gr[max_graph_size][4], int mouse_pos[1][2], int cats[5][2], int cheeses[5][2], double pct, double *QTable, int size_X, int graph_size)
{
  /*
     This function decides the action the mouse will take. It receives as inputs
     - The graph - so you can check for walls! The mouse must never move through walls
     - The mouse position
     - The cat position
     - The cheese position
     - A 'pct' value in [0,1] indicating the amount of time the mouse uses the QTable to decide its action,
       for example, if pct=.25, then 25% of the time the mouse uses the QTable to choose its action,
       the remaining 75% of the time it chooses randomly among the available actions.
       
     Remember that the training process involves random exploration initially, but as training
     proceeds we use the QTable more and more, in order to improve our QTable values around promising
     actions.
     
     The value of pct is controlled by QLearn_core_GL, and increases with each round of training.
     
     This function *must return* an action index in [0,3] where
        0 - move up
        1 - move right
        2 - move down
        3 - move left
        
     QLearn_core_GL will print a warning if your action makes the mouse cross a wall, or if it makes
     the mouse leave the map - this should not happen. If you see a warning, fix the code in this
     function!
     
   The Q-table has been pre-allocated and initialized to 0. The Q-table has
   a size of
   
        graph_size^3 x 4
        
   This is because the table requires one entry for each possible state, and
   the state is comprised of the position of the mouse, cat, and cheese. 
   Since each of these agents can be in one of graph_size positions, all
   possible combinations yield graph_size^3 states.
   
   Now, for each state, the mouse has up to 4 possible moves (up, right,
   down, and left). We ignore here the fact that some moves are not possible
   from some states (due to walls) - it is up to the QLearn_action() function
   to make sure the mouse never crosses a wall. 
   
   So all in all, you have a big table.
        
   For example, on an 8x8 maze, the Q-table will have a size of
   
       64^3 x 4  entries
       
       with 
       
       size_X = 8		<--- size of one side of the maze
       graph_size = 64		<--- Total number of nodes in the graph
       
   Indexing within the Q-table works as follows:
   
     say the mouse is at   i,j
         the cat is at     k,l
         the cheese is at  m,n
         
     state = (i+(j*size_X)) + ((k+(l*size_X))*graph_size) + ((m+(n*size_X))*graph_size*graph_size)
     ** Make sure you undestand the state encoding above!
     
     Entries in the Q-table for this state are

     *(QTable+(4*state)+a)      <-- here a is the action in [0,3]
     
     (yes, it's a linear array, no shorcuts with brackets!)
     
     NOTE: There is only one cat and once cheese, so you only need to use cats[0][:] and cheeses[0][:]
   */
  
  /***********************************************************************************************
   * TO DO: Complete this function
   ***********************************************************************************************/
  // set the seed of for the random to the clock?
  //srand(rand());
  // get the shorthand notation for all the agent positions
  int mx = mouse_pos[0][0];
  int my = mouse_pos[0][1];
  int cx = cats[0][0];
  int cy = cats[0][1];
  int chx = cheeses[0][0];
  int chy = cheeses[0][1];
  int start_index = (
		     (mx + (my * size_X)) +
		     ((cx + (cy * size_X)) * graph_size) +
		     ((chx + (chy * size_X)) * graph_size * graph_size));
  //time_t t;
  //srand((unsigned) time(&t));

  // for each of the four actions, choose it only if there is no wall in that direction
  // in addition, keep track of how many possible actions i so picking randomly is easier
  int num_actions = 0;
  int actions [4] = {0};
  for (int i = 0; i < 4; i ++){
    if (gr[mx + (my * size_X)][i] == 1){
      actions[num_actions] = i;
      num_actions ++;
    }
  }
  // figure out using rand() whether I am using a random action using pct
  int rand_flag = 0;
  if (pct > (rand() % 100)){
    rand_flag = 1;
  }
  // if i am choosing randomly, use rand() to choose from the possible actions
  if (rand_flag == 1){
    int action = actions [(rand() % num_actions)]; //(num_actions + 1)) - 1];
    return action;
  }
  // if i am not choosing randomly, choose the actions that has the highest value in the Q-table
  //printf("%d\n", num_actions);
  int best_action = actions[0];
  double best_action_value = *(QTable + (4 * start_index) + (actions [0]));
  //printf("Best action value before %f\n", best_action_value);
  for (int i = 1; i < num_actions; i ++){
    int action = actions [i];
    // get the q value from the q table
    double current_action_value = *(QTable + (4 * start_index) + action);
    if (current_action_value > best_action_value){
      best_action = action;
      best_action_value = current_action_value;
    }
  }
  //printf("Best action value after %f\n", best_action_value);
  //printf("%f with %d\n", best_action_value, best_action);
  //getchar();
  return best_action;  
}

double QLearn_reward(double gr[max_graph_size][4], int mouse_pos[1][2], int cats[5][2], int cheeses[5][2], int size_X, int graph_size)
{
  /*
    This function computes and returns a reward for the state represented by the input mouse, cat, and
    cheese position. 
    
    You can make this function as simple or as complex as you like. But it should return positive values
    for states that are favorable to the mouse, and negative values for states that are bad for the 
    mouse.
    
    I am providing you with the graph, in case you want to do some processing on the maze in order to
    decide the reward. 
        
    This function should return a maximim/minimum reward when the mouse eats/gets eaten respectively.      
   */

   /***********************************************************************************************
   * TO DO: Complete this function
   ***********************************************************************************************/ 
  double reward = 0;
  double mouse_ate = 0;
  double cheese_ate = 0;
  if (mouse_pos[0][0] == cats[0][0] && mouse_pos[0][1] == cats[0][1]){
    return -1;
  }

  if (mouse_pos[0][0] == cheeses[0][0] && mouse_pos[0][1] == cheeses[0][1]){
    return 1;
  }
  return 0;
}

void feat_QLearn_update(double gr[max_graph_size][4],double weights[25], double reward, int mouse_pos[1][2], int cats[5][2], int cheeses[5][2], int size_X, int graph_size)
{
  /*
    This function performs the Q-learning adjustment to all the weights associated with your
    features. Unlike standard Q-learning, you don't receive a <s,a,r,s'> tuple, instead,
    you receive the current state (mouse, cats, and cheese potisions), and the reward 
    associated with this action (this is called immediately after the mouse makes a move,
    so implicit in this is the mouse having selected some action)
    
    Your code must then evaluate the update and apply it to the weights in the weight array.    
   */
  
   /***********************************************************************************************
   * TO DO: Complete this function
   ***********************************************************************************************/
  // use maxQsa to get the maximum qvalue and the corresponding direction
  int maxa = 0;
  double maxq = 0;
  maxQsa(gr, weights, mouse_pos, cats, cheeses, size_X, graph_size, &maxq, &maxa);
  // use evaluateFeatures to get the features for this state
  double features[25] = {0};
  evaluateFeatures(gr, features, mouse_pos, cats, cheeses, size_X, graph_size);
  // use Qsa to get the q value for this state
  double qvalue = Qsa(weights, features);
  // use all this information to update each of the weights
  for (int i = 0; i < numFeatures; i++){
    weights[i] += alpha * (reward + (lambda * maxq) - qvalue) * features[i];
  }
}

int feat_QLearn_action(double gr[max_graph_size][4],double weights[25], int mouse_pos[1][2], int cats[5][2], int cheeses[5][2], double pct, int size_X, int graph_size)
{
  /*
    Similar to its counterpart for standard Q-learning, this function returns the index of the next
    action to be taken by the mouse.
    
    Once more, the 'pct' value controls the percent of time that the function chooses an optimal
    action given the current policy.
    
    E.g. if 'pct' is .15, then 15% of the time the function uses the current weights and chooses
    the optimal action. The remaining 85% of the time, a random action is chosen.
    
    As before, the mouse must never select an action that causes it to walk through walls or leave
    the maze.    
   */

  /***********************************************************************************************
   * TO DO: Complete this function
   ***********************************************************************************************/

  int num_actions = 0;
  int actions [4] = {0};
  for (int i = 0; i < 4; i ++){
    if (gr[mouse_pos[0][0] + (mouse_pos[0][1] * size_X)][i] == 1){
      actions[num_actions] = i;
      num_actions ++;
    }
  }
  // figure out using rand() whether I am using a random action using pct
  int rand_flag = 0;
  if (pct > (rand() % 100)){
    rand_flag = 1;
  }
  // if i am choosing randomly, use rand() to choose from the possible actions
  if (rand_flag == 1){
    int action = actions [(rand() % num_actions)]; //(num_actions + 1)) - 1];
    return action;
  }
  
  // if i am not choosing randomly, use maxQsa to get the best action
  int maxa = 0; // ****
  double maxq = 0;
  maxQsa(gr, weights, mouse_pos, cats, cheeses, size_X, graph_size, &maxq, &maxa);
  //printf("%d\n", maxa);
  return maxa;
}

void evaluateFeatures(double gr[max_graph_size][4],double features[25], int mouse_pos[1][2], int cats[5][2], int cheeses[5][2], int size_X, int graph_size)
{
  /*
   This function evaluates all the features you defined for the game configuration given by the input
   mouse, cats, and cheese positions. You are free to define up to 25 features. This function will
   evaluate each, and return all the feature values in the features[] array.
   
   Take some time to think about what features would be useful to have, the better your features, the
   smarter your mouse!
   
   Note that instead of passing down the number of cats and the number of cheese chunks (too many parms!)
   the arrays themselves will tell you what are valid cat/cheese locations.
   
   You can have up to 5 cats and up to 5 cheese chunks, and array entries for the remaining cats/cheese
   will have a value of -1 - check this when evaluating your features!
  */

   /***********************************************************************************************
   * TO DO: Complete this function
   ***********************************************************************************************/
  //void bfs(double gr[max_graph_size][4],int start[2],int cat_loc[10][2],int cats,int cheese_loc[10][2],int cheeses,int *min_cheese,int *min_cat,int *total_cheese,int *total_cat, int size_X, int size_Y);
  
  // calculate the number of cats and cheeses
  int num_cats = 0;
  int num_cheeses = 0;

  while (cats[num_cats][0] != -1){
    num_cats ++;
  }

  while (cheeses[num_cheeses][0] != -1){
    num_cheeses ++;
  }

  
  
  /* // true distance variables: */
  /* int min_cat = 0; */
  /* int total_cat = 0; */
  /* int min_cheese = 0; */
  /* int total_cheese = 0; */

  /* // calculate the distance to the closest cat, closest cheese, cumulative distance to all the cheeses and cumulative distance to all the cats */
  /* bfs(gr, mouse_pos[0], cats, num_cats, cheeses, num_cheeses, &min_cheese, &min_cat, &total_cheese, &total_cat, size_X, size_X); */

  //int num_around(double gr[max_graph_size][4],int start[2],int cat_loc[5][2],int cheese_loc[5][2],int cats,int depth, int size_X, int size_Y)
  //int shortest_distance(double gr[max_graph_size][4],int start[2],int end[2],int cat_loc[5][2],int cats,int mode, int size_X, int size_Y)
  

  // first feature: euclidean distance to the first cat
  double min_cat = sqrt(pow(abs(mouse_pos[0][0] - cats[0][0]), 2) + pow(abs(mouse_pos[0][1] - cats[0][1]), 2));
  for (int i = 1; i < num_cats; i ++){
    double dist_cat = sqrt(pow(abs(mouse_pos[0][0] - cats[i][0]), 2) + pow(abs(mouse_pos[0][1] - cats[i][1]), 2));
    if (dist_cat < min_cat){
      min_cat = dist_cat;
    }
  }
  double first  =  1.0 / (1 + min_cat);
  features[0] = first;
  
  //second feature: manhattan distance to the first cheese - change it to true distance
  double min_cheese = sqrt(pow(abs(mouse_pos[0][0] - cheeses[0][0]), 2) + pow(abs(mouse_pos[0][1] - cheeses[0][1]), 2));
  double second = 1.0 / (1 + min_cheese);
  features[1] = second;
  
  // third feature: how many walls are there around the mouse - improved the win rate by ~20% - keep it
  double third = 0;
  for (int i = 0; i < 4; i ++){
    third += gr[mouse_pos[0][0] + (mouse_pos[0][1] * size_X)][i];
  }
  features[2] = third / 4;
  
  // fourth feature: euclidean distance from the cheese to the cat - improved the win rate by ~5% - keep it
  double cheese_to_cat = sqrt(pow(abs(cats[0][0] - cheeses[0][0]), 2) + pow(abs(cats[0][1] - cheeses[0][1]), 2));
  double fourth = 1.0 / (1 + cheese_to_cat);
  //double fourth = 1.0 / (1 + shortest_distance(gr, cats[0], cheeses[0], cats, num_cats, 0, size_X, size_X));
  features[3] = fourth;

  //fifth feature: direction of the cat and the cheese? using the cosine law
  int x1 = (mouse_pos[0][0] - cats[0][0]);
  int y1 = (mouse_pos[0][1] - cats[0][1]);
  int x2 = (mouse_pos[0][0] - cheeses[0][0]);
  int y2 = (mouse_pos[0][1] - cheeses[0][1]);

  double dot = (x1 * x2) + (y1 * y2);
  double det = (x1 * y2) - (y1 * x2);
  double fifth = atan2(det, dot) / 3.15;
  features[4] = fifth;
    
  // ideas for features: some fields of specific sizes?(multiple of them around the mouse and the cheese), 
}


double Qsa(double weights[25], double features[25])
{
  /*
    Compute and return the Qsa value given the input features and current weights
   */

  /***********************************************************************************************
  * TO DO: Complete this function
  ***********************************************************************************************/  
  // this gives the q value given the weights and the features for a given state
  
  double qvalue = 0;
  // iterate over all the weights and get the linear combination of the features with these weights
  for (int i = 0; i < numFeatures; i++){
    qvalue += (weights[i] * features[i]);
    //printf("%f\n", qvalue);
  }
  return qvalue;
}

void maxQsa(double gr[max_graph_size][4],double weights[25],int mouse_pos[1][2], int cats[5][2], int cheeses[5][2], int size_X, int graph_size, double *maxU, int *maxA)
{
 /*
   Given the state represented by the input positions for mouse, cats, and cheese, this function evaluates
   the Q-value at all possible neighbour states and returns the max. The maximum value is returned in maxU
   and the index of the action corresponding to this value is returned in maxA.
   
   You should make sure the function does not evaluate moves that would make the mouse walk through a
   wall. 
  */
 
   /***********************************************************************************************
   * TO DO: Complete this function
   ***********************************************************************************************/

  int num_actions = 0;
  int actions [4] = {0};
  for (int i = 0; i < 4; i ++){
    if (gr[mouse_pos[0][0] + (mouse_pos[0][1] * size_X)][i] == 1){
      actions[num_actions] = i;
      num_actions ++;
    }
  }

  int new_mouse[1][2];
  new_mouse[0][0] = mouse_pos[0][0];
  new_mouse[0][1] = mouse_pos[0][1];
  // get the mouse position for that direction
  if (actions[0] == 0){ // up
    new_mouse[0][1] --;
  }
  if (actions[0] == 1){ // right
    new_mouse[0][0] ++;
  }
  if (actions[0] == 2){ // bottom
    new_mouse[0][1] ++;
  }
  if (actions[0] == 3){ // left
    new_mouse[0][0] --;
  }

  // get the features
  double features[25] = {0};
  evaluateFeatures(gr, features, new_mouse, cats, cheeses, size_X, graph_size);
  // get the qvalue
  double qvalue = Qsa(weights, features);

  int maxa = actions[0];
  double maxq = qvalue;

  
  // iterate over all the directions
  for (int j = 1; j < num_actions; j++){
    int i = actions[j];
    int new_mouse[1][2];
    new_mouse[0][0] = mouse_pos[0][0];
    new_mouse[0][1] = mouse_pos[0][1];
    // get the mouse position for that direction
    if (i == 0){ // up
      new_mouse[0][1] --;
    }
    if (i == 1){ // right
      new_mouse[0][0] ++;
    }
    if (i == 2){ // bottom
      new_mouse[0][1] ++;
    }
    if (i == 3){ // left
      new_mouse[0][0] --;
    }

    // get the features
    double features[25] = {0};
    evaluateFeatures(gr, features, new_mouse, cats, cheeses, size_X, graph_size);
    // get the qvalue
    double qvalue = Qsa(weights, features);
    // update the maxq and the maxa
    //printf("%f\n", qvalue);
    if (qvalue > maxq){
      maxq = qvalue;
      maxa = i;
    }
  }
  *maxU = maxq;
  *maxA = maxa;
}

/***************************************************************************************************
 *  Add any functions needed to compute your features below 
 *                 ---->  THIS BOX <-----
 * *************************************************************************************************/
void bfs(double gr[max_graph_size][4],int start[2],int cat_loc[5][2],int cats,int cheese_loc[5][2],int cheeses,int *min_cheese,int *min_cat,int *total_cheese,int *total_cat, int size_X, int size_Y){
  //using this for my queue
  typedef struct node{
    int x;
    int y;
    struct node *next;
  }Node;

  
  //create the head
  Node *head=(Node *)malloc(sizeof(Node));
  head->x=start[0];
  head->y=start[1];
  head->next=NULL;

  //create two arrays for visit marking and predecessor
  int visited[max_graph_size];
  int pred[max_graph_size];

  for (int i=0;i<max_graph_size;i++){
    visited[i]=0;
    pred[i]=0;
  }

  //mark the head visited and set its predecessor as -1
  visited[(head->x)+(head->y)*size_X]=1;
  pred[(head->x)+(head->y)*size_X]=-1;
  
  //start expanding
  while (head!=NULL){
    //printf("the head is %d %d\n",head->x,head->y);
    //initialize the neighbours to the head
    int neighbours[4][2]={0};
    for (int i=0;i<4;i++){
      neighbours[i][0]=head->x;
      neighbours[i][1]=head->y;
    }
    neighbours[0][1]--;
    neighbours[1][0]++;
    neighbours[2][1]++;
    neighbours[3][0]--;

    //check if each neighbour is valid
    for (int i=0;i<4;i++){
      //neighbour is not out of bounds
      if (neighbours[i][0]>=0 && neighbours[i][0]<=size_X
	  && neighbours[i][1]>=0 && neighbours[i][1]<=size_Y){
	//neighbour is reachable i,e., no wall and it is not visited yet
	//printf("adding neighbour %d %d\n",neighbours[i][0],neighbours[i][1]);
	//printf("visited? %d\n",visited[neighbours[i][0]+(neighbours[i][1])*32]);
	//getchar();
	if (gr[(head->x)+(head->y)*size_X][i]==1 && visited[neighbours[i][0]+(neighbours[i][1])*size_X]==0){
	  //mark it visited
	  visited[neighbours[i][0]+neighbours[i][1]*size_X]=1;
	  //add its predecessor
	  pred[neighbours[i][0]+neighbours[i][1]*size_X]=(head->x)+(head->y)*size_X;
	  //create a new node
	  Node *new_node=(Node *)malloc(sizeof(Node));
	  new_node->x=neighbours[i][0];
	  new_node->y=neighbours[i][1];
	  new_node->next=NULL;
	  //add the new node to the queue
	  Node *curr_node=head;
	  while (curr_node->next!=NULL){
	    curr_node=curr_node->next;
	  }
	  curr_node->next=new_node;
	}
      }
    }
    //get the new head
    Node *new_head=head->next;
    free(head);
    head=new_head;
  }

  int min=1000;
  int total=0;
  for (int i=0;i<cats;i++){
    int curr_index=cat_loc[i][0]+size_X*cat_loc[i][1];
    int parent_index=curr_index;
    int path_length = 0;
    //printf("start is %d %d, end is %d %d\n",start[0],start[1],end[0],end[1]);
    //printf("hmm %d\n",i);
    while (pred[curr_index]!=-1){
      //printf("current index is %d %d with %d\n",curr_index%32,curr_index/32,pred[curr_index]);
      //if (pred[curr_index == 0]){
      //      	in_the_way[curr_index] = 0;
      //	break;
      //}
      path_length++;
      curr_index=pred[curr_index];
    }
    if (path_length < min){
      min=path_length;

    }
    total += path_length;
  }
  *min_cat=min;
  *total_cat=total;
  
  min=1000;
  total=0;
  for (int i=0;i<cheeses;i++){
    *min_cheese=min;
    int curr_index=cheese_loc[i][0]+size_X*cheese_loc[i][1];
    int parent_index=curr_index;
    int path_length = 0;
    //printf("start is %d %d, end is %d %d\n",start[0],start[1],end[0],end[1]);
    //printf("hmm %d\n",i);
    while (pred[curr_index]!=-1){
      //printf("current index is %d %d with %d\n",curr_index%32,curr_index/32,pred[curr_index]);
      //if (pred[curr_index == 0]){
      //      	in_the_way[curr_index] = 0;
      //	break;
      //}
      path_length++;
      curr_index=pred[curr_index];
    }
    if (path_length < min){
      min=path_length;
    }
    total += path_length;
  }
  *min_cheese=min;
  *total_cheese=total;
}

int num_around(double gr[max_graph_size][4],int start[2],int cat_loc[5][2],int cheese_loc[5][2],int cats,int depth, int size_X, int size_Y){
  //using this for my queue
  typedef struct node{
    int x;
    int y;
    struct node *next;
  }Node;
  
  //create the head
  Node *head=(Node *)malloc(sizeof(Node));
  head->x=start[0];
  head->y=start[1];
  head->next=NULL;

  //create two arrays for visit marking and predecessor
  int visited[max_graph_size];

  for (int i=0;i<max_graph_size;i++){
    visited[i]=0;
  }

  //mark the head visited and set its predecessor as -1
  visited[(head->x)+(head->y)*size_X]=1;

  //counter for the depth
  int counter = 0;
  //counter for the no of cats seen
  int num = 0;
  
  //start expanding
  while (head!=NULL && counter!=depth){
    //check if the head is a cat
    
    for (int i=0;i<cats;i++){
      if (((head->x)+(head->y)*size_X)==(cat_loc[i][0]+size_X*cat_loc[i][1])){
	num ++;
      }
    }
    //printf("the head is %d %d\n",head->x,head->y);
    //initialize the neighbours to the head
    int neighbours[4][2]={0};
    for (int i=0;i<4;i++){
      neighbours[i][0]=head->x;
      neighbours[i][1]=head->y;
    }
    neighbours[0][1]--;
    neighbours[1][0]++;
    neighbours[2][1]++;
    neighbours[3][0]--;

    //check if each neighbour is valid
    for (int i=0;i<4;i++){
      //neighbour is not out of bounds
      if (neighbours[i][0]>=0 && neighbours[i][0]<=size_X
	  && neighbours[i][1]>=0 && neighbours[i][1]<=size_Y){
	//neighbour is reachable i,e., no wall and it is not visited yet
	//printf("adding neighbour %d %d\n",neighbours[i][0],neighbours[i][1]);
	//printf("visited? %d\n",visited[neighbours[i][0]+(neighbours[i][1])*32]);
	//getchar();
	if (gr[(head->x)+(head->y)*size_X][i]==1 && visited[neighbours[i][0]+(neighbours[i][1])*size_X]==0){
	  //mark it visited
	  visited[neighbours[i][0]+neighbours[i][1]*size_X]=1;
	  //create a new node
	  Node *new_node=(Node *)malloc(sizeof(Node));
	  new_node->x=neighbours[i][0];
	  new_node->y=neighbours[i][1];
	  new_node->next=NULL;
	  //add the new node to the queue
	  Node *curr_node=head;
	  while (curr_node->next!=NULL){
	    curr_node=curr_node->next;
	  }
	  curr_node->next=new_node;
	}
      }
    }
    //get the new head
    Node *new_head=head->next;
    free(head);
    head=new_head;
    counter ++;
  }
  
  return num;
}

int shortest_distance(double gr[max_graph_size][4],int start[2],int end[2],int cat_loc[5][2],int cats,int mode, int size_X, int size_Y){
  //using this for my queue
  typedef struct node{
    int x;
    int y;
    struct node *next;
  }Node;

  //index of the end point
  int end_index=end[0]+end[1]*size_X;
  
  //create the head
  Node *head=(Node *)malloc(sizeof(Node));
  head->x=start[0];
  head->y=start[1];
  head->next=NULL;
    
  //create two arrays for visit marking and predecessor
  int visited[max_graph_size];
  int pred[max_graph_size];

  for (int i=0;i<max_graph_size;i++){
    visited[i]=0;
    pred[i]=0;
  }

  //mark the head visited and set its predecessor as -1
  visited[(head->x)+(head->y)*size_X]=1;
  pred[(head->x)+(head->y)*size_X]=-1;
  
  //start expanding
  while (head!=NULL){
    //check if the head is the end point
    if (((head->x)+(head->y)*size_X)==end_index){
      //if so break
      break;
    }

    //printf("the head is %d %d\n",head->x,head->y);
    //initialize the neighbours to the head
    int neighbours[4][2]={0};
    for (int i=0;i<4;i++){
      neighbours[i][0]=head->x;
      neighbours[i][1]=head->y;
    }
    neighbours[0][1]--;
    neighbours[1][0]++;
    neighbours[2][1]++;
    neighbours[3][0]--;

    //check if each neighbour is valid
    for (int i=0;i<4;i++){
      //neighbour is not out of bounds
      if (neighbours[i][0]>=0 && neighbours[i][0]<=size_X
	  && neighbours[i][1]>=0 && neighbours[i][1]<=size_Y){
	//neighbour is reachable i,e., no wall and it is not visited yet
	//printf("adding neighbour %d %d\n",neighbours[i][0],neighbours[i][1]);
	//printf("visited? %d\n",visited[neighbours[i][0]+(neighbours[i][1])*32]);
	//getchar();
	//check if the neighbour is a cat
	int pass=1;
	if (mode){
	  for (int j=0;j<cats;j++){
	    if (cat_loc[j][0]==neighbours[i][0] && cat_loc[j][1]==neighbours[i][1]){
	      pass=0;
	    }
	  }
	}
	if (gr[(head->x)+(head->y)*size_X][i]==1 && visited[neighbours[i][0]+(neighbours[i][1])*size_X]==0 && pass){
	  //mark it visited
	  visited[neighbours[i][0]+neighbours[i][1]*size_X]=1;
	  //add its predecessor
	  pred[neighbours[i][0]+neighbours[i][1]*size_X]=(head->x)+(head->y)*size_X;
	  //create a new node
	  Node *new_node=(Node *)malloc(sizeof(Node));
	  new_node->x=neighbours[i][0];
	  new_node->y=neighbours[i][1];
	  new_node->next=NULL;
	  //add the new node to the queue
	  Node *curr_node=head;
	  while (curr_node->next!=NULL){
	    curr_node=curr_node->next;
	  }
	  curr_node->next=new_node;
	}
      }
    }
    //get the new head
    Node *new_head=head->next;
    free(head);
    head=new_head;
  }
  //calculate the path length
  int  path_length=0;
  int curr_index=end_index;
  //printf("start is %d %d, end is %d %d\n",start[0],start[1],end[0],end[1]);
  while (pred[curr_index]!=-1){
    //printf("current index is %d %d\n",curr_index%32,curr_index/32);
    if (pred[curr_index]==0){
      return 100;
    }
    path_length++;
    curr_index=pred[curr_index];
  }
  
  //printf("the path length is %d\n",path_length);
  return path_length;
}
