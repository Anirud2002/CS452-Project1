#include <stdlib.h>
#include <stdio.h>
#include "harness/unity.h"
#include "../src/lab.h"

void setUp(void) {
    printf("Setting up tests...\n");
}

void tearDown(void) {
    printf("Tearing down tests...\n");
}

void test_list_create(void) {
    List *list = list_create(LIST_LINKED_SENTINEL);
    TEST_ASSERT_NOT_NULL(list);
    TEST_ASSERT_TRUE(list_is_empty(list));
    TEST_ASSERT_EQUAL(0, list_size(list));
    list_destroy(list, NULL);
}

void test_list_append(void) {
    List *list = list_create(LIST_LINKED_SENTINEL);
    int *nums[3];
    for (int i = 0; i < 3; i++) {
        nums[i] = malloc(sizeof(int));
        *nums[i] = i + 1;
        TEST_ASSERT_TRUE(list_append(list, nums[i]));
    }
    
    TEST_ASSERT_EQUAL(3, list_size(list));
    TEST_ASSERT_EQUAL(1, *(int*)list_get(list, 0));
    TEST_ASSERT_EQUAL(2, *(int*)list_get(list, 1));
    TEST_ASSERT_EQUAL(3, *(int*)list_get(list, 2));
    
    list_destroy(list, free);
}

void test_list_insert(void) {
    List *list = list_create(LIST_LINKED_SENTINEL);
    
    int *num1 = malloc(sizeof(int));
    *num1 = 10;
    int *num2 = malloc(sizeof(int));
    *num2 = 20;
    
    TEST_ASSERT_TRUE(list_insert(list, 0, num1));
    TEST_ASSERT_TRUE(list_insert(list, 1, num2));
    TEST_ASSERT_EQUAL(2, list_size(list));
    TEST_ASSERT_EQUAL(10, *(int*)list_get(list, 0));
    TEST_ASSERT_EQUAL(20, *(int*)list_get(list, 1));
    
    int *num3 = malloc(sizeof(int));
    *num3 = 15;
    TEST_ASSERT_TRUE(list_insert(list, 1, num3));
    TEST_ASSERT_EQUAL(15, *(int*)list_get(list, 1));
    TEST_ASSERT_EQUAL(20, *(int*)list_get(list, 2));
    
    list_destroy(list, free);
}

void test_list_remove(void) {
    List *list = list_create(LIST_LINKED_SENTINEL);
    
    int *nums[3];
    for (int i = 0; i < 3; i++) {
        nums[i] = malloc(sizeof(int));
        *nums[i] = i + 1;
        list_append(list, nums[i]);
    }
    
    void *removed = list_remove(list, 1);
    TEST_ASSERT_NOT_NULL(removed);
    TEST_ASSERT_EQUAL(2, *(int*)removed);
    free(removed);
    
    TEST_ASSERT_EQUAL(2, list_size(list));
    TEST_ASSERT_EQUAL(1, *(int*)list_get(list, 0));
    TEST_ASSERT_EQUAL(3, *(int*)list_get(list, 1));
    
    list_destroy(list, free);
}

void test_list_edge_cases(void) {
    List *list = list_create(LIST_LINKED_SENTINEL);
    
    // Test NULL data
    TEST_ASSERT_TRUE(list_append(list, NULL));
    TEST_ASSERT_NULL(list_get(list, 0));
    
    // Test invalid index
    TEST_ASSERT_NULL(list_get(list, 99));
    TEST_ASSERT_FALSE(list_insert(list, 99, NULL));
    TEST_ASSERT_NULL(list_remove(list, 99));
    
    // Test empty list
    List *empty_list = list_create(LIST_LINKED_SENTINEL);
    TEST_ASSERT_TRUE(list_is_empty(empty_list));
    TEST_ASSERT_NULL(list_get(empty_list, 0));
    TEST_ASSERT_NULL(list_remove(empty_list, 0));
    
    list_destroy(list, NULL);
    list_destroy(empty_list, NULL);
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_list_create);
    RUN_TEST(test_list_append);
    RUN_TEST(test_list_insert);
    RUN_TEST(test_list_remove);
    RUN_TEST(test_list_edge_cases);
    return UNITY_END();
}
