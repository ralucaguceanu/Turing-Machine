/* GUCEANU Raluca-Zinca-Ioana 312CD */

#include "tema1.h"
#define max_instruction_length 20


/* alocarea memoriei pentru un nod din lista */
ListNode *createNode(Item elem) {
	ListNode *node = (ListNode *)malloc(sizeof(struct ListNode));
	node->elem = elem;
	node->next = NULL;
	node->prev = NULL;
	node->pos = 1;
	return node;
}

/* alocarea memoriei necesare listei */
List *createList(void) {
	List *list = (List *)malloc(sizeof(struct List));
	ListNode *first_node = createNode('#');
	ListNode *sentinel = createNode('\0');
	sentinel->pos = 0;
	sentinel->next = first_node;
	sentinel->prev = NULL;
	first_node->prev = sentinel;
	list->first = sentinel;
	list->last = first_node;
	return list;
}

/* inserarea caracterului "#" la final si actualizarea pozitiei degetului */
void insertEnd(Band *band) {
	ListNode *new_node = createNode('#');
	while (band->finger->next != NULL) {
		band->finger = band->finger->next;
	}
	new_node->pos = (band->finger->pos) + 1;
	new_node->prev = band->finger;
	band->finger->next = new_node;
	band->finger = new_node;
	band->list->last = new_node;
}

/* eliberarea memoriei alocate pentru lista */
List *destroyList(List *list) {
	if (list == NULL) {
		return NULL;
	}

	ListNode *iter = list->first, *temp = NULL;

	while (iter != NULL) {
		temp = iter;
		iter = iter->next;
		free(temp);
	}

	free(list);
	return NULL;
}

/* alocarea memoriei necesare benzii */
Band *initBand(void) {
	Band *band = (Band *)malloc(sizeof(struct Band));
	band->list = createList();   /* initializarea listei */
	band->finger = band->list->last;
	return band;
}

/* alocarea memoriei pentru coada cu instructiuni */
Queue* createQueue(void) {
	Queue *q = (Queue *)malloc(sizeof(struct Queue));
	q->size = 0;
	q->front = NULL;
	q->rear = NULL;
	return q;
}

/* alocarea memoriei pentru un nod din coada */
QueueNode *createQNode(Item *instr) {
	QueueNode *new_node = (QueueNode *)malloc(sizeof(struct QueueNode));
	new_node->elem = strdup(instr);
	new_node->next = NULL;
	return new_node;
}

/* verificarea in cazul unei cozi vide */
int isQueueEmpty(Queue *q) {
	if (q == NULL || q->front == NULL || q->rear == NULL || q->size == 0) {
		return 1;
	}
	return 0;
}

/* adaugare in coada */
void enqueue(Queue *q, Item *instr) {
	QueueNode *new_node = createQNode(instr);
	q->size++;
	if (isQueueEmpty(q)) {
		q->front = q->rear = new_node;
		return;
	}
	q->rear->next = new_node;
	q->rear = new_node;
}

/* eliminare din coada */
void dequeue(Queue* q) {
	QueueNode *tmp;
	if (!isQueueEmpty(q)) {
		q->size--;
		tmp = q->front;
		q->front = q->front->next;
		free(tmp->elem);
		free(tmp);
		if (q->size == 0) {
			q->front = q->rear = NULL;
			q = NULL;
			free(q);
		}
	}
}

/* eliberarea memoriei alocate pentru coada */
void destroyQueue(Queue *q) {
	while (!isQueueEmpty(q)) {
		dequeue(q);
	}
	free(q);
}

/* alocarea memoriei pentru o stiva */
Stack *createStack(void) {
	Stack *s = (Stack *)malloc(sizeof(struct Stack));
	s->head = NULL;
	return s;
}

/* alocarea memoriei pentru un nod al stivei */
StackNode *createSNode(ListNode *node) {
	StackNode *new_node = (StackNode *)malloc(sizeof(struct StackNode));
	new_node->elem = node;
	new_node->next = NULL;
	return new_node;
}

/* verificare in cazul unei stive vide */
int isStackEmpty(Stack *stack) {
	if (stack == NULL || stack->head == NULL) {
		return 1;
	}
	return 0;
}

