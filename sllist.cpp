#include "sllist.h"
#include <cstring>

const int default_priority = 1000;

// returns true if list is empty, i.e. contains no elements
bool is_empty(const sl_node* pHead)
{
    return pHead == nullptr;
}

// returns number of elements in list
int size(const sl_node* pHead)
{
    int node_count = 0;
    for ( ; pHead != nullptr; pHead = pHead->next)
        ++node_count;
    return node_count;
}

// adds element with the new name in the beginning of the list
// returns pointer to the new head of the list
sl_node* push_front(sl_node* pHead, const char* name)
{
    // priority of the first element has to be lower or the same
    // as in the next element in the list
    // default_priority is assumed if the list is empty
    int front_priority = default_priority;
    if (pHead != nullptr)
        front_priority = pHead->priority - 1;

    // create and link the new element
    sl_node* new_front = new sl_node;
    new_front->priority = front_priority;
    new_front->next = pHead;

    // copy the name
    int name_length = strlen(name);
    new_front->name = new char[name_length + 1]; // + 1 for '\0'
    strcpy(new_front->name, name);

    return new_front;
}

// removes the first element of the list
// returns pointer to the new head of the list
sl_node* pop_front(sl_node* pHead)
{
    // list can be empty - can't pop
    if (pHead == nullptr)
        return nullptr;

    sl_node* new_head = pHead->next;

    // free the name and node memory
    delete [] pHead->name;
    delete pHead;

    return new_head;
}

// removes all elements from the list
// returns pointer to the new head of the list
sl_node* clear(sl_node* pHead)
{
    while (pHead != nullptr)
        pHead = pop_front(pHead);
    return pHead;
}

// looks for element with the given name
// returns pointer to the element (sl_node) found
// or nullptr if the element is not found
sl_node* find(sl_node* pHead, const char* name)
{
    for ( ; pHead != nullptr; pHead = pHead->next)
    {
        if (strcmp(name, pHead->name) == 0)
            return pHead;
    }
    // name not found
    return nullptr;
}

// you have to implement these two functions

// inserts the new element with the given name and priority
// BEFORE the element of greater than or equal priority
// or at the end of the list if no such element exists
// returns pointer to the new head of the list
sl_node* insert(sl_node* pHead, const char* name, int priority)
{
    sl_node* new_node = new sl_node;
    new_node->priority = priority;

    int name_length = strlen(name);
    new_node->name = new char[name_length + 1]; // + 1 for '\0'
    strcpy(new_node->name, name);

    if(pHead == nullptr){
        new_node->next = nullptr;
        pHead = new_node;
    }else if(priority <= pHead->priority) {
        new_node->next = pHead;
        pHead = new_node;

    }else {
        sl_node* temp = pHead->next;
        sl_node* prev = pHead;

        while (temp != nullptr) {
            if (priority <= temp->priority) {
                prev->next = new_node;
                new_node->next = temp;
                break;
            }
            if(temp->next == nullptr){
                temp->next = new_node;
                new_node->next = nullptr;

                break;
            }
            prev = temp;
            temp = temp->next;
        }
    }
    return pHead;
}

// removes element with the given name from the list
// returns pointer to the new head of the list
sl_node* remove(sl_node* pHead, const char* name)
{
    if(strcmp(name, pHead->name) == 0) {
        sl_node* new_head = pHead->next;
        delete [] pHead->name;
        delete pHead;
        pHead = new_head;

    }else {
        sl_node* temp = pHead->next;
        sl_node* prev = pHead;

        while (temp != nullptr) {
            if (strcmp(name, temp->name) == 0) {
                prev->next = temp->next;
                delete [] temp->name;
                delete temp;
                break;
            }
            prev = temp;
            temp = temp->next;
        }
    }

    return pHead;
}

