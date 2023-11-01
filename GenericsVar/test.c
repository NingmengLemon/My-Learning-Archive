#include "generics.h"
#include <stdio.h>
#include <stdlib.h>

int main(void){
    GenericsType type = INT;
    // Test GenericsType size converter
    printf("%llu\n",_gtype_to_size(type));
    // Test create GenericsVar
    GenericsVar* v = create_gvar(type, &(int){1919810});
    printf("%d\n", extrcGvar(v, int));
    // Test modify GVar
    change_gvar(v, &(int){114514});
    printf("%d\n", extrcGvar(v, int));
    // Test change Gvar type
    type = DOUBLE;
    change_gtype(v, type);
    printf("%lf\n", extrcGvar(v, double));
    change_gvar(v, &(double){114514.1919810});
    printf("%lf\n", extrcGvar(v, double));
    // Destroy Gvar
    destroy_gvar(v);
    return EXIT_SUCCESS;
}