/* adaugare in stiva */
void push(Stack *stack, ListNode *node) {
	StackNode *new_node = createSNode(node);
	if (isStackEmpty(stack)) {
		stack->head = new_node;
		return;
	}
	new_node->next = stack->head;
	stack->head = new_node;
}

/* eliminare din stiva */
void pop(Stack *stack) {
	StackNode *tmp;
	if (!isStackEmpty(stack)) {
		tmp = stack->head;
		stack->head = stack->head->next;
		free(tmp);
	}
}

/* golire stiva */
void emptyStack(Stack *stack) {
	while (!isStackEmpty(stack)) {
		pop(stack);
	}
}

/* eliberarea memoriei alocate pentru stiva */
void destroyStack(Stack *stack) {
	emptyStack(stack);
	free(stack);
}

int MOVE_LEFT(Band *band) {
	if (band->finger->pos == 1) {
		return 0;
	}
	band->finger = band->finger->prev;
	return 1;
}

void MOVE_RIGHT(Band *band) {
	if (band->finger->next == NULL) {
		insertEnd(band);
	}
	else {
		band->finger = band->finger->next;
	}
}

void MOVE_LEFT_CHAR(Band *band, Item elem, FILE *out) {
	ListNode *iter = band->finger;

	/* verificare daca elementul se afla deja la pozitia degetului */
	if (band->finger->elem == elem) {
		return;
	}

	/* cautarea elementului */
	while (iter->pos != 1 && iter->elem != elem) {
		iter = iter->prev;
	}

	/* realizarea actualizarii corespunzatoare */
	if (iter->elem == elem) {
		band->finger = iter;
	} else {
		fprintf(out, "ERROR\n");   /* cazul in care nu se gaseste elementul */
	}
}

void MOVE_RIGHT_CHAR(Band *band, Item elem) {
	ListNode *iter = band->finger->next, *copy = band->finger;

	/* verificare daca elementul se afla deja la pozitia degetului */
	if (band->finger->elem == elem) {
		return;
	}

	/* cautarea elementului */
	while (iter != NULL) {
		if (iter->elem == elem) {
			band->finger = iter;
			return;
		}
		iter = iter->next;
	}
	if (band->finger == copy) {   /* cazul in care nu se gaseste elementul */
		insertEnd(band);
	}
}

void WRITE(Band *band, Item elem) {
	band->finger->elem = elem;
}

void INSERT_LEFT(Band *band, Item elem, FILE *out) {

	/* verificare daca inserarea se poate realiza */
	if (band->finger->pos == 1) {
		fprintf(out, "ERROR\n");
		return;
	}
	ListNode *new_node = createNode(elem), *iter = band->finger;

	/* realizarea legaturilor */
	new_node->pos = band->finger->pos;
	new_node->next = band->finger;
	new_node->prev = band->finger->prev;
	band->finger->prev->next = new_node;
	band->finger->prev = new_node;
	band->finger = new_node;

	/* actualizarea pozitiilor dupa inserare */
	while (iter != NULL) {
		iter->pos++;
		iter = iter->next;
	}
}

void INSERT_RIGHT(Band *band, Item elem) {
	ListNode *new_node = createNode(elem);

	/* inserare la final */
	if (band->finger->next == NULL) {
		new_node->pos = (band->finger->pos) + 1;
		new_node->prev = band->finger;
		band->finger->next = new_node;
		band->finger = new_node;
		band->list->last = new_node;
		return;
	}

	/* realizarea legaturilor pentru inserare in interiorul benzii */
	ListNode *iter = band->finger->next;
	new_node->pos = (band->finger->pos) + 1;
	new_node->next = band->finger->next;
	new_node->prev = band->finger;
	band->finger->next->prev = new_node;
	band->finger->next = new_node;
	band->finger = new_node;

	/* actualizarea pozitiilor dupa inserare */
	while (iter != NULL) {
		iter->pos++;
		iter = iter->next;
	}
}

void SHOW_CURRENT(Band *band, FILE *out) {
	fprintf(out, "%c\n", band->finger->elem);
}

void SHOW(Band *band, FILE *out) {
	ListNode *iter = band->list->first->next;
	while (iter != NULL) {
		if (iter->pos == band->finger->pos) {
			fprintf(out, "|%c|", iter->elem);
		} else {
			fprintf(out, "%c", iter->elem);
		}
		iter = iter->next;
	}
	fprintf(out, "\n");
}

