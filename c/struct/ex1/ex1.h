/**************--- reviwed by Naor ---*****************************************/
#ifndef __EX1_H__
#define __EX1_H__


/**************--- ENUM & STRUCTS ---******************************************/

typedef enum{
SUCCESS,
FAIL
} status_t;

struct element;
typedef struct element element_t;

typedef status_t (*print_func_t)(element_t const *element);
typedef status_t (*add_func_t)(element_t *element, int num);
typedef status_t (*free_func_t)(element_t const *element);

typedef struct functions
{
    print_func_t print_func;
    add_func_t add_func;
    free_func_t free_func;
} functions_t;

struct element
{
    void *value;
    const functions_t *funcs;
    
} element;

/**************--- INITIALIZATION ---******************************************/

status_t InitInt(element_t *new, int const num);
status_t InitDouble(element_t *new, double const num);
status_t InitStr(element_t *new, char* str);

/****************--- FUNCTIONS ---*********************************************/
status_t PrintAll (element_t *arr, int const size);
status_t AddAll (element_t *arr, int const size, int const add);
status_t FreeAll (element_t *arr, int const size);

#endif /* __EX1_H__ */


