#include "vector.h"

/**
 * Creates a new vector with the specified element size and initial capacity.
 *
 * @param element_size The size of each element in the vector.
 * @param initial_capacity The initial capacity of the vector.
 * @return A pointer to the newly created vector, or NULL if memory allocation fails.
 */
Vector *vector_create(size_t element_size, size_t initial_capacity) {
    if (initial_capacity == 0)
        initial_capacity = DEFAULT_VECTOR_CAPACITY;
    Vector *v = (Vector *)calloc(1, sizeof(Vector));
    if (v == NULL) {
        return NULL;
    }

    v->data = calloc(initial_capacity, element_size);
    if (v->data == NULL) {
        free(v);
        return NULL;
    }
    v->size = 0;
    v->capacity = initial_capacity;
    v->element_size = element_size;
    return v;
}

/**
 * Frees the memory allocated for the vector.
 *
 * @param v A pointer to the vector to be freed.
 */
void vector_free(Vector *v) {
    free(v->data);
    v->data = NULL;
    free(v);
}

/**
 * Resizes the vector to the specified new capacity.
 *
 * @param v A pointer to the vector to be resized.
 * @param new_capacity The new capacity of the vector.
 * @return true if the resize operation is successful, false otherwise.
 */
bool vector_resize(Vector *v, size_t new_capacity) {
    if(new_capacity==0) return false;
    void *new_data = realloc(v->data, new_capacity * v->element_size);
    if (new_data == NULL) {
        return false;
    }
    v->data = new_data;
    v->capacity = new_capacity;
    return true;
}

/**
 * Shrinks the vector's capacity to match its size.
 *
 * @param v A pointer to the vector to be shrunk.
 * @return true if the shrink operation is successful, false otherwise.
 */
bool vector_shrink(Vector *v) {
    return vector_resize(v, v->size == 0 ? 1 : v->size);
}

/**
 * Adds an element to the end of the vector.
 *
 * @param v A pointer to the vector.
 * @param element A pointer to the element to be added.
 * @return true if the push operation is successful, false otherwise.
 */
bool vector_push_back(Vector *v, const void *element) {
    if (v->size >= v->capacity) {
        // If the vector has reached its capacity, resize it to 1 if empty, or double its size if not empty
        if (!vector_resize(v, v->capacity == 0 ? 1 : v->capacity * 2)) {
            return false;
        }
    }
    memcpy((char *)v->data + (v->size * v->element_size), element,
           v->element_size);
    v->size++;
    return true;
}

/**
 * Removes the last element from the vector.
 *
 * @param v A pointer to the vector.
 */
void vector_pop_back(Vector *v) {
    if (v->size > 0) {
        v->size--;
    }
}

/**
 * Retrieves the element at the specified index in the vector.
 *
 * @param v A pointer to the vector.
 * @param index The index of the element to retrieve.
 * @return A pointer to the element at the specified index, or NULL if the index is out of bounds.
 */
void *vector_get(Vector *v, size_t index) {
    if (index >= v->size) {
        return NULL;
    }
    return (char *)v->data + (index * v->element_size);
}

/**
 * Clears the vector by setting its size to 0.
 *
 * @param v The vector to be cleared.
 */
void vector_clear(Vector* v){
    v->size = 0;
}
