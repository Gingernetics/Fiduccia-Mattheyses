#include <stdlib.h>
#include <stdio.h>
#include "basic_objects.h"
#include "dll_structure.h"

//This is a collection of objects that can be stored in the doubly-linked list

//############################################################



//Integer_data is mostly a test data object for debugging
void initialize_integer(struct integer* new_integer, int data){
	new_integer->data = data;
}

void print_integer(struct integer* object){
	printf("%d ", object->data);
}


//############################################################



//The most fundamental aspect of FM is the movement of cells to the correct partition
void initialize_cell(struct cell* new_cell, int identifier, int area){
	new_cell->identifier = identifier;
	new_cell->area = area;

	struct dll* nets = malloc(sizeof(nets));
	initialize_dll(nets);
	new_cell->nets = nets;

	new_cell->partition = 0;
	new_cell->gain = 0;
	new_cell->free_cell = 1;
}

//To find number of pins, call size_dll(cell->nets)
int cell_pinsize(struct cell* cell){
	//Should be an O(1) call
	dll_size(cell->nets);
}

//Adds a net to the the beginning of the cell's netlist
void add_net_to_cell(struct cell* cell, struct net* net){
	insert_node(cell->nets, 0, net);
}


//Consider deleting
void print_cell_area(struct cell* object){
	printf("%d ", object->area);
}



//Garbage collection for cells!
//Need to demalloc nets dll, then cell struct


//This might cause issues, if you deallocate all the nets in this cell, and then another cell tries to access that deallocated net.
//This is a many-to-many
void garbage_collection_cell(struct cell* cell){
	garbage_collection_dll(cell->nets);
	free(cell);
}



//############################################################



void initialize_net(struct net* net, int identifier){
	net->identifier = identifier;

	struct dll* free_cells = malloc(sizeof(free_cells));
	initialize_dll(free_cells);
	net->free_cells = free_cells;

	struct dll* locked_cells = malloc(sizeof(locked_cells));
	initialize_dll(locked_cells);
	net->locked_cells = locked_cells;

	net->num_cells_in_partition_A = 0;
	net->num_cells_in_partition_B = 0;

	net->number_of_cells=0;
}

void print_net(struct net* net){
	struct dll* cells = net->free_cells;
	printf("Net %d has %d cell[s]\n", net->identifier, cells->size);
	print_dll(cells, CELL);
}


//Some kind of garbage collection for nets
