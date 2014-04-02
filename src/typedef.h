#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

#ifndef TYPEDEF_H
#define TYPEDEF_H

typedef enum _Ret
{
	RET_OK,
	RET_OOM,
	RET_STOP,
	RET_INVALID_PARAMS,
	RET_FAIL
}Ret;

typedef void     (*DataDestroyFunc)(void* ctx, void* data);
typedef int      (*DataCompareFunc)(void* ctx, void* data);
typedef Ret      (*DataVisitFunc)(void* ctx, void* data);
typedef int      (*DataHashFunc)(void* data);

#ifdef __cplusplus
#define DECLS_BEGIN extern "C" {
#define DECLS_END   }
#else
#define DECLS_BEGIN
#define DECLS_END
#endif/*__cplusplus*/


#define SAFE_FREE(p) if(p != NULL) {free(p); p = NULL;}

typedef Ret (*SortFunc)(void** array, size_t nr, DataCompareFunc cmp);

#endif/*TYPEDEF_H*/

