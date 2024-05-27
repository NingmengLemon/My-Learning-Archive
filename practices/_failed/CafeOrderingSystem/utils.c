
#include "utils.h"

/*
读csv文件, 分行存入 vector
嗯其实是按行读取任意文本w
按照原计划应该分行之后再切成一列一列的, 但是找不到合适的容器来装
下面那个写入同理
*/
Vector *read_csv(char *filename) {
    Vector *result = vector_create(sizeof(char) * MAX_CSV_LINE_WIDTH, 10);
    if (!result) {
        return NULL;
    }
    FILE *file = fopen(filename, "r");
    if (!file) {
        vector_free(result);
        return NULL;
    }

    char buffer[MAX_CSV_LINE_WIDTH];
    while (fgets(buffer, sizeof(buffer), file)) {
        size_t len = strlen(buffer);
        if (len > 0 && buffer[len - 1] == '\n') {
            buffer[len - 1] = '\0';
        }
        vector_push_back(result, buffer);
    }

    fclose(file);
    return result;
}

/*
写 csv 文件
*/
void write_csv(Vector *lines, char *filename) {
    FILE *file = fopen(filename, "w+");
    if (file == NULL)
        return;
    for (size_t i = 0; i < lines->size; i++) {
        fprintf(file, "%s\n", (char *)vector_get(lines, i));
    }
}

char generate_random_char() {
    char charset[] =
        "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";
    int max_index = sizeof(charset) - 1;
    return charset[rand() % max_index];
}

void generate_random_string(char *str, int length) {
    if (str == NULL || length <= 0) {
        return;
    }
    for (int i = 0; i < length; i++) {
        str[i] = generate_random_char();
    }
}

void init_random(void) { srand((unsigned int)time(NULL)); }

void clear_buffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
        ;
}

/*
一个简易菜单
第一个参数是问题
第二个参数是选项数量
然后的可变参数是若干个字符串名, 可直接传入字面量, 数量要与选项数量相等
输入 0 表示取消

当输入不合法或取消时返回 0, 其余时候返回选项对应的序号 (从1始计)
*/
int easy_menu(char *question, int option_count, ...) {
    va_list args;
    va_start(args, option_count);

    char *option;
    char input[11];
    int choice;
    printf("%s\n", question);
    // printf("(0) Cancel\n");
    for (int i = 0; i < option_count; i++) {
        option = va_arg(args, char *);
        printf("(%d) %s\n", i + 1, option);
    }
    va_end(args);

    printf("[Input your choice]>");
    // clear_buffer();
    if (scanf("%d", &choice) == EOF) {
        choice = 0;
    }
    clear_buffer();

    // choice = atoi(input);
    if (choice <= 0 || choice > option_count)
        return 0;
    else
        return choice;
}
