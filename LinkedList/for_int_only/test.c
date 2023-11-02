#include "linkedlist.h"

void test(void){
    Link* new_linklist = create(11, true);
    int var=0;
    printf("");
    pop_item(new_linklist, 3, NULL);
    printf("");
    insert_item(new_linklist, 5, 114514);
    printf("");
    get_item(new_linklist, 5, &var);
    printf("%d",var);
    destroy_linklist(new_linklist);
    printf("");
}

bool solve_problem(int N, int M, int Z){
    Link* students = create(N, true);
    Link last = *students;
    Link current = (*students)->next;
    int index = 0;
    int count = 0;
    int tmp = 0;
    while((*students)->value >= M){
        while(current!=(*students)){
            last = current;
            current = current->next;
            index ++;
            count ++;
            if(count==M){
                count = 1;
                pop_item(students, index, &tmp);
                if(tmp==Z){
                    destroy_linklist(students);
                    return true;
                }
                index --;
                count --;
            }
        }
        last = current;
        current = current->next;
        index = 0;
    }
    destroy_linklist(students);
    return false;
}

int main(void){
    // test();
    // return EXIT_SUCCESS;

    int N,M,Z;
    bool res;
    scanf("%d %d %d",&N,&M,&Z);
    res = solve_problem(N,M,Z);
    if(res){
        printf("YES");
    }
    else{
        printf("NO");
    }

    return EXIT_SUCCESS;
}