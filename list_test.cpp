#include "sllist.h"
#include <cstring>
#include <iostream>

void check_empty_list(const sl_node* pHead)
{
    if (pHead != nullptr)
        std::cerr << "Error in head pointer - it should be nullptr.\n";

    if (is_empty(pHead) != true)
        std::cerr << "Error in empty() for empty list.\n";

    if (size(pHead) != 0)
        std::cerr << "Error in size() for empty list.\n";
}

int main()
{
    sl_node *list_head = nullptr;

    // tests on empty list
    check_empty_list(list_head);

    // tests on one-element list
    list_head = push_front(list_head, "the first client");

    if (size(list_head) != 1)
        std::cerr << "Error in size() for one-element list.\n";

    if (list_head == nullptr)
        std::cerr << "Error in header pointer for one-element list.\n";
    else
    {
        if (list_head->priority != default_priority) // default priority
            std::cerr << "Error in val member in one-element list.\n";
        if (list_head->next != nullptr)
            std::cerr << "Error in next member in one-element list.\n";
    }

    // pop the only client
    list_head = pop_front(list_head);
    // the list should be empty
    check_empty_list(list_head);

    // let's try to pop from empty list - should do no harm
    pop_front(list_head);
    check_empty_list(list_head);

    // try inserting element at the front
    list_head = insert(list_head, "the first", 55);

    if (size(list_head) != 1)
        std::cerr << "Error in size() after the first insert.\n";

    if (list_head == nullptr)
        std::cerr << "Error in header pointer after the first insert.\n";
    else
    {
        if (list_head->priority != 55)
            std::cerr << "Error in priority member after the first insert.\n";
        if (strcmp(list_head->name, "the first") != 0)
            std::cerr << "Error in the name after the first insert.\n";
        if (list_head->next != nullptr)
            std::cerr << "Error in next member after the first insert.\n";
    }


    // add the second element again at the front
    sl_node* the_last = list_head;

    list_head = insert(list_head, "the second", 33);

    if (size(list_head) != 2)
        std::cerr << "Error in size() after the second insert.\n";

    if (list_head == nullptr)
        std::cerr << "nullptr header pointer after the second insert.\n";
    else
    {
        if (list_head->priority != 33)
            std::cerr << "Error in priority member after the second insert.\n";
        if (strcmp(list_head->name, "the second") != 0)
            std::cerr << "Error in the name after the second insert.\n";
        if (list_head->next != the_last)
            std::cerr << "Error in next member after the second insert.\n";
    }

    // now the third element in the middle
    sl_node* the_first = list_head;

    list_head = insert(list_head, "the third", 44);

    if (size(list_head) != 3)
        std::cerr << "Error in size() after the third insert.\n";

    if (list_head == nullptr)
        std::cerr << "nullptr header pointer after the third insert.\n";
    else
    {
        // head of the list should not change
        if (list_head != the_first)
            std::cerr << "header pointer changed after the third insert.\n";
        sl_node* inserted = list_head->next;
        if (inserted != nullptr)
        {
            if (inserted->priority != 44)
                std::cerr << "Error in priority member after the third insert.\n";
            if (strcmp(inserted->name, "the third") != 0)
                std::cerr << "Error in the name after the third insert.\n";
            if (inserted->next != the_last)
                std::cerr << "Error in next member after the third insert.\n";
        }
    }

    // now the fourth element at the end
    list_head = insert(list_head, "the fourth", 66);

    if (size(list_head) != 4)
        std::cerr << "Error in size() after the fourth insert.\n";

    if (list_head == nullptr)
        std::cerr << "nullptr header pointer after the fourth insert.\n";
    else
    {
        // head of the list should not change
        if (list_head != the_first)
            std::cerr << "header pointer changed after the fourth insert.\n";
        sl_node* inserted = the_last->next;
        if (inserted != nullptr)
        {
            if (inserted->priority != 66)
                std::cerr << "Error in priority member after the fourth insert.\n";
            if (strcmp(inserted->name, "the fourth") != 0)
                std::cerr << "Error in the name after the fourth insert.\n";
            if (inserted->next != nullptr)
                std::cerr << "Error in next member after the fourth insert.\n";
        }
    }

    if (list_head == nullptr || the_last == nullptr || the_first == nullptr)
    {
        std::cerr << "\nThe list is broken - skipping remove tests.\n";
        return 1;
    }

    // now let's test remove
    list_head = remove(list_head, "non-removing");
    if (size(list_head) != 4)
        std::cerr << "Error in size() after non-removing remove.\n";

    // remove the last element
    list_head = remove(list_head, "the fourth");
    if (size(list_head) != 3)
        std::cerr << "Error in size() after removing the last element.\n";
    if (the_last->next != nullptr)
        std::cerr << "Invalid next pointer after removing the last element.\n";

    // remove the middle element
    list_head = remove(list_head, "the third");
    if (size(list_head) != 2)
        std::cerr << "Error in size() after removing the middle element.\n";
    if (the_first->next != the_last)
        std::cerr << "Invalid next pointer after removing the middle element.\n";

    // remove the first element
    list_head = remove(list_head, "the second");
    if (size(list_head) != 1)
        std::cerr << "Error in size() after removing the first element.\n";
    if (list_head->next != nullptr)
        std::cerr << "Invalid next pointer after removing the first element.\n";

    // remove the first (and only) element
    list_head = remove(list_head, "the first");
    check_empty_list(list_head);

    std::cerr << "End of tests.\n";
    return 0;
}

