#include <EASTL/internal/config.h>
#include <EASTL/allocator_malloc.h>
#include "CoreMinimal.h"

void* eastl_malloc(size_t size, int, const char*, int, unsigned, const char*, int)
{
    return FMemory::Malloc(size);
}

void eastl_free(void* p, int, const char*, int, unsigned, const char*, int)
{
    FMemory::Free(p);
}
