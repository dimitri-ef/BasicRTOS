#include "inc/circular_linked_list.h"

node *create_node(void *data)
{
    node *node = malloc(sizeof(node));
    node->data = data;
    node->next = NULL;
    return node;
}

node *create_empty_circular_linked_list(void *data)
{
    return NULL;
}

node *create_circular_linked_list(void *data)
{
    node *circular_linked_list = create_node(data);
    circular_linked_list->next = circular_linked_list;
    return circular_linked_list;
}

node *add_circular_linked_list(node *circular_linked_list, void *data)
{
    // if the circular linked list is empty
    if (!circular_linked_list)
        return create_circular_linked_list(data);

    node *new_node = create_node(data);
    new_node->next = circular_linked_list;

    node* tmp_node = circular_linked_list;

    while (circular_linked_list != tmp_node->next)
        tmp_node = tmp_node->next;

    // tmp node is now the last node of the circular linked list
    tmp_node->next = new_node;

    return circular_linked_list;
}

void destroy_circular_linked_list(node *circular_linked_list, void (*free_data_function)(void*))
{
    if (!circular_linked_list)
        return;

    node* tmp_node = circular_linked_list;
    node* prev_node;

    while (circular_linked_list != tmp_node->next)
    {
        prev_node = tmp_node;
        tmp_node = tmp_node->next;
        if (free_data_function)
            free_data_function(prev_node->data);
        else
            free(prev_node->data);
        free(prev_node);
    }
}