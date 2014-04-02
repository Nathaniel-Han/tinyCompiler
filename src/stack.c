#include "stack.h"
#include "dlist.h"

struct _Stack
{
	DList* dlist;
};

Stack* stack_create(DataDestroyFunc data_destroy, void* ctx)
{
	Stack* thiz = (Stack*)malloc(sizeof(Stack));

	if(thiz != NULL)
	{
		if((thiz->dlist = dlist_create(data_destroy, ctx)) == NULL)
		{
			free(thiz);
			thiz = NULL;
		}
	}

	return thiz;
}

Ret      stack_top(Stack* thiz, void** data)
{
	assert(thiz != NULL && data != NULL);

	return dlist_get_by_index(thiz->dlist, 0, data);
}

Ret      stack_push(Stack* thiz, void* data)
{
	assert(thiz != NULL);

	return dlist_prepend(thiz->dlist, data);
}

Ret      stack_pop(Stack* thiz)
{
	assert(thiz != NULL);

	return dlist_delete(thiz->dlist, 0);
}

size_t   stack_length(Stack* thiz)
{
	assert(thiz != NULL);

	return dlist_length(thiz->dlist);	
}

Ret      stack_foreach(Stack* thiz, DataVisitFunc visit, void* ctx)
{
	assert(thiz != NULL && visit != NULL);

	return dlist_foreach(thiz->dlist, visit, ctx);
}

Ret      stack_clear(Stack* thiz)
{
	assert(thiz != NULL);

	while(stack_length(thiz)!=0)
		stack_pop(thiz);

	return RET_OK;

}

void stack_destroy(Stack* thiz)
{
	if(thiz != NULL)
	{
		dlist_destroy(thiz->dlist);
		thiz->dlist = NULL;

		free(thiz);
	}

	return;
}








