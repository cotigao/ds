// Given a singly linked list with each node 
// containing an extra pointer called ´arbit´ 
// (apart from the standard next pointer) that 
// could point to any node in the linked list, 
// point to itself or be NULL, We have to 
// copy the entire list!

#include <stdio.h>
#include <stdlib.h>

#define NODES 5

typedef struct Node Node;

// Node in a linked list
struct Node {
    int value; // value (used as a node identifier - index)
    Node* arbit; // can point to itself, any node in the list, or can be NULL
    Node* next; // pointing to the next node in the linked list (i.e standard next pointer in a SLL)
};


/* Creates the original list with ´next´ and 
 * ´arbit´ pointers and with index as ´value´.
 * Note: This is a helper function (for demo purpose). 
 *       The original list could be created
 *       in whichever way (not in the scope), 
 *       as our problem statement is to duplicate 
 *       this original list. 
 */
static void
create_list (Node** head, Node** tail) {
    Node* arr[NODES];

    for (int i = 0; i < NODES; i++) {
        Node* n = (Node*)calloc(1, sizeof(Node));
        n->value = i;

        if (!*head) {
            arr[i] = *head = *tail = n;
        } else {
            arr[i] = (*tail)->next = n; 
            *tail = (*tail)->next;
        }
    }    

    for (int i = 0; i < NODES; i++) {
        int val;
        printf ("\nwhat node Node-%d should point to?\n", i);
        scanf("%d", &val);

        if (val >= 0 && val < NODES) {
            arr[i]->arbit = arr[val];
        } else if (val != -1) {
           i--;
           printf("ERROR: invalid input (range: 0 - %d); enter again\n", NODES - 1); 
        }
    }   
    printf("\n\n");
}


static void 
traverse_list (Node* head) {
    for (Node* cur = head; cur; cur = cur->next) {
        printf ("%p : %d,  %p : %d\n", cur, cur->value, cur->arbit, cur->arbit ? cur->arbit->value : -1); 
    }
    printf("\n\n");
}


static void
duplicate_list(Node* head, Node** dup_head, Node **dup_tail) {
    Node* cur = head;

    //loop through every node in the old list 
    //for every node in the old list, 
    // - create a new one
    // - set the new one's arbit to it's corresponding old node
    // - set the old node's next to the new node
    while (cur) {
        Node* n = (Node*)calloc(1, sizeof(Node));
        Node *tmp;

        n->value = cur->value;
        if (!*dup_head) {
            *dup_head = *dup_tail = n;
        } else {
            (*dup_tail)->next = n; 
            *dup_tail = (*dup_tail)->next;
        }

        tmp = cur->next;
        (*dup_tail)->arbit = cur;
        cur->next = *dup_tail;
        cur = tmp; 
    }

    for (cur = *dup_head; cur; cur = cur->next) {
        cur->arbit = cur->arbit->arbit ? cur->arbit->arbit->next : NULL;
    }
}


int 
main() {
    Node* head = NULL; 
    Node* tail = NULL; 
    
    Node* dup_head = NULL; 
    Node* dup_tail = NULL; 

    //helpers
    create_list(&head, &tail);
    traverse_list(head);

    
    duplicate_list(head, &dup_head, &dup_tail);
    traverse_list(dup_head);
}