void UNDO(Band *band, Stack *undo, Stack *redo) {
	push(redo, band->finger);   /* adaugare in stiva de redo */
	band->finger = undo->head->elem;
	pop(undo);
}

void REDO(Band *band, Stack *redo, Stack *undo) {
	push(undo, band->finger);   /* adaugare in stiva de undo */
	band->finger = redo->head->elem;
	pop(redo);
}

int main() {
	Band *band = initBand();   /* declararea benzii magice */
	Stack *undo = createStack();   /* declararea stivei pentru undo */
	Stack *redo = createStack();   /* declararea stivei pentru undo */
	Queue *q = createQueue();   /* declararea cozii cu instructiuni */

	int nr_instr = 0;   /* numarul de instructiuni citite */

	/* declararea unui caracter ajutator pentru trecerea la o noua linie */
	char white_space = '\0';

	/* declararea unui sir de caractere pentru memorarea cate unei operatii */
	char instr[max_instruction_length] = "\0";

	FILE *in = fopen("tema1.in", "rt");
	FILE *out = fopen("tema1.out", "wt");

	fscanf(in, "%d", &nr_instr);
	fscanf(in, "%c", &white_space);

	/* cititrea instructiunilor si construirea cozii,
	respectiv realizarea operatiilor corespunzatoare
	*/
	while (fgets(instr, max_instruction_length, in) && nr_instr > 0) {

		if (strcmp("SHOW_CURRENT\n", instr) == 0) {
			SHOW_CURRENT(band, out);
		}
		if (strcmp(instr, "SHOW\n") == 0) {
			SHOW(band, out);
		}

		/* adaugarea operatiilor de tip UPDATE in coada de instructiuni */
		if (strstr(instr, "MOVE")) {
			enqueue(q, instr);
		}

		if (strstr(instr, "WRITE")) {
			enqueue(q, instr);
		}

		if (strstr(instr, "INSERT")) {
			enqueue(q, instr);
		}

		/* efectuare UNDO/REDO */
		if (strcmp(instr, "UNDO\n") == 0) {
			UNDO(band, undo, redo);
		}

		if (strcmp(instr, "REDO\n") == 0) {
			REDO(band, redo, undo);
		}

		/* efectuarea operatiilor la intalnirea instructiunii "EXECUTE" */
		if (strcmp(instr, "EXECUTE\n") == 0) {
			if (q->front != NULL && strstr(q->front->elem, "MOVE_LEFT_")) {
				MOVE_LEFT_CHAR(band, q->front->elem[15], out);
			} else if (q->front != NULL
					&& strstr(q->front->elem, "MOVE_RIGHT_")) {
				MOVE_RIGHT_CHAR(band, q->front->elem[16]);
			} else if (q->front != NULL
					&& strstr(q->front->elem, "WRITE")) {
				WRITE(band, q->front->elem[6]);
				emptyStack(undo);
				emptyStack(redo);
			} else if (q->front != NULL
					&& strstr(q->front->elem, "INSERT_LEFT")) {
				INSERT_LEFT(band, q->front->elem[12], out);
			} else if (q->front != NULL
					&& strstr(q->front->elem, "INSERT_RIGHT")) {
				INSERT_RIGHT(band, q->front->elem[13]);
			} else if (q->front != NULL 
					&& strcmp(q->front->elem, "MOVE_LEFT\n") == 0) {
				ListNode *tmp = band->finger;
				if (MOVE_LEFT(band)) {
					push(undo, tmp);
				}
			} else if (q->front != NULL
					&& strcmp(q->front->elem, "MOVE_RIGHT\n") == 0) {
				push(undo, band->finger);
				MOVE_RIGHT(band);
			}

			dequeue(q);
		}
		
		nr_instr--;
	}

	fclose(in);
	fclose(out);

	/* eliberarea memoriei alocate */

	if (undo != NULL) {
		destroyStack(undo);
	}

	if (redo != NULL) {
		destroyStack(redo);
	}

	if (q != NULL) {
		destroyQueue(q);
	}	

	destroyList(band->list);

	free(band);

    return 0;
}
