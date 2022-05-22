#ifndef LIST_H_INCLUDED
#define LIST_H_INCLUDED

// Rajmund Kozuszek (121528)

struct sl_node {
    int priority;
    char *name;
    sl_node *next;
};

extern const int default_priority;

// in the following functions we assume that parameter pHead
// points to the first element of the singly linked list

bool is_empty(const sl_node* pHead);
// returns true if list is empty, i.e. contains no elements

int size(const sl_node* pHead);
// returns number of elements in list

sl_node* push_front(sl_node* pHead, const char* name);
// adds element with the new name in the beginning of the list
// returns pointer to the new head of the list

sl_node* pop_front(sl_node* pHead);
// removes the first element of the list
// returns pointer to the new head of the list

sl_node* clear(sl_node* pHead);
// removes all elements from the list
// returns pointer to the new head of the list

sl_node* find(sl_node* pHead, const char* name);
// looks for element with the given name
// returns pointer to the element (sl_node) found
// or nullptr if the element is not found

// you have to implement these two functions

sl_node* insert(sl_node* pHead, const char* name, int priority);
// inserts the new element with the given name and priority
// BEFORE the element of greater than or equal priority
// or at the end of the list if no such element exists
// returns pointer to the new head of the list

sl_node* remove(sl_node* pHead, const char* name);
// removes element with the given name from the list
// returns pointer to the new head of the list

#endif // SLLIST_H_INCLUDED
