#include <stdio.h>
#include "typedef.h"

#ifndef STACK_H
#define STACK_H

DECLS_BEGIN

struct _Stack;
typedef struct _Stack Stack;

Stack* stack_create(DataDestroyFunc data_destroy, void* ctx);

Ret      stack_top(Stack* thiz, void** data);
Ret      stack_push(Stack* thiz, void* data);
Ret      stack_pop(Stack* thiz);
size_t   stack_length(Stack* thiz);
Ret      stack_foreach(Stack* thiz, DataVisitFunc visit, void* ctx);
Ret      stack_clear(Stack* thiz);

void stack_destroy(Stack* thiz);

DECLS_END

#endif/*STACK_H*/

