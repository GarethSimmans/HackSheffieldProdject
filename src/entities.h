#include <stdio.h>
#include <stdlib.h>

typedef enum {
	red,
	blue,
} Colour;

typedef struct {
	int x;
	int y;
	Colour colour;
} Location;

typedef struct LinkedList{
	Location data;
	struct LinkedList *next;
} node;

node * createNode(void){
	node *temp = malloc(sizeof(struct LinkedList));
	temp->next = NULL;
	return temp;
}

void addNode(node head, Location value){
	node *temp,*p;
	temp = createNode();
	temp->data = value;
	p = &head;
	while(p->next != NULL){
		p = p->next;
	}
	p->next = temp;
}

void finalNode(node head){
	node * p;
	p = &head;
	while(p->next != NULL){
		p= p->next;
	}
	p->next = &head;
}
