#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void test_read_csv() {
    // Test case 1: Valid file
    Vector *result = read_csv("./cafe_items.csv");
    if (result != NULL) {
        printf("Test case 1 passed: File read successfully.\n");
        // Print the lines read from the file
        for (int i = 0; i < result->size; i++) {
            printf("%s\n", (char *)vector_get(result, i));
        }
        vector_free(result);
    } else {
        printf("Test case 1 failed: File read failed.\n");
    }

    // Test case 2: Invalid file
    result = read_csv("nonexistent.csv");
    if (result == NULL) {
        printf("Test case 2 passed: File read failed (as expected).\n");
    } else {
        printf("Test case 2 failed: File read succeeded (unexpected).\n");
        vector_free(result);
    }
}

void test_generate_random_string() {
    // Test case 1: Generate random string of length 10
    char str[11]; // 10 characters + null terminator
    generate_random_string(str, 10);
    printf("Test case 1: Random string: %s\n", str);

    // Test case 2: Generate random string of length 5
    generate_random_string(str, 5);
    printf("Test case 2: Random string: %s\n", str);
}

void test_menu() {
    printf("Testing easy menu.\n");
    int choice = easy_menu("111真要进去吗", 3, "111", "222", "333");
    if (choice == 1)
        printf("欢迎喵\n");
    else
        printf("虾头楠\n");
}

int main() {
    init_random();
    test_read_csv();
    test_generate_random_string();
    test_menu();
    return 0;
}