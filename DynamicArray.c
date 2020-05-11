#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define DEFAULT_CAPACITY 10

typedef struct _dA{
    void* Array;
	size_t typeSize;
	size_t arrSize;
	size_t capacity;
}dA;

dA* Init(size_t typeSize, size_t capacity){

    dA* DynamicArray;

    DynamicArray = (dA *)malloc(sizeof(dA));

    if(DynamicArray == NULL)
        return NULL;

    DynamicArray->Array = (dA *)malloc(typeSize * capacity);

    if(DynamicArray->Array == NULL){
        
        free(DynamicArray);
        return NULL;

    }
        

    DynamicArray->typeSize = typeSize;
    DynamicArray->capacity = capacity;
    DynamicArray->arrSize = 0;

    return DynamicArray;  
}

dA* FastInit(size_t typeSize){

    return Init(typeSize, DEFAULT_CAPACITY);

}

dA* Destroy(dA* DynamicArray){

    free(DynamicArray->Array);
    free(DynamicArray);

}

int Add(dA* DynamicArray, const void* value){

    if(DynamicArray->Array == NULL)
        return 0;

    if(DynamicArray->arrSize == DynamicArray->capacity){

        DynamicArray->capacity *= 2;
        DynamicArray->Array = realloc(DynamicArray->Array, DynamicArray->capacity * DynamicArray->typeSize);

    }

    memcpy((char *)DynamicArray->Array + DynamicArray->typeSize * DynamicArray->arrSize, value, DynamicArray->typeSize);

    ++DynamicArray->arrSize;
    
    return 1;
}

int AddInsert(dA* DynamicArray, size_t Index, const void* value){

    if(Index > DynamicArray->arrSize)
        return 0;
    
    char* src = (char *)DynamicArray->Array + DynamicArray->typeSize * Index; 
    char* dest = (char *)DynamicArray->Array + DynamicArray->typeSize * (Index + 1);

    if(DynamicArray->arrSize == DynamicArray->capacity){

        DynamicArray->capacity *= 2;
        DynamicArray->Array = realloc(DynamicArray->Array, DynamicArray->typeSize * DynamicArray->capacity);

    }
    
    memmove(dest, src, (DynamicArray->arrSize - Index) * DynamicArray->typeSize);
    memcpy(src, value, DynamicArray->typeSize);

    ++DynamicArray->arrSize;

    return 1;
}

int RemoveAt(dA* DynamicArray, size_t Index){

    if(Index >= DynamicArray->arrSize)
        return 0;
    
    char* src = (char *)DynamicArray->Array + DynamicArray->typeSize * (Index + 1);
    char* dest =  (char *)DynamicArray->Array + DynamicArray->typeSize * Index;

    memmove(dest, src, (DynamicArray->arrSize - Index) * DynamicArray->typeSize);

    --DynamicArray->arrSize;

    if(DynamicArray->capacity >= DynamicArray->arrSize * 2){

        DynamicArray->capacity /= 2;
        DynamicArray->Array = realloc(DynamicArray->Array, DynamicArray->capacity * DynamicArray->typeSize);

    }

    return 1;

}

void Clear(dA* DynamicArray){

    DynamicArray->arrSize = 0;

}

void GetItem(dA* DynamicArray, size_t Index, void* value){

    char* src = (char *)DynamicArray->Array + DynamicArray->typeSize * Index;
    memcpy(value, src, DynamicArray->typeSize);

}

void SetItem(dA* DynamicArray, size_t Index, const void* value){

    char* dest = (char *)DynamicArray->Array + DynamicArray->typeSize * Index;
    memcpy(dest, value, DynamicArray->typeSize);

}

void* GetArray(dA* DynamicArray){

    return DynamicArray->Array;

}

size_t GetSize(dA* DynamicArray){

    return DynamicArray->arrSize;

}

size_t GetCapacity(dA* DynamicArray){

    return DynamicArray->capacity;

}

int comp(const void* p1, const void *p2){
    
    return (*(int *)p1 - *(int *)p2);

}


void SortArray(dA* DynamicArray){

    qsort(DynamicArray->Array, GetSize(DynamicArray), DynamicArray->typeSize, comp);

}

/*

int main()
{
    dA* dynamicArray = FastInit(sizeof(int));
    printf("%p", dynamicArray);
    
    for (size_t i = 50; i > 0; i--)
    {
        if(i > 35)
            Add(dynamicArray, &i);
        else
            RemoveAt(dynamicArray, 1);
        printf("%d\n", dynamicArray->capacity);
    }
    
}

*/
