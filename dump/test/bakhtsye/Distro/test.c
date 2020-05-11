

#include <stdio.h>

#include <stdlib.h>

 

struct Pqueue{
	int length;
	int array[10240][3];
};

void printque(struct Pqueue *p){
    for(int i=1; i < p->length + 1;i++){
        printf(" (%d,%d)", p->array[i][0], p->array[i][1]);
    }
    printf("\n");
}

void insert(struct Pqueue *p, int x,int y, int priority){ 
	if(p->length == 0){
        //printf("Came into length 0\n");
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
    //printf("Removing max\n");
    if(p->length == 1){
        p->length -= 1;
        int returnx = p->array[1][0];
        int returny = p->array[1][1];
        p->array[1][0] = NULL;
        p->array[1][1] = NULL;
        return returnx + (returny*32);
        
    }
    int leafx = p->array[p->length][0];
    int leafy = p->array[p->length][1];
    int leafpriority = p->array[p->length][2];
    p->array[p->length][0] = (int)NULL;
    p->array[p->length][1] = (int)NULL;
    p->array[p->length][2] = (int)NULL;
    int returnx = p->array[1][0];
    int returny = p->array[1][1];
    int returnIndex = returnx + (returny*32);
    p->array[1][0] = leafx;
    p->array[1][1] = leafy;
    p->array[1][2] = leafpriority;
    int current_position = 1;
    while(p->array[current_position][2] < p->array[current_position*2][2] || p->array[current_position][2] < p->array[(current_position*2) + 1][2]){
        //printf("im in remove max\n");
        //printque(p);
        if(p->array[current_position*2][2] > p->array[(current_position*2)+1][2]){
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
        }
        if(p->array[current_position*2][2] < p->array[(current_position*2)+1][2]){
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
        }
    }
    p->length -= 1;
    return returnIndex;

}


void main(){
    printf("At least im here\n");
    
    struct Pqueue p;
    p.length = 0;
    insert(&p,14,26,35);
    insert(&p,13,11,-35);
    insert(&p,2,2,1);
    insert(&p,1,1,40);
    insert(&p,8,8,28);
    insert(&p,15,5,21);
    insert(&p,14,26,35);
    insert(&p,9,8,15);
    insert(&p,1,3,26);
    insert(&p,2,3,24);
    insert(&p,4,5,33);
    insert(&p,6,10,34);
    insert(&p,12,10,23);
    insert(&p,7,7,5);
    insert(&p,3,6,4);
    insert(&p,9,9,6);
    insert(&p,17,7,12);
    removeMax(&p);
    removeMax(&p);
    removeMax(&p);
    removeMax(&p);
    removeMax(&p);
    removeMax(&p);
    printf("Printing final queue\n");
    printque(&p);



}

 

