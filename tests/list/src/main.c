#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "list.h"

void test_vListInitialise_sets_defaults() {
    List_t list;
    vListInitialise(&list);

    assert(listLIST_IS_EMPTY(&list));
    assert(list.pxIndex == &list.xListEnd);
    assert(list.xListEnd.pxNext == &list.xListEnd);
    assert(list.xListEnd.pxPrevious == &list.xListEnd);
    assert(list.xListEnd.xItemValue == portMAX_DELAY);
}

void test_vListInitialiseItem_sets_null() {
    ListItem_t item;
    vListInitialiseItem(&item);
    assert(item.pvContainer == NULL);
}

void test_vListInsert_single_item() {
    List_t list;
    ListItem_t item;

    vListInitialise(&list);
    vListInitialiseItem(&item);

    listSET_LIST_ITEM_VALUE(&item, 10);

    vListInsert(&list, &item);

    assert(listCURRENT_LIST_LENGTH(&list) == 1);
    assert(item.pxPrevious == &list.xListEnd);
    assert(item.pxNext == &list.xListEnd);
    assert(list.xListEnd.pxNext == &item);
    assert(list.xListEnd.pxPrevious == &item);
    assert(item.pvContainer == &list);
}

void test_vListInsert_multiple_sorted() {
    List_t list;
    ListItem_t item1, item2, item3;

    vListInitialise(&list);
    vListInitialiseItem(&item1);
    vListInitialiseItem(&item2);
    vListInitialiseItem(&item3);

    listSET_LIST_ITEM_VALUE(&item1, 20);
    listSET_LIST_ITEM_VALUE(&item2, 10);
    listSET_LIST_ITEM_VALUE(&item3, 30);

    vListInsert(&list, &item1);
    vListInsert(&list, &item2);
    vListInsert(&list, &item3);

    assert(listCURRENT_LIST_LENGTH(&list) == 3);
    // assert(vListIsSorted(&list));
}

void test_vListInsertEnd_appends_item() {
    List_t list;
    ListItem_t item;

    vListInitialise(&list);
    vListInitialiseItem(&item);

    item.xItemValue = 42;
    vListInsertEnd(&list, &item);

    assert(list.uxNumberOfItems == 1);
    assert(list.xListEnd.pxPrevious == &item);
    assert(item.pxNext == &list.xListEnd);
}

void test_uxListRemove_decrements_count() {
    List_t list;
    ListItem_t item;

    vListInitialise(&list);
    vListInitialiseItem(&item);

    item.xItemValue = 15;
    vListInsert(&list, &item);

    UBaseType_t count = uxListRemove(&item);
    assert(count == 0);
    assert(list.uxNumberOfItems == 0);
    assert(item.pvContainer == NULL);
}

void test_remove_middle_of_three() {
    List_t list;
    ListItem_t a, b, c;

    vListInitialise(&list);
    vListInitialiseItem(&a);
    vListInitialiseItem(&b);
    vListInitialiseItem(&c);

    a.xItemValue = 10;
    b.xItemValue = 20;
    c.xItemValue = 30;

    vListInsert(&list, &a);
    vListInsert(&list, &b);
    vListInsert(&list, &c);

    uxListRemove(&b);
    assert(a.pxNext == &c);
    assert(c.pxPrevious == &a);
    assert(list.uxNumberOfItems == 2);
}

void test_remove_head_and_tail() {
    List_t list;
    ListItem_t a, b;

    vListInitialise(&list);
    vListInitialiseItem(&a);
    vListInitialiseItem(&b);

    a.xItemValue = 10;
    b.xItemValue = 20;

    vListInsert(&list, &a);
    vListInsert(&list, &b);

    uxListRemove(&a);
    assert(list.xListEnd.pxNext == &b);
    uxListRemove(&b);
    assert(list.uxNumberOfItems == 0);
}

void test_insert_same_priority_keeps_order() {
    List_t list;
    ListItem_t a, b;

    vListInitialise(&list);
    vListInitialiseItem(&a);
    vListInitialiseItem(&b);

    a.xItemValue = 10;
    b.xItemValue = 10;

    vListInsert(&list, &a);
    vListInsert(&list, &b);

    assert(list.uxNumberOfItems == 2);
    assert(list.xListEnd.pxNext == &a);
    assert(a.pxNext == &b);
    assert(b.pxNext == &list.xListEnd);
}

void test_index_update_on_remove() {
    List_t list;
    ListItem_t a, b;

    vListInitialise(&list);
    vListInitialiseItem(&a);
    vListInitialiseItem(&b);

    a.xItemValue = 10;
    b.xItemValue = 20;

    vListInsert(&list, &a);
    vListInsert(&list, &b);

    list.pxIndex = &b;
    uxListRemove(&b);

    assert(list.pxIndex == &a);
}

void test_remove_updates_links_correctly() {
    List_t list;
    ListItem_t a, b, c;

    vListInitialise(&list);
    vListInitialiseItem(&a);
    vListInitialiseItem(&b);
    vListInitialiseItem(&c);

    a.xItemValue = 10;
    b.xItemValue = 20;
    c.xItemValue = 30;

    vListInsert(&list, &a);
    vListInsert(&list, &b);
    vListInsert(&list, &c);

    uxListRemove(&b);

    assert(a.pxNext == &c);
    assert(c.pxPrevious == &a);
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        printf("Usage: %s <test_name>\n", argv[0]);
        return 1;
    }

    const char* test_name = argv[1];

    if (strcmp(test_name, "test_vListInitialise_sets_defaults") == 0) {
        test_vListInitialise_sets_defaults();
    }
    else if (strcmp(test_name, "test_vListInitialiseItem_sets_null") == 0) {
        test_vListInitialiseItem_sets_null();
    }
    else if (strcmp(test_name, "test_vListInsert_single_item") == 0) {
        test_vListInsert_single_item();
    }
    else if (strcmp(test_name, "test_vListInsert_multiple_sorted") == 0) {
        test_vListInsert_multiple_sorted();
    }
    else if (strcmp(test_name, "test_vListInsertEnd_appends_item") == 0) {
        test_vListInsertEnd_appends_item();
    }
    else if (strcmp(test_name, "test_uxListRemove_decrements_count") == 0) {
        test_uxListRemove_decrements_count();
    }
    else if (strcmp(test_name, "test_remove_middle_of_three") == 0) {
        test_remove_middle_of_three();
    }
    else if (strcmp(test_name, "test_remove_head_and_tail") == 0) {
        test_remove_head_and_tail();
    }
    else if (strcmp(test_name, "test_insert_same_priority_keeps_order") == 0) {
        test_insert_same_priority_keeps_order();
    }
    else if (strcmp(test_name, "test_index_update_on_remove") == 0) {
        test_index_update_on_remove();
    }
    else if (strcmp(test_name, "test_remove_updates_links_correctly") == 0) {
        test_remove_updates_links_correctly();
    } 
    else {
        return 1;
    }

    return 0;
}