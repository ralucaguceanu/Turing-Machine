/* GUCEANU Raluca-Zinca-Ioana 312CD */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef char Item;

/* structura pentru un nod al listei */
typedef struct ListNode {
	Item elem;
	struct ListNode *next;
	struct ListNode *prev;
	int pos;
} ListNode;

/* structura pentru lista dubla inlantuita */
typedef struct List {
	ListNode *first;
	ListNode *last;
} List;

/* structura pentru banda magica */
typedef struct Band {
	List *list;
	ListNode *finger;
} Band;

/* structura pentru un nod din coada */
typedef struct QueueNode {
	Item *elem;
	struct QueueNode *next;
} QueueNode;

/* structura pentru coada ce contine instructiunile */
typedef struct Queue {
	QueueNode *front;
	QueueNode *rear;
	long size;
} Queue;

/* structura pentru un nod din stiva */
typedef struct StackNode {
	ListNode *elem;
	struct StackNode *next;
} StackNode;

/* structura pentru stivele de undo si redo */
typedef struct Stack {
	StackNode* head;
} Stack;

List *createList(void);
ListNode *createNode(Item elem);
void insertEnd(Band *band);
List *destroyList(List *list);

Band *initBand(void);

Queue* createQueue(void);
QueueNode *createQNode(Item *instr);
int isQueueEmpty(Queue *q);
void enqueue(Queue *q, Item *instr);
void dequeue(Queue* q);
void destroyQueue(Queue *q);

Stack *createStack(void);
StackNode *createSNode(ListNode *node);
int isStackEmpty(Stack *stack);
void push(Stack *stack, ListNode *node);
void pop(Stack *stack);
void emptyStack(Stack *stack);
void destroyStack(Stack *stack);

int MOVE_LEFT(Band *band);
void MOVE_RIGHT(Band *band);
void MOVE_LEFT_CHAR(Band *band, Item elem, FILE *out);
void MOVE_RIGHT_CHAR(Band *band, Item elem);
void WRITE(Band *band, Item elem);
void INSERT_LEFT(Band *band, Item elem, FILE *out);
void INSERT_RIGHT(Band *band, Item elem);
void SHOW_CURRENT(Band *band, FILE *out);
void SHOW(Band *band, FILE *out);
void UNDO(Band *band, Stack *undo, Stack *redo);
void REDO(Band *band, Stack *redo, Stack *undo);
