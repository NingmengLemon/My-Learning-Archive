#include "backend.h"

int main(void) {
    init_all();
    print_all_items();
    print_all_orders();

    char tmp[PATH_MAX+1];
    GETCWD(tmp, PATH_MAX);
    printf("Current workdir: %s\n", tmp);

    return 0;
}