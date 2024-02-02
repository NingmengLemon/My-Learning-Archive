#include "generics.h"

char GenericsType_specifiers[][5] = {
    "%c", "%hd", "%d", "%ld", "%lld",
    "%f", "%lf", "%Lf", 
    "%d",
    "%hhu", "%hu", "%u", "%lu", "%llu"
};

size_t _gtype_to_size(GenericsType type){
    switch (type) {
        case CHAR:
            return sizeof(char);
        case SHORT:
            return sizeof(short);
        case INT:
            return sizeof(int);
        case LONG:
            return sizeof(long);
        case LONG_LONG:
            return sizeof(long long);

        case FLOAT:
            return sizeof(float);
        case DOUBLE:
            return sizeof(double);
        case LONG_DOUBLE:
            return sizeof(long double);

        case BOOL:
            return sizeof(bool);

        case UNSIGNED_CHAR:
            return sizeof(unsigned char);
        case UNSIGNED_SHORT:
            return sizeof(unsigned short);
        case UNSIGNED_INT:
            return sizeof(unsigned int);
        case UNSIGNED_LONG:
            return sizeof(unsigned long);
        case UNSIGNED_LONG_LONG:
            return sizeof(unsigned long long);
            
        default:
            return UNDEFINED_GTYPE_SIZE;
    }
}

GenericsVar* create_gvar(GenericsType type, void* data){
    size_t size = _gtype_to_size(type);
    GenericsVar* var = (GenericsVar*)malloc(sizeof(GenericsVar));
    if(var==NULL) return NULL;

    var->type = type;
    var->data = (void*)malloc(size);
    if(var->data==NULL){
        free(var);
        return NULL;
    }
    if(data!=NULL){
        memcpy(var->data, data, size);
    }
    return var;
}

void destroy_gvar(GenericsVar* var){
    if(var==NULL) return;
    free(var->data);
    free(var);
}

bool change_gtype(GenericsVar* var, GenericsType new_type){
    GenericsType orig_type = var->type;
    void* new_data = (void*)malloc(_gtype_to_size(new_type));
    if(new_data==NULL){
        return false;
    }
    free(var->data);
    var->data = new_data;
    var->type = new_type;
    return true;
}

void change_gvar(GenericsVar* var, void* new_data){
    if(new_data!=NULL){
        memcpy(var->data, new_data, _gtype_to_size(var->type));
    }
}

GenericsVar* copy_gvar(const GenericsVar* var){
    size_t size = _gtype_to_size(var->type);
    GenericsVar* copied = (GenericsVar*)malloc(sizeof(GenericsVar));
    if(copied==NULL) return NULL;

    copied->data = (void*)malloc(size);
    if(copied->data==NULL){
        free(copied);
        return NULL;
    }
    memcpy(copied->data, var->data, size);
    copied->type = var->type;
    return copied;
}

void print_gvar(const GenericsVar* var){
    switch (var->type) {
        case CHAR:
            printf(GenericsType_specifiers[CHAR], extrcGvar(var, char));
            return;
        case SHORT:
            printf(GenericsType_specifiers[SHORT], extrcGvar(var, short));
            return;
        case INT:
            printf(GenericsType_specifiers[INT], extrcGvar(var, int));
            return;
        case LONG:
            printf(GenericsType_specifiers[LONG], extrcGvar(var, long));
            return;
        case LONG_LONG:
            printf(GenericsType_specifiers[LONG_LONG], extrcGvar(var, long long));
            return;

        case FLOAT:
            printf(GenericsType_specifiers[FLOAT], extrcGvar(var, float));
            return;
        case DOUBLE:
            printf(GenericsType_specifiers[DOUBLE], extrcGvar(var, double));
            return;
        case LONG_DOUBLE:
            printf(GenericsType_specifiers[LONG_DOUBLE], extrcGvar(var, long double));
            return;

        case BOOL:
            printf(GenericsType_specifiers[BOOL], extrcGvar(var, bool));
            return;

        case UNSIGNED_CHAR:
            printf(GenericsType_specifiers[UNSIGNED_CHAR], extrcGvar(var, unsigned char));
            return;
        case UNSIGNED_SHORT:
            printf(GenericsType_specifiers[UNSIGNED_SHORT], extrcGvar(var, unsigned short));
            return;
        case UNSIGNED_INT:
            printf(GenericsType_specifiers[UNSIGNED_INT], extrcGvar(var, unsigned int));
            return;
        case UNSIGNED_LONG:
            printf(GenericsType_specifiers[UNSIGNED_LONG], extrcGvar(var, unsigned long));
            return;
        case UNSIGNED_LONG_LONG:
            printf(GenericsType_specifiers[UNSIGNED_LONG_LONG], extrcGvar(var, unsigned long long));
            return;
    }
}